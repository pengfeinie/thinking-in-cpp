


int add(int x, int y)
{
    return x + y;
}

int main(int argc, char const *argv[])
{
    // 1.左值引用只能引用左值
    int t = 8;
    int& rt1 = t;
    //int& rt2 = 8; // 编译报错，因为8是右值，左值引用不能直接引用右值

    // 2.但是const左值引用既可以引用左值
    const int& rt3 = t;
    const int& rt4 = 8; // 也可以引用右值 const int& rt4本质上也是一个常量，指向一个不能被修改的右值，也是安全的

    int x = 20;
    int y = 30;   
    const double& r1 = x + y;
    const double& r2 = add(x, y);
    return 0;
}


// int main(int argc, char const *argv[])
// {
//     int a = 10;
//     int* p = &a;
//     int b = 20;

//     // 以下几个是对上面左值的左值引用
//     int& ra = a;
//     int*& rp = p;
//     int& r = *p;
//     const int& rb = b;


//     int x = 20;
//     int y = 30;

//     // 以下几个是右值引用
//     int&& rr1 = 10;
//     double&& rr2 = x + y;
//     double&& rr3 = add(x, y);
//     return 0;
// }
