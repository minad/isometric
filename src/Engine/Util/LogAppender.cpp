#include "Engine/Util/LogAppender.h"
#include "Engine/Util/Logger.h"
#include <iostream>

namespace Engine {
namespace Util {

namespace {

const char* levelToString(Logger::Level level)
{
    switch (level)
    {
    case Logger::DEBUG:   return "DEBUG";
    case Logger::INFO:    return "INFO";
    case Logger::NOTICE:  return "NOTICE";
    case Logger::WARNING: return "WARNING";
    default:              return "ERROR";
    }
}

}

SmartPtr<LogAppender> LogAppender::instance;

LogAppender::LogAppender()
    : file("isometric.log")
{
    start();
}

LogAppender::~LogAppender()
{
    requestQuit();
    cond.signal();
    wait();
    file.close();
}

void LogAppender::append(Logger::Level level, const std::string& msg, const char* file, const char* func, int line)
{
    mutex.lock();
    entries.push(Entry(level, msg, file, func, line));
    if (entries.size() >= 10)
        cond.signal();
    mutex.unlock();
}

int LogAppender::run()
{
    while (!isQuitRequested())
    {
        mutex.lock();
        cond.wait(mutex);
        
	while (!entries.empty())
	{
            Entry e = entries.front();
	    entries.pop();
	    
	    std::stringstream logstr;
            logstr << '[' << levelToString(e.level) << "] " << e.msg
                   << " (" << e.file << ':' << e.line << ", " << e.func << ')' << std::endl;

            std::cout << logstr.str();
            file      << logstr.str();
	}

	std::cout.flush();
	file.flush();

	mutex.unlock();
    }
    
    return 0;
}

LogAppender* LogAppender::getInstance()
{
    if (!instance)
        instance = new LogAppender();
    return instance;
}

} // namespace Util
} // namespace Engine
