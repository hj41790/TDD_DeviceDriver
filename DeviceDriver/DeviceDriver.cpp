#include "DeviceDriver.h"

#include <windows.h>

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
	unsigned char value = m_hardware->read(address);

	for (int i = 0; i < 4; i++)
	{
		if (value != m_hardware->read(address))
			throw ReadFailException("Read Fail");
		Sleep(200);
	}

	return (int)value;
}

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}