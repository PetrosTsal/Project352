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
#include <string.h>

#define let auto
#define object Object()

std::map<std::string, var_t> g_evals;
std::map<std::string, var_t> g_evals_cond;
std::vector<std::string> g_calls;
std::string tmp_cond ; 
std::tuple <var_t,std::function<var_t(void)>> val;
bool in = 1;
class Object ; 
Object *msg_object, *rec_object;

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
    std::map<std::string, var_t2> obj_values;
    std::map<std::string, std::function<var_t(void)>> obj_funcs;
    var_t value1;
    std::string index, assign_idx;
    std::vector<std::string> evals;
    std::vector<std::string> evals_cond;
    std::vector<std::string> calls;
    int communicate;
    bool initialized;

public:
    /**  */
    Object(){
        this->communicate = 0;
        this->initialized = 0;
        in = 0;
    }

    /**  */
    ~Object(){

    }

    void operator=(var_t val){
/*
        std::cout << "index: " << this->assign_idx << std::endl;
        std::cout <<"Operator = in Object " ;
        std::visit([](const auto &y){std::cout << y;}, val);
        std::cout << std::endl;

        for(auto x = this->obj_values.begin(); x != this->obj_values.end(); x++){
            std::cout << "{" << x->first << ", ";
            std::visit([](auto &y){std::cout << y;}, this->obj_values[x->first]);
            std::cout << "}" << std::endl;
        }

        std::map<std::string, var_t>::iterator itr = obj_values.find(assign_idx);      

        if (itr != obj_values.end())
            itr->second = val;
        
        for(auto x = this->obj_values.begin(); x != this->obj_values.end(); x++){
            std::cout << "{" << x->first << ", ";
            std::visit([](auto &y){std::cout << y;}, this->obj_values[x->first]);
            std::cout << "}" << std::endl;
        }

        //assign_idx.clear();*/

        return;
    }

    Object operator[](value val){
        std::cout<<"entered in this[]\n";
        Object obj = *this;
        int j = 0 ;
        var_t tmpv;
        std::string tmp = std::to_string(j);
        
        while((tmpv = val.qFront()) != (var_t)0){
            tmp = std::to_string(j);
            obj_values.insert({tmp, tmpv});
            j++;
        }
       keys_map3.clear();
        return obj;
    }
   

    Object operator[](std::map<std::string, var_t2> keys_map){

        obj_values = keys_map;
        obj_funcs = funcs_map ; 
        calls = g_calls;
        in = 1;
        g_calls.clear();
        g_evals_cond.clear();
        keys_map3.clear();
        funcs_map.clear() ; 
        g_evals.clear();
        return *this;

    }

    Object operator[](std::string key){
       
        this->assign_idx = key;
        return *this;
    }


    std::map<std::string, var_t2> getValues(){
        return (this->obj_values);
    }

    
    friend void set_communication(Object* , Object *);
    friend void get_communication(Object* , std::string);

    

    void printObject(){
        std::cout<<"Now entering printObject()\n";
        if(this->obj_values.empty()) std::cout << "DE GEMIZEI RE MALAKA TO OBJECT" << std::endl;
    
        for(std::map<std::string, var_t2>::iterator x  = this->obj_values.begin(); x != this->obj_values.end(); x++){
            std::cout << "{" << x->first << ", " ;    
            var_t tmp = std::get<var_t>(this->obj_values[x->first]);
            auto* str  = std::get_if<std::string>(&tmp);
            if ( str != nullptr)
                std::cout<<"it went here";
                //std::cout<<*str;
            std::visit([](const auto &y){std::cout << y;}, tmp);   
            
           
            std::cout << "}" << std::endl;
        }

        for(std::map<std::string, std::function<var_t(void)>>::iterator x  = this->obj_funcs.begin(); x != this->obj_funcs.end(); x++){
            std::cout << "{" << x->first << ", " ;
            std::function<var_t(void)> tmp = this->obj_funcs[x->first];
            var_t tmp2 = tmp(); 
            std::cout<<"}\n";
        }
    }



    friend bool _eval_cond(std::string ev);
    friend var_t _eval(std::string ev);
    friend var_t _arg(std::string ar) ;
    friend var_t _self(std::string sel) ;
    friend void printCopy(Object*);

};






void printCopy(Object* cpy){
    Object copy = *cpy ;
    std::cout<<"Now the copy object will be printed \n";
    for(std::map<std::string, std::function<var_t(void)>>::iterator x  = copy.obj_funcs.begin(); x != copy.obj_funcs.end(); x++){
            std::cout << "{" << x->first << ", " ;
            std::function<var_t(void)> tmp = copy.obj_funcs[x->first];
            var_t tmp2 = tmp(); 
            std::cout<<"}\n";
    }
    return ;
}

void get_communication(Object *rec , std::string ind){
        
        if ( rec != NULL ){
            if ( (*rec).obj_funcs[ind] != NULL ){
                std::function<var_t(void)> tmp = (*rec).obj_funcs[ind];
                var_t res = tmp(); 
                (*rec).obj_values[ind] = res ; 
            }
        }else {
            std::cout<<"INVALID GET_COMMUNICATION\n";
        }
        return ;
    }

void set_communication(Object* rec , Object* msg ){
   
    std::cout<<"Starting connection between 2 Objects .\n";
    if (rec != NULL && msg != NULL){
        for(std::vector<std::string>::iterator x  = (*msg).calls.begin(); x != (*msg).calls.end(); x++){
            for ( std::map<std::string , std::function<var_t(void)>>::iterator y = (*rec).obj_funcs.begin() ; y != (*rec).obj_funcs.end(); y++){
                std::string s1 = x->data(), s2 = y->first;
                if (s1 == s2){
                    get_communication(rec , y->first);
                    std::cout << "Terminating connection .\n" ; 
                    return;
                }else{
                    std::cout << " The messenger's function doesn't exist in receiver object" << std::endl;
                }
            }
        }
    }else {
        std::cout<<"INVALID SET_COMMUNICATION\n";
    }
    return ;
}


