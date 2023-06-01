#include "bluetooth.h"

void bluetooth::connect()
{


	const char* destination_name = "org.bluez";
	const char* object_path = "/org/bluez/hci0";
	auto sdbus_proxy = sdbus::createProxy(destination_name, object_path);
	sdbus_proxy->finishRegistration();


	auto method = sdbus_proxy->createMethodCall("org.bluez.Adapter1", "StartDiscovery");
	sdbus_proxy->callMethod(method);
}
