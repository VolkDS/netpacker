#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>

#include <netpacker/netpacker.h>

using namespace std;

void reader(const uint8_t* buf, size_t len)
{
    auto end = buf + len;

    auto v1 = netpacker::get<uint32_t>(buf, end, 1);
    auto v2 = netpacker::get<int32_t>(buf, end, 3);
    auto v3 = netpacker::get<int32_t>(buf, end);

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
}

int main(int /*argc*/, char** /*argv*/)
{
    std::vector<uint8_t> data = {0x01, 0x00, 0x00, 0x01,
                                 0x00, 0x00, 0x00, 0x02};

    reader(data.data(), data.size());
    return 0;
}

