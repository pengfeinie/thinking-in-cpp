#include <iostream>
#include <string>

class Base{
    private:
        virtual void display() {
            std::cout<<"Base display()"<<std::endl;
        }
        
        void say() {
            std::cout<<"Base say()"<<std::endl;
        }
 
    public:
        void exec() {
            display();
            say();
        }

        void fun1(std::string a) {
            std::cout<<"Base fun1(string)"<<std::endl;
        }

        void fun1(int a) {
            std::cout<<"Base fun1(int)"<<std::endl;
        }
};
 
class ChildA:public Base{
    public:
        void display() {
            std::cout<<"ChildA display()"<<std::endl;
        }

        void fun1(int a,int b) {
            std::cout<<"ChildA fun1(int,int)"<<std::endl;
        }

        void say() {
            std::cout<<"ChildA say()"<<std::endl;
        }
};
 
class ChildB: public Base{
    public:
        void fun1(int a) {
            std::cout<<"ChildB fun1(int)"<<std::endl;
        }
};
 
int main()
{
    ChildA childa;
    Base* base=&childa;
    base->exec();   //ChildA display()
                    //Base say()
 
    childa.exec();   //ChildA display()
                    //Base say()

    childa.say(); // ChildA say()

    ChildB childb;
    childb.fun1(1); //ChildB fun1(int)
}