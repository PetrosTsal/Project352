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

std::map<std::string, var_t2> g_evals;
std::map<std::string, bool> g_evals_cond;
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

        Object obj = *this;
        int j = 0 ;
        var_t tmpv;
        std::string tmp = std::to_string(j);
        
        while((tmpv = val.qFront()) != (var_t)0){
            tmp = std::to_string(j);
            obj_values.insert({tmp, tmpv});
            j++;
        }
        
        return obj;
    }

    Object operator[](std::map<std::string, var_t2> keys_map3){

        obj_values = keys_map3;
        calls = g_calls;
        in = 1;
        g_calls.clear();
        g_evals_cond.clear();
        keys_map3.clear();
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

    void set_communication(Object o){
        for(auto x = this->calls.begin(); x != this->calls.end(); x++){
            for ( auto y = o.getValues().begin() ; y != o.getValues().end(); y++){
                std::string s1 = x->data(), s2 = y->first;
                if (s1 == s2){
                    //tote shmainei oti brikame to analogo func("x->data()") sto rec object kai kanoume ta evals prwta kai meta return y->second
                    //ekteloume kata seira ta eval_cond me index == cond
                    //emvolemena sto eval_cond me index cond ekteloume ta evals me index cond 
                    //telos kanoume return to value y-second 
                    o.get_communication(*this , s1);
                    return;
                }else{
                    std::cout << " The messenger's function doesn't exist in receiver object" << std::endl;
                }
            }
        }
        return ;
    }

    void get_communication(Object o , std::string ind){
        // o == msg object 
        //*this == rec object 
        //tha sindeei eval_cond kai eval me ta antistoixa functions tou msg object , dld to o 
        if ( this->getValues()[ind].index() == 1 ){
            std::function<var_t(void)> run = std::get<std::function<var_t(void)>>((*msg_object).getValues()[ind]);
            var_t runvar = run() ; 
        }
    
        return ;
    }

    void printObject(){
        
        if(this->obj_values.empty()) std::cout << "DE GEMIZEI RE MALAKA TO OBJECT" << std::endl;
    
        for(auto x = this->obj_values.begin(); x != this->obj_values.end(); x++){
            std::cout << "{" << x->first << ", ";
            if (int var = obj_values[x->first].index() != 1){
                var_t tmp = std::get<var_t>(this->obj_values[x->first]);
                std::visit([](const auto &y){std::cout << y;}, tmp);   
            }else{
                std::function<var_t(void)> tmp = std::get<std::function<var_t(void)>>(this->obj_values[x->first]);
                var_t(*const* ptr)(void) = tmp.target<var_t(*)(void)>();
                std::cout << ptr;
            }
            
            std::cout << "}" << std::endl;
        }
    }

    friend var_t _eval_cond(std::string ev);
    friend var_t _eval(std::string ev);

};



void operator<<(Object rec, Object msg){

    msg_object = new Object;
    msg_object = &msg;
    rec_object = new Object;
    rec_object = &rec;
    msg.set_communication(rec);
    // delete(msg_object);
    // delete(rec_object);
    msg_object = nullptr;
    rec_object = nullptr;
    return;
}

var_t _eval(std::string ev){
    if(&rec_object == nullptr && &msg_object == nullptr ){
        tmp_cond = ev; 
        g_evals.insert({ev, 0});
        return 0 ; 
    }else{
        var_t res ; 
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
        }
        std::cout << "ERROR FUNC(" << ev << ")" << "NOT EXISTS IN MESSAGE OBJECT . " << std::endl ; 
    }
    return -1; 
}

var_t _eval_cond(std::string ev){
   
   //NA TSEKAROUME TON ELEGXO SE INITIAL STATUS KAI EPIKOINWNIA 
    if(&rec_object == nullptr && &msg_object == nullptr ){
        tmp_cond = ev; 
        g_evals_cond.insert({ev, 0});
    }else{
        var_t res ; 
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
        }
        std::cout << "ERROR FUNC(" << ev << ")" << "NOT EXISTS IN MESSAGE OBJECT . " << std::endl ; 
    }
    return 0 ; 
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
