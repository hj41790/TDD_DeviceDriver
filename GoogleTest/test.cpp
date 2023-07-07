#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;

class MockFlashMemory : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDrvierTest, ReadSucceedTest) {
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);

	EXPECT_CALL(flashmemory, read)
		.Times(5)
		.WillRepeatedly(Return('A'));

	EXPECT_EQ('A', driver.read(0xdeadbeaf));
}

TEST(DeviceDrvierTest, ReadFailTest) {
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);

	EXPECT_CALL(flashmemory, read)
		.Times(5)
		.WillOnce(Return('A'))
		.WillOnce(Return('A'))
		.WillRepeatedly(Return('B'));

	EXPECT_THROW(driver.read(0xdeadbeaf), ReadFailException);
}