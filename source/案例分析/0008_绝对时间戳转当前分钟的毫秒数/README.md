# 第9章 绝对时间戳转毫秒数

要将自1970年1月1日以来的毫秒数转换为当前分钟的毫秒数，你可以使用C++的`std::chrono`库来处理时间。具体步骤如下：

1. 获取当前时间的毫秒数。
2. 计算当前时间的分钟数。
3. 计算当前分钟的毫秒数。

以下是一个示例代码：

```
#include <iostream>
#include <chrono>

int main() {
    // 获取当前时间的毫秒数
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto epoch = now_ms.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::milliseconds>(epoch);
    long long duration = value.count();

    // 计算当前时间的分钟数
    long long minutes = duration / (60 * 1000);

    // 计算当前分钟的毫秒数
    long long current_minute_ms = duration % (60 * 1000);

    std::cout << "当前分钟的毫秒数: " << current_minute_ms << std::endl;

    return 0;
}
```

### 代码解释：

1. **获取当前时间的毫秒数**：
   - `std::chrono::system_clock::now()` 获取当前时间点。
   - `std::chrono::time_point_cast<std::chrono::milliseconds>(now)` 将时间点转换为毫秒精度。
   - `time_since_epoch()` 获取自1970年1月1日以来的时间长度。
   - `std::chrono::duration_cast<std::chrono::milliseconds>(epoch)` 将时间长度转换为毫秒。
2. **计算当前时间的分钟数**：
   - `duration / (60 * 1000)` 将毫秒数转换为分钟数。
3. **计算当前分钟的毫秒数**：
   - `duration % (60 * 1000)` 获取当前分钟内的毫秒数。

### 输出：

程序将输出当前分钟内的毫秒数。

### 示例输出：

```
当前分钟的毫秒数: 34567
```

这个输出表示当前分钟已经过去了34567毫秒。
