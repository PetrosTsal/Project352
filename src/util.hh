#include <string>
#include <vector>
#include <variant>
#include <map>
#include <iostream>

using var_t = std::variant<int, double, std::string, bool, void*>;

std::map<std::string, var_t> keys_map;

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

        return;
    }
};

Key g_Key;

#define key(x) g_Key(x)


