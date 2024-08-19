# 智能指针

C/C++ 语言最为人所诟病的特性之一就是存在内存泄露问题，因此后来的大多数语言都提供了内置内存分配与释放功能，有的甚至干脆对语言的使用者屏蔽了内存指针这一概念。这里不置贬褒，手动分配内存与手动释放内存有利也有弊，自动分配内存和自动释放内存亦如此，这是两种不同的设计哲学。有人认为，内存如此重要的东西怎么能放心交给用户去管理呢？而另外一些人则认为，内存如此重要的东西怎么能放心交给系统去管理呢？在 C/C++ 语言中，内存泄露的问题一直困扰着广大的开发者，因此各类库和工具的一直在努力尝试各种方法去检测和避免内存泄露，如 boost，智能指针技术应运而生。

C++11 中推出了三种智能指针，unique_ptr、shared_ptr 和 weak_ptr，同时也将 auto_ptr 置为废弃 (deprecated)。

理解智能指针需要从下面三个层次：

- 从较浅的层面看，智能指针是利用了一种叫做RAII（资源获取即初始化）的技术对普通的指针进行封装，这使得智能指针实质是一个对象，行为表现的却像一个指针。
- 智能指针的作用是防止忘记调用delete释放内存和程序异常的进入catch块忘记释放内存。另外指针的释放时机也是非常有考究的，多次释放同一个指针会造成程序崩溃，这些都可以通过智能指针来解决。
- 智能指针还有一个作用是把值语义转换成引用语义。

## C++ 98/03 的尝试——std::auto_ptr

在 2019 年讨论 **std::auto_ptr** 不免有点让人怀疑是不是有点过时了，确实如此，随着 C++11 标准的出现（最新标准是 C++20），**std::auto_ptr** 已经被彻底废弃了，取而代之是 **std::unique_ptr**。然而，我之所以还向你介绍一下 **std::auto_ptr** 的用法以及它的设计不足之处是想让你了解 C++ 语言中智能指针的发展过程，一项技术如果我们了解它过去的样子和发展的轨迹，我们就能更好地掌握它，不是吗？**std::auto_ptr** 的基本用法如下代码所示：

```c++
#include <memory>

int main()
{
    //初始化方式1
    std::auto_ptr<int> sp1(new int(8));
    //初始化方式2
    std::auto_ptr<int> sp2;
    sp2.reset(new int(8));

    return 0;
}
```

智能指针对象 **sp1** 和 **sp2** 均持有一个在堆上分配的 int 对象，其值均是 8，这两块堆内存均可以在 **sp1** 和 **sp2** 释放时得到释放。这是 **std::auto_ptr** 的基本用法。

**std::auto_ptr** 真正让人容易误用的地方是其不常用的复制语义，即当复制一个 **std::auto_ptr** 对象时（拷贝复制或 operator = 复制），原对象所持有的堆内存对象也会转移给复制出来的对象。示例代码如下：

```c++
#include <iostream>
#include <memory>

int main()
{
    //测试拷贝构造
    std::auto_ptr<int> sp1(new int(8));
    std::auto_ptr<int> sp2(sp1);
    if (sp1.get() != NULL)
    {
        std::cout << "sp1 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp1 is empty." << std::endl;
    }

    if (sp2.get() != NULL)
    {
        std::cout << "sp2 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp2 is empty." << std::endl;
    }

    //测试赋值构造
    std::auto_ptr<int> sp3(new int(8));
    std::auto_ptr<int> sp4;
    sp4 = sp3;
    if (sp3.get() != NULL)
    {
        std::cout << "sp3 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp3 is empty." << std::endl;
    }

    if (sp4.get() != NULL)
    {
        std::cout << "sp4 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp4 is empty." << std::endl;
    }

    return 0;
}
```

上述代码中分别利用拷贝构造和赋值构造来创建新的 std::auto_ptr 对象，因此 sp1 持有的堆对象被转移给 sp2，sp3 持有的堆对象被转移给 sp4。我们得到程序执行结果如下：

由于 **std::auto_ptr** 这种不常用的复制语义，我们应该避免在 stl 容器中使用 **std::auto_ptr**，例如我们绝不应该写出如下代码：

```
std::vector<std::auto_ptr<int>> myvectors;
```

