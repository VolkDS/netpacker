#ifndef NETPACKER_GET_H
#define NETPACKER_GET_H

#include <cstring>
#include <iterator>
#include <vector>
#include <string>
#include <type_traits>

#include <netinet/in.h>

#include <netpacker/byteorder.h>
#include <netpacker/error.h>

namespace netpacker {

template <typename T,
          typename InputIt,
          typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
T get(InputIt& possition, InputIt last)
{
    using unsigned_t = typename std::make_unsigned<T>::type;
    unsigned_t value = 0;

    if (std::distance(possition, last) < static_cast<std::ptrdiff_t>(sizeof(T))) {
        throw EndOfBuffer();
    }

    std::copy(possition, possition + sizeof(T), reinterpret_cast<uint8_t*>(&value));

    unsigned_t nval = network_to_host(value);
    possition += sizeof(T);
    if constexpr (std::is_same_v<T, decltype(nval)>) {
        return nval;
    }
    else {
        return static_cast<T>(nval);
    }
}

template <typename T,
          typename InputIt,
          typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
T get(InputIt& possition, InputIt last, typename std::iterator_traits<InputIt>::difference_type len)
{
    if (len >= static_cast<std::ptrdiff_t>(sizeof(T))) {
        return get<T>(possition, last);
    }

    using unsigned_t = typename std::make_unsigned<T>::type;
    unsigned_t value = 0;

    if (std::distance(possition, last) < len) {
        throw EndOfBuffer();
    }

    std::copy(possition, possition + len,
        reinterpret_cast<uint8_t*>(&value) + sizeof(decltype(value)) - len);

    unsigned_t nval = network_to_host(value);
    possition += len;
    if constexpr (std::is_same_v<T, decltype(nval)>) {
        return nval;
    }
    else {
        return static_cast<T>(nval);
    }
}

template <typename T,
          typename InputIt,
          typename std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>
T get(InputIt& possition, InputIt last, typename std::iterator_traits<InputIt>::difference_type len)
{
    if (std::distance(possition, last) < len) {
        throw EndOfBuffer();
    }

    T value(possition, possition + len);
    possition += len;
    return value;
}

template <typename T,
          typename InputIt,
          typename std::enable_if_t<std::is_same<T, std::vector<uint8_t>>::value, bool> = true>
T get(InputIt& possition, InputIt last, typename std::iterator_traits<InputIt>::difference_type len)
{
    if (std::distance(possition, last) < len) {
        throw EndOfBuffer();
    }

    T value(possition, possition + len);
    possition += len;
    return value;
}

} // namespace netpacker

#endif /* NETPACKER_GET_H */
