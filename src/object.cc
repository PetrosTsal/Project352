#include "object.hh"


int main(){
    
   /* let a = object[ call("34"), 
                    func("hello"){
                        std::cout << "a object hello\n";
                        return 1;}
    ];  */

    let c = object[ key("y") = 2 , call("33"), func("34"){
                        int r = std::get<int>(self("y")) ; 
                        std::cout << "C OBJECT 34 from communication" << r << std::endl;
                        return true;
                        },
                        func("hello"){
                            std::cout<<"hello from communication\n" ; 
                    
                        return 1;}
                        
    ];  

    let d = object[ key("x")=1 , func("33"){
                            int r = std::get<int>(arg("y")) ; 
                            std::cout<<"Entered d Object " <<r <<std::endl;
                            if ( eval_cond("34"))
                                eval("hello");
                            return 0 ;
                    }              
    ];
   

    

     let f = object[ call("33"), func("34"){
                        std::cout << "f OBJECT 34 from communication\n";
                        return true;
                        },
                        func("hello"){
                            std::cout<<"hello from communication g\n" ; 
                    
                        return 1
                        ;}
    ];  

    let g = object[ func("33"){
                            std::cout<<"Entered g Object\n";
                            if ( eval_cond("34"))
                                eval("hello");
                            return 0 ;
                    },    
                    key("1") = "ELA RE"          
    ];

    d<<c ;

    g<<f ;

    
    let a = object[values 1, 3.14, "hello", true];
    g.printObject();

    return 0;
}

// Kainourgio Key operator=(functional) kai ena map me keys kai functions 
