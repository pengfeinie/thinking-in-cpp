#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
 
void* operator new(std::size_t n) {
  std::cout << "[Allocating " << n << " bytes]";
  return malloc(n);
}
void operator delete(void* p) throw() {
  free(p);
}

std::string h("helloooo00000000000000000000000000000000000");

int main() {
  for (size_t i = 0; i < 24; ++i) {
    std::cout << i << ": " << std::string(i, '=') << std::endl;
  }
  std::cout << "/* message */" << std::endl;
  std::string* hello = new std::string("hello");  
  std::cout << "/* message */" << std::endl;
  return 0;
}

// g++ test03.cpp -o test03