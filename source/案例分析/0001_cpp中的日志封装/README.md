# 第2章 C++中的日志使用

现在有三个不同的项目分别使用的日志库是spdlog, log4cpp 和 glog。现在想设计一个全新的NewLogger，来封装多个不同的日志库，并且还需要支持使用fmt库来实现参数打印。

## 1. 设计思路

设计一个全新的 `NewLogger` 来封装多个不同的日志库（如 `spdlog`, `log4cpp`, 和 `glog`），并且支持使用 `fmt` 库来实现参数打印，是一个复杂的任务。以下是一个详细的解决方案，包括设计思路、代码示例和实现步骤。

1. **抽象日志库接口**：首先，我们需要定义一个抽象的日志库接口，所有具体的日志库实现都将遵循这个接口。
2. **适配器模式**：为每个具体的日志库（`spdlog`, `log4cpp`, `glog`）创建适配器类，这些适配器类将实现抽象日志库接口。
3. **NewLogger 类**：`NewLogger` 类将使用这些适配器来封装不同的日志库，并提供统一的接口供用户使用。
4. **使用 `fmt` 库**：在 `NewLogger` 中集成 `fmt` 库，以便支持参数化的日志消息。

## 2. 代码实现

### 2.1 抽象日志库接口

```c++
#include <string>
#include <memory>

class LoggerInterface {
public:
    virtual ~LoggerInterface() = default;

    virtual void log(const std::string& level, const std::string& message) = 0;
    virtual void debug(const std::string& message) = 0;
    virtual void info(const std::string& message) = 0;
    virtual void warn(const std::string& message) = 0;
    virtual void error(const std::string& message) = 0;
};
```

### 2.2 适配器类

#### 2.1 `SpdlogAdapter`

```c++
#include "spdlog/spdlog.h"
#include "LoggerInterface.h"

class SpdlogAdapter : public LoggerInterface {
public:
    SpdlogAdapter(std::shared_ptr<spdlog::logger> logger) : logger_(logger) {}

    void log(const std::string& level, const std::string& message) override {
        if (level == "debug") logger_->debug(message);
        else if (level == "info") logger_->info(message);
        else if (level == "warn") logger_->warn(message);
        else if (level == "error") logger_->error(message);
    }

    void debug(const std::string& message) override {
        logger_->debug(message);
    }

    void info(const std::string& message) override {
        logger_->info(message);
    }

    void warn(const std::string& message) override {
        logger_->warn(message);
    }

    void error(const std::string& message) override {
        logger_->error(message);
    }

private:
    std::shared_ptr<spdlog::logger> logger_;
};
```

#### 2.2 `Log4CppAdapter`

```c++
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "LoggerInterface.h"

class Log4CppAdapter : public LoggerInterface {
public:
    Log4CppAdapter(log4cpp::Category& logger) : logger_(logger) {}

    void log(const std::string& level, const std::string& message) override {
        if (level == "debug") logger_.debug(message);
        else if (level == "info") logger_.info(message);
        else if (level == "warn") logger_.warn(message);
        else if (level == "error") logger_.error(message);
    }

    void debug(const std::string& message) override {
        logger_.debug(message);
    }

    void info(const std::string& message) override {
        logger_.info(message);
    }

    void warn(const std::string& message) override {
        logger_.warn(message);
    }

    void error(const std::string& message) override {
        logger_.error(message);
    }

private:
    log4cpp::Category& logger_;
};
```

#### 2.3 `GlogAdapter`

```c++
#include "glog/logging.h"
#include "LoggerInterface.h"

class GlogAdapter : public LoggerInterface {
public:
    GlogAdapter() {}

    void log(const std::string& level, const std::string& message) override {
        if (level == "debug") LOG(INFO) << message;
        else if (level == "info") LOG(INFO) << message;
        else if (level == "warn") LOG(WARNING) << message;
        else if (level == "error") LOG(ERROR) << message;
    }

    void debug(const std::string& message) override {
        LOG(INFO) << message;
    }

    void info(const std::string& message) override {
        LOG(INFO) << message;
    }

    void warn(const std::string& message) override {
        LOG(WARNING) << message;
    }

    void error(const std::string& message) override {
        LOG(ERROR) << message;
    }
};
```

