#include "Engine/Util/Logger.h"
#include "Engine/Util/LogAppender.h"
#include <iostream>

namespace Engine {
namespace Util {

Logger Logger::mainLogger(Logger::INFO);

void Logger::log(Level level, const std::string& msg, const char* file, const char* func, int line)
{
    LogAppender::getInstance()->append(level, msg, file, func, line);
} 

} // namespace Util
} // namespace Engine
