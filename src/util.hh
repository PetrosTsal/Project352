#include <string>
#include <vector>
#include <variant>
#include <map>
#include <iostream>
#include <functional>
#include <tuple>

#define none 0

using var_t = std::variant<int, double, std::string, bool, void*>;

using var_t2 = std::variant<var_t , std::function<var_t(void)>>; 

std::map<std::string, var_t> keys_map;
std::map<std::string , var_t2 > keys_map3;
std::map<std::string, std::function<var_t(void)>> funcs_map;
std::map<std::string, std::tuple<var_t, std::function<var_t(void)>>> keys_map2 ;

class Key{

    std::string key;
    var_t value;

public:

    Key(){}

    Key operator()(std::string k){
        this->key = k;
        return *this;
    }
    
    std::map<std::string, var_t2> operator=(var_t value){
        this->value = value;
       
        keys_map3.insert({this->key, this->value});
        
        return keys_map3;
    }

    // Key operator,(Key add){
    //     g_Key.keys_map.insert({add.key, add.value});
    //     return *this;
    // }

    

    // void print_map(){

    //     var_t tmp;

    //     for(auto it = keys_map.cbegin(); it != keys_map.cend(); ++it){
    //         std::cout << it->first << " ";
    //         tmp = it->second;
    //         std::visit([](const auto &y){std::cout << y;}, tmp);
    //         std::cout << std::endl;
    //     }
    
    //     return;
    // }

    
};

class Func{

    std::string key;
    
public: 
    Func() {

    }

    Func operator()(std::string k){
        this->key = k;
        return *this;
    }

    std::map<std::string,var_t2> operator=(std::function<var_t(void)> f){
        keys_map3.insert({this->key, &f});
        return keys_map3;
    }
};

Key g_Key;
Func g_Func;

#define key(x) g_Key(x)
//#define g_Func(x) g_Func(x)


#define lambda [](void)
#define func(x) g_Func(x)=lambda
//comment

