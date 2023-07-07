#include "DeviceDriver.h"

#include <vector>
#include <windows.h>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice *hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
	vector<unsigned char> res;

	for (int i = 0; i < 5; i++)
	{
		res.push_back(m_hardware->read(address));
		Sleep(200);
	}

	unsigned char value = res[0];
	for(unsigned char item : res)
	{
		if (value != item)
			throw ReadFailException("Read Fail");
	}

	return (int)value;
}

void DeviceDriver::write(long address, int data)
{
	// TODO: implement this method
	m_hardware->write(address, (unsigned char)data);
}