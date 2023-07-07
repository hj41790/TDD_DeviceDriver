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

TEST(DeviceDrvierTest, WriteSucceedTest) {
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);

	EXPECT_CALL(flashmemory, read)
		.Times(1)
		.WillRepeatedly(Return('A'));

	EXPECT_CALL(flashmemory, write)
		.Times(1);

	EXPECT_NO_THROW(driver.write(0xdeadbeaf, 'A'));
}

TEST(DeviceDrvierTest, WriteFailTest) {
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);

	EXPECT_CALL(flashmemory, read)
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	EXPECT_THROW(driver.write(0xdeadbeaf, 'A'), WriteFailException);

}