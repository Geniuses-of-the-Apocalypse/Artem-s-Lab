#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const double PI = 3.14159;

class Triangle{
    protected:
        double a,b,c;
        
    public:
        Triangle(double aa=1, double bb=1, double cc=1);
        
        void changeA(double aa);
        void changeB(double bb);
        void changeC(double cc);
        bool validTriangle();
        
        void calcAngles(double& angleAlpha, double& angleBeta, double& angleGamma);
        double calcPerim();
        
        friend istream& operator >> (istream& i, Triangle& var);
        friend ostream& operator << (ostream& o, const Triangle& var);
        
};

Triangle::Triangle(double aa, double bb, double cc){
    changeA(aa); 
    changeB(bb); 
    changeC(cc);
    if(!(validTriangle())){
        cout << "Ошибка (Одна из сторон больше суммы двух других). Выход из программы"; 
        exit(0);
    }
}

void Triangle::changeA(double aa){
    if(aa<=0){cout << "Ошибка (А<0). Выход из программы"; exit(0);}
    a = aa;
}

void Triangle::changeB(double bb){
    if(bb<=0){cout << "Ошибка (B<0). Выход из программы"; exit(0);}
    b = bb;
}

void Triangle::changeC(double cc){
    if(cc<=0){cout << "Ошибка (C<0). Выход из программы"; exit(0);}
    c = cc;
}

bool Triangle::validTriangle(){
    bool abMorec, acMoreb, bcMorea, allSidesValid;
    abMorec = (a+b) > c;
    acMoreb = (a+c) > b;
    bcMorea = (b+c) > a;
    allSidesValid = a>0 && b>0 && c>0;
    return abMorec && acMoreb && bcMorea && allSidesValid;
}

void Triangle::calcAngles(double& angleAlpha, double& angleBeta, double& angleGamma){
    //альфа - угол между сторонами a и c
    //бета - угол между сторонами a и b
    //гамма - угол между сторонами c и b
    angleAlpha = acos((a*a + c*c - b*b) / (2*a*c)) * 180/PI;
    angleBeta = acos((a*a + b*b - c*c) / (2*a*b)) * 180/PI;
    angleGamma = acos((c*c + b*b - a*a) / (2*c*b)) * 180/PI;
}

double Triangle::calcPerim(){return a+b+c;}

istream& operator >> (istream& i, Triangle& var){
    i >> var.a >> var.b >> var.c;
    if(!(var.validTriangle())){
        cout << "Ошибка. Выход из программы"; 
        exit(0);
    }
    return i;
}

ostream& operator << (ostream& o, const Triangle& var){
    o << "Сторона A = " << var.a << endl
    << "Сторона B = " << var.b << endl
    << "Сторона C = " << var.c << endl;
    return o;
}

class RightAngle : public Triangle{
    private:
        double area;
    public:
        RightAngle(double aa=3, double bb=4, double cc=5);

        int validRightAngle();
        
        double calcArea(int type);

        friend istream& operator >> (istream& i, RightAngle& var);
        friend ostream& operator << (ostream& o, const RightAngle& var);
};

RightAngle::RightAngle(double aa, double bb, double cc): Triangle(aa,bb,cc){
    if(validRightAngle() == 0){
        cout << "Ошибка (Не яв. прямоугольным треугольником). Выход из программы"; 
        exit(0);
    area = calcArea(validRightAngle());
    }

    
}

//определяет прямоугольный-ли треугольник и какая у него гипотенуза
// 0 - не прям. треуг, 1 - гипотенуза A, 2 - гипотенуза B, 3 - гипотенуза C
int RightAngle::validRightAngle(){
    bool abEqualc, acEqualb, bcEquala;
    abEqualc = (a*a + b*b) == (c*c);
    acEqualb = (a*a + c*c) == (b*b);
    bcEquala = (b*b + c*c) == (a*a);

    if(bcEquala) return 1; 
    if(acEqualb) return 2;
    if(abEqualc) return 3;
    else return 0;
}

double RightAngle::calcArea(int type){
    switch(type){
        case 1: return b*c*0.5;
        case 2: return a*c*0.5;
        case 3: return a*b*0.5;
    }
    cout << "Ошибка (Не яв. прямоугольным треугольником). Выход из программы"; exit(0);
}

istream& operator >> (istream& i, RightAngle& var){
    i >> var.a >> var.b >> var.c;
    var.area = var.calcArea(var.validRightAngle());
    //не ввожу случай ошибки тк его calcArea покрывает
    return i;
}

ostream& operator << (ostream& o, const RightAngle& var){
    o << "Сторона A = " << var.a << endl
    << "Сторона B = " << var.b << endl
    << "Сторона C = " << var.c << endl
    << "Площадь = " << var.area << endl;
    return o;
}

int main() {
    int choice;
    double change;
    Triangle tri;
    cout << "Вв. треугольник" << endl; cin >> tri;
    cout << tri;

    do{
        cout << "Поменять сторону? 0-нет 1-да: "; cin >> choice;
        if(!choice) break;
        cout << "1-A, 2-B, 3-C, 0-выход: "; cin >> choice;
        switch(choice){
            case 1: {
                cin >> change;
                tri.changeA(change);
            }
            case 2: {
                cin >> change;
                tri.changeB(change);
            }
            case 3: {
                cin >> change;
                tri.changeC(change);
            }
        }
    }while(choice);
    
    double angle1, angle2, angle3;
    tri.calcAngles(angle1,angle2,angle3);

    cout << "Углы треуглольника:" << endl
    << angle1 << endl
    << angle2 << endl
    << angle3 << endl;

    cout << "Периметр = " << tri.calcPerim() << endl;

    RightAngle rig;
    cout << "Вв. прямоугольный треугольник" << endl; cin >> rig;
    cout << rig;

    do{
        cout << "Поменять сторону? 0-нет 1-да: "; cin >> choice;
        if(!choice) break;
        cout << "1-A, 2-B, 3-C, 0-выход: "; cin >> choice;
        switch(choice){
            case 1: {
                cin >> change;
                rig.changeA(change);
                if(rig.validRightAngle() == 0){cout << "Ошибка (Не яв. прямоугольным треугольником). Выход из программы"; exit(0);}
            }
            case 2: {
                cin >> change;
                rig.changeB(change);
                if(rig.validRightAngle() == 0){cout << "Ошибка (Не яв. прямоугольным треугольником). Выход из программы"; exit(0);}
            }
            case 3: {
                cin >> change;
                rig.changeC(change);
                if(rig.validRightAngle() == 0){cout << "Ошибка (Не яв. прямоугольным треугольником). Выход из программы"; exit(0);}
            }
        }
    }while(choice);

    rig.calcAngles(angle1,angle2,angle3);

    cout << "Углы треуглольника:" << endl
    << angle1 << endl
    << angle2 << endl
    << angle3 << endl;

    cout << "Периметр = " << rig.calcPerim() << endl;
    return 0;
}
