#include <iostream>

class AA{

    public:
        template <typename T>
        T sum(T a, T b,T c){
            return a+b+c;
        }

        template <typename T, typename Y, typename X>
        T minus(T a, Y b, X c){
            return a-b-c;
        }

};

int main(int argc, char const *argv[])
{
    AA a;
    // _ZN2AA3sumIiEET_S1_S1_S1_
    std::cout<<a.sum<int>(1,2,3)<<std::endl;
    // _ZN2AA3sumIdEET_S1_S1_S1
    std::cout<<a.sum<double>(3.0,4.0,5.0)<<std::endl;

    // _ZN2AA5minusIdifEET_S1_T0_T1
    std::cout<<a.minus<double,int,float>(10.0,2,3.0f)<<std::endl;
    // _ZN2AA5minusIidiEET_S1_T0_T1
    std::cout<<a.minus<int, double, int>(20,2.0,4)<<std::endl;

    return 0;
}


// 1. 编译
// g++ test_overload_02.cpp -o test_overload_02

// 2. objdump
// objdump -t test_overload_02
// 结论：通过objdump分析，得知模板函数的描述符的规律如下: _ZN+类长度+类名+函数名长度+函数名+I+模板类型首字母+EET+占位符。
