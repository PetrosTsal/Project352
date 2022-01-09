#include <iostream>
#include <vector>
#include <map>
#include <variant>
//#include "util.hh"

#define let auto

void print(){}

template <typename T, typename... Types>
void print(T var1, Types... var2){
    
    std::cout << var1 << std::endl;
    
    print(var2...);
}

// class Object{

//     std::map;

// public:
//     Object(){
//         std::cout << "An empty object" << std::endl;
//     }

//     Object(int x){
//         std::cout << "A new object" << std::endl;
//     }
// };


// class Values{

    

// public:
//     Values(){}

//     Values operator,(boost::variant<int, double, std::string, bool, void*> val){
//         values.push_back(val);
//     }

//     void pushback(boost::variant<int, double, bool, void*> val){
//         values.push_back(val);
//     }

// };

std::vector<var_t> vals;

int main(){
 
    vals = {1, 4.5, "vlaka", 445, false};

    for(auto& v: vals){

        std::visit([](auto&& arg){std::cout << arg;}, v);
        std::cout << x << std::endl;
    }
    
    // let x = a[value val];
    // let y = object[value val1];

    // Object a = Object();
    
}







value val = new value();//global keno temp
#define values  val , // anti gia Values val sketo val kai tha anaferetai ston global temp Values val 
Object obj = new Object(); // global keno temp 
#define object obj// h obj##. an to pairnei san ksexosisto token 


 class value{

    std::queue<boost::variant<....>>values;

public:
        value(){

        }

        value operator,(boost::variant valu){

            val.values.push(valu);
            return val;
        }

    
}


