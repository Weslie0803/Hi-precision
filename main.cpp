#include "Hprecision.h"

int main(){
    Hprec hp(123);
    hp = hp + hp;
    std::cout << hp << std::endl;
    return 0;
}