当用算法对容器操作的时候（如最常见的容器元素遍历），很难避免不对容器中的元素实现赋值传递，这样便会使容器中多个元素被置为空指针，这不是我们想看到的，会造成很多意想不到的错误。

以史为鉴，作为 **std::auto_ptr** 的替代者 **std::unique_ptr** 吸取了这个经验教训。下文会来详细介绍。

正因为 **std::auto_ptr** 的设计存在如此重大缺陷，C++11 标准在充分借鉴和吸收了 boost 库中智能指针的设计思想，引入了三种类型的智能指针，即 **std::unique_ptr**、**std::shared_ptr** 和 **std::weak_ptr**。

## std::unique_ptr

**std::unique_ptr** 对其持有的堆内存具有唯一拥有权，也就是说引用计数永远是 1，**std::unique_ptr** 对象销毁时会释放其持有的堆内存。同一时刻只能有一个unique_ptr指向给定对象(通过禁止拷贝语义，赋值语义，只有移动语义来实现) . 相比于原始指针, unique_ptr用于其RAII的特性，使得在出现异常的情况下，动态资源能得到释放。

unique_ptr指针本身的生命周期：从unique_ptr指针创建时开始，直到离开作用域。离开作用域时，若其指向对象，则将其所指对象销毁（默认使用delete操作符，用户可指定其他操作）。

unique_ptr指针与其所指对象的关系：在智能指针生命周期内，可以改变智能指针所指对象，如创建智能指针时通过构造函数指定、通过reset方法重新指定、通过release方法释放所有权、通过移动语义转移所有权。

可以使用以下方式初始化一个 **std::unique_ptr** 对象：

```c++
//初始化方式1
std::unique_ptr<int> sp1(new int(123));
std::cout << " *(sp1.get()) = " << *(sp1.get()) << std::endl;
sp1.release();
std::cout << " after release, (sp1.get() == nullptr) = " << (sp1.get() == nullptr) << std::endl;
sp1.reset(new int(456));
std::cout << " after reset, *(sp1.get()) = " << *(sp1.get()) << std::endl;

//初始化方式2
std::unique_ptr<int> sp2;
std::cout << " (sp2.get() == nullptr) = " << (sp2.get() == nullptr) << std::endl;
sp2.reset(new int(123));
std::cout << " after reset, *(sp2.get()) = " << *(sp2.get()) << std::endl;

//初始化方式3
std::unique_ptr<int> sp3 = std::make_unique<int>(123);
std::unique_ptr<int> sp4(std::make_unique<int>(1234));
std::cout << *(sp3.get()) << std::endl;
std::cout << *(sp4.get()) << std::endl;
```

你应该尽量使用初始化方式 3 的方式去创建一个 **std::unique_ptr** 而不是方式 1 和 2，因为形式 3 更安全。

鉴于 **std::auto_ptr** 的前车之鉴，**std::unique_ptr** 禁止复制语义，为了达到这个效果，**std::unique_ptr** 类的拷贝构造函数和赋值运算符（operator =）被标记为 **delete**。

因此，下列代码是无法通过编译的：

```c++
std::unique_ptr<int> sp1(std::make_unique<int>(123));
//以下代码无法通过编译
//std::unique_ptr<int> sp2(sp1);
std::unique_ptr<int> sp3;
//以下代码无法通过编译
//sp3 = sp1;
```

禁止复制语义也存在特例，即可以通过一个函数返回一个 std::unique_ptr.

```c++
#include <memory>

std::unique_ptr<int> func(int val)
{
    std::unique_ptr<int> up(new int(val));
    return up;
}

int main()
{
    std::unique_ptr<int> sp1 = func(123);
    return 0;
}
```

上述代码从 func 函数中得到一个 **std::unique_ptr** 对象，然后返回给 sp1。

既然 **std::unique_ptr** 不能复制，那么如何将一个 **std::unique_ptr** 对象持有的堆内存转移给另外一个呢？答案是使用移动构造：

```c++
#include <memory>

int main()
{
    std::unique_ptr<int> sp1(std::make_unique<int>(123));
    std::unique_ptr<int> sp2(std::move(sp1));
    std::unique_ptr<int> sp3;
    sp3 = std::move(sp2);
    return 0;
}
```

