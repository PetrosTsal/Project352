#include "object.hh"

#define lambda [](void)
#define func(x) key(x)=lambda

int main(){
    
    let a = object;
    Object b;
    b[values 1, 3.14, "hello", true, &a];
    //b.printObject();

    //b["2"] = 25;

    a[  key("c") = 1,
        func("d"){return 1;}];

    printObject(a);


    //printObject(b);



    return 0;
}

// Kainourgio Key operator=(functional) kai ena map me keys kai functions 



