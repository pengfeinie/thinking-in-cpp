#include <iostream>

class Phone{
    public:
        int number;
        Phone(){
            std::cout << "Create Phone." << std::endl;
        }
        ~Phone(){
            std::cout << "Destoried Phone." << std::endl;
        }

};


class Person{
    public:
        int age;
        Phone phone;
        Person(){
            std::cout << "Create Person." << std::endl;
        }
        ~Person(){
            std::cout << "Destoried Person." << std::endl;
        }
};


int main(int argc, char const *argv[])
{
    Person* p = new Person();
    p->age = 10;
    p->phone.number = 11111;
    
    delete p;
    
    return 0;
}

// g++ test02.cpp -o test02