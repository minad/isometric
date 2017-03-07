#ifndef _Engine_Exception_h
#define _Engine_Exception_h

#include <exception>
#include <string>

namespace Engine {

class Exception : public std::exception
{
public:

    Exception(const std::string& message, const std::string& reason)
        : message(message), reason(reason)
    {
    }

    ~Exception() throw()
    {
    }

    const std::string& getReason() const throw()
    {
        return reason;
    }

    const std::string& getMessage() const throw()
    {
        return message;
    }

    const char* what() const throw()
    {
        return (message + ": " + reason).c_str();
    }

private:

    std::string message, reason;
};

} // namespace Engine

#endif // _Engine_Exception_h

