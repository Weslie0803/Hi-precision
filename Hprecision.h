#pragma once
#include<iostream>
#include<vector>

class Hprec{
    std::vector<short> _storage;    //for storing
    bool positive;  //true when positive
    public:
    Hprec(){}
    Hprec(int res){
        if(res < 0){
            positive = false;
            res = -res;
        }
        else{
            positive = true;
        }
        while(res != 0){
            _storage.push_back(res % 10);
            res = res / 10;
        }
    }
    void output(){
        if(positive == false) std::cout << '-';
        auto it = _storage.end();
        while(it != _storage.begin()){
            --it;
            std::cout << *it;
        }
    }
    friend std::ostream & operator<<(std::ostream & out, Hprec & _hp);

    void operator+=(Hprec & _hp);   //all += & + based on this function
    void operator+=(int num);
    Hprec operator+(Hprec & _hp);
    Hprec operator+(int num);
    void operator*=(Hprec & _hp);
    void operator*=(int num);
    Hprec operator*(Hprec & _hp);
    Hprec operator*(int num);
    
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
void Hprec::operator+=(int num){
    Hprec _hp(num);
    this->operator+=(_hp);
}

Hprec Hprec::operator+(Hprec & _hp){
    Hprec hp = *this;
    hp += _hp;
    return hp;
}
Hprec Hprec::operator+(int num){
    Hprec _hp(num);
    return this->operator+(_hp);
}

Hprec Hprec::operator*(Hprec & _hp){
    Hprec dest;
    for(auto i = 0; i < _hp._storage.size() ; i++){
        for(auto it = _storage.begin(); it != _storage.end(); it++){
            Hprec tmp;
            for(int j = 0; j < i; j++){
                tmp._storage.push_back(0);
            }
            auto tmp_it = --tmp._storage.end();
            *tmp_it += (*it * _hp._storage[i]) % 10;
            tmp._storage.push_back((*it * _hp._storage[i]) / 10);
        }
    }
}
