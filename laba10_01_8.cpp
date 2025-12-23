//C++ 11
#include <iostream>
#include <type_traits>
using namespace std;

// базовый случай: один аргумент
template<typename T>
auto reverseArgs(T arg) {return arg;}

// рекурсивный случай: несколько аргументов
template<typename First, typename Second, typename... Rest>
typename common_type<First, Second, Rest...>::type 
reverseArgs(First first, Second second, Rest... rest) {
    return reverseArgs(second, rest..., first);
}

int main() {
    auto result1 = reverseArgs(1);
    cout << "reverseArgs(1) = " << result1 << endl;
    auto result2 = reverseArgs(1, 2);
    cout << "reverseArgs(1, 2) = " << result2 << endl;
    auto result3 = reverseArgs(1, 2, 3);
    cout << "reverseArgs(1, 2, 3) = " << result3 << endl;
    auto result4 = reverseArgs(1, 2, 3, 4);
    cout << "reverseArgs(1, 2, 3, 4) = " << result4 << endl;
}
