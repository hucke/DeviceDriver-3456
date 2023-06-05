#include "DeviceDriver.h"
#include <stdexcept>

class ReadFailException : public std::exception
{
public:
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly

    int result = 0;
    for (int i = 0; i < 5; ++i)
    {
        if (i == 0) {
            result = (int)(m_hardware->read(address));
            continue;
        }

        int value = (int)(m_hardware->read(address));
        if (result != value)
            throw ReadFailException();
    }

    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}
