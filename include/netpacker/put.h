#ifndef NETPACKER_PUT_H
#define NETPACKER_PUT_H

#include <cstring>
#include <iterator>
#include <type_traits>

#include <netinet/in.h>

#include <netpacker/byteorder.h>
#include <netpacker/error.h>

namespace netpacker {

template <typename OutputIt,
          typename T,
          typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
OutputIt put(OutputIt possition, OutputIt last, const T& value)
{
    // TODO: fix for width floating-point types (since C++23)
    // float16_t, float32_t, float64_t, float128_t, bfloat16_t
    using unsigned_t = typename std::conditional<
            std::is_integral<T>::value,
            std::make_unsigned<T>,
            std::conditional<
                std::is_same<T, float>::value,
                std::common_type<uint32_t>::type,
                std::common_type<uint64_t>::type
            >>::type::type;
    unsigned_t nval = 0;

    if (std::distance(possition, last) < static_cast<std::ptrdiff_t>(sizeof(T))) {
        throw BufferOverflow();
    }

    if constexpr (std::is_same_v<T, decltype(nval)>) {
        nval = host_to_network(value);
    }
    else {
        nval = host_to_network(reinterpret_cast<const unsigned_t&>(value));
    }

    const auto* begin = reinterpret_cast<const uint8_t*>(&nval);
    const auto* end = begin + sizeof(T);
    std::copy(begin, end, possition);
    return possition + sizeof(T);
}

template <typename OutputIt,
          typename T,
          typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
OutputIt put(OutputIt possition, OutputIt last, const T& value, size_t len)
{
    if (len >= sizeof(T)) {
        return put(possition, last, value);
    }

    // TODO: fix for width floating-point types (since C++23)
    // float16_t, float32_t, float64_t, float128_t, bfloat16_t
    using unsigned_t = typename std::conditional<
            std::is_integral<T>::value,
            std::make_unsigned<T>,
            std::conditional<
                std::is_same<T, float>::value,
                std::common_type<uint32_t>::type,
                std::common_type<uint64_t>::type
            >>::type::type;
    unsigned_t nval = 0;

    if (std::distance(possition, last) < static_cast<std::ptrdiff_t>(len)) {
        throw BufferOverflow();
    }

    if constexpr (std::is_same_v<T, decltype(nval)>) {
        nval = host_to_network(value);
    }
    else {
        nval = host_to_network(reinterpret_cast<const unsigned_t&>(value));
    }

    const auto* begin = reinterpret_cast<const uint8_t*>(&nval) + sizeof(nval) - len;
    const auto* end = begin + len;
    std::copy(begin, end, possition);
    return possition + static_cast<std::ptrdiff_t>(len);
}

template <typename OutputIt,
          typename T,
          typename std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>
OutputIt put(OutputIt possition, OutputIt last, const T& value)
{
    if (std::distance(possition, last) < static_cast<std::ptrdiff_t>(value.size())) {
        throw BufferOverflow();
    }

    std::copy(value.begin(), value.end(), possition);
    return possition + static_cast<std::ptrdiff_t>(value.size());
}

template <typename OutputIt,
          typename T,
          typename std::enable_if_t<std::is_same<T, std::vector<uint8_t>>::value, bool> = true>
OutputIt put(OutputIt possition, OutputIt last, const T& value)
{
    if (std::distance(possition, last) < static_cast<std::ptrdiff_t>(value.size())) {
        throw BufferOverflow();
    }

    std::copy(value.begin(), value.end(), possition);
    return possition + static_cast<std::ptrdiff_t>(value.size());
}

} // namespace netpacker

#endif /* NETPACKER_PUT_H */
