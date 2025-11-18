//Во всех заданиях, помимо указанных в задании операций, обязательно должны быть реализованы //следующие методы:
//– метод инициализации init;
//– ввод с клавиатуры read;
//– вывод на экран display;
//– преобразование в строку toString.

//Все задания должны быть реализованы двумя способами:
//- тип данных представляется структурой с необходимыми полями, а операции реализуются как //внешние функции, которые получают объекты данного типа в качестве аргументов;
//– как класс с закрытыми полями, где операции реализуются как методы класса.
//8. Рациональная (несократимая) дробь представляется парой целых чисел (a, b), где a – числитель, b – знаменатель. Создать класс Rational для работы с рациональными дробями. Обязательно должны быть реализованы операции:
//– сложения add, (a, b) + (c, d) = (ad + bc, bd);
//– вычитания sub, (a, b) – (c, d) = (ad – bc, bd);
//– умножения mul, (a, b)*(c, d) = (ac, bc);
//– деления div, (a, b)/(c, d) = (ad, bc);
//– сравнение equal, greate, less.
#include <iostream>
#include <string>
using namespace std;
//доделать

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
    Rational(int aa = 1, int bb = 1){
        a = aa;
        b = bb;
    }
    
    void init(int aa, int bb){
        a = aa;
        b = bb;
    }
    
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
        
        cout << "Дробь:" << endl;
        cout << a << endl;
        cout << string(maxLen, '-') << endl;
        cout << b << endl;
    }
    
    string toString(){
        int  maxLen;
        maxLen = max(numLen(a),numLen(b));
        string drob{to_string(a) + "\n" + string(maxLen, '-') + "\n" + to_string(b)}
        return drob;
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
