#include <iostream>

//вспомогательная структура для хранения значений
template<typename... Ts>
struct ReversedTuple;

//специализация для пустого набора
template<>
struct ReversedTuple<> {
    static auto reverse() {
        return []() {};
    }
};

//специализация для непустого набора
template<typename T, typename... Ts>
struct ReversedTuple<T, Ts...> {
    static auto reverse(T&& first, Ts&&... rest) {
        return [first = std::forward<T>(first), 
                rest_tuple = ReversedTuple<Ts...>::reverse(std::forward<Ts>(rest)...)]() mutable {
            rest_tuple();
            return first;
        };
    }
};

//основная функция для C++17
template<typename... Args>
auto reverseArgs17(Args&&... args) {
    //fold expression для создания лямбды
    auto printer = [&args...]() {
        (std::cout << ... << args);
    };
    
    //возвращаем функцию, которая будет вызываться рекурсивно
    return ReversedTuple<Args...>::reverse(std::forward<Args>(args)...);
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
