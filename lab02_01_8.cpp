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
    
    void add(Rational c){
        a = (a*c.b) + (c.a*b);
        b *= c.b;
        this->reduce();
    }
    
    void sub(Rational c){
        a = (a*c.b) - (c.a*b);
        b *= c.b;
        this->reduce();
    }
    
    void mul(Rational c){
        a *= c.a;
        b *= c.b;
        this->reduce();
    }
    
    void div(Rational c){
        a *= c.b;
        b *= c.a;
        this->reduce();
    }
    
    bool equal(Rational c){
        float a1 = a, b1 = b;
        float a2 = c.a, b2 = c.b;
        return (a1/b1) == (a2/b2);
    }
    
    int greate(Rational c){
        float a1 = a, b1 = b;
        float a2 = c.a, b2 = c.b;
        if((a1/b1) == (a2/b2)) return 2;
        return (a1/b1) > (a2/b2);
    }
    
    int less(Rational c){
        float a1 = a, b1 = b;
        float a2 = c.a, b2 = c.b;
        if((a1/b1) == (a2/b2)) return 2;
        return (a1/b1) < (a2/b2);
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
        << "(7)d1 += d2" << endl
        << "(8)d1 -= d2" << endl
        << "(9)d1 *= d2" << endl
        << "(10)d1 /= d2" << endl
        << "(11)Выв. d1 == d2" << endl
        << "(12)Выв. d1 > d2" << endl
        << "(13)Выв. d1 < d2" << endl
        << "(0)Выход" << endl
        << "Ввод: ";
}

const int M = 4;

int main() {
    cout << "Конструктор без аргументов" << endl;
    Rational c1;
    c1.display();
    
    cout << "Конструктор инициализации" << endl;
    Rational c2(13, 20);
    c2.display();
    
    cout << "Метод инициализации" << endl;
    Rational c3;
    c3.init(123, 432);
    c3.display();
    
    cout << "Ввод с клавиатуры" << endl;
    Rational c4;
    c4.read();
    c4.display();
    
    cout << "Конструктор копирования" << endl;
    Rational c5(c4);
    c5.display();
    
    cout << "Массив" << endl;
    int aa=1, bb=5; Rational mas[M];
    for(int i=0; i<M; i++){
        mas[i] = Rational(aa+i, bb+i);
        cout << "mas[" << i << "]" << endl;
        mas[i].display();
    }
    
    
    cout << "Демонстрация методов и ф-ций" << endl;
    Rational d1, d2;
    int choice = 0;
    do{
        menu();
        cin >> choice;
        
        switch(choice){
            case 1: d1.read(); break;
            case 2: d2.read(); break;
            case 3: d1.display(); break;
            case 4: d2.display(); break;
            case 5: cout << d1.toString() << endl; break;
            case 6: cout << d2.toString() << endl; break;
            case 7: d1.add(d2); break;
            case 8: d1.sub(d2); break;
            case 9: d1.mul(d2); break;
            case 10: d1.div(d2); break;
            case 11: cout << (d1.equal(d2)?"d1 == d2":"d1 != d2") << endl; break;
            case 12: 
                if(d1.greate(d2)==2) {cout << "d1 == d2" << endl; break;}
                else {cout << (d1.greate(d2)?"d1 > d2":"d1 < d2") << endl; break;}
            case 13: 
                if(d1.greate(d2)==2) {cout << "d1 == d2" << endl; break;}
                else {cout << (d1.less(d2)?"d1 < d2":"d1 > d2") << endl; break;}
        }
    }while(choice);
    return 0;
}
