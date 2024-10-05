#include <vector>

#include <netpacker/netpacker.h>
#include <CppUTest/TestHarness.h>

TEST_GROUP(get_tests)
{
    std::vector<uint8_t> blob;

    void setup()
    {
        blob = {0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02};
    }

    void teardown()
    {
        blob.clear();
    }
};

TEST(get_tests, Get)
{
    const uint8_t* data = blob.data();
    UNSIGNED_LONGS_EQUAL(2, netpacker::get<uint8_t>(data));
}
