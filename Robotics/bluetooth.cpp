#include "bluetooth.h"

void bluetooth::connect()
{
	const char* destination_name = "org.bluez.Adapter1";
	const char* object_path = "org/bluez/hci0";
	auto sdbus_proxy = sdbus::createProxy(destination_name, object_path);
	sdbus_proxy->finishRegistration();

	
}
