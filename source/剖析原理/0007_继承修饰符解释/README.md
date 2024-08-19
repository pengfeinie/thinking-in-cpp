# 继承修饰符解释

在C++中，子类继承父类时，使用冒号（`:`）后面的访问说明符（`public`、`private`、`protected`）来指定继承的类型。这些访问说明符决定了父类的成员在子类中的访问权限。具体区别如下：

##  `public` 继承

当使用 `public` 继承时，父类的 `public` 成员在子类中仍然是 `public` 的，父类的 `protected` 成员在子类中仍然是 `protected` 的，而父类的 `private` 成员在子类中不可访问。

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

##  `protected` 继承

当使用 `protected` 继承时，父类的 `public` 成员在子类中变为 `protected` 的，父类的 `protected` 成员在子类中仍然是 `protected` 的，而父类的 `private` 成员在子类中不可访问。

```c++
class Derived : protected Base {
    // publicMember 变为 protected
    // protectedMember 仍然是 protected
    // privateMember 不可访问
};
```

## `private` 继承

当使用 `private` 继承时，父类的 `public` 成员和 `protected` 成员在子类中都变为 `private` 的，而父类的 `private` 成员在子类中不可访问。

```c++
class Derived : private Base {
    // publicMember 变为 private
    // protectedMember 变为 private
    // privateMember 不可访问
};
```

## 总结

- **`public` 继承**：保持父类成员的原有访问权限。
- **`protected` 继承**：将父类的 `public` 成员变为 `protected`，其他成员保持不变。
- **`private` 继承**：将父类的 `public` 和 `protected` 成员都变为 `private`。

选择哪种继承方式取决于设计需求。通常，`public` 继承是最常用的，因为它保持了接口的可见性，符合面向对象编程中的“is-a”关系。`protected` 和 `private` 继承更多用于实现细节的隐藏，适用于更复杂的继承层次结构。