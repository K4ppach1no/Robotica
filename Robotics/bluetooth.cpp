#include "bluetooth.h"

void bluetooth::connect()
{
	

	const char* destination_name = "org.bluez";
	const char* object_path = "/org/bluez/hci0";
	const char* interface_name = "org.bluez.Adapter1";

	auto sdbus_proxy = sdbus::createProxy(destination_name, object_path);
	sdbus_proxy->uponSignal("DeviceFound").onInterface(interface_name).call(on_device_found);
	sdbus_proxy->uponSignal("PropertyChanged").onInterface(interface_name).call(on_property_changed);
	sdbus_proxy->finishRegistration();

	
	const char* method_name = "StartDiscovery";
	auto method = sdbus_proxy->createMethodCall(interface_name, method_name);
	sdbus_proxy->callMethod(method);

	std::this_thread::sleep_for(std::chrono::seconds(5));
}


void bluetooth::on_device_found() {
	std::cout << "Device found!\n";
}

void bluetooth::on_property_changed() {
	std::cout << "Property changed!\n";
}