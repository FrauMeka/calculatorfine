#include<iostream>
#include<stack>
#include<cmath>

using namespace std;

// Функция для выполнения математических операций
double calculate(char op, double left, double right = 0) {
    
    if (op == '+') 
        return left + right; 
    else if (op == '-') 
        return left - right; 
    else if (op == '*') 
        return left * right; 
    else if (op == '/') { 
        if (right != 0) 
            return left / right; 
        else {
            cout << "Error: Division by zero!" << endl; //
            return 0;
        }
    }
    else if (op == '^') 
        return pow(left, right); 
    else if (op == 's') 
        return sqrt(left); 
    else if (op == 'r')
        return round(left); 
    else if (op == 'a') 
        return abs(left);
    return 0; // Этот случай не должен произойти в корректном выражении
}

// Функция для определения приоритета оператора
int pri(char op) {
    if (op == '^' || op == 'r' || op == 's' || op == 'a') // 
        return 3;
    else if (op == '*' || op == '/') 
        return 2; 
    else if (op == '+' || op == '-') 
        return 1; 
    return -1; // Этот случай не должен произойти в корректном выражении
}

int main() {
    cout << "Welcome to the Mathematical Expression Calculator!" << endl;
    cout << "This calculator can evaluate basic mathematical expressions including addition, subtraction, multiplication, division, square root, rounding, and absolute value." << endl;
    cout << "Use s(n) for sqrt, r(n) for round, a(n)for abs."<<endl;
    char choice = 'y';
    while (choice == 'y' || choice == 'Y') {
       
        string math;
        cout << "Enter a mathematical expression: ";
        getline(cin, math);

        // Инициализируем стеки для операторов и операндов
        stack<char> s; // Стек для операторов
        stack<double> op_s; // Стек для операндов

        double number = 0; // Переменная для хранения числа
        double decimalPlace = 10; // Переменная для учета десятичных разрядов

        // Обрабатываем каждый символ в строке математического выражения
        for (auto i = 0; i < math.size(); i++) {
            if (isdigit(math[i])) { // Если символ является цифрой
                number = number * 10 + (math[i] - '0'); // Формируем число
            } else if (math[i] == '.') { // Если символ является точкой (для десятичной дроби)
                i++; // Переходим к следующему символу после точки
                while (i < math.size() && isdigit(math[i])) { // Пока следующий символ - цифра
                    number += (math[i] - '0') / decimalPlace; // Добавляем дробную часть числа
                    decimalPlace *= 10; // Увеличиваем разряд десятых
                    i++; // Переходим к следующему символу
                }
                i--; // Возвращаемся на один символ назад, чтобы не пропустить следующий символ после дроби
            } else if (math[i] == '(') { // Если символ является открывающей скобкой
                s.push('('); // Помещаем ее в стек операторов
            } else if (math[i] == ')') { // Если символ является закрывающей скобкой
                op_s.push(number); // Помещаем число в стек операндов
                number = 0; // Обнуляем число для следующего использования
                decimalPlace = 10; // Сбрасываем разряд десятых
                while (s.top() != '(') { // Пока верхний элемент стека операторов не является открывающей скобкой
                    double r = op_s.top(); // Получаем верхний операнд
                    op_s.pop(); // Удаляем его из стека
                    double l = op_s.top(); // Получаем следующий операнд
                    op_s.pop(); // Удаляем его из стека
                    double re = calculate(s.top(), l, r); // Выполняем операцию с помощью оператора
                    op_s.push(re); // Помещаем результат обратно в стек операндов
                    s.pop(); // Удаляем использованный оператор из стека
                }
                s.pop(); // Удаляем открывающую скобку из стека операторов
            } else if (math[i] == '+' || math[i] == '-' || math[i] == '*' || math[i] == '/' || math[i] == '^' || math[i] == 's' || math[i] == 'r' || math[i] == 'a') { 
                op_s.push(number); // Помещаем число в стек операндов
                number = 0; // Обнуляем число для следующего использования
                decimalPlace = 10; // Сбрасываем разряд десятых

                int pC = pri(math[i]); // Получаем приоритет текущего оператора
                while (!s.empty() && pri(s.top()) >= pC) { // Пока стек операторов не пуст и приоритет верхнего оператора больше или равен приоритету текущего оператора
                    double r = op_s.top(); // Получаем верхний операнд
                    op_s.pop(); // Удаляем его из стека
                    double l = op_s.top(); // Получаем следующий операнд
                    op_s.pop(); // Удаляем его из стека
                    double re = calculate(s.top(), l, r); // Выполняем операцию с помощью оператора
                    op_s.push(re); // Помещаем результат обратно в стек операндов
                    s.pop(); // Удаляем использованный оператор из стека
                }
                s.push(math[i]); // Помещаем текущий оператор в стек операторов
            }
        }

        // Помещаем последнее обработанное число в стек операндов
        op_s.push(number);

        // Обрабатываем оставшиеся операторы
        while (!s.empty()) {
            double r = op_s.top(); // Получаем верхний операнд
            op_s.pop(); // Удаляем его из стека
            double l = op_s.top(); // Получаем следующий операнд
            op_s.pop(); // Удаляем его из стека
            double re = calculate(s.top(), l, r); // Выполняем операцию с помощью оператора
            op_s.push(re); // Помещаем результат обратно в стек операндов
            s.pop(); // Удаляем использованный оператор из стека
        }

        
        cout << "Result:" << op_s.top() << endl;


        cout << "Do you want to continue (y/n)?";
        cin >> choice;
        
       
        while (cin.get() != '\n');

    }
    
    cout << "До свидания!" << endl; 
    return 0;
}
