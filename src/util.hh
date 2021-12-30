#include <iostream>
#include <vector>
#include <string>
#include <cstdarg>

#define let auto
#define none 0

class object{
    // vector<int> int_values;
    // vector<double> double_values;
    // vector<string> string_values;
    // vector<bool> bool_values;
    std::vector<void*> voidptr_values;

public:

    object(){
        // int x = 5;
        // double y = 3.14;
        // string z = "malaka\n";
        // bool t = 0;
        // voidptr_values.push_back((void*)&x);
        // voidptr_values.push_back((void*)&y);
        // voidptr_values.push_back((void*)&z);
        // voidptr_values.push_back((void*)&t);
        voidptr_values.push_back(none);
    }

    object(void* x, ...){

        std::va_list args;
        va_start(args, x);

    }
    
};

#define values void*
#define object[x] object(x)



