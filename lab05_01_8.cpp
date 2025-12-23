#include <iostream>
#include <string>
using namespace std;

template <typename T> void heap(T mas[], int n, int i){
    int large = i; //наибольший как корень
    int left = 2*i + 1;
    int right = 2*i + 2;

    //левый больше корня
    if(left < n && mas[left] > mas[large]) large = left;
    //правый больше чем наибольший на данный момент
    if(right < n && mas[right] > mas[large]) large = right;
    //если наибольший не корень
    if(large != i){
        T temp = mas[i];
        mas[i] = mas[large];
        mas[large] = temp;
        heap(mas, n, large);
    }
}

template <typename T> void sortHeap(T mas[], int n){
    for(int i=n/2 - 1; i>=0; i--) heap(mas, n, i);
    for(int i=n - 1; i>0; i--){
        T temp = mas[0];
        mas[0] = mas[i];
        mas[i] = temp;
        heap(mas, i, 0);
    }
}

int main() {
    int intMas[] = {60, 72, 9, 86, 63, 98, 93};
    int intN = sizeof(intMas) / sizeof(intMas[0]); //кол-во эл в массиве

    cout << "Массив int:" << endl;
    for(int i=0; i<intN; i++) cout << intMas[i] << " ";
    cout << endl;

    sortHeap(intMas, intN);

    cout << "Отсортированный Массив int:" << endl;
    for(int i=0; i<intN; i++) cout << intMas[i] << " ";
    cout << endl;


    string strMas[] = {"aftermath", "secretary", "assort", "decrease", "coat", "lettuce"};
    int strN = sizeof(strMas) / sizeof(strMas[0]);

    cout << "Массив string:" << endl;
    for(int i=0; i<strN; i++) cout << strMas[i] << " ";
    cout << endl;

    sortHeap(strMas, strN);

    cout << "Отсортированный Массив string:" << endl;
    for(int i=0; i<strN; i++) cout << strMas[i] << " ";
    cout << endl;



    double doubleMas[] = {9.14, 3.84, 7.61, 0.74, 7.54, 2.38, 4.45, 5.81, 4.34, 9.09};
    int doubleN = sizeof(doubleMas) / sizeof(doubleMas[0]); //кол-во эл в массиве

    cout << "Массив double:" << endl;
    for(int i=0; i<doubleN; i++) cout << doubleMas[i] << " ";
    cout << endl;

    sortHeap(doubleMas, doubleN);

    cout << "Отсортированный Массив double:" << endl;
    for(int i=0; i<doubleN; i++) cout << doubleMas[i] << " ";
    cout << endl;
}
