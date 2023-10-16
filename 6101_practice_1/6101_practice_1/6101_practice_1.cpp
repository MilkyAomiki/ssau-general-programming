// Расчет параметров угла
#include <iostream>
using namespace std;
int main() {
    setlocale(LC_ALL, "RU");
    int angle;
    double pi = atan(1) * 4;


    char ans;
    //do {
    cout << "Введите значение угла в градусах: ";
    cin >> angle;
    cout << "sin(" << angle << ") = " << sin(angle * pi / 180.0) << endl;
    cout << "cos(" << angle << ") = " << cos(angle * pi / 180.0) << endl;
    cout << "tg(" << angle << ") = " << tan(angle * pi / 180.0) << endl;

    cout << "Хотите ли Вы продолжить?(Y/N)" << endl;  //Запрос на повтор программы

    cin >> ans;
    // } while ((ans == 'Y') || (ans == 'y'));



    // } while (!(cin >> ans) || (cin.peek() != '\n') || ((ans != 'Y') && (ans != 'y') && (ans != 'n') && (ans != 'N'))); {
      //   cin.clear();
       //  while (cin.get() != '\n');
       //  cout << "Данные введены некорректно! Попробуйте снова " << endl;







    return 0;
}
