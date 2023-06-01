#include "bluetooth.h"

void bluetooth::connect()
{
	

	const char* destination_name = "org.bluez";
	const char* object_path = "/org/bluez/hci0";
	const char* interface_name = "org.bluez.Adapter1";
	auto callback_function = onsignal_callback;

	auto sdbus_proxy = sdbus::createProxy(destination_name, object_path);
	sdbus_proxy->uponSignal("DeviceFound").onInterface(interface_name).call(callback_function);
	sdbus_proxy->finishRegistration();

	
	const char* method_name = "StartDiscovery";
	auto method = sdbus_proxy->createMethodCall(interface_name, method_name);
	sdbus_proxy->callMethod(method);
}


void onsignal_callback() {
	std::cout << "Device found!\n";
}