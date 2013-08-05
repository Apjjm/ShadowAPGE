#ifndef HELPERMACROS_HPP
#define HELPERMACROS_HPP

//__forceinline macro
#ifdef __MINGW32__
#define __alwaysinline __attribute__((always_inline))
#else
#ifdef __GNUC__
#define __alwaysinline __attribute__((always_inline))
#endif
#endif

#ifdef _MSC_VER
#define __alwaysinline __forceinline
#endif

#ifndef __alwaysinline
#define __alwaysinline inline
#endif


//LOGGING MACROS
#ifndef DEBUG_LOG
#define LOGD(x) do { APGE::Logger::info()<<"D:"<<x<<std::endl; } while(false)
#else
#define LOGD(x)
#endif

#define LOGI(x) do { APGE::Logger::info()<<"I:"<<x<<std::endl; } while(false)
#define LOGW(x) do { APGE::Logger::warn()<<"W:"<<x<<std::endl; } while(false)
#define LOGE(x) do { APGE::Logger::error()<<"E:"<<x<<std::endl; } while(false)
#define FATAL(x) do { APGE::Logger::error()<<"FATAL: "<<x<<std::endl; APGE::Application::getApplication().abort(EXIT_FAILURE); } while(false)
#define FATALC(x,y) do { APGE::Logger::error()<<"FATAL: "<<x<<std::endl; APGE::Application::getApplication().abort(y); } while(false)
#include "Logger.hpp"

#endif // HELPERMACROS_HPP
