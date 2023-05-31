#pragma once
#include <string>
#include <iostream>
#include <optional>
#include <simpleble/SimpleBLE.h>

namespace ble = SimpleBLE;

class bluetooth
{
public:
	void connect(ble::BluetoothAddress mac_address);

	//time to scan for in ms
	static const int SCANTIME = 1000 * 10;

private:
	void intitialize();
	void select_adapter(ble::Adapter& adapter);
	void scan(ble::Adapter& adapter,  std::vector<ble::Peripheral>& peripherals);
};

