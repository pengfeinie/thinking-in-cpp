#include <iostream>
#include <cstring>


class MyString
{
    public:
        MyString() = default;

        MyString(const char* str)
        {
            std::cout << "created !" << std::endl;
            m_size = std::strlen(str);
            m_data = new char[m_size];
            std::memcpy(m_data, str, m_size);
        }

        MyString(const MyString& other)
        {
            std::cout << "copied !" << std::endl;
            m_size = other.m_size;
            m_data = new char[m_size];
            std::memcpy(m_data, other.m_data, m_size);
        }

        MyString(MyString&& other) noexcept
        {
            std::cout << "moved !" << std::endl;
            m_size = other.m_size;
            m_data = other.m_data;

            other.m_size = 0;
            other.m_data = nullptr;
        }

        ~MyString()
        {
            std::cout << "destoryed !" << std::endl;
            delete m_data;
        }

        void print()
        {
            for (uint32_t i = 0; i < m_size; i++) 
            {
                printf("%c", m_data[i]);
            }
            printf("\n");
        }

    private:
        char* m_data;
        uint32_t m_size;
};

class Entity
{
    public:
        Entity(const MyString& str)
        : m_str(str)
        {

        }

        Entity(MyString&& str)
        : m_str(std::move(str))
        {

        }

    void printName()
    {
        m_str.print();
    }
    
    private:
        MyString m_str;
};


int main(int argc, char const *argv[])
{
    Entity entity("Jimmy");
    entity.printName();

    std::cin.get();
    return 0;
}

// g++ test_move_01.cpp -std=c++14 -o test_move_01




