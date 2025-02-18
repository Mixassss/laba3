#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <windows.h>

using namespace std;

vector<int> Eratos(int num) { // решето Эратосфена
    vector<int> numbersToNum; //Создает вектор numbersToNum и заполняет его числами от 0 до num - 1.
    vector<int> Prostie; //Создает вектор Prostie для хранения простых чисел.
    for (int i = 0; i < num; i++) {
        numbersToNum.push_back(i); 
    }

    for (int i = 2; i < num; i++) { //Использует алгоритм "решето Эратосфена": начиная с 2 (первое простое число), отмечает все кратные числа как составные (присваивает им значение 0).
        if (numbersToNum[i] != 0) {
            for (int j = i + numbersToNum[i]; j < num; j += numbersToNum[i]) { 
                numbersToNum[j] = 0;
            }
        }
    }
    for (int i = 0; i < num; i++) {
        if (numbersToNum[i] != 0 && numbersToNum[i] != 1) {
            Prostie.push_back(numbersToNum[i]); //После завершения алгоритма, добавляет все ненулевые и не единицу числа в вектор Prostie.
        }
    }
    return Prostie; //Возвращает вектор Prostie, содержащий все простые числа до num.
}

int Moded(int number, int m) {
    int result = 1; //Инициализирует переменную result со значением 1.
    for (int i = 0; i < m; i++) { //Выполняет операцию возведения числа number в степень m с использованием цикла.
        result *= number;
        result %= (m + 1); //После каждого умножения result на number, остаток от деления результата на (m + 1) присваивается самому результату.
    }
    return result; //Возвращает полученный результат после выполнения всех итераций цикла.
}


int Generator(vector<int> numberProst, int n, vector<int>& number, vector<int>& dividers, int R) { // Генератор
    int m = (n - 1) / R; //Функция вычисляет m, которое равно (n - 1) / R.
    int i = 0; //Затем она перебирает простые числа из вектора numberProst
    while (m > 1) {
        if (m % numberProst[i] == 0) { //если m делится на текущее простое число, добавляет это простое число в вектор dividers
            dividers.push_back(numberProst[i]);
            m /= numberProst[i]; //делит m на это число
        }
        else {
            i++;
        }
    }

    int t = 5; //функция генерирует t случайных чисел в диапазоне от 0 до n - 1
    for (int j = 0; j < t; j++) {
        number.push_back(rand() % (n)); //сохраняет их в вектор number
    }

    for (int j : number) { //После этого она проверяет, выполняется ли для каждого сгенерированного числа условие
        if ((Moded(j, n - 1) % n) != 1) {
            return 0; //Если условие не выполняется, то функция возвращает 0
        }
    }
    return 1;
}

int Miller(vector<int> numberProst, int n) { // Тест Миллера
    vector<int> dividers;
    vector<int> number;
    int test = Generator(numberProst, n, number, dividers, 2); //Использует функцию Generator для генерации случайных чисел и нахождения делителей числа (n - 1)
    if (test == 0) return 0; //Если тест генератора не прошел, то функция возвращает 0.
    int k = 0;
    for (int j : dividers) {
        for (int z : number) {
            if ((Moded(z, (n - 1) / j) % n) != 1) { //Затем она проходит по всем делителям и проверяет, выполняется ли условие для каждого сгенерированного числа z и делителя j
                k++;
                break;
            }
        }
    }
    if (k == 0) { //Если условие не выполняется ни для одного числа, то функция возвращает 0
        return 0;
    }
    return 1;
}

int Poli(vector<int> numberProst, int n) { // Тест Поклингтона
    int k = 0;
    vector<int> dividers;
    vector<int> number;
    int R = 4;
    if ((n / 8) != 0) {
        R = rand() % (n / 8) * 2;
        if (R == 0) {
            R = 4;
        }
    }

    int test = Generator(numberProst, n, number, dividers, R);
    if (test == 0)return 0;
    for (int z : number) {
        for (int j : dividers) {
            if ((Moded(z, (n - 1) / j) % n) == 1) {
                k++;
                break;
            }
        }
    }
    if (k == 0) {
        return 1;
    }
    return 0;

}

