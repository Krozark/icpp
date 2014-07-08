#include <iostream>

extern "C"{
    int test_print(int i){
        std::cout<<i<<std::endl;
        return 42;
    }
}
