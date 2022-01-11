#include <string>
#include <vector>
#include <variant>
#include <map>
#include <iostream>

using var_t = std::variant<int, double, std::string, bool, void*>;

class Key{

public:

    std::map<std::string, var_t> keys_map;
    std::string key;
    var_t value;

    Key(){}

    Key operator()(std::string k){
        this->key = k;
        return *this;
    }
    
    Key operator=(var_t value){
        this->value = value;
        return *this;
    }

    Key operator,(Key add){
        g_Key.keys_map.insert({add.key, add.value});
        return *this;
    }

    void print_map(){

        var_t tmp;

        for(auto it = this->keys_map.cbegin(); it != this->keys_map.cend(); ++it){
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


