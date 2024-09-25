# 第3章 c++中如何将原始指针封装为 std::unique_ptr 

在 C++ 中，`std::unique_ptr` 是一个智能指针，用于管理动态分配的内存，并确保在 `std::unique_ptr` 对象被销毁时，它所管理的内存也会被自动释放。你可以通过以下几种方式将原始指针封装为 `std::unique_ptr`。

## 1. 思路

### 1.1 直接使用 `std::unique_ptr` 的构造函数

你可以直接使用 `std::unique_ptr` 的构造函数来封装一个原始指针。例如：

```c++
#include <memory>

int main() {
    // 创建一个原始指针
    int* raw_ptr = new int(42);

    // 将原始指针封装为 std::unique_ptr
    std::unique_ptr<int> unique_ptr(raw_ptr);

    // 现在 unique_ptr 管理 raw_ptr 指向的内存
    // 当 unique_ptr 离开作用域时，raw_ptr 指向的内存会被自动释放

    return 0;
}
```

### 1.2 使用 `std::unique_ptr` 的 `reset` 方法

你也可以使用 `std::unique_ptr` 的 `reset` 方法来封装一个原始指针。例如：

```c++
#include <memory>

int main() {
    // 创建一个原始指针
    int* raw_ptr = new int(42);

    // 创建一个空的 std::unique_ptr
    std::unique_ptr<int> unique_ptr;

    // 使用 reset 方法将原始指针封装为 std::unique_ptr
    unique_ptr.reset(raw_ptr);

    // 现在 unique_ptr 管理 raw_ptr 指向的内存
    // 当 unique_ptr 离开作用域时，raw_ptr 指向的内存会被自动释放

    return 0;
}
```

### 1.3 使用 `std::unique_ptr` 的 `make_unique` 函数（C++14 及以上）

如果你使用的是 C++14 或更高版本，你可以使用 `std::make_unique` 函数来创建 `std::unique_ptr`，而不需要手动创建原始指针。例如：

```c++
#include <memory>

int main() {
    // 使用 std::make_unique 创建 std::unique_ptr
    std::unique_ptr<int> unique_ptr = std::make_unique<int>(42);

    // 现在 unique_ptr 管理新分配的内存
    // 当 unique_ptr 离开作用域时，内存会被自动释放

    return 0;
}
```

## 2. 注意事项

- 一旦你将原始指针封装为 `std::unique_ptr`，就不应该再手动删除该指针，否则会导致双重删除（double delete）错误。
- `std::unique_ptr` 是独占所有权的智能指针，因此不能有多个 `std::unique_ptr` 同时管理同一块内存。

通过这些方法，你可以安全地将原始指针封装为 `std::unique_ptr`，从而避免内存泄漏和手动管理内存的复杂性。
