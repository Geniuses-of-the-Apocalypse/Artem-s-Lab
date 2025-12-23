#include <iostream>
#include <cmath>
#include <string>
#include <exception>

using namespace std;

class FazzyNumber {
private:
    double left;//x - e1
    double x;
    double right;//x + e2
    
public:
    FazzyNumber(double l, double c, double r) : left(l), x(c), right(r) {}
    
    double getLeft() const {return left;}
    double getX() const {return x;}
    double getRight() const {return right;}
    double getE1() const {return x - left;}
    double getE2() const {return right - x;}
    
    void print() const {
        cout << "(" << left << ", " << x << ", " << right << ")";
    }
};

class FuzzyInverseExceptionEmpty {};

class FuzzyInverseExceptionWithParams {
public:
    double left, x, right;
    string message;
    
    FuzzyInverseExceptionWithParams(double l, double c, double r, const string& mes) 
        : left(l), x(c), right(r), message(mes) {}
};

class FuzzyInverseStdException : public exception {
private:
    double left, x, right;
    string errMes;
    
public:
    FuzzyInverseStdException(double l, double c, double r, const string& mes) 
        : left(l), x(c), right(r), errMes(mes) {}
    
    const char* what() const noexcept override {
        return errMes.c_str();
    }
    
    double getLeft() const {return left;}
    double getX() const {return x;}
    double getRight() const {return right;}
};

bool isValidFuzzyNumber(const FazzyNumber& num) {
    return !(isnan(num.getLeft()) || isnan(num.getX()) || isnan(num.getRight()) || isinf(num.getLeft()) || isinf(num.getX()) || isinf(num.getRight()));
}

//ф-ция для вычисления обратного нечеткого числа
FazzyNumber calculateInverse(const FazzyNumber& num) {
    double x = num.getX();
    double e1 = num.getE1();
    double e2 = num.getE2();
    
    double invLeft = 1.0/(x + e2);//1/(A+ar)
    double invX = 1.0/x;//1/A
    double invRight = 1.0/(x - e1);//1/(A-al)
    
    return FazzyNumber(invLeft, invX, invRight);
}

//1. Без спецификации исключений
FazzyNumber fuzzyInverse1(const FazzyNumber& num) {
    if (!isValidFuzzyNumber(num)) throw "Ошибка: параметры нечеткого числа содержат NaN или бесконечность";
    if (num.getX() <= 0) throw "Ошибка: центральное значение нечеткого числа должно быть положительным";
    if (num.getLeft() <= 0) throw "Ошибка: левая граница нечеткого числа должна быть положительной";
    if (abs(num.getX()) < 1e-15 || abs(num.getLeft()) < 1e-15) throw "Ошибка: деление на очень маленькое число";
    
    return calculateInverse(num);
}

//2. Ф-ция, которая не генерирует исключений noexcept (throw я не понял почему у меня не работает)
FazzyNumber fuzzyInverse2(const FazzyNumber& num) noexcept {
    if (!isValidFuzzyNumber(num) || num.getX() <= 0 || num.getLeft() <= 0 || 
        abs(num.getX()) < 1e-15 || abs(num.getLeft()) < 1e-15) {
        return FazzyNumber(NAN, NAN, NAN);
    }
    
    return calculateInverse(num);
}

//3. С использованием стандартных исключений
FazzyNumber fuzzyInverse3(const FazzyNumber& num) {
    if (!isValidFuzzyNumber(num)) throw invalid_argument("Параметры нечеткого числа содержат NaN или бесконечность");
    if (num.getX() <= 0) throw invalid_argument("Центральное значение нечеткого числа должно быть положительным");
    if (num.getLeft() <= 0) throw invalid_argument("Левая граница нечеткого числа должна быть положительной");
    if (abs(num.getX()) < 1e-15 || abs(num.getLeft()) < 1e-15) throw invalid_argument("Деление на очень маленькое число");
    
    return calculateInverse(num);
}

//4. С собственным исключением (пустой класс)
FazzyNumber fuzzyInverse4_1(const FazzyNumber& num) {
    if (!isValidFuzzyNumber(num) || num.getX() <= 0 || num.getLeft() <= 0 || 
        abs(num.getX()) < 1e-15 || abs(num.getLeft()) < 1e-15) throw FuzzyInverseExceptionEmpty();
    
    return calculateInverse(num);
}

