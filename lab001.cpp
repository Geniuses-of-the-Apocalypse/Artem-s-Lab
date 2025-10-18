#include <iostream>
using namespace std;

struct para{
    int first, second;
    
    para(int sfirst = 1, int ssecond= 3){
        first = sfirst;
        second = ssecond;
    }
    
    void read(){
        do{
        cout << "Вв. левую границу диапозона(вкл): "; cin >> first;
        cout << "Вв. правую границу диапозона(не вкл): "; cin >> second;
        if(first>= second) cout<<"Ошибка ввода" << endl;
        }while(first>=second);
    }
    
    void display(){
        cout << "Левая граница диапозона(вкл): " << first << endl;
        cout << "Правая граница диапозона(не вкл): " << second << endl;
    }
    
    int rangecheck(int num){
        if(num >= first && num < second) return 1;
        return 0;
    }
};

int main() {
    int n;
    para one;
    do{
    one.read();
    one.display();
    
    cout<<"Вв. число для проверки диапозона: "; cin >> n;
    
    if(one.rangecheck(n)) cout<<"В диапозоне"<< endl;
    else cout<<"Вне диапозона" << endl;
    
    cout<<"Продолжать ввод? 1-да, 0-нет "; cin>> n;
    }while(n);
    return 0;
}
