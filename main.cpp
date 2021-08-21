#include "Hprecision.h"

int main(){
    Hprec hp(9999);
    hp = hp + 1;
    std::cout << hp << std::endl;
    hp = 9;
    Hprec lp = 11;
    Hprec mul = lp * hp;
    std::cout << mul << std::endl;
    return 0;
}