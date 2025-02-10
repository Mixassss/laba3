#include <iostream>
#include <math.h>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <windows.h>

using namespace std;

vector<int> Eratos(int num) { // ������ ����������
    vector<int> numbersToNum; //������� ������ numbersToNum � ��������� ��� ������� �� 0 �� num - 1.
    vector<int> Prostie; //������� ������ Prostie ��� �������� ������� �����.
    for (int i = 0; i < num; i++) {
        numbersToNum.push_back(i); 
    }

    for (int i = 2; i < num; i++) { //���������� �������� "������ ����������": ������� � 2 (������ ������� �����), �������� ��� ������� ����� ��� ��������� (����������� �� �������� 0).
        if (numbersToNum[i] != 0) {
            for (int j = i + numbersToNum[i]; j < num; j += numbersToNum[i]) { 
                numbersToNum[j] = 0;
            }
        }
    }
    for (int i = 0; i < num; i++) {
        if (numbersToNum[i] != 0 && numbersToNum[i] != 1) {
            Prostie.push_back(numbersToNum[i]); //����� ���������� ���������, ��������� ��� ��������� � �� ������� ����� � ������ Prostie.
        }
    }
    return Prostie; //���������� ������ Prostie, ���������� ��� ������� ����� �� num.
}

int Moded(int number, int m) {
    int result = 1; //�������������� ���������� result �� ��������� 1.
    for (int i = 0; i < m; i++) { //��������� �������� ���������� ����� number � ������� m � �������������� �����.
        result *= number;
        result %= (m + 1); //����� ������� ��������� result �� number, ������� �� ������� ���������� �� (m + 1) ������������� ������ ����������.
    }
    return result; //���������� ���������� ��������� ����� ���������� ���� �������� �����.
}


int Generator(vector<int> numberProst, int n, vector<int>& number, vector<int>& dividers, int R) { // ���������
    int m = (n - 1) / R; //������� ��������� m, ������� ����� (n - 1) / R.
    int i = 0; //����� ��� ���������� ������� ����� �� ������� numberProst
    while (m > 1) {
        if (m % numberProst[i] == 0) { //���� m ������� �� ������� ������� �����, ��������� ��� ������� ����� � ������ dividers
            dividers.push_back(numberProst[i]);
            m /= numberProst[i]; //����� m �� ��� �����
        }
        else {
            i++;
        }
    }

    int t = 5; //������� ���������� t ��������� ����� � ��������� �� 0 �� n - 1
    for (int j = 0; j < t; j++) {
        number.push_back(rand() % (n)); //��������� �� � ������ number
    }

    for (int j : number) { //����� ����� ��� ���������, ����������� �� ��� ������� ���������������� ����� �������
        if ((Moded(j, n - 1) % n) != 1) {
            return 0; //���� ������� �� �����������, �� ������� ���������� 0
        }
    }
    return 1;
}

int Miller(vector<int> numberProst, int n) { // ���� �������
    vector<int> dividers;
    vector<int> number;
    int test = Generator(numberProst, n, number, dividers, 2); //���������� ������� Generator ��� ��������� ��������� ����� � ���������� ��������� ����� (n - 1)
    if (test == 0) return 0; //���� ���� ���������� �� ������, �� ������� ���������� 0.
    int k = 0;
    for (int j : dividers) {
        for (int z : number) {
            if ((Moded(z, (n - 1) / j) % n) != 1) { //����� ��� �������� �� ���� ��������� � ���������, ����������� �� ������� ��� ������� ���������������� ����� z � �������� j
                k++;
                break;
            }
        }
    }
    if (k == 0) { //���� ������� �� ����������� �� ��� ������ �����, �� ������� ���������� 0
        return 0;
    }
    return 1;
}

