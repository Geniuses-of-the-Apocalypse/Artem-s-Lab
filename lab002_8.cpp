#include <iostream>
using namespace std;

class Rational{
    int a, b;
    
    void add(int c, int d){
        this a += c;
        this b *= d;
    }
    
    void sub(int c, int d){
        this a -= c;
        this b *= d;
    }
    
    void mul(int c, int d){
        this a *= c;
        this b *= d;
    }
    
    void div(int c, int d){
        this a *= d;
        this b *= c;
    }
    
    bool equal(Rational c1, Rational c2){
        
    }
};

int main() {
    
    return 0;
}
