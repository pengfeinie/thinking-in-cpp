#include <memory>
#include <iostream>
#include <string>

std::unique_ptr<int> func(int val)
{
    std::unique_ptr<int> up(new int(val));
    return up;
}

void print_value(std::unique_ptr<int> up)
{
    std::cout << *(up.get()) << std::endl;
}

void print_value_v2(std::unique_ptr<int>& up)
{
    std::cout << *(up.get()) << std::endl;
}


int main()
{
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

    std::unique_ptr<int> sp5 = std::make_unique<int>(123456);
    // print_value(sp5); // error, can't implicitly invoke move constructor on lvalue
    print_value(std::move(sp5)); // OK but don't use sp5 afterwards

    std::unique_ptr<int> sp6 = std::make_unique<int>(12345678);
    print_value_v2(sp6);

    // std::unique_ptr<int> sp1 = func(123);
    // std::cout << *(sp1.get()) << std::endl;
    return 0;
}

// g++ test_unique_01.cpp -std=c++14 -o test_unique_01