以上代码利用 std::move 将 sp1 持有的堆内存（值为 123）转移给 sp2，再把 sp2 转移给 sp3。最后，sp1 和 sp2 不再持有堆内存的引用，变成一个空的智能指针对象。并不是所有的对象的 std::move 操作都有意义，只有实现了移动构造函数（Move Constructor）或移动赋值运算符（operator =）的类才行，而 **std::unique_ptr** 正好实现了这二者。

这绝不是特定于std::unique_ptr，而是适用于任何可移动的类。因为标准允许编译器这么做：

- 如果支持move构造，那么调用move构造。
- 如果不支持move，那就调用copy构造。
- 如果不支持copy，那就报错吧。

**拷贝构造和拷贝赋值**

首先，让我们复习一下拷贝语义(`copy semantics`)

**拷贝构造函数** 通过创建一份该类的拷贝来初始化一个类。**拷贝赋值运算符** 通过拷贝一个已存在类对象，创建一个新的对象。默认情况下，如果一个类没有显式的提供，C++ 将会默认提供拷贝构造函数和拷贝赋值函数。这些由编译器提供的函数仅实现了浅拷贝，在进行动态分配内存的类对象上使用可能造成问题。因此在涉及动态内存分配的类必须通过重写这些函数来进行深拷贝。

**移动构造和移动赋值**

C++ 定义了两个新的函数来实现 **“移动语义”**：一个是 **移动构造函数**，一个是 **移动赋值操作符** 。

拷贝构造函数的和拷贝赋值函数的目标是创建一份对象的拷贝到另一个对象，移动构造函数和移动赋值赋值运算符是来移动资源的 **所有权(ownership)** ，从一个对象到另一个对象（这样做消耗的资源少很多）。

定义一个移动构造函数和一个移动赋值函数和拷贝的同类函数所实现的目的相似。然而，这些复制函数的风格采用 **常量左值引用** 参数，移动函数的风格使用了 **非常量右值引用** 参数。

**何时调用移动构造函数和移动赋值运算符**

如果你有一个接受std::unique_ptr作为参数的函数，你将无法将sp5传递给它。您必须显式调用move构造函数，但在这种情况下，在调用print_value()之后不应使用变量sp5。

```c++
void print_value(std::unique_ptr<int> up)
{
    std::cout << *(up.get()) << std::endl;
}

int main()
{
    std::unique_ptr<int> sp5 = std::make_unique<int>(123456);
    // print_value(sp5); // error, can't implicitly invoke move constructor on lvalue
    print_value(std::move(sp5)); // OK but don't use sp5 afterwards
    return 0;
}
```

我们可以使用引用来解决这个问题。

```c++
void print_value_v2(std::unique_ptr<int>& up)
{
    std::cout << *(up.get()) << std::endl;
}

int main()
{
    std::unique_ptr<int> sp6 = std::make_unique<int>(12345678);
    print_value_v2(sp6);
    return 0;
}
```

**为什么 unique_ptr 需要明确知道类型的析构函数**

这个问题是我写 `unique_ptr` 调试接口的时候才注意到的，之前确实不知道。为什么会这样呢？首先我们必须要知道 `unique_ptr` 到底封装了什么？通常 `unique_ptr` 就是简单的对裸指针封装，并且禁用拷贝和赋值：

## std::shared_ptr

shared_ptr多个指针指向相同的对象。shared_ptr使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。每使用他一次，内部的引用计数加1，每析构一次，内部的引用计数减1，减为0时，自动删除所指向的堆内存。shared_ptr内部的引用计数是线程安全的，但是对象的读取需要加锁。

初始化。智能指针是个模板类，可以指定类型，传入指针通过构造函数初始化。也可以使用make_shared函数初始化。不能将指针直接赋值给一个智能指针，一个是类，一个是指针。

注意不要用一个原始指针初始化多个shared_ptr，否则会造成二次释放同一内存。shared_ptr的一个最大的陷阱是循环引用，循环引用会导致堆内存无法正确释放，导致内存泄漏。

## std::weak_ptr

**std::weak_ptr** 是一个不控制资源生命周期的智能指针，是对对象的一种弱引用，只是提供了对其管理的资源的一个访问手段，引入它的目的为协助 **std::shared_ptr** 工作。很多人对`std::weak_ptr`的认识只是不增加`std::shared_ptr`的引用计数，可以用来解决`std::shared_ptr`可能造成的循环引用问题。但是，实际对它的认识还是不够深刻，本文将从几个实际应用场景讲解，深入了解这种智能指针。

