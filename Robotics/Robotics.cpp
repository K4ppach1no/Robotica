#include <iostream>
#include <string>
#include <simpleble/SimpleBLE.h>
#include <optional>
#include "bluetooth.h"


int main()
{
    std::cout << "Started!\n";

    bluetooth bluetooth;
    bluetooth.connect("a4:50:46:55:2f:db");



}
