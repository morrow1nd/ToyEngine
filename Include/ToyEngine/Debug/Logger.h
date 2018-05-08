#pragma once

#include "ToyEngineConfig.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Log/Logger.h"
#include "ToyUtility/DesignPattern/ISingleton.h"
#include "ToyUtility/Container/List.h"


namespace ToyEngine
{


#define TOY_MACRO_TO_STRING(x) #x

// For the reason: https://stackoverflow.com/a/19343239
#define TOY_INNER_MACRO_TWICE(x) TOY_MACRO_TO_STRING(x)


#define TOY_LOG_TRACE(fmt, ...)     ToyEngine::ToyLogger::Instance().Trace(__FILE__ ":" __FUNCTION__ ":L" TOY_INNER_MACRO_TWICE(__LINE__) ": " fmt, ##__VA_ARGS__)
#define TOY_LOG_DEBUG(fmt, ...)     ToyEngine::ToyLogger::Instance().Debug(__FILE__ ":" __FUNCTION__ ":L" TOY_INNER_MACRO_TWICE(__LINE__) ": " fmt, ##__VA_ARGS__)
#define TOY_LOG_INFO(fmt, ...)      ToyEngine::ToyLogger::Instance().Info(__FILE__ ":" __FUNCTION__ ":L" TOY_INNER_MACRO_TWICE(__LINE__) ": " fmt, ##__VA_ARGS__)
#define TOY_LOG_WARN(fmt, ...)      ToyEngine::ToyLogger::Instance().Warn(__FILE__ ":" __FUNCTION__ ":L" TOY_INNER_MACRO_TWICE(__LINE__) ": " fmt, ##__VA_ARGS__)
#define TOY_LOG_ERROR(fmt, ...)     ToyEngine::ToyLogger::Instance().Error(__FILE__ ":" __FUNCTION__ ":L" TOY_INNER_MACRO_TWICE(__LINE__) ": " fmt, ##__VA_ARGS__)
#define TOY_LOG_FATAL(fmt, ...)     ToyEngine::ToyLogger::Instance().Fatal(__FILE__ ":" __FUNCTION__ ":L" TOY_INNER_MACRO_TWICE(__LINE__) ": " fmt, ##__VA_ARGS__)


class ToyLogger : public ToyUtility::ISingleton<ToyLogger>
{
public:
    void Init()
    {
        m_Loggers.resize(1);
        m_Loggers[0].InitConsoleLogger();
       // m_Loggers[1].InitBasicFileLogger("logs/log.txt");
        //m_Loggers[2].InitNetLogger();
    }

    void DeInit()
    {
        ToyUtility::Logger::ReleaseAllLoggers();
    }


    template<typename T>
    inline void Trace(const T& msg)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Trace(msg);
        }
    }

    template <typename Arg1, typename... Args>
    inline void Trace(const char* fmt, const Arg1 &arg1, const Args&... args)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Trace(fmt, arg1, args...);
        }
    }

    template<typename T>
    inline void Debug(const T& msg)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Debug(msg);
        }
    }

    template <typename Arg1, typename... Args>
    inline void Debug(const char* fmt, const Arg1 &arg1, const Args&... args)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Debug(fmt, arg1, args...);
        }
    }

    template<typename T>
    inline void Info(const T& msg)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Info(msg);
        }
    }

    template <typename Arg1, typename... Args>
    inline void Info(const char* fmt, const Arg1 &arg1, const Args&... args)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Info(fmt, arg1, args...);
        }
    }

    template<typename T>
    inline void Warn(const T& msg)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Warn(msg);
        }
    }

    template <typename Arg1, typename... Args>
    inline void Warn(const char* fmt, const Arg1 &arg1, const Args&... args)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Warn(fmt, arg1, args...);
        }
    }

    template<typename T>
    inline void Error(const T& msg)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Error(msg);
        }
    }

    template <typename Arg1, typename... Args>
    inline void Error(const char* fmt, const Arg1 &arg1, const Args&... args)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Error(fmt, arg1, args...);
        }
    }

    template<typename T>
    inline void Fatal(const T& msg)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Fatal(msg);
        }
    }

    template <typename Arg1, typename... Args>
    inline void Fatal(const char* fmt, const Arg1 &arg1, const Args&... args)
    {
        for (auto i = m_Loggers.begin(), end = m_Loggers.end(); i != end; ++i)
        {
            (*i).Fatal(fmt, arg1, args...);
        }
    }


private:
    ToyUtility::List<ToyUtility::Logger> m_Loggers;
};


} // end of namespace ToyEngine