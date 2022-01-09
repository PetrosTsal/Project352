#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <variant>
#include <cstdarg>
#include <iterator>
#include <map>
#include <unordered_map>

#define let auto
#define none 0

using var_t = std::variant<int, double, std::string, bool, void*>; // NA PROSTHESOYME OBJECT

class value{

    std::queue<var_t> values;

public:

    friend value operator,(var_t val);
        
};

    value operator,(var_t val){

        value.values.push(val);
        re
    }

/**  */
class Object{

    /**  */
    std::unordered_map<std::string, std::variant<int, double, std::string, bool, Object, void*>> values_umap;


public:
    /**  */
    Object(){

        std::cout << "AN EMPTY OBJECT" << std::endl;

    }
    
    /**  */
    Object(int a){

    }

    /**  */
    ~Object(){

    }

    Object operator[](value val){


        val.values

        Object.map

        // return object.some_container[str];
    }

    Object operator[](boost::variant<key, value> k){

        return Object;
    }
};

Object operator[](values val){

}

int main(){

    let x = a[value val];
    let y = object[value val1];

    Object a = Object();
    a[5];
}