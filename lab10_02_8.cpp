#include <iostream>

// Вспомогательная структура для хранения значений
template<typename... Ts>
struct ReversedTuple;

// Специализация для пустого набора
template<>
struct ReversedTuple<> {
    static auto reverse() {
        return []() {};
    }
};

// Специализация для непустого набора
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

// Основная функция для C++17
template<typename... Args>
auto reverseArgs17(Args&&... args) {
    // Fold expression для создания лямбды
    auto printer = [&args...]() {
        (std::cout << ... << args);
    };
    
    // Возвращаем функцию, которая будет вызываться рекурсивно
    return ReversedTuple<Args...>::reverse(std::forward<Args>(args)...);
}
