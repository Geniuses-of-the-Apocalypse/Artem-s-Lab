#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Array {
protected:
    static const int MAX_SIZE = 100;
    unsigned char* data;
    int count;

public:
    //конструктор инициализации
    Array(int n = 0, unsigned char initVal = 0) {
        if (n < 0) n = 0;
        if (n > MAX_SIZE) n = MAX_SIZE;
        
        count = n;
        data = new unsigned char[MAX_SIZE];
        
        for (int i = 0; i < n; i++) {
            data[i] = initVal;
        }
        for (int i = n; i < MAX_SIZE; i++) {
            data[i] = 0;
        }
    }
    
    //конструктор копирования
    Array(const Array& other) {
        count = other.count;
        data = new unsigned char[MAX_SIZE];
        
        for (int i = 0; i < MAX_SIZE; i++) {
            data[i] = other.data[i];
        }
    }
    
    //деструктор
    virtual ~Array() {
        delete[] data;
    }
    
    //оператор присваивания
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            count = other.count;
            data = new unsigned char[MAX_SIZE];
            
            for (int i = 0; i < MAX_SIZE; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    //оператор индексирования с проверкой
    unsigned char& operator[](int index) {
        if (index < 0 || index >= count) {
            static unsigned char dummy;
            cerr << "Индекс " << index << " выходит за границы [0, " << count-1 << "]" << endl;
            return dummy;
        }
        return data[index];
    }
    
    const unsigned char& operator[](int index) const {
        if (index < 0 || index >= count) {
            static unsigned char dummy;
            cerr << "Индекс " << index << " выходит за границы [0, " << count-1 << "]" << endl;
            return dummy;
        }
        return data[index];
    }
    
    //виртуальный метод сложения
    virtual Array* addArrays(const Array& other) const {
        int newCount = (count > other.count) ? count : other.count;
        Array* result = new Array(newCount);
        
        for (int i = 0; i < newCount; i++) {
            unsigned char val1 = (i < count) ? data[i] : 0;
            unsigned char val2 = (i < other.count) ? other.data[i] : 0;
            result->data[i] = val1 + val2;
        }
        
        return result;
    }
    
    int getCount() const { return count; }
    int getMaxSize() const { return MAX_SIZE; }
    
    //метод для вывода массива
    virtual void print() const {
        cout << "Массив [" << count << "]: ";
        for (int i = 0; i < count; i++) {
            cout << (int)data[i] << " ";
        }
        cout << endl;
    }
};

//класс для работы с шестнадцатеричными числами
class Hex : public Array {
public:
    Hex(int n = 0, unsigned char initVal = 0) : Array(n, initVal) {
        //проверка, что все цифры в диапазоне 0-15
        for (int i = 0; i < n; i++) {
            if (data[i] > 15) data[i] = 15;
        }
    }
    
    //переопределение метода сложения для шестнадцатеричных чисел
    Hex* addArrays(const Array& other) const override {
        const Hex* otherHex = dynamic_cast<const Hex*>(&other);
        if (!otherHex) {
            cerr << "Ошибка: попытка сложить Hex с другим типом объекта" << endl;
            return nullptr;
        }
        
        int newCount = (count > otherHex->count) ? count : otherHex->count;
        Hex* result = new Hex(newCount);
        
        int carry = 0;
        for (int i = 0; i < newCount || carry; i++) {
            if (i >= MAX_SIZE) {
                cerr << "Переполнение максимального размера" << endl;
                break;
            }
            
            unsigned char val1 = (i < count) ? data[i] : 0;
            unsigned char val2 = (i < otherHex->count) ? otherHex->data[i] : 0;
            int sum = val1 + val2 + carry;
            
            result->data[i] = sum % 16;
            carry = sum / 16;
            
            if (i >= newCount) {
                result->count = i + 1;
            }
        }
        
        return result;
    }
    
    //метод для преобразования в строку
    string toString() const {
        string result;
        bool leadingZero = true;
        
        for (int i = count - 1; i >= 0; i--) {
            if (data[i] == 0 && leadingZero && i != 0) continue;
            leadingZero = false;
            
            if (data[i] < 10) {
                result += ('0' + data[i]);
            } else {
                result += ('A' + (data[i] - 10));
            }
        }
        
        return result.empty() ? "0" : result;
    }
    
    void print() const override {
        cout << "Hex число: " << toString() << " (в массиве: ";
        for (int i = 0; i < count; i++) {
            cout << (int)data[i] << " ";
        }
        cout << ")" << endl;
    }
};

//класс для работы с восьмеричными числами
class Octal : public Array {
public:
    Octal(int n = 0, unsigned char initVal = 0) : Array(n, initVal) {
        //проверка, что все цифры в диапазоне 0-7
        for (int i = 0; i < n; i++) {
            if (data[i] > 7) data[i] = 7;
        }
    }
    
    //переопределение метода сложения для восьмеричных чисел
    Octal* addArrays(const Array& other) const override {
        const Octal* otherOctal = dynamic_cast<const Octal*>(&other);
        if (!otherOctal) {
            cerr << "Ошибка: попытка сложить Octal с не-Octal объектом" << endl;
            return nullptr;
        }
        
        int newCount = (count > otherOctal->count) ? count : otherOctal->count;
        Octal* result = new Octal(newCount);
        
        int carry = 0;
        for (int i = 0; i < newCount || carry; i++) {
            if (i >= MAX_SIZE) {
                cerr << "Переполнение максимального размера!" << endl;
                break;
            }
            
            unsigned char val1 = (i < count) ? data[i] : 0;
            unsigned char val2 = (i < otherOctal->count) ? otherOctal->data[i] : 0;
            int sum = val1 + val2 + carry;
            
            result->data[i] = sum % 8;
            carry = sum / 8;
            
            if (i >= newCount) {
                result->count = i + 1;
            }
        }
        
        return result;
    }
    
