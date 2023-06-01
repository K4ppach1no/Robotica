#include "bluetooth.h"

void bluetooth::connect()
{
	
	std::cout << "starting to connect\n";

	const char* destination_name = "org.bluez";
	const char* object_path = "/org/bluez/hci0";
	const char* interface_name = "org.bluez.Adapter1";

	auto sdbus_proxy = sdbus::createProxy(destination_name, object_path);
	sdbus_proxy->uponSignal("DeviceFound").onInterface(interface_name).call(on_device_found);
	sdbus_proxy->uponSignal("PropertyChanged").onInterface(interface_name).call(on_property_changed);
	sdbus_proxy->finishRegistration();

	std::cout << "start discovery\n";

	auto reply = sdbus_proxy->callMethod(sdbus_proxy->createMethodCall(interface_name, "StartDiscovery"));
	
	

	std::this_thread::sleep_for(std::chrono::seconds(5));
	if (!reply.isValid()) {
		std::cout << "reply is invalid\n";
	}
	if (reply.isEmpty()) {
		std::cout << "reply is empty\n";
	}


	auto reply = sdbus_proxy->callMethod(sdbus_proxy->createMethodCall(interface_name, "StopDiscovery"));
}


void bluetooth::on_device_found() {
	std::cout << "Device found!\n";
}

void bluetooth::on_property_changed() {
	std::cout << "Property changed!\n";
}