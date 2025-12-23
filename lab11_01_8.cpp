#include <iostream>
using namespace std;

enum class TempScale {C, F, K}; //цельсий, фарренгейт, кельвин

constexpr auto convTemp = [](double value, TempScale from, TempScale to) constexpr {
    //цельсий - база
    double c=0;
    
    switch (from) {
        case TempScale::C:
            c = value;
            break;
        case TempScale::F:
            c = (value - 32.0)*5/9;
            break;
        case TempScale::K:
            c = value - 273.15;
            break;
    }
    
    switch (to) {
        case TempScale::C:
            return c;
        case TempScale::F:
            return c*9/5 + 32.0;
        case TempScale::K:
            return c + 273.15;
        default:
            return c;
    }
};

int main() {
    double cBoil = 100;
    double fBoil = convTemp(cBoil, TempScale::C, TempScale::F);
    double kBoil = convTemp(fBoil, TempScale::F, TempScale::K);
    cout << "Темп. кипения воды в C: " << cBoil << endl
    << "Темп. кипения воды в F: " << fBoil << endl
    << "Темп. кипения воды в K: " << kBoil << endl;
}