void operator<<(Object rec, Object msg){

    msg_object = new Object;
    msg_object = &msg;
    rec_object = new Object;
    rec_object = &rec;
   // printCopy(msg_object);
    set_communication(rec_object , msg_object);
    rec = *rec_object ; 
    msg = *msg_object ; 
    // delete(msg_object);
    // delete(rec_object);
    msg_object = NULL;
    rec_object = NULL;
    return;
}

var_t _eval(std::string ev){
    if(rec_object == NULL && msg_object == NULL ){
        tmp_cond = ev; 
        g_evals.insert({ev, 0});
        return 0 ; 
    }else{
       if ( msg_object != NULL ){
            var_t res ;  
            for(std::map<std::string , std::function<var_t(void)>>::iterator x  = (*msg_object).obj_funcs.begin(); x != (*msg_object).obj_funcs.end(); x++){
                if ( x->first == ev){
                    std::function<var_t(void)> tmp = (*msg_object).obj_funcs[x->first];
                    var_t res = tmp(); 
                    (*msg_object).obj_values[x->first] = res ; 
                    return res ; 
                }
            }
            std::cout << "ERROR FUNC(" << ev << ")" << "NOT EXISTS IN MESSAGE OBJECT . " << std::endl ; 
            return 0 ; 
        }else{
            std::cout<<"ERROR IN _EVAL_COND REC_OBJECT == NULL \n";
        }
    }
    return -1 ; 
   
}

bool _eval_cond(std::string ev){
   
   //NA TSEKAROUME TON ELEGXO SE INITIAL STATUS KAI EPIKOINWNIA 
    if(rec_object == NULL && msg_object == NULL ){
        tmp_cond = ev; 
        g_evals_cond.insert({ev, 0});
    }else{
        if ( msg_object != NULL ){
            var_t res ;  
            for(std::map<std::string , std::function<var_t(void)>>::iterator x  = (*msg_object).obj_funcs.begin(); x != (*msg_object).obj_funcs.end(); x++){
                if ( x->first == ev){
                    std::function<var_t(void)> tmp = (*msg_object).obj_funcs[x->first];
                    //var_t res{tmp()}; 
                    res = tmp() ; 
                    (*msg_object).obj_values[x->first] = res ; 
                    return std::get<bool>(res) ; 
                }
            }
            std::cout << "ERROR FUNC(" << ev << ")" << "NOT EXISTS IN MESSAGE OBJECT . " << std::endl ; 
            return 0 ; 
        }else{
            std::cout<<"ERROR IN _EVAL_COND MSG_OBJECT == NULL \n";
        }
    }
    return 0 ; 
    /*var_t res ; 
        for ( auto x = (*msg_object).getValues().begin() ; x != (*msg_object).getValues().end() ; x++ ){
            if ( x->first == ev ){
                if ( (*msg_object).getValues()[x->first].index() == 1 ){
                    std::function<var_t(void)> tmp = std::get<std::function<var_t(void)>>((*msg_object).getValues()[x->first]);
                    res = tmp() ; 
                    (*rec_object).getValues()[x->first] = res  ;
                    return  res ; // NA TSEKAROUME MIPWS THELEI CAST SE BOOL  NA EPISTREFEI H EVAL_COND
                }else{
                    std::cout << "ERROR FUNC(" << ev << ")" << "EXISTS AS VARIABLE IN MESSAGE OBJECT . " << std::endl ; 
                }
            }
        }*/
}

var_t _arg(std::string ar){
    if ( msg_object == NULL && rec_object == NULL){
        return 0 ; 
    }else{
        if ( msg_object != NULL ){
            var_t res ; 
            for(std::map<std::string , var_t2>::iterator x  = (*msg_object).obj_values.begin(); x != (*msg_object).obj_values.end(); x++){
                if ( x->first == ar){
                    res =std::get<var_t>((*msg_object).obj_values[x->first]) ; 
                    return res ; 
                }
            }
            std::cout<<" ERROR IN arg(x) , X WASN'T FOUNT IN SENDER.\n" ;
            return -1 ; 
        }else{
            std::cout<<" ERROR IN arg(x) , SENDER WASN'T FOUNT .\n" ;
            return -1 ; 
        }
    }
}

var_t _self(std::string sel){
    if ( msg_object == NULL && rec_object == NULL){
        return 0 ; 
    }else{
        if ( rec_object != NULL ){
            var_t res ; 
            for(std::map<std::string , var_t2>::iterator y = (*rec_object).obj_values.begin(); y != (*rec_object).obj_values.end(); y++){
                if ( y->first == sel){
                    res =std::get<var_t>((*rec_object).obj_values[y->first]) ; 
                    return res ; 
                }
            }
            std::cout<<" ERROR IN arg(x) , X WASN'T FOUNT IN RECEIVER.\n" ;
            return -1 ; 
        }else{
            std::cout<<" ERROR IN arg(x) , RECEIVER WASN'T FOUNT .\n" ;
            return -1 ; 
        }
    }
}

void _call(std::string c){
     
    g_calls.push_back(c);
    return ;
}

value g_value;

#define values g_value,
#define eval(x) _eval(x)
#define eval_cond(x) _eval_cond(x)
#define call(x) _call(x)
#define arg(x) _arg(x)
#define self(x) _self(x)
