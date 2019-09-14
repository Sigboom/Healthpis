/*********************************************
 * creat time: 2019/8/4
 * author: Daniel Doni
 * email: sigboom@163.com
 * ******************************************/
/*使用C++重写该项目 感谢sylar项目*/

#include <iostream>
#include <string>

namespace healthpis{

class Logger;
class LoggerManager;

class LogLevel {
public:
    enum Level {
        UNKNOW = 0,//打开所有日志记录
        DEBUG, //打印运行信息
        INFO,  //用于生产环境中输出的信息
        WARN,    //表明潜在的错误
        ERROE,   //发生不影响系统继续运行的错误
        FATAL,   //每个严重的错误将会导致程序退出
        OFF      //关闭所有日志记录
    }
    /* * * *
     * funcname: ToString
     * used: 将日志级别转换成文本格式输出
     * * * */
    static const char* ToSring(LogLevel::Level level);
    /* * * *
     * funcname: LogLevel
     * used: 将文本转化为日志级别
     * * * */
    static LogLevel::Level FromString(const std::string& str);
};


class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;

    LogEvent();
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char *file,
            uint32_t thread_id, const std::string& thread_name);
    const char *getFile() const { return m_file;}
    int32_t getLine() const {return m_line;}
    uint32_t getThreadId() {return m_threadId;}
    const std::string& getThreadName() const {return m_threadName;}
    LogLevel::Level getLevel() const { return m_level;}
    
private:
    const char* m_file = nullptr; // 文件名
    int32_t m_line = 0; // 行号
    uint32_t m_elapse = 0; //程序运行的秒数
    uint32_t m_threadId = 0; //线程号
    uint32_t m_fiberId = 0;  //协程Id
    uint64_t m_time = 0; //时间戳
    std::string m_threamName;//线程名
    std::stringstream m_ss; // 日志内容流
    std::shared_ptr<Logger> m_logger; //日志器
    LogLevel::Level m_level;
};

class LogFormatter {

};

class LogAppender {

};

class StdoutLogAppender: public LogAppender {
};

class FileLogAppender: public LogAppender {
};

class Logger {

};

class LoggerManager {
};

}
