# 第7章 如何判断两辆车的行驶方向

## 1.如何判断两个车子是不是通向行使

要判断两个车子是否同向行驶，我们可以通过比较它们的航向角（heading）来实现。航向角通常表示车辆行驶的方向，通常以度数表示，范围从0度到360度。如果两个车子的航向角相差不大，我们可以认为它们是同向行驶的。

以下是一个简单的C++实现，假设我们有两个车子的航向角，并判断它们是否同向行驶：

```c++
#include <iostream>
#include <cmath>

// 定义一个小的阈值，用于判断两个航向角是否接近
const double THRESHOLD = 10.0; // 例如，10度以内的差异认为是同向行驶

// 函数：判断两个航向角是否同向行驶
bool isSameDirection(double heading1, double heading2) {
    // 计算两个航向角的差值
    double diff = std::abs(heading1 - heading2);

    // 如果差值小于阈值，认为是同向行驶
    if (diff <= THRESHOLD) {
        return true;
    }

    // 考虑航向角跨越0度和360度的情况
    if (diff > 180.0) {
        diff = 360.0 - diff;
    }

    return diff <= THRESHOLD;
}

int main() {
    double heading1, heading2;

    // 输入两个车子的航向角
    std::cout << "Enter the heading of car 1 (in degrees): ";
    std::cin >> heading1;

    std::cout << "Enter the heading of car 2 (in degrees): ";
    std::cin >> heading2;

    // 判断是否同向行驶
    if (isSameDirection(heading1, heading2)) {
        std::cout << "The two cars are moving in the same direction." << std::endl;
    } else {
        std::cout << "The two cars are moving in different directions." << std::endl;
    }

    return 0;
}
```

代码解释：

1. **THRESHOLD**: 这是一个阈值，用于判断两个航向角是否接近。如果两个航向角的差值小于这个阈值，我们认为它们是同向行驶的。
2. **isSameDirection函数**: 这个函数接受两个航向角作为参数，并返回一个布尔值，表示它们是否同向行驶。
   - 首先计算两个航向角的绝对差值。
   - 如果差值小于阈值，直接返回`true`。
   - 如果差值大于180度，说明航向角跨越了0度和360度的边界，此时我们需要计算360度减去差值，再判断是否小于阈值。
3. **main函数**: 用户输入两个车子的航向角，然后调用`isSameDirection`函数判断它们是否同向行驶，并输出结果。

示例：

假设输入的航向角分别为45度和50度，程序会输出：

```bash
The two cars are moving in the same direction.
```

假设输入的航向角分别为45度和135度，程序会输出：

```bash
The two cars are moving in different directions.
```

这个实现考虑了航向角跨越0度和360度的情况，确保了判断的准确性。

## 2.如何判断两个车子是不是逆向行使

要判断两个车子是否逆向行驶，我们可以通过比较它们的航向角（heading）来实现。逆向行驶意味着两个车子的航向角相差大约180度。

以下是一个简单的C++实现，假设我们有两个车子的航向角，并判断它们是否逆向行驶：

```c++
#include <iostream>
#include <cmath>

// 定义一个小的阈值，用于判断两个航向角是否接近180度
const double THRESHOLD = 10.0; // 例如，10度以内的差异认为是逆向行驶

// 函数：判断两个航向角是否逆向行驶
bool isOppositeDirection(double heading1, double heading2) {
    // 计算两个航向角的差值
    double diff = std::abs(heading1 - heading2);

    // 如果差值接近180度，认为是逆向行驶
    if (std::abs(diff - 180.0) <= THRESHOLD) {
        return true;
    }

    // 考虑航向角跨越0度和360度的情况
    if (diff > 180.0) {
        diff = 360.0 - diff;
    }

    return std::abs(diff - 180.0) <= THRESHOLD;
}

int main() {
    double heading1, heading2;

    // 输入两个车子的航向角
    std::cout << "Enter the heading of car 1 (in degrees): ";
    std::cin >> heading1;

    std::cout << "Enter the heading of car 2 (in degrees): ";
    std::cin >> heading2;

    // 判断是否逆向行驶
    if (isOppositeDirection(heading1, heading2)) {
        std::cout << "The two cars are moving in opposite directions." << std::endl;
    } else {
        std::cout << "The two cars are not moving in opposite directions." << std::endl;
    }

    return 0;
}
```

