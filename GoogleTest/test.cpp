#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../DeviceDriver/DeviceDriver.cpp"
#include "../DeviceDriver/App.cpp"

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
		.WillOnce(Return('A'))
		.WillOnce(Return('A'))
		.WillRepeatedly(Return('B'));

	EXPECT_THROW(driver.read(0xdeadbeaf), ReadFailException);
}

TEST(DeviceDrvierTest, WriteSucceedTest) {
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);

	EXPECT_CALL(flashmemory, read)
		.WillRepeatedly(Return(0xFF));

	EXPECT_CALL(flashmemory, write)
		.Times(1);

	EXPECT_NO_THROW(driver.write(0xdeadbeaf, 'A'));
}

TEST(DeviceDrvierTest, WriteFailTest) {
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);

	EXPECT_CALL(flashmemory, read)
		.WillRepeatedly(Return('A'));

	EXPECT_THROW(driver.write(0xdeadbeaf, 'A'), WriteFailException);
}

TEST(DeviceDrvierTest, AppReadPassTest)
{
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);
	App app(&driver);

	EXPECT_CALL(flashmemory, read)
		.WillRepeatedly(Return(1));

	EXPECT_NO_THROW(app.ReadAndPrint(0x1000, 0x1004));
}

TEST(DeviceDrvierTest, AppReadFailTest)
{
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);
	App app(&driver);

	EXPECT_CALL(flashmemory, read)
		.WillOnce(Return(3))
		.WillOnce(Return(3))
		.WillOnce(Return(3))
		.WillRepeatedly(Return(1));

	EXPECT_THROW(app.ReadAndPrint(0x1000, 0x1004), ReadFailException);
}

TEST(DeviceDrvierTest, AppWritePassTest)
{
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);
	App app(&driver);

	EXPECT_CALL(flashmemory, read)
		.WillRepeatedly(Return(0xFF));

	EXPECT_NO_THROW(app.WriteAll(5));
}

TEST(DeviceDrvierTest, AppWriteFailTest)
{
	MockFlashMemory flashmemory;
	DeviceDriver driver(&flashmemory);
	App app(&driver);

	EXPECT_CALL(flashmemory, read)
		.WillRepeatedly(Return(0));

	EXPECT_THROW(app.WriteAll(5), WriteFailException);
}