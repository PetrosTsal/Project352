/*author 4175 and 4128 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <variant>
#include <map>
#include <functional>
#include <list>
#include <ctype.h>

class Object;

using var_t = std::variant<int, double, std::string, bool, void*>;
using var_t2 = std::variant<var_t , std::function<var_t(void)>>;



std::map<std::string , var_t2> keys_map3;
std::map<std::string, std::function<var_t(void)>> funcs_map;
Object *msg_object, *rec_object;
std::vector<std::string> g_calls;
std::string tmp_cond;  



class Key{

    std::string key;
    var_t value;

public:

    Key(){}


    Key operator()(std::string k){
        this->key = k;
        return *this;
    }

    
    std::map<std::string, var_t2> operator=(var_t value){
        this->value = value;
       
        keys_map3.insert({this->key, this->value});
        
        return keys_map3;
    }   
};



class Func{

    std::string key;
    
public: 

    Func() {

    }


    Func operator()(std::string k){
        this->key = k;
        return *this;
    }


    std::map<std::string,var_t2> operator=(std::function<var_t(void)> f){

        funcs_map.insert({this->key,f});
        keys_map3.insert({this->key, &f});
        return keys_map3;
    }
};



class value{

    std::vector<var_t> values;

public:

    value(){}

    var_t get_value(){
        if(!values.empty()){
            var_t tmp = values.back();
            values.pop_back();
            return tmp;
        }
        else return 0;
    }

    size_t get_size(){

        return this->values.size();
    }

    

    friend value operator,(value val, var_t var);
};

value operator,(value val, var_t var){

        val.values.push_back(var);

        return val;
}



class Object{

    std::map<std::string, var_t2> obj_values;
    std::map<std::string, std::function<var_t(void)>> obj_funcs;
    std::vector<std::string> calls;

public:

    Object(){
    }


    ~Object(){

    }


    void operator=(var_t val){


        return;
    }


    Object operator[](value val){
        
        int j = val.get_size() - 1;
        var_t tmpv;

        while(j >= 0){
            tmpv = val.get_value();
            std::string tmp = std::to_string(j);
            tmp = std::to_string(j);
            keys_map3.insert({tmp, tmpv});
            j--;
        }

        this->obj_values = keys_map3;
        this->obj_funcs = funcs_map ; 
        this->calls = g_calls; 
        keys_map3.clear();
        funcs_map.clear();
        g_calls.clear(); 
        return *this;
    }


    Object operator[](std::map<std::string, var_t2> keys_map){

        this->obj_values = keys_map;
        this->obj_funcs = funcs_map ; 
        this->calls = g_calls; 
        keys_map3.clear();
        funcs_map.clear() ;
        g_calls.clear(); 
        return *this;

    }

    
    var_t & operator[](std::string key){
       
        var_t &tmp = std::get<var_t>(this->obj_values[key]);

        return tmp;
    }


    std::map<std::string, var_t2> getValues(){

        return (this->obj_values);
    }


    void printObject(){
        std::cout<<"object [ ";
        if(this->obj_values.empty()){
            std::cout << "Empty object ] \n" << std::endl;
            return;
        }
        
        for(std::map<std::string, var_t2>::iterator x  = this->obj_values.begin(); x != this->obj_values.end(); x++){
            std::map<std::string, var_t2>::iterator end = x ; 
            int idx = std::get<var_t>(this->obj_values[x->first]).index();
            std::cout << " \" " << x->first << " \" : " ;
            var_t tmp = std::get<var_t>(this->obj_values[x->first]);
            
            if(idx == 4)  
                std::cout << "function with address: ";
            std::visit([](const auto &y){std::cout << y;}, tmp); 
            if ( (++end) != this->obj_values.end())
                std::cout << ",";
        }
        std::cout<<" ];";
        std::cout<<"\n\n";
        return;
    }

    friend void set_communication(Object* , Object *);

    friend void get_communication(Object* , std::string);

    friend bool _eval_cond(std::string ev);

    friend var_t _eval(std::string ev);

    friend var_t _arg(std::string ar);

    friend var_t _self(std::string sel);

    friend void printCopy(Object*);

    friend std::list<var_t> arguments_list();

    friend var_t input(std::string) ; 

   
};


std::ostream& operator<< (std::ostream& stream, const var_t &var){

    var_t tmp = var;
    
    std::visit([](const auto &y){std::cout << y;}, tmp);

    
    return stream;
}

std::istream& operator>> (std::istream& stream, const var_t &var){

    var_t tmp = var;

    std::cin >> var;

    return stream;
}



var_t input(std::string msg){

    std::string in;

    std::cout << msg << ": ";
    std::cin >> in;
    var_t newval ; 
    reinterpret_cast<var_t&>(newval) = in;
    
    return newval;
}


void printCopy(Object* cpy){
    Object copy = *cpy ;
    for(std::map<std::string, std::function<var_t(void)>>::iterator x  = copy.obj_funcs.begin(); x != copy.obj_funcs.end(); x++){
            std::cout << "{" << x->first << ", " ;
            std::function<var_t(void)> tmp = copy.obj_funcs[x->first];
            var_t tmp2 = tmp(); 
            std::cout<<"}\n";
    }
    return;
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
   
    if (rec != NULL && msg != NULL){
        for(std::vector<std::string>::iterator x  = (*msg).calls.begin(); x != (*msg).calls.end(); x++){
            for ( std::map<std::string , std::function<var_t(void)>>::iterator y = (*rec).obj_funcs.begin() ; y != (*rec).obj_funcs.end(); y++){
                std::string s1 = x->data(), s2 = y->first;
                if (s1 == s2){
                    get_communication(rec , y->first);
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





var_t _eval(std::string ev){
    if(rec_object == NULL && msg_object == NULL ){ 
        return 0; 
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
    if(rec_object == NULL && msg_object == NULL){
        return 0;
    }else{
        if(msg_object != NULL){
            var_t res ;  
            for(std::map<std::string , std::function<var_t(void)>>::iterator x  = (*msg_object).obj_funcs.begin(); x != (*msg_object).obj_funcs.end(); x++){
                if (x->first == ev){
                    std::function<var_t(void)> tmp = (*msg_object).obj_funcs[x->first];
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

    return 0; 
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
            std::cout<<" ERROR IN arg(x) , X WASN'T FOUNT IN RECEIVER. RETURNED -1 .\n" ;
            return -1 ; 
        }else{
            std::cout<<" ERROR IN arg(x) , RECEIVER WASN'T FOUNT . RETURNED -1 .\n" ;
            return -1 ; 
        }
    }
}



void _call(std::string c){
    g_calls.push_back(c);
    return ;
}


std::list<var_t> arguments_list(){
    std::list<var_t> args ;
    for(std::map<std::string , var_t2>::iterator l = (*msg_object).obj_values.begin(); l != (*msg_object).obj_values.end(); l++){
        var_t inp = std::get<var_t>((*msg_object).obj_values[l->first]) ; 
        args.push_back(inp) ;
    }
    return args ; 
}

Object ref(Object q){

    return q ; 
}


void operator<<(Object rec, Object msg){

    msg_object = new Object;
    msg_object = &msg;
    rec_object = new Object;
    rec_object = &rec;
    set_communication(rec_object , msg_object);
    rec = *rec_object ; 
    msg = *msg_object ; 
    msg_object = NULL;
    rec_object = NULL;
    return;
}



Key g_Key;
Func g_Func;
value g_value;



#define none 0
#define let auto
#define object Object()
#define key(x) g_Key(x)
#define lambda [](void)
#define func(x) g_Func(x)=lambda
#define values g_value,
#define eval(x) _eval(x)
#define eval_cond(x) _eval_cond(x)
#define call(x) _call(x)
#define arg(x) _arg(x)
#define self(x) _self(x)
#define args_list arguments_list()
#define nl std::endl