    //метод для преобразования в строку
    string toString() const {
        string result;
        bool leadingZero = true;
        
        for (int i = count - 1; i >= 0; i--) {
            if (data[i] == 0 && leadingZero && i != 0) continue;
            leadingZero = false;
            result += ('0' + data[i]);
        }
        
        return result.empty() ? "0" : result;
    }
    
    void print() const override {
        cout << "Octal число: " << toString() << " (в массиве: ";
        for (int i = 0; i < count; i++) {
            cout << (int)data[i] << " ";
        }
        cout << ")" << endl;
    }
};

int main() {
    //работа с классом Array
    cout << "1. Array:" << endl;
    Array arr1(5, 3);  //массив из 5 элементов, каждый равен 3
    Array arr2(3, 4); 
    
    cout << "arr1: ";
    arr1.print();
    cout << "arr2: ";
    arr2.print();
    
    Array* sumArray = arr1.addArrays(arr2);
    cout << "Сумма arr1 + arr2: ";
    sumArray->print();
    delete sumArray;
    
    cout << "\n2. Hex:" << endl;
    //создаем шестнадцатеричное число 0x1A5
    Hex hex1(3);
    hex1[0] = 5;  //младший разряд
    hex1[1] = 10; //A
    hex1[2] = 1;  //старший разряд
    
    //создаем шестнадцатеричное число 0x2F
    Hex hex2(2);
    hex2[0] = 15; //F
    hex2[1] = 2; 
    
    cout << "hex1 = ";
    hex1.print();
    cout << "hex2 = ";
    hex2.print();
    
    //вызов через указатель на базовый класс
    Array* hexPtr1 = &hex1;
    Array* hexPtr2 = &hex2;
    Array* hexSum = hexPtr1->addArrays(*hexPtr2);
    
    if (hexSum) {
        cout << "Сумма hex1 + hex2 = ";
        hexSum->print();
        delete hexSum;
    }
    
    cout << "\n3. Octal:" << endl;
    //создаем восьмеричное число 075 (61 в десятичной)
    Octal oct1(2);
    oct1[0] = 5;  
    oct1[1] = 7; 
    
    //создаем восьмеричное число 014
    Octal oct2(2);
    oct2[0] = 4;
    oct2[1] = 1;
    
    cout << "oct1 = ";
    oct1.print();
    cout << "oct2 = ";
    oct2.print();
    
    //вызов через указатель на базовый класс
    Array* octPtr1 = &oct1;
    Array* octPtr2 = &oct2;
    Array* octSum = octPtr1->addArrays(*octPtr2);
    
    if (octSum) {
        cout << "Сумма oct1 + oct2 = ";
        octSum->print();
        delete octSum;
    }
    
    cout << "\n4. Демонстрация полиморфизма:" << endl;
    //массив указателей на базовый класс
    Array* objects[4];
    objects[0] = new Hex(2);
    dynamic_cast<Hex*>(objects[0])->operator[](0) = 12; //C
    dynamic_cast<Hex*>(objects[0])->operator[](1) = 1;
    
    objects[1] = new Hex(3);
    dynamic_cast<Hex*>(objects[1])->operator[](0) = 8; 
    dynamic_cast<Hex*>(objects[1])->operator[](1) = 3; 
    dynamic_cast<Hex*>(objects[1])->operator[](2) = 2;  
    
    objects[2] = new Octal(2);
    dynamic_cast<Octal*>(objects[2])->operator[](0) = 7; 
    dynamic_cast<Octal*>(objects[2])->operator[](1) = 5; 
    
    objects[3] = new Octal(3);
    dynamic_cast<Octal*>(objects[3])->operator[](0) = 4; 
    dynamic_cast<Octal*>(objects[3])->operator[](1) = 3;  
    dynamic_cast<Octal*>(objects[3])->operator[](2) = 1; 
    
    for (int i = 0; i < 4; i++) {
        cout << "Объект " << i << ": ";
        objects[i]->print();
    }
    
    //сложение объектов одного типа через виртуальный метод
    cout << "\nСложение объектов 0 и 1 (оба Hex):" << endl;
    Array* sum1 = objects[0]->addArrays(*objects[1]);
    if (sum1) {
        sum1->print();
        delete sum1;
    }
    
    cout << "\nСложение объектов 2 и 3 (оба Octal):" << endl;
    Array* sum2 = objects[2]->addArrays(*objects[3]);
    if (sum2) {
        sum2->print();
        delete sum2;
    }
    
    //попытка сложить объекты разных типов
    cout << "\nПопытка сложить объекты 0 и 2 (Hex и Octal):" << endl;
    Array* sum3 = objects[0]->addArrays(*objects[2]);
    if (sum3) {
        sum3->print();
        delete sum3;
    }
    
    //очистка памяти
    for (int i = 0; i < 4; i++) {
        delete objects[i];
    }
    

    cout << "\n5. Проверка оператора индексирования:" << endl;
    Array test(3, 7);
    cout << "test[0] = " << (int)test[0] << endl;
    cout << "test[1] = " << (int)test[1] << endl;
    cout << "test[2] = " << (int)test[2] << endl;
    cout << "Попытка доступа к test[10]: ";
    unsigned char val = test[10];
    
    return 0;
}
