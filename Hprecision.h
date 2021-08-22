#pragma once
#include<iostream>
#include<vector>

class Hprec{
    std::vector<short> _storage;    //for storing
    bool positive;  //true when positive
    void auto_check();
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
    friend std::istream & operator>>(std::istream & in , Hprec & _hp);

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

std::ostream & operator<<(std::ostream & out, Hprec & _hp){
    _hp.output();
    return out;
}
std::istream & operator>>(std::istream & in , Hprec & _hp){
    int tmp;
    in >> tmp;
    _hp = tmp;
    return in;
} 

void Hprec::operator+=(Hprec & _hp){
    int i = 0;
    auto it2 = _hp._storage.begin();
    while(it2 != _hp._storage.end()){
        if(i == _storage.size()){
            _storage.push_back(*it2);
            it2 ++;
            i ++;
        }
        else{
            _storage[i] += *it2;/*
            if(_storage[i] >= 10){
                auto tmp = _storage[i] / 10;
                if((i+1) == _storage.size()){
                    _storage.push_back(_storage[i] / 10);
                    _storage[i] = _storage[i] % 10; 
                }
                else{
                    _storage[i] = _storage[i] % 10;
                    _storage[i+1] += tmp;
                }
            }*/
            i++;
            it2++;
        }
    }
    this->auto_check();
}

void Hprec::auto_check(){
    for(int i = 0; i < this->_storage.size(); i++){
        if(_storage[i] >= 10){
            if(i == this->_storage.size() - 1){
                _storage.push_back(_storage[i] / 10);
                _storage[i] %= 10;
            }
            else{
                _storage[i+1] += (_storage[i] / 10);
                _storage[i] %= 10;
            }
        }
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
    Hprec dest = 0;
    for(auto i = 0; i < _hp._storage.size() ; i++){
        Hprec tmp;
        for(int j = 0; j < i; j++){
            tmp._storage.push_back(0);
        }
        auto tmp_it = --tmp._storage.end();
        for(auto it = _storage.begin(); it != _storage.end(); it++){
            tmp._storage.push_back(0);
            tmp_it = --tmp._storage.end();
            *tmp_it += *it * _hp._storage[i];/*
            if(*tmp_it >= 10){
                tmp._storage.push_back((*tmp_it) / 10);
                tmp_it = --tmp._storage.end();
                tmp_it--;
                *tmp_it = *tmp_it % 10;
            }*/
        }
        tmp.auto_check();
        dest += tmp;
    }
    return dest;
}