代码解释：

1. **THRESHOLD**: 这是一个阈值，用于判断两个航向角是否接近180度。如果两个航向角的差值与180度的差值小于这个阈值，我们认为它们是逆向行驶的。
2. **isOppositeDirection函数**: 这个函数接受两个航向角作为参数，并返回一个布尔值，表示它们是否逆向行驶。
   - 首先计算两个航向角的绝对差值。
   - 如果差值与180度的差值小于阈值，直接返回`true`。
   - 如果差值大于180度，说明航向角跨越了0度和360度的边界，此时我们需要计算360度减去差值，再判断是否与180度的差值小于阈值。
3. **main函数**: 用户输入两个车子的航向角，然后调用`isOppositeDirection`函数判断它们是否逆向行驶，并输出结果。

示例：

假设输入的航向角分别为45度和225度，程序会输出：

```bash
The two cars are moving in opposite directions.
```

假设输入的航向角分别为45度和50度，程序会输出：

```bash
The two cars are not moving in opposite directions.
```

这个实现考虑了航向角跨越0度和360度的情况，确保了判断的准确性。

## 3.如何判断两个车子是不是十字路口的交叉行使

要判断两个车子是否在十字路口交叉行驶，我们可以通过分析它们的航向角（heading）来实现。交叉行驶意味着两个车子的航向角相差大约90度或270度。

以下是一个简单的C++实现，假设我们有两个车子的航向角，并判断它们是否在十字路口交叉行驶：

```c++
#include <iostream>
#include <cmath>

// 定义一个小的阈值，用于判断两个航向角是否接近90度或270度
const double THRESHOLD = 10.0; // 例如，10度以内的差异认为是交叉行驶

// 函数：判断两个航向角是否交叉行驶
bool isCrossingDirection(double heading1, double heading2) {
    // 计算两个航向角的差值
    double diff = std::abs(heading1 - heading2);

    // 如果差值接近90度或270度，认为是交叉行驶
    if (std::abs(diff - 90.0) <= THRESHOLD || std::abs(diff - 270.0) <= THRESHOLD) {
        return true;
    }

    // 考虑航向角跨越0度和360度的情况
    if (diff > 180.0) {
        diff = 360.0 - diff;
    }

    return std::abs(diff - 90.0) <= THRESHOLD || std::abs(diff - 270.0) <= THRESHOLD;
}

int main() {
    double heading1, heading2;

    // 输入两个车子的航向角
    std::cout << "Enter the heading of car 1 (in degrees): ";
    std::cin >> heading1;

    std::cout << "Enter the heading of car 2 (in degrees): ";
    std::cin >> heading2;

    // 判断是否交叉行驶
    if (isCrossingDirection(heading1, heading2)) {
        std::cout << "The two cars are moving in crossing directions." << std::endl;
    } else {
        std::cout << "The two cars are not moving in crossing directions." << std::endl;
    }

    return 0;
}
```

代码解释：

1. **THRESHOLD**: 这是一个阈值，用于判断两个航向角是否接近90度或270度。如果两个航向角的差值与90度或270度的差值小于这个阈值，我们认为它们是交叉行驶的。
2. **isCrossingDirection函数**: 这个函数接受两个航向角作为参数，并返回一个布尔值，表示它们是否交叉行驶。
   - 首先计算两个航向角的绝对差值。
   - 如果差值与90度或270度的差值小于阈值，直接返回`true`。
   - 如果差值大于180度，说明航向角跨越了0度和360度的边界，此时我们需要计算360度减去差值，再判断是否与90度或270度的差值小于阈值。
3. **main函数**: 用户输入两个车子的航向角，然后调用`isCrossingDirection`函数判断它们是否交叉行驶，并输出结果。

示例：

假设输入的航向角分别为45度和135度，程序会输出：

Copy code

```bash
The two cars are moving in crossing directions.
```

假设输入的航向角分别为45度和50度，程序会输出：

Copy code

```bash
The two cars are not moving in crossing directions.
```

这个实现考虑了航向角跨越0度和360度的情况，确保了判断的准确性。
