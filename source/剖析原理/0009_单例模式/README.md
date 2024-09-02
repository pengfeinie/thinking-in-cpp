# 第10章 单例模式

在 C++ 中实现单例模式有多种方法，每种方法都有其优缺点。以下是三种常见的实现方式：

## 1. 懒汉式单例模式（Lazy Initialization Singleton）

懒汉式单例模式在第一次使用时才创建实例，适用于实例化开销较大的对象。

```c++
#include <iostream>
#include <memory>

class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;
        return instance;
    }

    void doSomething() {
        std::cout << "Doing something!" << std::endl;
    }

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {
        // 私有构造函数
    }
};

int main() {
    Singleton::getInstance().doSomething();
    return 0;
}
```

## 2. 饿汉式单例模式（Eager Initialization Singleton）

饿汉式单例模式在程序启动时就创建实例，适用于实例化开销较小的对象。

```c++
#include <iostream>

class Singleton {
public:
    static Singleton& getInstance() {
        return instance;
    }

    void doSomething() {
        std::cout << "Doing something!" << std::endl;
    }

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {
        // 私有构造函数
    }

    static Singleton instance;
};

Singleton Singleton::instance;

int main() {
    Singleton::getInstance().doSomething();
    return 0;
}
```

### 3. 使用 `std::call_once` 实现的线程安全单例模式

`std::call_once` 可以确保单例实例在多线程环境下只被创建一次。

```c++
#include <iostream>
#include <memory>
#include <mutex>

class Singleton {
public:
    static Singleton& getInstance() {
        std::call_once(initFlag, &Singleton::init);
        return *instance;
    }

    void doSomething() {
        std::cout << "Doing something!" << std::endl;
    }

    // 禁用拷贝构造函数和赋值操作符
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {
        // 私有构造函数
    }

    static void init() {
        instance = std::make_unique<Singleton>();
    }

    static std::unique_ptr<Singleton> instance;
    static std::once_flag initFlag;
};

std::unique_ptr<Singleton> Singleton::instance;
std::once_flag Singleton::initFlag;

int main() {
    Singleton::getInstance().doSomething();
    return 0;
}
```

## 4. 总结

- **懒汉式单例模式**：适用于实例化开销较大的对象，延迟初始化。
- **饿汉式单例模式**：适用于实例化开销较小的对象，程序启动时初始化。
- **线程安全单例模式**：使用 `std::call_once` 确保多线程环境下的线程安全性。

选择哪种实现方式取决于具体的应用场景和需求。