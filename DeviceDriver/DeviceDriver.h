#pragma once
#include <exception>

#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
	DeviceDriver(FlashMemoryDevice *hardware);
	int read(long address);
	void write(long address, int data);

protected:
	FlashMemoryDevice *m_hardware;
};

class WriteFailException : public std::exception
{
public:
	explicit WriteFailException(char const* _Message)
		: exception(_Message)
	{
	}
};