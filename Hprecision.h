#pragma once
#include<iostream>
#include<vector>

class Hprec{
    std::vector<short> _storage;    //for storing
    public:
    Hprec(){}
    Hprec(int res){
        while(res != 0){
            _storage.push_back(res % 10);
            res = res / 10;
        }
    }
    void output(){
        auto it = _storage.end();
        while(it != _storage.begin()){
            --it;
            std::cout << *it;
        }
    }
    friend std::ostream & operator<<(std::ostream & out, Hprec & _hp);

    void operator+=(Hprec & _hp);
    Hprec operator+(Hprec & _hp);
    
    ~Hprec(){}
};

std::ostream &  operator<<(std::ostream & out, Hprec & _hp){
    _hp.output();
    return out;
}

void Hprec::operator+=(Hprec & _hp){
    auto it1 = this->_storage.begin();
    auto it2 = _hp._storage.begin();
    while(it2 != _hp._storage.end()){
        if(it1 == _storage.end()){
            _storage.push_back(*it2);
        }
        else{
            *it1 += *it2;
            if(*it1 >= 10){
                auto tmp = *it1 / 10;
                if(++it1 == _storage.end()){
                    _storage.push_back(*(--it1) / 10);
                    *it1 = *it1 % 10; 
                }
                else{
                    *(it1--) += tmp;
                }
            }
        }
        it1 ++;
        it2 ++;
    }
}

Hprec Hprec::operator+(Hprec & _hp){
    Hprec hp = *this;
    hp += _hp;
    return hp;
}
