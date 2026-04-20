#include <iostream>
using namespace std;

struct Para{
    int first, second;
    
    Para(int sfirst = 1, int ssecond= 3){
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
        else return 0;
    }
    
};

Para make_Para(int l, int r){
    if(l>=r){cout << "Ошибка"; exit(0);}
    Para sus;
    sus.first = l;
    sus.second = r;
    return sus;
}

int main() {
    int n;
    Para one;
    Para two = make_Para(1, 10);
    do{
    one.read();
    one.display();
    
    cout<<"Вв. число для проверки диапозона 1: "; cin >> n;
    
    if(one.rangecheck(n)) cout<<"В диапозоне 1"<< endl;
    else cout<<"Вне диапозона 1" << endl;
    
    two.display();
    
    cout<<"Вв. число для проверки диапозона 2: "; cin >> n;
    
    if(two.rangecheck(n)) cout<<"В диапозоне 2"<< endl;
    else cout<<"Вне диапозона 2" << endl;
    
    cout<<"Продолжать ввод? 1-да, 0-нет "; cin>> n;
    }while(n);
    return 0;
}
