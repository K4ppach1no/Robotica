#include "../Robotics/opencv.cpp" //cpp is needed otherwise it will give a linker error
#include "../Robotics/image_data.cpp" //cpp is needed otherwise it will give a linker error

#include "gtest/gtest.h"
#include <pugixml.hpp>
#include <iostream>
#include <filesystem>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>

//TODO: probably change this
#define OFFSET 40
#define RESIZE_SIZE 500
const std::string directory_path = "\\Images\\"; // TODO: make generic
const std::filesystem::path current_path = std::filesystem::current_path();
const std::string full_path = current_path.string() + directory_path;


/** 
 * \brief get the xml data from the xml file
 * \param filename string of the filename
 * \param center this will be filled with the center of the object
 * \param xmin this will be filled with the xmin of the object
 * \param ymin this will be filled with the ymin of the object
 * \param xmax this will be filled with the xmax of the object
 * \param ymax this will be filled with the ymax of the object
 * \return true if the xml has been loaded successfully, false otherwise
 */
bool get_xml_data(const std::string& filename, Point2f& center, int& xmin, int& ymin, int& xmax, int& ymax)
{
    pugi::xml_document doc;

    //check if the xml has been loaded successfully
    if (const pugi::xml_parse_result result = doc.load_file((full_path + filename + ".xml").c_str()); !result)
    {
        std::cout << "xml path is wrong" << std::endl;
        return false;
    }

    //initialization
    const pugi::xml_node root = doc.child("annotation");
    const pugi::xml_node object = root.child("object");

    //get the bounding box coordinates
    const pugi::xml_node bndbox = object.child("bndbox");
    xmin = std::stoi(bndbox.child_value("xmin"));
    ymin = std::stoi(bndbox.child_value("ymin"));
    xmax = std::stoi(bndbox.child_value("xmax"));
    ymax = std::stoi(bndbox.child_value("ymax"));

    // Calculate the center of the bounding box
    center = Point2f((xmin + xmax) / 2.0f, (ymin + ymax) / 2.0f);
}

/**
 * \brief TODO: perhaps remove this, currently it's for showing the result
 */
void print_data(Mat& img, const Point2f* normalized_center = nullptr)
{
    //show result
    resize(img, img, Size(500, 500), 0, 0, INTER_LINEAR);
    if (normalized_center != nullptr) circle(img, *normalized_center, OFFSET, Scalar(0, 0, 255), -1);
    imshow("result", img);
    waitKey(0);
}

TEST(OpenCV, ObjectDetection)
{
    //initialize variables
    int xmin, ymin, xmax, ymax;
    Point2f center;
    opencv open = opencv();
    image_data data;

    //loop through all files in directory
    for (const auto& entry : std::filesystem::directory_iterator(full_path))
    {
        //check if file is xml
        if (entry.path().extension() == ".xml")
        {
            auto img = imread(full_path + entry.path().filename().stem().string() + ".jpg", IMREAD_COLOR);
            if (!open.detect_object(img, data))
            {
                print_data(img);
                FAIL() << "there should be an object but isn't";
            }

            //get xml data
            if (!get_xml_data(entry.path().filename().stem().string(), center, xmin, ymin, xmax, ymax))
                return;

            // normalize points to set size
            const Point2f normalized_center(center.x / img.size().width * RESIZE_SIZE,
                                            center.y / img.size().height * RESIZE_SIZE);

            //TODO: remove this, only used for showing the result
            if (!(data.center.x >= normalized_center.x - OFFSET
                && data.center.x <= normalized_center.x + OFFSET))
            {
                print_data(img, &normalized_center);
                FAIL() << "center is not within acceptable range";
            }

            //check if center data is correct
            EXPECT_TRUE(data.center.x >= normalized_center.x - OFFSET
                && data.center.x <= normalized_center.x + OFFSET);

            //TODO: remove this, only used for showing the result
            if (!(data.center.y >= normalized_center.y - OFFSET
                && data.center.y <= normalized_center.y + OFFSET))
            {
                print_data(img, &normalized_center);
                FAIL() << "center is not within acceptable range";
            }

            //check if center data is correct
            EXPECT_TRUE(data.center.y >= normalized_center.y - OFFSET
                && data.center.y <= normalized_center.y + OFFSET);

            //calculate area of result and xml
            const float result_area = data.rotatedarea;

            //TODO: this can be done better, for now it's just a quick fix
            //get normalized area
            const float xml_area = ((float)xmax / img.size().width * RESIZE_SIZE - (float)xmin / img.size().width *
                RESIZE_SIZE) * ((float)ymax / img.size().height * RESIZE_SIZE - (float)ymin / img.size().height *
                RESIZE_SIZE);

            //TODO: remove this, only used for showing the result
            if (!(result_area / xml_area > 0.8 && result_area / xml_area < 1.2))
            {
                print_data(img, &normalized_center);
                FAIL() << "area is not within acceptable range: " << result_area / xml_area;
            }

            //check if area is within acceptable range
            EXPECT_TRUE(result_area / xml_area > 0.8 && result_area / xml_area < 1.2);
        }
    }
}
