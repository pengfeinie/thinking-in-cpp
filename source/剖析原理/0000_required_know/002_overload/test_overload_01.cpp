#include <iostream>
#include <string>

class AA{

    public:
        // _ZN2AA3sumEii
        int sum(int a , int b){
            return a+b;
        }

        // _ZN2AA3sumEdd
        double sum(double a, double b){
            return a+b;
        }
};

int main(int argc, char const *argv[])
{
    AA a;
    std::cout << "sum(1,2)=" <<a.sum(1,2) << std::endl;
    std::cout << "sum(3.0,4.0)=" <<a.sum(3.0,4.0) << std::endl;
    return 0;
}


// 1. 编译
// g++ test_overload_01.cpp -o test_overload_01

// 2. objdump
// objdump -t test_overload_01
// 结论：通过 objdump 分析，得知重载函数的描述符的规律如下：_ZN+类长度+类名+函数名长度+函数名+E+类型首字母
