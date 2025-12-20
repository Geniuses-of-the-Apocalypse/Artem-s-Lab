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

struct Rational{
    int a, b;
    
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
        cout << " " << a << endl;
        cout << string(maxLen+2, '-') << endl;
        cout << " " << b << endl;
    }
};

string toString(Rational c){
    int  maxLen;
    maxLen = max(numLen(c.a),numLen(c.b));
    string drob{to_string(c.a) + "\n" + string(maxLen, '-') + "\n" + to_string(c.b)};
    return drob;
}
    
Rational reduce(Rational c){
    int z = c.a, x = c.b, del;
    Rational end;
    while(z>0 && x>0){
        if(z >= x) z %= x;
        else x %= z;
    }
    if(z > x) del = z;
    else del = x;
    end.a = c.a / del;
    end.b = c.b / del;
    return end;
}
    
Rational add(Rational c1, Rational c2){
    Rational end;
    end.a = (c1.a*c2.b) + (c2.a*c1.b);
    end.b = c1.b * c2.b;
    end = reduce(end);
    return end;
}

Rational sub(Rational c1, Rational c2){
    Rational end;
    end.a = (c1.a*c2.b) - (c2.a*c1.b);
    end.b = c1.b * c2.b;
    end = reduce(end);
    return end;
}

Rational mul(Rational c1, Rational c2){
    Rational end;
    end.a = c1.a * c2.a;
    end.b = c2.b * c2.b;
    end = reduce(end);
    return end;
}

Rational div(Rational c1, Rational c2){
    Rational end;
    end.a = c1.a * c2.b;
    end.b = c1.b * c2.a;
    end = reduce(end);
    return end;
}

bool equal(Rational c1, Rational c2){
    float a1 = c1.a, b1 = c1.b;
    float a2 = c2.a, b2 = c2.b;
    return (a1/b1) == (a2/b2);
}

int greate(Rational c1, Rational c2){
    float a1 = c1.a, b1 = c1.b;
    float a2 = c2.a, b2 = c2.b;
    if((a1/b1) == (a2/b2)) return 2;
    return (a1/b1) > (a2/b2);
}

int rLess(Rational c1, Rational c2){
    float a1 = c1.a, b1 = c1.b;
    float a2 = c2.a, b2 = c2.b;
    if((a1/b1) == (a2/b2)) return 2;
    return (a1/b1) < (a2/b2);
}


void menu(){
    cout << "Меню:" <<endl
        << "(1)Вв. дробь d1" << endl
        << "(2)Вв. дробь d2" << endl
        << "(3)Выв. дробь d1" << endl
        << "(4)Выв. дробь d2" << endl
        << "(5)Выв. дробь d1 через string" << endl
        << "(6)Выв. дробь d2 через string" << endl
        << "(7)Выв. d1 + d2" << endl
        << "(8)Выв. d1 - d2" << endl
        << "(9)Выв. d1 * d2" << endl
        << "(10)Выв. d1 / d2" << endl
        << "(11)Выв. d1 == d2" << endl
        << "(12)Выв. d1 > d2" << endl
        << "(13)Выв. d1 < d2" << endl
        << "(0)Выход" << endl
        << "Ввод: ";
}

int main() {
    Rational d1, d2, d3;
    int choice = 0;
    do{
        menu();
        cin >> choice;
        
        switch(choice){
            case 1: d1.read(); break;
            case 2: d2.read(); break;
            case 3: d1.display(); break;
            case 4: d2.display(); break;
            case 5: cout << toString(d1) << endl; break;
            case 6: cout << toString(d2) << endl; break;
            case 7: 
                d3 = add(d1, d2); 
                d3.display(); 
                break;
            case 8: 
                d3 = sub(d1, d2); 
                d3.display(); 
                break;
            case 9: 
                d3 = mul(d1, d2); 
                d3.display(); 
                break;
            case 10: 
                d3 = div(d1, d2); 
                d3.display(); 
                break;
            case 11: cout << (equal(d1, d2)?"d1 == d2":"d1 != d2") << endl; break;
            case 12: 
                if(greate(d1, d2)==2) {cout << "d1 == d2" << endl; break;}
                else {cout << (greate(d1, d2)?"d1 > d2":"d1 < d2") << endl; break;}
            case 13: 
                if(greate(d1, d2)==2) {cout << "d1 == d2" << endl; break;}
                else {cout << (rLess(d1, d2)?"d1 < d2":"d1 > d2") << endl; break;}
        }
    }while(choice);
    return 0;
}
