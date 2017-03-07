#ifndef _Engine_Util_LogAppender_h
#define _Engine_Util_LogAppender_h

#include "Engine/Base.h"
#include "Engine/SmartPtr.h"
#include "Engine/Util/Logger.h"
#include "Engine/Util/Thread.h"
#include "Engine/Util/Condition.h"
#include "Engine/Util/Mutex.h"
#include <string>
#include <iosfwd>
#include <fstream>
#include <queue>

namespace Engine {
namespace Util {

class LogAppender : private Thread, public Base
{
public:

    static LogAppender* getInstance();

    void append(Logger::Level level, const std::string& msg,
                const char* file, const char* func, int line);

private:

    LogAppender();
    ~LogAppender();
    
    int run();

    struct Entry
    {
        Logger::Level level;
        std::string   msg;
        const char*   file;
        const char*   func;
        int           line;

        Entry(Logger::Level level, const std::string& msg,
              const char* file, const char* func, int line)
            : level(level), msg(msg), file(file), func(func), line(line)
        {
        }
    };

    std::ofstream     file;
    std::queue<Entry> entries;
    Mutex             mutex;
    Condition         cond;

    static SmartPtr<LogAppender> instance;
};

} // namespace Util
} // namespace Engine

#endif // _Engine_Util_LogAppender_h
