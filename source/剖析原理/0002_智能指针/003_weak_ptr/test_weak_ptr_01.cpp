#include <memory>
#include <iostream>
#include <string>




#include <iostream>
#include <memory>

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

// g++ test_weak_ptr_01.cpp -std=c++14 -o test_weak_ptr_01