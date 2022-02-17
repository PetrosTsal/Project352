
/*author 4128 and 4175 */

#include "object.hh"


int main(){
    
    let o1 = object;
    let o2 = object[values "1.1.1.1", "127.0.0.1", "hello", false];
    let o3 = object[ 
        key("a") = 3,
        key("b") = 3.14, 
        key("c") = lambda{std::cout << "Hello" << std::endl; return 0;}, 
        func("d"){return 3+2;}
    ];

    let printf_impl = object [ 
        func("printf") { 
            var_t t =1 , o = 6 ; 
            std::cout<<"entered in printf_imp\n";
            for (auto& v : args_list)
                std::cout << v << nl; 
            return none;
        }
    ];

    

    let o4 = object [call("printf"), values 1, 2, 3, 4 ];



    printf_impl << o4;

    let conn_impl = object [
        key("ip") = "127.0.0.1",
        key("port") = 3030,
        func("connect"){
            if(eval_cond("_cond_"))
                eval("_success_");
            else
                eval("_failure_");
            return none;
        }
    ];

    let connection = object [
        call("connect"),
        key("ip") = "1.1.1.1",
        key("port") = 5000,
        func("_cond_"){
            int i = std::get<int>(arg("port")); //DEN PROLAVAME NA KANOUME ARITHMETIC OPERATIONS OVERLOAD EPOMENWS AN THES ARITHMETIC PRAKSEIS KANE CAST OPWS EDW
            int j = std::get<int>(self("port"));
            return (i == j);},
        func("_success_"){
            std::cout << arg("ip") << " connect to " << self("ip") << nl;
            return none;
        },
        func("_failure_"){
            std::cout << arg("ip") << " failed to connect to " << self("ip") << nl;
            return none; 
        }
    ];

    conn_impl << connection;

    o3["a"] = 2 ; 

    o1.printObject();
    o2.printObject();
    o3.printObject();

    return 0;
}