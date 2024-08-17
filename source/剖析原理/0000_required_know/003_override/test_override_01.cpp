#include <iostream>

class Base {
    public:
        virtual void func() {
            std::cout << "Base::func" << std::endl;
        }
};

class Driver : public Base {
    public:
        void func() {
            std::cout << "Driver::func" << std::endl;
        }
};

int main(int argc, char** argv) {
    Base* ptr1 = new Base();
    Base* ptr2 = new Driver();
    ptr1->func();
    ptr2->func();
    return 0;
}

// g++ test_override_01.cpp -o test_override_01
// objdump -t test_override_01
