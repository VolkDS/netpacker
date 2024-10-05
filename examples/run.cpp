#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

#include <netpacker/netpacker.h>

using namespace std;

/*
 * 
 */

void builder(uint8_t* buf, size_t /*len*/)
{
    buf = netpacker::put(buf, uint8_t{0x31}); //v1
    buf = netpacker::skipbytes(buf, 3);
    buf = netpacker::put(buf, uint32_t{0x303132}, 3); //v2
    buf = netpacker::skipbytes(buf, 3);
    buf = netpacker::put(buf, uint16_t{0x3033}); //v3
    buf = netpacker::put(buf, uint32_t{0x00bb}); //v4
    buf = netpacker::skipbytes(buf, 2);
    buf = netpacker::put(buf, uint32_t{0x7fffffff}); //v5
    buf = netpacker::put(buf, uint64_t{0x20}); //v6

/*
31 00 00 00 
30 31 32 00 
00 00 30 33 
00 00 00 bb 
00 00 7f ff 
ff ff 00 00 
00 00 00 00 
00 20 00 00 
*/
}

void reader(const uint8_t* buf, size_t len)
{
    auto end = buf + len;

    auto v1 = netpacker::get<uint8_t>(buf, end);
    buf = netpacker::skipbytes(buf, 3);
    auto v2 = netpacker::get<std::string>(buf, end, 4);
    buf = netpacker::skipbytes(buf, 2);
    auto v3 = netpacker::get<uint16_t>(buf, end, 2);
    auto v4 = netpacker::get<uint32_t>(buf, end);
    buf = netpacker::skipbytes(buf, 2);
    auto v5 = netpacker::get<int32_t>(buf, end);
    auto v6 = netpacker::get<int64_t>(buf, end);

/*
    auto pos = buf - start;
    if ((len - pos) < sizeof(uint64_t))
    {
        std::cout << "too short buf for read 64 bit" << std::endl;
    }
    else
    {
        uint64_t v6 = netpacker::get<uint64_t>(buf);
    }
*/
    std::cout << "v1:" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(v1) << std::endl;
    //for (const auto& v : v2) {
        std::cout << "v2:" << v2 << "("<< v2.size() <<")"<<std::endl;
    //}
    std::cout << "v3:" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(v3) << std::endl;
    std::cout << "v4:" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(v4) << std::endl;
    std::cout << "v5:" << std::setw(2) << std::setfill('0') << std::dec << static_cast<int>(v5) << std::endl;
    std::cout << "v6:" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int64_t>(v6) << std::endl;
}

int main(int /*argc*/, char** /*argv*/)
{
    std::vector<uint8_t> data(32);
    for (unsigned int k = 0; k < 1; k++) {
        builder(data.data(), data.size());
        
        for (unsigned int i = 0; i < data.size(); i++) {
            if ((i % 4 == 0) && (i != 0)) {
                std::cout << std::endl;
            }
            std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(data[i]) << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;

        reader(data.data(), data.size());

        data.clear();
        data.resize(8);
    }

    //std::byte woo{0xff};
    /*
    for (unsigned int i = 0; i < data.size(); i++) {
        if ((i % 4 == 0) && (i != 0)) {
            std::cout << std::endl;
        }
        std::cout << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(data[i]) << " ";
    }
    */  
    return 0;
}

