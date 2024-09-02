# 第9章 线程安全

在C++中，确保多个线程对同一个对象进行操作时的线程安全是一个常见的问题。我们可以使用互斥锁（mutex）来保护共享资源，从而避免数据竞争和不一致。

## 1. 案例

下面是一个简单的案例，展示了如何使用`std::mutex`来确保两个线程对同一个对象进行操作时的线程安全。

```c++
#include <iostream>
#include <thread>
#include <mutex>

class Counter {
public:
    Counter() : value(0) {}

    void increment() {
        std::lock_guard<std::mutex> lock(mutex); // 加锁
        ++value;
    }

    void decrement() {
        std::lock_guard<std::mutex> lock(mutex); // 加锁
        --value;
    }

    int getValue() const {
        return value;
    }

private:
    int value;
    mutable std::mutex mutex; // 互斥锁
};

void threadFunc1(Counter& counter) {
    for (int i = 0; i < 10000; ++i) {
        counter.increment();
    }
}

void threadFunc2(Counter& counter) {
    for (int i = 0; i < 10000; ++i) {
        counter.decrement();
    }
}

int main() {
    Counter counter;

    std::thread t1(threadFunc1, std::ref(counter));
    std::thread t2(threadFunc2, std::ref(counter));

    t1.join();
    t2.join();

    std::cout << "Final value: " << counter.getValue() << std::endl;

    return 0;
}
```

## 2. 解释

1. **Counter类**:
   - `Counter`类有一个私有成员变量`value`，用于存储计数值。
   - `increment`和`decrement`方法用于增加和减少计数值。
   - 在`increment`和`decrement`方法中，使用`std::lock_guard`来自动管理互斥锁，确保在方法执行期间锁是有效的。
2. **线程函数**:
   - `threadFunc1`和`threadFunc2`分别对`Counter`对象进行增加和减少操作。
   - 每个线程循环10000次，分别调用`increment`和`decrement`方法。
3. **主函数**:
   - 创建一个`Counter`对象。
   - 创建两个线程`t1`和`t2`，分别执行`threadFunc1`和`threadFunc2`，并传递`Counter`对象的引用。
   - 使用`join`方法等待两个线程完成。
   - 最后输出`Counter`对象的最终值。

通过使用`std::mutex`和`std::lock_guard`，我们确保了对`Counter`对象的访问是线程安全的，避免了数据竞争和不一致的问题。