//4. С собственным исключением (класс с полями)
FazzyNumber fuzzyInverse4_2(const FazzyNumber& num) {
    if (!isValidFuzzyNumber(num)) throw FuzzyInverseExceptionWithParams(num.getLeft(), num.getX(), num.getRight(), "Параметры нечеткого числа содержат NaN или бесконечность");
    if (num.getX() <= 0) throw FuzzyInverseExceptionWithParams(num.getLeft(), num.getX(), num.getRight(), "Центральное значение нечеткого числа должно быть положительным");
    if (num.getLeft() <= 0) throw FuzzyInverseExceptionWithParams(num.getLeft(), num.getX(), num.getRight(), "Левая граница нечеткого числа должна быть положительной");
    if (abs(num.getX()) < 1e-15 || abs(num.getLeft()) < 1e-15) throw FuzzyInverseExceptionWithParams(num.getLeft(), num.getX(), num.getRight(), "Деление на очень маленькое число");
    
    return calculateInverse(num);
}

//4. С собственным исключением (наследник от exception)
FazzyNumber fuzzyInverse4_3(const FazzyNumber& num) {
    if (!isValidFuzzyNumber(num)) throw FuzzyInverseStdException(num.getLeft(), num.getX(), num.getRight(), "Параметры нечеткого числа содержат NaN или бесконечность");
    if (num.getX() <= 0) throw FuzzyInverseStdException(num.getLeft(), num.getX(), num.getRight(), "Центральное значение нечеткого числа должно быть положительным");
    if (num.getLeft() <= 0) throw FuzzyInverseStdException(num.getLeft(), num.getX(), num.getRight(), "Левая граница нечеткого числа должна быть положительной");
    if (abs(num.getX()) < 1e-15 || abs(num.getLeft()) < 1e-15) throw FuzzyInverseStdException(num.getLeft(), num.getX(), num.getRight(), "Деление на очень маленькое число");
    
    return calculateInverse(num);
}

