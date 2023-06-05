#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;

class FlasMemoryDeviceMock : public FlashMemoryDevice
{
public:
    // unsigned char read(long address) = 0;
    // void write(long address, unsigned char data) = 0;
    MOCK_METHOD(unsigned char, read, (long), (override));
    MOCK_METHOD(void, write, (long, unsigned char), (override));
};

// 대역
// 스터빙 or Behavior 검증
// 

TEST(DeviceDriver, ReadNormal)
{
    FlasMemoryDeviceMock fmdMock;
    EXPECT_CALL(fmdMock, read)
        .Times(5)
        .WillRepeatedly(Return(5));


    DeviceDriver dd(&fmdMock);
    EXPECT_THAT(dd.read(0), Eq(5));
}

TEST(DeviceDriver, ReadFail)
{
    FlasMemoryDeviceMock fmdMock;
    EXPECT_CALL(fmdMock, read(0x0A))
        .WillOnce(Return(1))
        .WillRepeatedly(Return(5));


    DeviceDriver dd(&fmdMock);
    EXPECT_THROW(dd.read(0x0A), ReadFailException);
}