### 3. `NewLogger` 类

```c++
#include "LoggerInterface.h"
#include "fmt/format.h"
#include <memory>
#include <string>

class NewLogger {
public:
    NewLogger(std::unique_ptr<LoggerInterface> logger) : logger_(std::move(logger)) {}

    template <typename... Args>
    void log(const std::string& level, const std::string& format, Args&&... args) {
        std::string message = fmt::format(format, std::forward<Args>(args)...);
        logger_->log(level, message);
    }

    template <typename... Args>
    void debug(const std::string& format, Args&&... args) {
        std::string message = fmt::format(format, std::forward<Args>(args)...);
        logger_->debug(message);
    }

    template <typename... Args>
    void info(const std::string& format, Args&&... args) {
        std::string message = fmt::format(format, std::forward<Args>(args)...);
        logger_->info(message);
    }

    template <typename... Args>
    void warn(const std::string& format, Args&&... args) {
        std::string message = fmt::format(format, std::forward<Args>(args)...);
        logger_->warn(message);
    }

    template <typename... Args>
    void error(const std::string& format, Args&&... args) {
        std::string message = fmt::format(format, std::forward<Args>(args)...);
        logger_->error(message);
    }

private:
    std::unique_ptr<LoggerInterface> logger_;
};
```

### 4. 使用示例

#### 4.1 直接使用

```c++
#include "NewLogger.h"
#include "SpdlogAdapter.h"
#include "Log4CppAdapter.h"
#include "GlogAdapter.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "log4cpp/Category.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "glog/logging.h"

int main() {
    // 使用 spdlog
    auto spdlog_logger = spdlog::stdout_color_mt("console");
    NewLogger spdlog_new_logger(std::make_unique<SpdlogAdapter>(spdlog_logger));
    spdlog_new_logger.info("Hello, {}!", "World");

    // 使用 log4cpp
    log4cpp::PatternLayout* layout = new log4cpp::PatternLayout();
    layout->setConversionPattern("%d [%p] %m%n");
    log4cpp::OstreamAppender* appender = new log4cpp::OstreamAppender("console", &std::cout);
    appender->setLayout(layout);
    log4cpp::Category& log4cpp_logger = log4cpp::Category::getRoot().getInstance("main");
    log4cpp_logger.addAppender(appender);
    log4cpp_logger.setPriority(log4cpp::Priority::DEBUG);
    NewLogger log4cpp_new_logger(std::make_unique<Log4CppAdapter>(log4cpp_logger));
    log4cpp_new_logger.info("Hello, {}!", "World");

    // 使用 glog
    google::InitGoogleLogging("main");
    NewLogger glog_new_logger(std::make_unique<GlogAdapter>());
    glog_new_logger.info("Hello, {}!", "World");

    return 0;
}
```

#### 4.2 使用回调函数

##### 4.2.1 声明回调函数

```c++
//logger_wapper.h
#include <memory>

typedef std::unique_ptr<Logger>(*Provider)(); 

class LoggerWapper {
    public:
    	LoggerWapper(Provider callback){
            provider_ = callback;
        }
        
    	std::unique_ptr<Logger> getProvider(){
            return provider_();
        }
    private:
    	Provider provider_ = nullptr;
}

```

##### 4.2.1 定义回调函数

```c++
#include "logger_wapper.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

std::unique_ptr<Logger> pullProvider(){
    auto logger = spdlog::stdout_color_mt("console");
    return std::make_unique<SpdlogAdapter>(logger);
} 
```

##### 4.2.1 使用

```c++
int main(){
    LoggerWapper wapper(pullProvider);
    NewLogger newLogger(wapper.getProvider());
    newLogger.info("Hello, {}!", "World");
}
```



### 5. 总结

通过上述设计，我们创建了一个 `NewLogger` 类，它能够封装多个不同的日志库（`spdlog`, `log4cpp`, `glog`），并且支持使用 `fmt` 库来实现参数化的日志消息。每个具体的日志库通过适配器类与 `NewLogger` 进行交互，从而实现了日志库的统一接口。
