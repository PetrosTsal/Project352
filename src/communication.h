#include "object.hh"

void f(std::string input){

}

#define eval(x) f(x)




void operator<<(Object rec, Object msg){

    // rec.communicate = 1 ; 
    // msg.communicate = 2 ; 
    msg.set_communication(rec);
    //rec.get_communication(msg);
    
}