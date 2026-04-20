#include <iostream>
#include <string>
using namespace std;

int numLen(int n){
    int len = 0;
    while(n){
        n /= 10;
        len++;
    }
    return len;
}

class Rational{
    int a, b;
    
    public:
    Rational(){a = 2; b = 3;}
    Rational(int aa, int bb){a = aa; b = bb;}
    Rational(const Rational &t){a = t.a; b = t.b;}
    
    void init(int aa, int bb){a = aa; b = bb;}
    
    void read(){
        int aa, bb;
        cout << "Вв. числитель дроби: "; cin >> aa;
        cout << "Вв. знаменатель дроби: "; cin >> bb;
        a = aa;
        b = bb;
    }
    
    void display(){
        int  maxLen;
        maxLen = max(numLen(a),numLen(b));
        cout << a << endl;
        cout << string(maxLen, '-') << endl;
        cout << b << endl;
    }
    
    string toString(){
        int  maxLen;
        maxLen = max(numLen(a),numLen(b));
        string drob{to_string(a) + "\n" + string(maxLen, '-') + "\n" + to_string(b)};
        return drob;
    }
    
    void reduce(){
        int c = a, d = b, del;
        //общий делитель по алгоритму евклида
        while(c>0 && d>0){
            if(c >= d) c %= d;
            else d %= c;
        }
        if(c > d) del = c;
        else del = d;
        a /= del;
        b /= del;
    }
    
    Rational operator + (Rational& var) const{
        Rational t((a*var.b) + (var.a*b), b*var.b);
        t.reduce();
        return t;
    }
    
    Rational operator - (Rational& var) const{
        Rational t((a*var.b) - (var.a*b), b*var.b);
        t.reduce();
        return t;
    }
    
    Rational operator * (Rational& var) const{
        Rational t(a*var.a, b*var.b);
        t.reduce();
        return t;
    }
    
    Rational operator / (Rational& var) const{
        Rational t(a*var.b, b*var.a);
        t.reduce();
        return t;
    }
    
    bool operator == (Rational& var) const{
        float a1 = a, b1 = b;
        float a2 = var.a, b2 = var.b;
        return (a1/b1) == (a2/b2);
    }
    
    bool operator != (Rational& var) const{
        return !(*this == var);
    }
    
    bool operator > (Rational& var) const{
        float a1 = a, b1 = b;
        float a2 = var.a, b2 = var.b;
        return (a1/b1) > (a2/b2);
    }
    
    bool operator < (Rational& var) const{
        float a1 = a, b1 = b;
        float a2 = var.a, b2 = var.b;
        return (a1/b1) < (a2/b2);
    }
    
    friend istream& operator >> (istream& i, Rational& var){
        i >> var.a >> var.b;
        return i;
    }
    
    friend ostream& operator << (ostream& o, Rational& var){
        o << var.a << '/' << var.b;
        return o;
    }
    
};

void menu(){
    cout << "Меню:" <<endl
        << "(1)Вв. дробь d1" << endl
        << "(2)Вв. дробь d2" << endl
        << "(3)Выв. дробь d1" << endl
        << "(4)Выв. дробь d2" << endl
        << "(5)Выв. дробь d1 через string" << endl
        << "(6)Выв. дробь d2 через string" << endl
        << "(7)d1 = d1 + d2" << endl
        << "(8)d1 = d1 - d2" << endl
        << "(9)d1 = d1 * d2" << endl
        << "(10)d1 = d1 / d2" << endl
        << "(11)Выв. d1 == d2" << endl
        << "(12)Выв. d1 > d2" << endl
        << "(13)Выв. d1 < d2" << endl
        << "(0)Выход" << endl
        << "Ввод: ";
}

int main() {
    Rational d1, d2;
    int choice = 0;
    do{
        menu();
        cin >> choice;
        
        switch(choice){
            case 1: cin >> d1; break;
            case 2: cin >> d2; break;
            case 3: cout << "Дробь d1: " << d1 << endl; break;
            case 4: cout << "Дробь d2: " << d2 << endl; break;
            case 5: cout << d1.toString() << endl; break;
            case 6: cout << d2.toString() << endl; break;
            case 7: d1 = d1 + d2; break;
            case 8: d1 = d1 - d2; break;
            case 9: d1 = d1 * d2; break;
            case 10: d1 = d1 / d2; break;
            case 11: cout << (d1 == d2?"d1 == d2":"d1 != d2") << endl; break;
            case 12: cout << (d1 > d2?"d1 > d2":"d1 <= d2") << endl; break;
            case 13: cout << (d1 < d2?"d1 < d2":"d1 >= d2") << endl;
        }
    }while(choice);
    return 0;
}
