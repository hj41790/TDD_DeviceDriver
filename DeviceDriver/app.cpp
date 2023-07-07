#include <iostream>

#include "DeviceDriver.h"

using namespace std;

class App
{
public:
	void ReadAndPrint(long startAddr, long endAddr)
	{
		for (long addr = startAddr; addr < endAddr; ++addr)
		{
			cout << driver->read(addr);
		}
		cout << endl;
	}

	void WriteAll(int value)
	{
		for (long addr = 0; addr < 4; ++addr)
		{
			driver->write(addr, value);
		}
	}

	explicit App(DeviceDriver* driver_) : driver(driver_) {}

protected:
	DeviceDriver *driver;
};