int64_t power(int a, int b) { // степень
    int64_t s = 1; //Функция использует цикл, в котором переменная s умножается на a в каждой итерации
    for (int i = 0; i < b; i++) {
        s = s * a;
    }
    return s;

}

int powerMod(int a, int b, int m) { // a^x mod p
    int s = 1; //Функция вычисляет остаток от деления числа a, возведенного в степень b, на число m
    for (int i = 0; i < b; i++) {
        s = s * a; //Использует цикл, в котором переменная s умножается на a в каждой итерации
        s = s % m; //затем берется остаток от деления s на m
    }
    return s;
}

int GOST(int t, int q) { // ГОСТ Р 34.10 - 94.
    bool f = false;
    int p = 0;
    while (true) {
        int N = power(2, t - 1) / q; //Алгоритм вычисляет N как power(2, t - 1) / q
        if (N % 2 == 1)N++; //Если N нечетное, то к нему прибавляется 1
        int u = 0; //Затем, в цикле, перебираются значения u (начинается с 0, увеличивается на 2 в каждой итерации)
        while (true) { 
            p = (N + u) * q + 1; //Для каждого u вычисляется p как (N + u) * q + 1
            if (power(2, t) < p) { //Если p больше, чем power(2, t), то цикл прерывается
                break;
            }
//Затем проверяются условия
            if ((power(2, p - 1) % p == 1) && (power(2, N + u) % p != 1)) {
                f = true;
                break;
            }

            u = u + 2;
        }

        if (f) {
            return p; //Если оба условия выполнены, то функция возвращает значение p
        }
    }
}

int MillerRabin(int number, int k) { // Миллер-Рабин
    if (number == 2 || number == 3) return 1;
    if (number < 2 || number % 2 == 0) return 0;
    int d = number - 1;
    int s = 0;
    int y = 0;
    while (d % 2 == 0)
    {
        d /= 2;
        s += 1;
    }
    for (int i = 0; i < k; i++) {
        int a = rand() % (number - 4) + 2;
        int x = powerMod(a, d, number);
        for (int j = 0; j < s; j++) {
            y = (x * x) % number;
            if (y == 1 && x != 1 && x != (number - 1)) {
                return 0;
            }
            x = y;
        }
        if (y != 1) {
            return 0;
        }
    }
    return 1;
}


void GenerateAndTestPrimes(vector<int> primes, int(*testFunc)(vector<int>, int), string testName) {
    vector<int> generatedPrimes;
    vector<int> rejectedFalsePositives;
    int totalRejected = 0;
    int totalChecked = 0;

    while (generatedPrimes.size() < 10) {
        int candidate = rand() % (500 - 4) + 2;
        
        if (testFunc(primes, candidate)) {
            generatedPrimes.push_back(candidate);
            int falsePositives = 0;
            if (!MillerRabin(candidate, 10)) {
                falsePositives = 1;
            }
            rejectedFalsePositives.push_back(falsePositives);
            totalRejected += falsePositives;
        }
        totalChecked++;
    }

    cout << "Тесты: " << testName << endl;
    cout << "----------------------------------------------" << endl;
    cout << "| #  | Простые | Вероятностный тест | Ложная позиция |" << endl;
    cout << "----------------------------------------------" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "| " << setw(2) << (i + 1) << " | " << setw(5) << generatedPrimes[i] << " | "
             << (MillerRabin(generatedPrimes[i], 10) ? "   +   " : "   -   ") << " | "
             << setw(9) << rejectedFalsePositives[i] << " |" << endl;
    }
    cout << "----------------------------------------------" << endl;
    cout << "Всего проверено: " << totalChecked << ", Общее количество ложных срабатываний: " << totalRejected << "\n\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));

    vector<int> primes = Eratos(500);
    cout << "500 простых сгенерированных чисел при помощи решета Эратосфена:" << endl;
    for (int p : primes) cout << p << " ";
    cout << endl << endl;

    GenerateAndTestPrimes(primes, Miller, "Миллер тест");
    GenerateAndTestPrimes(primes, Poli, "Поклингтон тест");
    GenerateAndTestPrimes(primes, [](vector<int>, int) { return GOST(5, 7); }, "GOST R 34.10-94");

    return 0;
}
