#include "util.hh"


using namespace std;

void print(){}

template <typename T, typename... Types>
void print(T var1, Types... var2){
    
    cout << var1 << endl;
    
    print(var2...);
}

int main(){

    

    // let x = 4;
    // char arr[10] = "hello you";

    // cout << arr[4] << endl;
    // cout << 4[arr] << endl;

    // // cout << x << endl;

    // print(1, 2, 3.14,
    //       "Pass me any "
    //       "number of arguments",
    //       "I will print\n");

        

    return 0;
}
    
