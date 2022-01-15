#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <variant>
#include <cstdarg>
#include <iterator>
#include <map>
#include <unordered_map>
#include "util.hh"

#define let auto
#define none 0
#define object Object()


//using var_t = std::variant<int, double, std::string, bool, void*>; // NA PROSTHESOYME OBJECT KAI FUNC


class value{

    std::queue<var_t> values;

public:

    value(){}

    var_t qFront(){
        if(!values.empty()){
            var_t tmp = values.front();
             values.pop();
            return tmp;
        }
        else return 0;
    }

    void printVal(){
        std::queue<var_t> values2 = values;
        if (values.empty())
            std::cout << "DE gemizei to values" << std::endl;
        while(!values2.empty()){
            var_t tmp = values2.front();
            std::visit([](const auto &y){std::cout << y;}, tmp);
           std:: cout << std::endl;
            values2.pop();
        }
        return;
    }

    friend value operator,(value val, var_t var);

};

value operator,(value val, var_t var){

        var_t tmp ;
        val.values.push(var);
        tmp = val.values.front();
        

        return val;
}

/**  */
class Object{

    /**  */
    std::map<std::string, var_t> values_map;
    var_t value1;
    std::string index, assign_idx;

public:
    /**  */
    Object(){

        std::cout << "AN EMPTY OBJECT" << std::endl;

    }

    /**  */
    ~Object(){

    }

    void operator=(var_t val){

        std::cout << "index: " << this->assign_idx << std::endl;
        std::cout <<"Operator = in Object " ;
        std::visit([](const auto &y){std::cout << y;}, val);
        std::cout << std::endl;

        std::map<std::string, var_t>::iterator itr = values_map.find(assign_idx);

        std::visit([](const auto &y){std::cout << y;}, itr->second);        

        if (itr != values_map.end())
            itr->second = val;
        
        std::visit([](const auto &y){std::cout << y;}, this->values_map[assign_idx]);
        assign_idx.clear();

        return;
    }

    Object operator[](value val){

        Object obj = *this;
        int j = 0 ;
        var_t tmpv;
        std::string tmp = std::to_string(j);
        
        while((tmpv = val.qFront()) != (var_t)0){
            tmp = std::to_string(j);
            values_map.insert({tmp, tmpv});
            j++;
        }
        
        return obj;
    }

    Object operator[](std::map<std::string, var_t> keysMap){

        values_map = keysMap;
        keysMap.clear();
        return *this;
    }

    Object operator[](std::string key){
        this->assign_idx = key;
        return *this;
    }

    friend void printObject(Object o);
};



void printObject(Object o){
        
    if(o.values_map.empty()) std::cout << "DE GEMIZEI RE MALAKA TO OBJECT" << std::endl;

    for(auto x = o.values_map.begin(); x != o.values_map.end(); x++){
        std::cout << "{" << x->first << ", ";
        std::visit([](auto &y){std::cout << y;}, o.values_map[x->first]);
        std::cout << "}" << std::endl;
    }
}

//Object g_object;
value g_value;

#define values g_value,