// Функция для тестирования
void testFunction(int variant, const FazzyNumber& num, const string& description) {
    cout << "Тест: " << description << " -> ";
    num.print();
    cout << endl;
    
    try {
        FazzyNumber result(NAN, NAN, NAN);
        bool hasResult = false;
        
        switch (variant) {
            case 1:
                result = fuzzyInverse1(num);
                hasResult = true;
                break;
            case 2:
                result = fuzzyInverse2(num);
                if (isnan(result.getX())) cout << "Ошибка: возвращено нечеткое число с NaN" << endl;
                else hasResult = true;
                break;
            case 3:
                result = fuzzyInverse3(num);
                hasResult = true;
                break;
            case 4:
                //С собственным исключением
                cout << "[Пустой класс]" << endl;
                try {
                    result = fuzzyInverse4_1(num);
                    cout << "Результат: ";
                    result.print();
                    cout << endl;
                } catch (const FuzzyInverseExceptionEmpty&) {
                    cout << "Поймано исключение FuzzyInverseExceptionEmpty" << endl;
                }
                
                cout << "[Класс с полями]" << endl;
                try {
                    result = fuzzyInverse4_2(num);
                    cout << "Результат: ";
                    result.print();
                    cout << endl;
                } catch (const FuzzyInverseExceptionWithParams& e) {
                    cout << "Поймано исключение FuzzyInverseExceptionWithParams: " 
                         << e.message << " (left=" << e.left << ", x=" << e.x << ", right=" << e.right << ")" << endl;
                }
                
                cout << "[Наследник от exception]" << endl;
                try {
                    result = fuzzyInverse4_3(num);
                    cout << "Результат: ";
                    result.print();
                    cout << endl;
                } catch (const FuzzyInverseStdException& e) {
                    cout << "Поймано исключение FuzzyInverseStdException: " 
                         << e.what() << " (left=" << e.getLeft() << ", x=" << e.getX() << ", right=" << e.getRight() << ")" << endl;
                }
                return;
        }
        
        if (hasResult) {
            cout << "Результат: ";
            result.print();
            cout << endl;
        }
        
    } catch (const char* e) {
        cout << "Поймано исключение типа const char*: " << e << endl;
    } catch (const string& e) {
        cout << "Поймано исключение типа string: " << e << endl;
    } catch (const invalid_argument& e) {
        cout << "Поймано исключение invalid_argument: " << e.what() << endl;
    } catch (const FuzzyInverseExceptionEmpty&) {
        cout << "Поймано исключение FuzzyInverseExceptionEmpty" << endl;
    } catch (const FuzzyInverseExceptionWithParams& e) {
        cout << "Поймано исключение FuzzyInverseExceptionWithParams: " 
             << e.message << " (left=" << e.left << ", x=" << e.x << ", right=" << e.right << ")" << endl;
    } catch (const FuzzyInverseStdException& e) {
        cout << "Поймано исключение FuzzyInverseStdException: " 
             << e.what() << " (left=" << e.getLeft() << ", x=" << e.getX() << ", right=" << e.getRight() << ")" << endl;
    } catch (const exception& e) {
        cout << "Поймано исключение: " << e.what() << endl;
    } catch (...) {
        cout << "Поймано неизвестное исключение" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    
    struct TestCase {
        FazzyNumber num;
        string description;
    };
    
    TestCase tests[] = {
        {FazzyNumber(2.0, 3.0, 4.0), "Нормальный случай (положительное число)"},
        {FazzyNumber(0.5, 1.0, 1.5), "Нормальный случай (другое положительное число)"},
        {FazzyNumber(-1.0, 0.0, 1.0), "Центральное значение = 0 (ошибка)"},
        {FazzyNumber(-2.0, -1.0, 0.0), "Отрицательное центральное значение (ошибка)"},
        {FazzyNumber(0.0, 1.0, 2.0), "Левая граница = 0 (ошибка)"},
        {FazzyNumber(NAN, 1.0, 2.0), "Левая граница = NaN (ошибка)"},
        {FazzyNumber(1.0, 2.0, INFINITY), "Правая граница = бесконечность (ошибка)"},
        {FazzyNumber(1e-16, 1e-15, 0.1), "Очень маленькое центральное значение (ошибка деления)"}
    };
    
    for (int variant = 1; variant <= 4; ++variant) {
        cout << "\n=== Тестирование " << variant << " ===" << endl;
        
        for (const auto& test : tests) {
            testFunction(variant, test.num, test.description);
            cout << endl;
        }
    }
    
    cout << "\n=== Демонстрация корректных вычислений ===" << endl;
    FazzyNumber normalNum(2.0, 3.0, 4.0);
    cout << "Исходное нечеткое число: ";
    normalNum.print();
    cout << endl;
    
    try {
        //обратное число по формуле (1/(A+ar), 1/A, 1/(A-al))
        double x = normalNum.getX();
        double e1 = normalNum.getE1(); // x - left
        double e2 = normalNum.getE2(); // right - x
        
        cout << "Формула: A' = (1/(" << x << "+" << e2 << "), 1/" << x << ", 1/(" << x << "-" << e1 << "))" << " = (1/" << (x + e2) << ", " << (1.0/x) << ", 1/" << (x - e1) << ")" << endl;
        
        FazzyNumber result1 = fuzzyInverse1(normalNum);
        FazzyNumber result2 = fuzzyInverse2(normalNum);
        FazzyNumber result3 = fuzzyInverse3(normalNum);
        FazzyNumber result4_1 = fuzzyInverse4_1(normalNum);
        FazzyNumber result4_2 = fuzzyInverse4_2(normalNum);
        FazzyNumber result4_3 = fuzzyInverse4_3(normalNum);
        
        cout << "Обратное нечеткое число: ";
        result1.print();
        cout << endl;
        
        //проверка, что все ф-ции дают одинаковый результат
        if (result1.getX() == result2.getX() && result2.getX() == result3.getX() &&
            result3.getX() == result4_1.getX() && result4_1.getX() == result4_2.getX() &&
            result4_2.getX() == result4_3.getX()) {
            cout << "Все функции дают одинаковый результат" << endl;
        } else {
            cout << "Расхождение в результатах" << endl;
        }
        
    } catch (...) {
        cout << "Неожиданная ошибка" << endl;
    }
    
    return 0;
}
