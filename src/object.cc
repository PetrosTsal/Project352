#include "object.hh"


int main(){
    
    let a = object[ call("34"), 
                    func("hello"){
                        std::cout << "a object hello\n";
                        return 1;}
    ];  

    let c = object[  func("34"){
                        std::cout << "C OBJECT 34\n";
                        eval("hello");
                        return 1;}
    ];  
   

    c << a ;
   // a.printObject();

    
    return 0;
}

// Kainourgio Key operator=(functional) kai ena map me keys kai functions 