int Poli(vector<int> numberProst, int n) { // ���� �����������
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

int64_t power(int a, int b) { // �������
    int64_t s = 1; //������� ���������� ����, � ������� ���������� s ���������� �� a � ������ ��������
    for (int i = 0; i < b; i++) {
        s = s * a;
    }
    return s;

}

int powerMod(int a, int b, int m) { // a^x mod p
    int s = 1; //������� ��������� ������� �� ������� ����� a, ������������ � ������� b, �� ����� m
    for (int i = 0; i < b; i++) {
        s = s * a; //���������� ����, � ������� ���������� s ���������� �� a � ������ ��������
        s = s % m; //����� ������� ������� �� ������� s �� m
    }
    return s;
}

int GOST(int t, int q) { // ���� � 34.10 - 94.
    bool f = false;
    int p = 0;
    while (true) {
        int N = power(2, t - 1) / q; //�������� ��������� N ��� power(2, t - 1) / q
        if (N % 2 == 1)N++; //���� N ��������, �� � ���� ������������ 1
        int u = 0; //�����, � �����, ������������ �������� u (���������� � 0, ������������� �� 2 � ������ ��������)
        while (true) { 
            p = (N + u) * q + 1; //��� ������� u ����������� p ��� (N + u) * q + 1
            if (power(2, t) < p) { //���� p ������, ��� power(2, t), �� ���� �����������
                break;
            }
//����� ����������� �������
            if ((power(2, p - 1) % p == 1) && (power(2, N + u) % p != 1)) {
                f = true;
                break;
            }

            u = u + 2;
        }

        if (f) {
            return p; //���� ��� ������� ���������, �� ������� ���������� �������� p
        }
    }
}

int MillerRabin(int number, int k) { // ������-�����
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

int main() {
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    srand(time(0));
    
    int num = 500;

    vector<int> Prostie = Eratos(num); //���������� ������� Eratos ��� ������ ���� ������� ����� �� num.
    cout << "������� ����� �� " << num << ": " << endl;
    for (int i : Prostie) {
        cout << setw(4) << i;
    }
    cout << endl;
    int t = 5;
    int q = 7;
    if (q < power(2, t / 2 + 1)) { //���� q ������, ��� power(2, t / 2 + 1), �� ��� ���������� ������� GOST ��� ��������� �������� ����� �� ���� � 34.10 - 94 � ������� ��� �� �������.
        int number = GOST(t, q);
        cout << number << endl;
    }
    vector<int> ReallyProstie; //������� ��� �������: ReallyProstie (��� �������� ��������� ������� �����)
    vector<int> BadOnes; //BadOnes (��� �������� ���������� ����������� �����)
    int MissedOnes = 0; //C������ ���������� MissedOnes ��� �������� ���������� ����������� �����
    int TotalNums = 0; //���������� TotalNums ��� �������� ���������� ����������� �����
    while (ReallyProstie.size() < 10) { //� �����, ���� ������ ������� ReallyProstie �� ������ ����� 10, ������������ ��������� �����
        int test = rand() % (500 - 4) + 2; //test � ��������� �� 2 �� 498

        if (Miller(Prostie, test) && Poli(Prostie, test)) { //����� �����������, �������� �� ����� test �������, ��������� ������� Miller � Poli
            ReallyProstie.push_back(test); //���� ��, �� ����� ����������� � ������ ReallyProstie
            BadOnes.push_back(MissedOnes); //���������� ����������� ����� ����������� � ������ BadOnes
            MissedOnes = 0; //MissedOnes ����������
        }
        else {
            MissedOnes += MillerRabin(test, 10); //���� ����� test �� �������� �������, �� MissedOnes ������������� �� ��������� ����� �������-������
        }
        TotalNums++;
    }
    cout << "������� ������� ����������� �����: ";
    for (int i : BadOnes) {
        cout << i << " ";
    }
    MissedOnes = 0;
    cout << endl;
    cout << "�������� �����: " << TotalNums << endl;
    cout << "10 ������������ �����:" << endl;
    for (int i : ReallyProstie) {
        cout << setw(5) << i;
        // ����������� ������� ��� �������� � ������� ������ ������ � �����������
        if (Poli(Prostie, i) && !MillerRabin(i, 10)) {
            cout << " -"; // ���� Poli ����� � MillerRabin �����
        }
        else {
            cout << " +"; // � ��������� ������
        }
        cout << endl;
    }
    
    for (int i : ReallyProstie) {
        cout << setw(5) << i;
        MissedOnes = MillerRabin(i, 10);
        if (MissedOnes == 1) {
            cout << " +";
        }
        else {
            cout << " -";
        }
        cout << endl;
    }

    return 0;
}
