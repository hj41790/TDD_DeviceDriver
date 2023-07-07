#pragma once
#include "FlashMemoryDevice.h"

#include <exception>

class DeviceDriver
{
public:
	DeviceDriver(FlashMemoryDevice *hardware);
	int read(long address);
	void write(long address, int data);

protected:
	FlashMemoryDevice *m_hardware;
};

class ReadFailException : public std::exception
{
public:
	explicit ReadFailException(char const* _Message)
		: exception(_Message)
	{
	}
};