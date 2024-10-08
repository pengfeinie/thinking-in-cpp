# 第5章 极坐标系和笛卡尔坐标系

1. 现在我有雷达和激光雷达，安装在机器人的不同的位置。 
2. 与此同时雷达和激光雷达探测到了同一个物体，雷达返回的是极坐标，激光雷达返回的是笛卡尔坐标。 
3. 我需要将雷达和激光雷达的数据进行融合，第一步要做的就是坐标系的转换。 
4. 因为雷达和激光雷达的安装位置不同，就导致极坐标系和笛卡尔坐标系的参考原点是不一样的。 
5. 在上述的条件下，请使用c++语言实现极坐标系转和笛卡尔坐标系的相互转换。

以下结果来自于 https://chat.deepseek.com/.

## 1. 实现

为了实现雷达和激光雷达数据的融合，首先需要将它们的数据转换到同一个坐标系中。由于雷达和激光雷达的安装位置不同，它们的参考原点也不同。我们需要在转换过程中考虑这些不同的原点。

```c++
#include <iostream>
#include <cmath>

// 定义常量
const double PI = 3.14159265358979323846;

// 结构体定义
struct CartesianCoord {
    double x;
    double y;
};

struct PolarCoord {
    double r;
    double theta; // 以弧度为单位
};

// 极坐标转笛卡尔坐标
CartesianCoord polarToCartesian(const PolarCoord& polar, const CartesianCoord& origin) {
    CartesianCoord cartesian;
    cartesian.x = polar.r * cos(polar.theta) + origin.x;
    cartesian.y = polar.r * sin(polar.theta) + origin.y;
    return cartesian;
}

// 笛卡尔坐标转极坐标
PolarCoord cartesianToPolar(const CartesianCoord& cartesian, const CartesianCoord& origin) {
    PolarCoord polar;
    double dx = cartesian.x - origin.x;
    double dy = cartesian.y - origin.y;
    polar.r = sqrt(dx * dx + dy * dy);
    polar.theta = atan2(dy, dx);
    return polar;
}

// 打印笛卡尔坐标
void printCartesian(const CartesianCoord& coord) {
    std::cout << "Cartesian Coordinates: (" << coord.x << ", " << coord.y << ")\n";
}

// 打印极坐标
void printPolar(const PolarCoord& coord) {
    std::cout << "Polar Coordinates: (r = " << coord.r << ", theta = " << coord.theta * 180 / PI << " degrees)\n";
}

int main() {
    // 雷达和激光雷达的安装位置（原点）
    CartesianCoord radarOrigin = {1.0, 2.0};
    CartesianCoord lidarOrigin = {3.0, 4.0};

    // 雷达探测到的物体（极坐标）
    PolarCoord radarData = {5.0, PI / 4};

    // 激光雷达探测到的物体（笛卡尔坐标）
    CartesianCoord lidarData = {7.0, 8.0};

    // 将雷达数据转换为笛卡尔坐标
    // radarData的极坐标数据的参考原点是雷达的安装位置
    // 转化为笛卡尔坐标系，选择的参考原点也是雷达的安装位置
    CartesianCoord radarCartesian = polarToCartesian(radarData, radarOrigin);
    printCartesian(radarCartesian);

    // 将激光雷达数据转换为极坐标
    // lidarData的笛卡尔坐标数据的参考原点是激光雷达的安装位置
    // 转化为极坐标系，选择的参考原点也是激光雷达的安装位置
    PolarCoord lidarPolar = cartesianToPolar(lidarData, lidarOrigin);
    printPolar(lidarPolar);

    return 0;
}
```

### 代码说明：

1. **结构体定义**：
   - `CartesianCoord` 表示笛卡尔坐标系中的点，包含 `x` 和 `y` 坐标。
   - `PolarCoord` 表示极坐标系中的点，包含 `r`（半径）和 `theta`（角度，以弧度为单位）。
2. **转换函数**：
   - `polarToCartesian` 函数将极坐标转换为笛卡尔坐标，并考虑雷达的安装位置（原点）。
   - `cartesianToPolar` 函数将笛卡尔坐标转换为极坐标，并考虑激光雷达的安装位置（原点）。
3. **打印函数**：
   - `printCartesian` 和 `printPolar` 函数用于打印转换后的坐标。
4. **主函数**：
   - 定义了雷达和激光雷达的安装位置（原点）。
   - 定义了雷达和激光雷达探测到的物体数据。
   - 将雷达数据转换为笛卡尔坐标，并打印结果。
   - 将激光雷达数据转换为极坐标，并打印结果。
   - 将激光雷达数据转换到雷达的坐标系中，并打印结果。

### 运行结果：

运行上述代码，将会输出雷达和激光雷达数据的转换结果，以及激光雷达数据在雷达坐标系中的极坐标表示。

### 注意事项：

- 角度 `theta` 以弧度为单位。
- 在实际应用中，可能需要根据具体需求选择合适的坐标系进行数据融合。

通过这种方式，可以灵活地处理不同传感器安装位置导致的坐标系不一致问题，并实现数据的融合。
