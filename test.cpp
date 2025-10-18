#incldue <iostream>
#include "mystring.h"

int main() {
    MyString s1("Hello");
    MyString s2("World");
    MyString s3 = s1 + s2;
    std::cout << s3 << std::endl; // Output: HelloWorld

    MyString s4("Hello");
    MyString s5("World");           
}