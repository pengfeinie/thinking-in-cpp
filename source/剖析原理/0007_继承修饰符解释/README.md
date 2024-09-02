# 第8章 继承修饰符解释

在C++中，子类继承父类时，使用冒号（`:`）后面的访问说明符（public、private、protected）来指定继承的类型。这些访问说明符决定了父类的成员在子类中的访问权限。具体区别如下：

## 1. 继承方式

###  1.1 public 继承

当使用 public 继承时，父类的 public 成员在子类中仍然是 public 的，父类的 protected 成员在子类中仍然是 protected 的，而父类的 private 成员在子类中不可访问。

```c++
class Base {
    public:
        int publicMember;
    protected:
        int protectedMember;
    private:
        int privateMember;
};

class Derived : public Base {
    // publicMember 仍然是 public
    // protectedMember 仍然是 protected
    // privateMember 不可访问
};
```

###  1.2 protected 继承

当使用 protected 继承时，父类的 public 成员在子类中变为 protected 的，父类的 protected 成员在子类中仍然是 protected 的，而父类的 private 成员在子类中不可访问。

```c++
class Derived : protected Base {
    // publicMember 变为 protected
    // protectedMember 仍然是 protected
    // privateMember 不可访问
};
```

### 1.3 private 继承

当使用 private 继承时，父类的 public 成员和 protected 成员在子类中都变为 private 的，而父类的 private 成员在子类中不可访问。

```c++
class Derived : private Base {
    // publicMember 变为 private
    // protectedMember 变为 private
    // privateMember 不可访问
};
```

## 2. 总结

- **public 继承**：保持父类成员的原有访问权限。
- **protected 继承**：将父类的 public 成员变为 protected，其他成员保持不变。
- **private 继承**：将父类的 public 和 protected 成员都变为 private。

选择哪种继承方式取决于设计需求。通常，public 继承是最常用的，因为它保持了接口的可见性，符合面向对象编程中的“is-a”关系。protected 和 private 继承更多用于实现细节的隐藏，适用于更复杂的继承层次结构。

## 3. 继承中的单例问题

### 3.1 子类继承父类，父类要求是单例，子类也要求是单例

在C++中，实现单例模式通常需要确保类的构造函数是私有的，并且提供一个静态方法来获取类的唯一实例。当子类继承父类并且两者都要求是单例时，我们需要确保每个类的实例都是唯一的。

以下是一个示例，展示了如何在C++中实现一个父类和子类的单例模式：

```c++
#include <iostream>
#include <memory>
#include <mutex>

// 父类单例模板
template <typename T>
class Singleton {
public:
    static T& getInstance() {
        static T instance;
        return instance;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;

private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

// 父类
class Parent : public Singleton<Parent> {
    friend class Singleton<Parent>; // 允许Singleton模板访问私有构造函数
private:
    Parent() {
        std::cout << "Parent constructor called" << std::endl;
    }

public:
    ~Parent() {
        std::cout << "Parent destructor called" << std::endl;
    }

    void show() {
        std::cout << "Parent show method called" << std::endl;
    }
};

// 子类
class Child : public Parent, public Singleton<Child> {
    friend class Singleton<Child>; // 允许Singleton模板访问私有构造函数
private:
    Child() {
        std::cout << "Child constructor called" << std::endl;
    }

public:
    ~Child() {
        std::cout << "Child destructor called" << std::endl;
    }

    void show() {
        std::cout << "Child show method called" << std::endl;
    }
};

int main() {
    Parent::getInstance().show();
    Child::getInstance().show();

    return 0;
}
```

在这个示例中：

1. `Singleton` 是一个模板类，用于确保任何继承它的类都是单例的。它提供了一个静态方法 `getInstance` 来获取类的唯一实例。
2. `Parent` 类继承自 `Singleton<Parent>`，并且它的构造函数是私有的，以确保只有 `Singleton` 模板可以创建它的实例。
3. `Child` 类继承自 `Parent` 和 `Singleton<Child>`，并且它的构造函数也是私有的。

通过这种方式，我们可以确保 `Parent` 和 `Child` 类都是单例的，并且每个类的实例都是唯一的。在 `main` 函数中，我们分别获取 `Parent` 和 `Child` 的实例并调用它们的 `show` 方法。

## 4. vritual 函数，子类在实现时，想要分文件编写，该如何处理?

在C++中，如果你有一个基类中的虚函数，并且希望在子类中分文件编写实现，你可以按照以下步骤进行处理：

1. **基类声明**：在基类的头文件中声明虚函数。
2. **子类声明**：在子类的头文件中继承基类并声明虚函数的重写。
3. **子类实现**：在子类的源文件中实现虚函数。

下面是一个具体的例子：

基类头文件 (`Base.h`)

```c++
#ifndef BASE_H
#define BASE_H

class Base {
public:
    virtual void virtualFunction() = 0; // 纯虚函数
    virtual ~Base() = default; // 虚析构函数
};

#endif // BASE_H
```

子类头文件 (`Derived.h`)

```c++
#ifndef DERIVED_H
#define DERIVED_H

#include "Base.h"

class Derived : public Base {
public:
    void virtualFunction() override; // 声明重写的虚函数
};

#endif // DERIVED_H
```

子类源文件 (`Derived.cpp`)

```c++
#include "Derived.h"
#include <iostream>

void Derived::virtualFunction() {
    std::cout << "Derived virtualFunction implementation" << std::endl;
}
```

主程序文件 (`main.cpp`)

```c++
#include "Derived.h"

int main() {
    Base* basePtr = new Derived();
    basePtr->virtualFunction();
    delete basePtr;
    return 0;
}
```

### 解释

1. **基类声明**：在 `Base.h` 中，我们声明了一个纯虚函数 `virtualFunction`，这使得 `Base` 成为一个抽象类。同时，我们声明了一个虚析构函数，以确保在删除基类指针时能够正确调用子类的析构函数。
2. **子类声明**：在 `Derived.h` 中，我们继承了 `Base` 类，并声明了 `virtualFunction` 的重写。
3. **子类实现**：在 `Derived.cpp` 中，我们实现了 `virtualFunction` 的具体逻辑。
4. **主程序文件**：在 `main.cpp` 中，我们创建了一个 `Derived` 类的实例，并调用其虚函数。

通过这种方式，你可以将虚函数的声明和实现分文件编写，保持代码的模块化和清晰。

