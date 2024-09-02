# 第13章 如何遍历vector

在 C++ 中，遍历 `std::vector` 有多种方法，以下是几种常见的方法：

## 1. 使用范围 for 循环（C++11 及以后）

这是最简单和最推荐的方法，适用于 C++11 及以后的版本。

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for (const auto& element : vec) {
        std::cout << element << " ";
    }

    return 0;
}
```

## 2. 使用迭代器

迭代器是一种通用的遍历容器的方法，适用于所有标准容器。

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}
```

如果你使用 C++11 或更高版本，可以使用 `auto` 关键字简化代码：

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}
```

### 3. 使用索引

虽然这种方法不如前两种方法现代，但在某些情况下仍然有用。

```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }

    return 0;
}
```

### 4. 使用 `std::for_each` 算法（C++11 及以后）

`std::for_each` 是标准库中的一个算法，可以用来对容器中的每个元素执行一个函数。

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    std::for_each(vec.begin(), vec.end(), [](int element) {
        std::cout << element << " ";
    });

    return 0;
}
```

以上几种方法都可以用来遍历 `std::vector`，选择哪种方法取决于你的具体需求和个人偏好。