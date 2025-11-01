#include <iostream>
using namespace std;
//я в задании не увидел некоторые требования, переделаю их позже
class Rational{
    int a, b;
    
    public:
    Rational(int aa = 1, int bb = 1){
        a = aa;
        b = bb;
    }
    
    void drob_Change(int c, int d){
        a = c;
        b = d;
    }
    
    void vivod(){
        cout
    }
    void add(int c, int d){
        a += c;
        b *= d;
    }
    
    void sub(int c, int d){
        a -= c;
        b *= d;
    }
    
    void mul(int c, int d){
        a *= c;
        b *= d;
    }
    
    void div(int c, int d){
        a *= d;
        b *= c;
    }

    //общий делитель по алгоритму евклида
    int del(){
        int c = a, d = b;
        while(c>0 && d>0){
            if(c >= d) c %= d;
            else d %= c;
        }
        if(c > d) return c;
        else return d;
    }
    
    bool equal(Rational c1, Rational c2){
        int d1 = c1.del();
        int d2 = c2.del();
        return true;
    }
};

int main() {
    Rational d1, d2;
    return 0;
}