**std::weak_ptr** 可以从一个 **std::shared_ptr** 或另一个 **std::weak_ptr** 对象构造，**std::shared_ptr** 可以直接赋值给 **std::weak_ptr** ，也可以通过 **std::weak_ptr** 的 **lock()** 函数来获得 **std::shared_ptr**。它的构造和析构不会引起引用计数的增加或减少。**std::weak_ptr** 可用来解决 **std::shared_ptr** 相互引用时的死锁问题（即两个**std::shared_ptr** 相互引用，那么这两个指针的引用计数永远不可能下降为 0， 资源永远不会释放）。

```c++
int main()
{
    //创建一个std::shared_ptr对象
    std::shared_ptr<int> sp1(new int(123));
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过构造函数得到一个std::weak_ptr对象
    std::weak_ptr<int> sp2(sp1);
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过赋值运算符得到一个std::weak_ptr对象
    std::weak_ptr<int> sp3 = sp1;
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过一个std::weak_ptr对象得到另外一个std::weak_ptr对象
    std::weak_ptr<int> sp4 = sp2;
    std::cout << "use count: " << sp1.use_count() << std::endl;

    //通过std::weak_ptr 的 lock() 函数来获得 std::shared_ptr
    if (!sp4.expired()) {
        std::shared_ptr<int> sp5 = sp4.lock();
        std::cout << "use count: " << sp1.use_count() << std::endl;
    }
    return 0;
}
```

既然，**std::weak_ptr** 不管理对象的生命周期，那么其引用的对象可能在某个时刻被销毁了，如何得知呢？**std::weak_ptr** 提供了一个 **expired()** 方法来做这一项检测，返回 true，说明其引用的资源已经不存在了；返回 false，说明该资源仍然存在，这个时候可以使用 **std::weak_ptr** 的 **lock()** 方法得到一个 **std::shared_ptr** 对象然后继续操作资源，以上代码演示了该用法。

有读者可能对上述代码产生疑问，既然使用了 **std::weak_ptr** 的 **expired()** 方法判断了对象是否存在，为什么不直接使用 **std::weak_ptr** 对象对引用资源进行操作呢？实际上这是行不通的，**std::weak_ptr** 类没有重写 **operator->** 和 **operator*** 方法，因此不能像 **std::shared_ptr** 或 **std::unique_ptr** 一样直接操作对象，同时 **std::weak_ptr** 类也没有重写 **operator!** 操作，因此也不能通过 **std::weak_ptr** 对象直接判断其引用的资源是否存在。

之所以 **std::weak_ptr** 不增加引用资源的引用计数不管理资源的生命周期，是因为，即使它实现了以上说的几个方法，调用它们也是不安全的，因为在调用期间，引用的资源可能恰好被销毁了，这会造成棘手的错误和麻烦。

因此，**std::weak_ptr** 的正确使用场景是那些资源如果可能就使用，如果不可使用则不用的场景，它不参与资源的生命周期管理。例如，网络分层结构中，Session 对象（会话对象）利用 Connection 对象（连接对象）提供的服务工作，但是 Session 对象不管理 Connection 对象的生命周期，Session 管理 Connection 的生命周期是不合理的，因为网络底层出错会导致 Connection 对象被销毁，此时 Session 对象如果强行持有 Connection 对象与事实矛盾。

**std::weak_ptr** 的应用场景，经典的例子是订阅者模式或者观察者模式中。这里以订阅者为例来说明，消息发布器只有在某个订阅者存在的情况下才会向其发布消息，而不能管理订阅者的生命周期。

**智能指针对象的大小**

一个 **std::unique_ptr** 对象大小与裸指针大小相同（即 sizeof(std::unique_ptr) == sizeof(void*)），而 **std::shared_ptr** 的大小是 **std::unique_ptr** 的一倍。



**参考**

- [https://greedysky.github.io/2020/04/20/C++11%E4%B8%AD%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88%E7%9A%84%E5%8E%9F%E7%90%86%E8%AF%A6%E8%A7%A3/#](https://greedysky.github.io/2020/04/20/C++11%E4%B8%AD%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88%E7%9A%84%E5%8E%9F%E7%90%86%E8%AF%A6%E8%A7%A3/#)
- [https://www.cnblogs.com/Solstice/archive/2011/08/16/2141515.html](https://www.cnblogs.com/Solstice/archive/2011/08/16/2141515.html)