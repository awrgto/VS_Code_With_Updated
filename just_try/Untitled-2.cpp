#include <iostream>
char* afunc(char* a, char* b);
int main( ) {
    double r = 0.001, sum = 0;
    //long n = 50, p = 10000;
    std::cout << sizeof(sum + sum * r) << std::endl;
    std::cout << sizeof((1.0l + r)) << std::endl;
    std::cout << sizeof((1.0f + r)) << std::endl;
    std::cout << sizeof((1 + r)) << std::endl;

    char a[] = "12345", b[] = "12345";
    std::cout <<*afunc(a,b)<<std::endl;
}

char* afunc(char* a,char* b){
    int i = 0;
    for (; a[i] != '\0'; i++)
        if (a[i] != b[i]) break;
    return &b[i];
}