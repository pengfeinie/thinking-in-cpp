# 第8章 匈牙利算法详解与实现

匈牙利算法是一种高效的**二分图最大匹配**或**最优分配**算法，常用于解决任务分配问题，例如将工人分配给任务以最小化成本。该算法通过多步矩阵操作和调整来寻找最优匹配，保证了分配成本的最小化。

## **1.算法概述**

### 1.1 矩阵减法

首先对矩阵进行行列减法：

- **行减法**：每行减去该行的最小值，使每行至少有一个零。

```c++
void step1(){
	for (int row = 0; row < costMatrix_.rows(); ++row) {
    	double minVal = costMatrix_.row(row).minCoeff();
    	Eigen::VectorXd scalarVector = Eigen::VectorXd::Constant(costMatrix_.cols(), min_val);
    	costMatrix_.row(row) -= scalarVector.transpose();
	}
}
```

这段代码使用了一个循环来处理一个矩阵 `cost_matrix_`，并对每一行进行操作。具体来说，它对矩阵的每一行进行了归约操作，使得每一行的最小值变为零。以下是代码的详细分析：

**代码分析**

1. **循环遍历每一行**：

   ```c++
   for (int row = 0; row < costMatrix_.rows(); ++row)
   ```

   这段代码使用了一个 `for` 循环，遍历矩阵 `costMatrix_` 的每一行。`row` 是当前行的索引，从 0 开始。

2. **找到当前行的最小值**：

   ```
   double minVal = costMatrix_.row(row).minCoeff();
   ```

   在循环的每一次迭代中，代码首先找到当前行 `row` 中的最小值，并将其存储在变量 `minVal` 中。`minCoeff()` 是 Eigen 库中的一个函数，用于返回向量或矩阵中的最小值。

3. **创建一个常量向量**：

   ```
   Eigen::VectorXd scalarVector = Eigen::VectorXd::Constant(costMatrix_.cols(), minVal);
   ```

   接下来，代码创建了一个与当前行长度相同的向量 `scalarVector`，这个向量的所有元素都被设置为 `minVal`。`Eigen::VectorXd::Constant` 是 Eigen 库中的一个静态函数，用于创建一个所有元素都相同的向量(列向量)。

4. **减去常量向量**：

   ```
   costMatrix_.row(row) -= scalarVector.transpose();
   ```

   最后，代码将当前行的每个元素减去 `minVal`。`scalarVector.transpose()` 是将 `scalarVector` 转置为行向量，以便与矩阵的行进行减法操作。`-=` 是 Eigen 库中的运算符重载，用于就地减法操作。

**总结**

这段代码的作用是对矩阵 `costMatrix_` 的每一行进行归约操作，使得每一行的最小值变为零。具体步骤如下：

1. 遍历矩阵的每一行。
2. 找到当前行的最小值。
3. 创建一个与当前行长度相同的常量向量，所有元素都等于最小值。
4. 将当前行的每个元素减去这个常量向量。

最终，矩阵 `costMatrix_` 的每一行的最小值都会变为零，而其他元素则相应地减去了该行的最小值。



- **列减法**：在行减法的基础上，每列再减去该列的最小值，使每列至少有一个零。





### 2. 划线覆盖零元素

用尽量少的直线（横线或竖线）覆盖矩阵中的所有零元素。如果划线数量等于矩阵维度，则已找到最优解，否则进入下一步。

### 3. 调整矩阵

找到未被线覆盖的最小元素并调整矩阵：

- 未被覆盖的元素减去最小值。
- 交叉线的交点元素加上最小值。
- 其他已被线覆盖的元素保持不变。

### 4. 寻找匹配

使用调整后的矩阵寻找最优匹配。优先选择那些行或列中只有一个零的元素进行匹配。

### 5. 计算最小成本

根据原始成本矩阵，计算匹配方案的总成本。
