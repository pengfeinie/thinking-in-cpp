# 第4章 c++中如何打印enum class 

在 C++ 中，`enum class`（也称为强类型枚举）是一种强类型的枚举类型，它不会隐式转换为整数类型，因此不能直接使用 `std::cout` 或其他输出流来打印 `enum class` 的值。要打印 `enum class` 的值，你需要将其转换为整数类型或使用其他方法。

## 1. 思路

### 1.1  显式转换为整数类型

你可以将 `enum class` 的值显式转换为整数类型（如 `int`），然后打印该整数。

```c++
#include <iostream>

enum class Color { Red, Green, Blue };

int main() {
    Color c = Color::Green;
    std::cout << static_cast<int>(c) << std::endl;  // 输出: 1
    return 0;
}
```

### 1.2 使用 `switch` 语句

如果你希望打印 `enum class` 的名称而不是整数值，可以使用 `switch` 语句来实现。

```c++
#include <iostream>

enum class Color { Red, Green, Blue };

void printColor(Color c) {
    switch (c) {
        case Color::Red:
            std::cout << "Red" << std::endl;
            break;
        case Color::Green:
            std::cout << "Green" << std::endl;
            break;
        case Color::Blue:
            std::cout << "Blue" << std::endl;
            break;
        default:
            std::cout << "Unknown color" << std::endl;
            break;
    }
}

int main() {
    Color c = Color::Green;
    printColor(c);  // 输出: Green
    return 0;
}
```

### 1.3 使用映射（Map）

你可以使用 `std::map` 或 `std::unordered_map` 将 `enum class` 的值映射到字符串，然后打印相应的字符串。

```c++
#include <iostream>
#include <map>
#include <string>

enum class Color { Red, Green, Blue };

std::map<Color, std::string> colorMap = {
    {Color::Red, "Red"},
    {Color::Green, "Green"},
    {Color::Blue, "Blue"}
};

void printColor(Color c) {
    std::cout << colorMap[c] << std::endl;
}

int main() {
    Color c = Color::Green;
    printColor(c);  // 输出: Green
    return 0;
}
```

### 1.4. 使用 `std::to_string` 和 `std::map`

如果你希望将 `enum class` 的值转换为字符串，可以使用 `std::to_string` 和 `std::map` 的组合。

```c++
#include <iostream>
#include <map>
#include <string>

enum class Color { Red, Green, Blue };

std::map<Color, std::string> colorMap = {
    {Color::Red, "Red"},
    {Color::Green, "Green"},
    {Color::Blue, "Blue"}
};

std::string colorToString(Color c) {
    return colorMap[c];
}

int main() {
    Color c = Color::Green;
    std::cout << colorToString(c) << std::endl;  // 输出: Green
    return 0;
}
```

## 2. 总结

- 如果你只需要打印 `enum class` 的整数值，可以使用 `static_cast<int>` 进行显式转换。
- 如果你需要打印 `enum class` 的名称，可以使用 `switch` 语句或映射（`std::map`）来实现。

选择哪种方法取决于你的具体需求。
