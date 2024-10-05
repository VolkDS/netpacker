#ifndef NETPACKER_SKIP_H
#define NETPACKER_SKIP_H

#include <iterator>

#include <netpacker/error.h>

namespace netpacker {

template <typename OutputIt>
inline OutputIt skipbytes(OutputIt first, OutputIt last, typename std::iterator_traits<OutputIt>::difference_type bytes)
{
    if (std::distance(first, last) < bytes) {
        throw EndOfBuffer();
    }
    return first + bytes;
}

} // namespace netpacker

#endif /* NETPACKER_SKIP_H */
