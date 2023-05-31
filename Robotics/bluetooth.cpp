#include "bluetooth.h"

void bluetooth::connect(ble::BluetoothAddress mac_address)
{
	intitialize();

	//get the bluetooth adapter
	ble::Adapter adapter;
	select_adapter(adapter);

	//scan for available devices
	std::vector<ble::Peripheral> peripherals;
	scan(adapter, peripherals);

	for (ble::Peripheral peripheral : peripherals) {
		if (peripheral.address() == mac_address) {
			std::cout << "found the device!\n";
			break;
		}
	}

}


void bluetooth::intitialize()
{
	//code is based on this example from the library repository:
	//https://github.com/OpenBluetoothToolbox/SimpleBLE/blob/main/examples/simpleble/cpp/connect/connect.cpp

	//check if bluetooth is even enabled
	if (!SimpleBLE::Adapter::bluetooth_enabled()) {
		std::cout << "bluetooth is disabled!\n";
		return;
	}
	
	
}

void bluetooth::select_adapter(SimpleBLE::Adapter& adapter)
{
	auto adapters = SimpleBLE::Adapter::get_adapters();

	if (adapters.empty()) {
		std::cout << "no adapter was found\n";
		return;
	}

	if (adapters.size() == 1) {
		std::cout << "Found one adapter: " << adapters.front().address() << ". Using this one.\n";
		adapter = adapters.front();
	}

	if (adapters.size() > 1) {
		std::cout << "found multiple bluetooth adapters.\nSelecting the first one:"
			<< adapters.front().address() << "\n";
		adapter = adapters.front();
	}
}

void bluetooth::scan(ble::Adapter& adapter, std::vector<SimpleBLE::Peripheral>& peripherals)
{
	//when an adapter is found, add it to the list
	adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral peripheral) { 
		peripherals.push_back(peripheral);


		std::cout << "device found: [adress: "
			<< peripheral.address()
			<< " identifier: "
			<< peripheral.identifier()
			<< " rssi: "
			<< peripheral.rssi()
			<< "]\n";
		});


	adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });
	adapter.set_callback_on_scan_stop([]() { std::cout << "Scan stopped." << std::endl; });
	
	adapter.scan_for(SCANTIME);
}
