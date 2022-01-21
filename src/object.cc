#include "object.hh"


int main(){
    
    let o1 = object;
    let o2 = object[values 3, 3.14, "hello", false];
    // let o3 = object[ 
    //     key("a") = 3,
    //     key("b") = 3.14, 
    //     key("c") = lambda{std::cout << "Hello" << std::endl; return 0;}, 
    //     func("d"){return 3+2;}
    // ];

    let printf_impl = object [ 
        func("printf") { 
            for (auto& v : args_list)
                std::cout << v << nl; 
            return none;
        }
    ];

    

    let o3 = object [ call("printf"), values 1, 2, 3, 4 ];

    o3.printObject();
    printf_impl<<o3;

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
            int i = std::get<int>(arg("port"));
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


    return 0;
} 