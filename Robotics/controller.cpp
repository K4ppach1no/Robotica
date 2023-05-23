#include "pch.h"
#include "controller.h"

void controller::remote_to_arm(int value)
{
}

void controller::weight_to_text(float weight)
{
}

void controller::led_aan(frequency frequence)
{
}

void controller::detect_object()
{

}

int main()
{
    opencv opencv_;
    opencv_.detect_object();

    waitKey(0);
    cout << "Hello World!\n";
}