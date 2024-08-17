#include <memory>
#include <iostream>
#include <string>
#include <iostream>
#include <memory>

class Person
{

    private:
        int age;

    public: 
        void setAge(int age)
        {
            this->age = age;
        }

        int getAge()
        {
            return age;
        }
};

int main()
{
    Person p1;
    p1.setAge(20);

    Person& p2 = p1;
    p2.setAge(30);

    std::cout << "p1 address" << &p1 <<std::endl;
    std::cout << "p2 address" << &p2 <<std::endl;

    return 0;
}

// g++ test_weak_ptr_02.cpp -std=c++14 -o test_weak_ptr_02