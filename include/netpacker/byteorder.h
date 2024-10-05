#ifndef NETPACKER_DETAIL_BYTEORDER_H
#define NETPACKER_DETAIL_BYTEORDER_H

#include <exception>

namespace netpacker {
namespace detail {

inline uint64_t byte_reverse(uint64_t n)
{
    uint64_t step32 = n << 32 | n >> 32;
    uint64_t step16 = (step32 & 0x0000FFFF0000FFFFULL) << 16 | (step32 & 0xFFFF0000FFFF0000ULL) >> 16;
    return (step16 & 0x00FF00FF00FF00FFULL) << 8 | (step16 & 0xFF00FF00FF00FF00ULL) >> 8;
}

inline uint64_t htonll(uint64_t n)
{
#if defined(htobe64)
    return htobe64(n);
#else
#  if __BYTE_ORDER == __BIG_ENDIAN
    return n;
#  else
    return byte_reverse(n);
#  endif
#endif
}

inline uint64_t ntohll(uint64_t n)
{
#if defined(be64toh)
    return be64toh(n);
#else
#  if __BYTE_ORDER == __BIG_ENDIAN
    return n;
#  else
    return byte_reverse(n);
#  endif
#endif
}

} // namespace detail


template <typename T,
          typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
inline T host_to_network(T value)
{
    if constexpr (__BYTE_ORDER == __BIG_ENDIAN || sizeof(T) == sizeof(uint8_t)) {
        return value;
    }

    else if constexpr (sizeof(T) == sizeof(uint16_t)) {
        return htons(value);
    }

    else if constexpr (sizeof(T) == sizeof(uint32_t)) {
        return htonl(value);
    }

    else if constexpr (sizeof(T) == sizeof(uint64_t)) {
        return detail::htonll(value);
    }

    else {
        throw std::exception("host_to_network: unexpected size");
    }
}

template <typename T,
          typename std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
inline T network_to_host(T value)
{
    if constexpr (__BYTE_ORDER == __BIG_ENDIAN || sizeof(T) == sizeof(uint8_t)) {
        return value;
    }

    else if constexpr (sizeof(T) == sizeof(uint16_t)) {
        return ntohs(value);
    }

    else if constexpr (sizeof(T) == sizeof(uint32_t)) {
        return ntohl(value);
    }

    else if constexpr (sizeof(T) == sizeof(uint64_t)) {
        return detail::ntohll(value);
    }

    else {
        throw std::exception("network_to_host: unexpected size");
    }
}

} // namespace netpacker
#endif /* NETPACKER_DETAIL_BYTEORDER_H */
