#include <iostream>
#include <stdio.h>
#include <string>

const char* g1 = "Hello";
const char* g2 = "Hello";
char* g1_1 = "Hello";
char* g2_1 = "Hello";

char g3[] = "Hello";
char g4[] = "Hello";
char g3_1[] = {'H','e','l','l','o','\0'};
char g4_1[] = {'H','e','l','l','o','\0'};

std::string g5 = "Hello";
std::string g6 = "Hello";

int main(int argc, char const *argv[])
{
    const char* s1 = "Hello";
    const char* s2 = "Hello";
    char* s1_1 = "Hello";
    char* s2_1 = "Hello";

    char s3[] = "Hello";
    char s4[] = "Hello";
    char s3_1[] = {'H','e','l','l','o','\0'};
    char s4_1[] = {'H','e','l','l','o','\0'};

    std::string s5 = "Hello";
    std::string s6 = "Hello";

    printf( "全局变量--const char* g1--内存地址: %p ,字符指针g1指向Hello的内存地址:     %p\n", &g1, &(g1[0]));
    printf( "全局变量--const char* g2--内存地址: %p, 字符指针g2指向Hello的内存地址:     %p\n", &g2, &(g2[0])); 
    printf( "全局变量----- char* g1_1--内存地址: %p, 字符指针g1_1指向Hello的内存地址:   %p\n", &g1_1, &(g1_1[0])); 
    printf( "全局变量----- char* g2_1--内存地址: %p, 字符指针g2_1指向Hello的内存地址:   %p\n" , &g2_1, &(g2_1[0])); 
    printf( "局部变量--const char* s1--内存地址: %p ,字符指针s1指向Hello的内存地址:     %p\n", &s1, &(s1[0]));
    printf( "局部变量--const char* s2--内存地址: %p, 字符指针s2指向Hello的内存地址:     %p\n", &s2, &(s2[0])); 
    printf( "局部变量----- char* s1_1--内存地址: %p, 字符指针s1_1指向Hello的内存地址:   %p\n", &s1_1, &(s1_1[0])); 
    printf( "局部变量----- char* s2_1--内存地址: %p, 字符指针s2_1指向Hello的内存地址:   %p\n" , &s2_1, &(s2_1[0])); 

    printf( "全局变量-------char g3[]--内存地址: %p, 字符数组g3指向Hello的内存地址:     %p\n", &g3, &(g3[0]));
    printf( "全局变量-------char g4[]--内存地址: %p, 字符数组g4指向Hello的内存地址:     %p\n", &g4, &(g4[0]));
    printf( "全局变量-----char g3_1[]--内存地址: %p, 字符数组g3_1指向Hello的内存地址:   %p\n", &g3_1, &(g3_1[0]));
    printf( "全局变量-----char g4_1[]--内存地址: %p, 字符数组g4_1指向Hello的内存地址:   %p\n", &g4_1, &(g4_1[0])); 
    printf( "局部变量-------char s3[]--内存地址: %p, 字符数组s3指向Hello的内存地址:     %p\n", &s3, &(s3[0]));
    printf( "局部变量-------char s4[]--内存地址: %p, 字符数组s4指向Hello的内存地址:     %p\n", &s4, &(s4[0]));
    printf( "局部变量-----char s3_1[]--内存地址: %p, 字符数组s3_1指向Hello的内存地址:   %p\n", &s3_1, &(s3_1[0]));
    printf( "局部变量-----char s4_1[]--内存地址: %p, 字符数组s4_1指向Hello的内存地址:   %p\n", &s4_1, &(s4_1[0])); 

    printf( "全局变量--std::string g5--内存地址: %p, std::string g5指向Hello的内存地址: %p\n", &g5, &(g5[0])); 
    printf( "全局变量--std::string g6--内存地址: %p, std::string g6指向Hello的内存地址: %p\n", &g6, &(g6[0]));
    printf( "局部变量--std::string s5--内存地址: %p, std::string s5指向Hello的内存地址: %p\n", &s5, &(s5[0])); 
    printf( "局部变量--std::string s6--内存地址: %p, std::string s6指向Hello的内存地址: %p\n", &s6, &(s6[0])); 
    return 0;
}


// g++ test01.cpp -o test01