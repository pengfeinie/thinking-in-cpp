#include <iostream>

// 重定义需要注意：
//  1. 不在同一个作用域（分别位于基类、派生类）.
//  2. 函数的名字必须相同.
//  3. 对函数的返回值无要求.
//  3. 对函数的形参列表无要求.
//  4. 对函数的访问权限无要求.

class Base {
    public:
        int func1() {
            std::cout << "Base::func1" << std::endl;
            return 0;
        }
    private:
        std::string func2(int i) {
            std::cout << "Base::func2" << std::endl;
            return "base";
        }
    protected:
        void func3() {
            std::cout << "Base::func3" << std::endl;
        }
    public:
        void sayHello(){
            std::cout << "Base::sayHello()" << std::endl;
        }
        void sayHello(int i){
            std::cout << "Base::sayHello(int i)" << std::endl;
        }
        void sayHello(int i,std::string){
            std::cout << "Base::sayHello(int i,std::string)" << std::endl;
        }
        int sayHello(int i,double j){
            std::cout << "Base::sayHello(int i,double j)" << std::endl;
            return 0;
        }
        virtual void sayHello(int i,double j,std::string k){
            std::cout << "Base::sayHello(int i,double j,std::string k)" << std::endl;
        }
};

class ChildA : public Base {
    public:
        void func1() {
            std::cout << "ChildA::func1" << std::endl;
        }
        void func2() {
            std::cout << "ChildA::func2" << std::endl;
        }
        void func3() {
            std::cout << "ChildA::func3" << std::endl;
        }
        void sayHello(int i,double j){
            std::cout << "ChildA::sayHello(int i,double j)" << std::endl;
        }
};

int main(int argc, char** argv) {
    Base* ptr1 = new Base();
    Base* ptr2 = new ChildA();
    ptr1->func1(); // Base::func1
    ptr1->sayHello(1,2); // Base::sayHello(int i,double j)
    ptr2->func1(); // Base::func1
    ptr2->sayHello(1,2); // Base::sayHello(int i,double j)

    ChildA* ptr3 = new ChildA();
    ptr3->func1(); // ChildA::func1
    ptr3->func2(); // ChildA::func2
    ptr3->func3(); // ChildA::func3
    ptr3->sayHello(1,2); // ChildA::sayHello(int i,double j)
    return 0;
}

// g++ test_redefining_01.cpp -o test_redefining_01
// objdump -t test_redefining_01
