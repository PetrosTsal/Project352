#include <string>
#include <vector>
#include <variant>
#include <map>
#include <iostream>
#include <functional>

using var_t = std::variant<int, double, std::string, bool, void*>;

std::map<std::string, var_t> keys_map;
std::map<std::string ,var_t> funcs_map ; 

class Key{

    std::string key;
    var_t value;

public:

    Key(){}

    Key operator()(std::string k){
        this->key = k;
        return *this;
    }
    
    std::map<std::string, var_t> operator=(var_t value){
        this->value = value;
        keys_map.insert({this->key, this->value});
        return keys_map;
    }

    // Key operator,(Key add){
    //     g_Key.keys_map.insert({add.key, add.value});
    //     return *this;
    // }

    

    void print_map(){

        var_t tmp;

        for(auto it = keys_map.cbegin(); it != keys_map.cend(); ++it){
            std::cout << it->first << " ";
            tmp = it->second;
            std::visit([](const auto &y){std::cout << y;}, tmp);
            std::cout << std::endl;
        }

        for(auto it = funcs_map.cbegin(); it != funcs_map.cend(); ++it){

            std::cout <<"func(" << it->first << ")";
            tmp = it->second;
            std::cout <<"with estimated value = ";
            std::visit([](const auto &y){std::cout << y;}, tmp);
            std::cout << std::endl;
        }

    
        return;
    }

    
};

class Func{

    std::string key;
    var_t value;

public: 
    Func() {

    }

    Func operator()(std::string k){
        this->key = k;
        return *this;
    }

    std::map<std::string, var_t> operator=(std::function<var_t()> f){
        this->value = f(); 
        funcs_map.insert({this->key, this->value});
        return funcs_map;
    }

    void print_map(){
        var_t tmp ; 
        for(auto it = funcs_map.cbegin(); it != funcs_map.cend(); ++it){

            std::cout <<"func(" << it->first << ")";
            tmp = it->second;
            std::cout <<"with estimated value = ";
            std::visit([](const auto &y){std::cout << y;}, tmp);
            std::cout << std::endl;
        }
        return;
    }
};

Key g_Key;
Func g_Func;

#define key(x) g_Key(x)
//#define g_Func(x) g_Func(x)


#define lambda [](void)
#define func(x) g_Func(x)=lambda
//comment

