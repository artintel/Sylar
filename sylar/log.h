#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__
#include <string>
#include <stdint.h>
#include <list>
#include <stringstreams>
#include <sstream>
#include <fstream>
#include <vector>

class Logger;

namespace sylar{
//日志事件
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();

    const char* getFIle() const { return m_file; }
    int32_t getLine() const { return m_line; }
    uint32_t getElapse() const { return m_elapse; }
    uint32_t getThreadId() const { return m_threadId; }
    uint32_t getFiberId() const { return m_fiberId; }
    uint64_t getTime() const { return m_time; }
    const std::string& getCOntent() const { return m_content; }
private:
    const char* m_file = nullptr;   //文件名
    int32_t m_line = 0;             //行号
    uint32_t m_elapse = 0;          //程序启动到开始到现在的毫秒数
    uint32_t m_threadId = 0;        //线程ID
    uint32_t m_fiberId = 0;         //协程ID
    uint64_t m_time = 0;            //时间戳
    std::string m_content;

};

//日志级别
class LogLevel{
public:
    enum Level{
       UKNOWN = 0;
       DEBUG = 1,
       INFO = 2,
       WARN = 3,
       EOORO = 4,
       FATAL = 5
    };

    static const char* ToString(LogLevel::Level level);

};


//日志格式器
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);
    
    //%t    %thread_id %m%n -->  时间   线程号 消息 换行    这是定义的一种固定化格式
    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
public:
    //定义一个子模块
    class FormateItem{
    public:
        FOrmatItem(const std::string& fmt = "")
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormateItem(){}
        virtual void std::string format(std::ostream& os, std::shared_ptr<Logger> logger,  LogLevel::Level level, LogEvent::ptr event) = 0;
    };

   void init(); 
private:
    std::string m_pattern;
    std::vector<FormateItem::ptr> m_items;
};


//日志输出地
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LOgEvent::ptr event) = 0;//定义纯虚基类，在字类中进行实现

    void setFormatter(LogFormatter::ptr val){ m_formatter = val; }
    LogFromatter::ptr getFormatter() const { return m_formatter; }
protected://这样，字类就可以使用到
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger{
public:
    typedef std:shared_ptr<Logger> ptr;
    
    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);
    
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);
    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level val){ m_level = val; }

    const std::string& getName() const { return m_name; }
private:
    std::string m_name;                                //日志名称
    LogLevel::Level m_level;                           //日志级别
    std::list<LogAppender::ptr> m_appenders;           //Appender集合
};

//输出到控制台的Appender
class StdoutLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(LogLevel::Level level, LogEvent::ptr event) override;
private:
};


//定义输出到文件的Appender
class FileLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FIleLogAppender(const std::string& filename);   //需要文件名
    void Log(LogLevel::Level level, LogEvent::ptr event) override;  //override 重写关键字，可以避免派生类中忘记重写续汉书的错误
    //重新打开文件，文件打开成功返回true
    bool reopen();
private:
    std::string m_ame;
    std::ofstream m_filestream;
};


}



#endif
