#include <string>
#include <vector>
#include <iostream>

class Key{

    std::string key;
    int value;

public:

    Key(){}

    Key operator()(std::string key){
        this->key = key;
        return *this;
    }
    
    Key operator=(int value){
        this->value = value;
        std::cout << "Operator=" << this->value;
        return *this;
    }

    std::string getKey(){return this->key;}

    int getValue(){return this->value;}
};

Key g_Key;
std::vector<Key> g_Keys;
