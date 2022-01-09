#include <iostream>
#include <vector>
#include <string>
#include <cstdarg>
#include <iterator>
#include <map>
#include <unordered_map>
#include <boost/variant.hpp>

#define let auto
#define none ...
#define object Object
// #define values value
// #define values "v",




class value{

    
    std::vector<boost::variant<int, float>> values;

public:
    value operator,(boost::variant val){

        value.values.push(val);

    }
};

/**  */
class Object{

    /**  */
    std::unordered_map<std::string, boost::variant<int, double, std::string, bool, Object, void*>> values_umap;


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
};



