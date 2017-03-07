#ifndef _Engine_Util_Logger_h
#define _Engine_Util_Logger_h

#include <string>
#include <sstream>

namespace Engine {
namespace Util {

class Logger
{
public:

    enum Level
    {
        DEBUG   = 0,
        INFO    = 1,
        NOTICE  = 2,
        WARNING = 3,
        ERROR   = 4,
    };

    Logger(Level level)
        : level(level) {}

    void setLevel(Level l)
    {
        level = l;
    }

    bool isLevelEnabled(Level l)
    {
        return (l >= level);
    }

    void log(Level l, const std::string& msg, const char* file, const char* func, int line);

    static Logger mainLogger;

private:

    Level level;
};

#define LOG(logger, level, message) \
if (logger.isLevelEnabled(logger.level)) { \
    std::stringstream msg; \
    msg << message; \
    logger.log(logger.level, msg.str(), __FILE__, __PRETTY_FUNCTION__, __LINE__); \
}

#define LOG_DEBUG(logger, message) \
    LOG(logger, DEBUG, message)

#define LOG_INFO(logger, message) \
    LOG(logger, INFO, message)
    
#define LOG_NOTICE(logger, message) \
    LOG(logger, NOTICE, message)
    
#define LOG_WARNING(logger, message) \
    LOG(logger, WARNING, message)
    
#define LOG_ERROR(logger, message) \
    LOG(logger, DEBUG, message)

} // namespace Util
} // namespace Engine

#endif // _Engine_Util_Logger_h
