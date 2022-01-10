#include "util.hh"
#include <iostream>

#define key(x) g_Key(x)



int main(){

    key("a") = 5;
    std::cout << "Key: " << g_Key.getKey() << " Value: " << g_Key.getValue() << std::endl;
    return 0;
}


