#ifndef NETPACKER_ERROR_H
#define NETPACKER_ERROR_H

#include <exception>

namespace netpacker {

class Exception : public std::exception
{
protected:
    Exception() noexcept = default;

public:
    virtual ~Exception() = default;
};

class EndOfBuffer : public Exception
{
public:
    EndOfBuffer() noexcept = default;

    const char* what() const noexcept override
    {
        return "End of buffer";
    }
};

class BufferOverflow : public Exception
{
public:
    BufferOverflow() noexcept = default;

    const char* what() const noexcept override
    {
        return "Buffer overflow";
    }
};

}

#endif
