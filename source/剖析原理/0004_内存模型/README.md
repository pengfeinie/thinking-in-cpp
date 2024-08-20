# 第5章 内存模型简明解读

## 1. 堆与栈

C++程序运行时，内存大致分为堆（heap）和栈（stack）两部分。栈主要用于存储局部变量和函数调用信息，其分配与释放由编译器自动管理，遵循后进先出（LIFO）原则。而堆则是动态分配内存区域，程序员通过new操作符申请，使用完毕后需手动调用delete释放。

```c++
int main() {
    // 栈上分配
    int stackVar = 42;

    // 堆上分配
    int* heapPtr = new int(1337);
    delete heapPtr; // 必须手动释放
}
```

## 2. 内存泄漏与悬挂指针

忘记释放已分配内存会导致内存泄漏，而继续使用已释放内存的指针则会形成悬挂指针。这些问题不易察觉，却可能导致程序崩溃、数据损坏甚至安全漏洞。

```c++
void problematicFunction() {
    int* ptr = new int(42); // 分配内存
    // ... 未正确释放内存 ...
} // 函数结束，ptr丢失，内存泄漏

int* danglingPtr() {
    int* p = new int(1337);
    delete p;
    return p; // 返回已释放内存的指针，形成悬挂指针
}
```

## 3. 智能指针轻松入门

智能指针是C++标准库提供的内存管理利器，它们在构造时自动分配内存，在析构时自动释放内存，有效防止内存泄漏。这里重点介绍两种常用的智能指针：

std::unique_ptr: 独占所有权，不允许复制，可通过移动语义转移所有权。

std::shared_ptr: 共享所有权，引用计数管理，多个智能指针可同时指向同一块内存，当最后一个引用消失时自动释放。

```c++
#include <memory>
int main() {
    // 使用unique_ptr
    std::unique_ptr<int> uptr(new int(42)); // 自动释放
    // std::unique_ptr<int> uptr2 = uptr; // 编译错误：不能复制unique_ptr

    // 使用shared_ptr
    std::shared_ptr<int> sptr(new int(1337));
    std::shared_ptr<int> sptr2 = sptr; // 共享所有权，引用计数+1
}
```

## 4. 智能指针实战应用

**构建资源管理类** 借助智能指针，您可以轻松创建管理特定资源（如文件、网络连接等）的类。只需在类内部使用智能指针存储资源，并在类析构时自动释放。

```c++
#include <fstream>
#include <memory>

class ManagedFile {
public:
    ManagedFile(const std::string& filename) : file_{std::make_unique<std::fstream>(filename)} {}
    ~ManagedFile() = default; // 文件在类析构时自动关闭

private:
    std::unique_ptr<std::fstream> file_;
};
```

**管理动态数组** 智能指针同样适用于管理动态数组。使用std::unique_ptr结合std::array或std::vector可以实现自动释放数组内存。

```c++
std::unique_ptr<int[]> arrPtr(new int[100]); // 动态数组自动释放
std::unique_ptr<std::vector<int>> vecPtr = std::make_unique<std::vector<int>>(100); // 使用vector更便捷
```

**避免裸指针传递** 在函数参数或返回值中，尽量使用智能指针代替裸指针，以确保资源得到有效管理。

```c++
std::shared_ptr<int> createInt(int value) {
    return std::make_shared<int>(value); // 返回智能指针，自动管理内存
}

void processInt(std::shared_ptr<int> ptr) {
    // 在函数内部，智能指针确保内存安全
}
```



**参考**

- [https://cloud.tencent.com/developer/article/2408557](https://cloud.tencent.com/developer/article/2408557)