#pragma once

#include "ToyEngineConfig.h"
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Log/Logger.h"
#include "ToyUtility/DesignPattern/ISingleton.h"
#include "ToyUtility/Container/List.h"


namespace ToyEngine
{


#define TOY_LOG_TRACE(fmt, ...)     ToyLogger::Instance().Trace(fmt, ##__VA_ARGS__)
#define TOY_LOG_DEBUG(fmt, ...)     ToyLogger::Instance().Debug(fmt, ##__VA_ARGS__)
#define TOY_LOG_INFO(fmt, ...)      ToyLogger::Instance().Info(fmt, ##__VA_ARGS__)
#define TOY_LOG_WARN(fmt, ...)      ToyLogger::Instance().Warn(fmt, ##__VA_ARGS__)
#define TOY_LOG_ERROR(fmt, ...)     ToyLogger::Instance().Error(fmt, ##__VA_ARGS__)
#define TOY_LOG_FATAL(fmt, ...)     ToyLogger::Instance().Fatal(fmt, ##__VA_ARGS__)


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
            (*i).Trace(fmt, args);
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
            (*i).Debug(fmt, args);
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
            (*i).Info(fmt, args);
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
            (*i).Warn(fmt, args);
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
            (*i).Error(fmt, args);
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
            (*i).Fatal(fmt, args);
        }
    }


private:
    ToyUtility::List<ToyUtility::Logger> m_Loggers;
};


} // end of namespace ToyEngine