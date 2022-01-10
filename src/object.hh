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
#define object Object()

class Object;

using var_t = std::variant<int, double, std::string, bool, void*>; // NA PROSTHESOYME OBJECT KAI FUNC

class value{

    std::queue<var_t> values;

public:

    value(){}

    var_t qFront(){
        if(!values.empty()){
            var_t tmp = values.front();
            std::visit([](const auto &y){std::cout << y;}, tmp);
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
        std::cout << "Operator," << std::endl;
        std::visit([](const auto &y){std::cout << y;}, tmp);

        return val;
}

class key{

    std::string id;
    var_t value;

public:

    key(std::string id){
        this->id = id;
    }

};


/**  */
class Object{

    /**  */
    std::map<std::string, var_t> values_map;


public:
    /**  */
    Object(){

        std::cout << "AN EMPTY OBJECT" << std::endl;

    }

    /**  */
    ~Object(){

    }

    Object operator[](value val){

        Object obj = *this;
        int j = 0 ;
        var_t tmpv;
        std::string tmp = std::to_string(j);
        val.printVal();
        while((tmpv = val.qFront()) != (var_t)0){
            tmp = std::to_string(j);
            values_map.insert({tmp, tmpv});
            j++;
        }
        
        std::cout << "Operator[]" << std::endl;
        return obj;
    }

    Object operator[](key k){



    }

    void printObject(){
        
        if(values_map.empty()) std::cout << "DE GEMIZEI RE MALAKA TO OBJECT" << std::endl;

        for(auto x = values_map.begin(); x != values_map.end(); x++){
            var_t tmp = x->second;
            std::cout << "{" << x->first << ", ";
            std::visit([](const auto &y){std::cout << y;}, tmp);
            std::cout << "}" << std::endl;

        }

    }
};

//Object g_object;
value g_value;

#define values g_value,