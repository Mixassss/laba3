#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
#include <cmath>
#include <windows.h>

using namespace std;

vector<double> coffee(double Tk, double Tsr, double r, int time) { // ����������� ����������� ���� �� ��������
	vector<double> temperatures; // ������ ��� �����������
	for (int i = 1; i <= time; i++) {
		double t = Tsr + (Tk - Tsr) * exp(-r * i); // ���������� �� ������ ���������������� �������
		temperatures.push_back(t);
	}
	return temperatures;
}

pair<double, double> aprox(const vector<double>& x, const vector<double>& y) { // �������� ���������������� ������
	double sumx = accumulate(x.begin(), x.end(), 0.0); // ����� ���� �
	double sumy = accumulate(y.begin(), y.end(), 0.0); // ����� ���� �
	double xy = inner_product(x.begin(), x.end(), y.begin(), 0.0); // ����� ������������ ���� � �� �
	double xx = inner_product(x.begin(), x.end(), x.begin(), 0.0); // ����� ���� � � ��������
	double n = x.size();
	pair <double, double> approximatingLine; // ���� �������� ���������������� ������
	approximatingLine.first = (n * xy - sumx * sumy) / (n * xx - sumx * sumx); // �������� �
	approximatingLine.second = (sumy - approximatingLine.first * sumx) / n; // �������� b
	return approximatingLine;
}

double korrel(const vector<double>& x, const vector<double>& y) { // ����������� ����������
	double xsr = accumulate(x.begin(), x.end(), 0.0) / x.size(); // ������� �������� �
	double ysr = accumulate(y.begin(), y.end(), 0.0) / y.size(); // ������� �������� �
	double sumxy = 0, sumxx = 0, sumyy = 0;
	for (int i = 0; i < x.size(); i++) {
		sumxy += (x[i] - xsr) * (y[i] - ysr); // ����� ������������ �������� ���� � � � �������� �� �������� ���� � �� � ��������
		sumxx += (x[i] - xsr) * (x[i] - xsr); // ����� �������� �������� ���� � � � ��������
		sumyy += (y[i] - ysr) * (y[i] - ysr); // ����� �������� �������� ���� � � � ��������
	}
	return sumxy / sqrt(sumxx * sumyy); // ������� ������������
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double Tk = 90; // ����������� ����
	double Tsr = 25; // ����������� ���������� �����
	double r = 0.005; // ����������� ���������
	int time = 60; // ����� ��������� � �������
	vector<double> temperatures = coffee(Tk, Tsr, r, time); // ���������� ������� � ������������
	vector<double> times; // ������ ��� �������
	cout << "__________________________" << endl;
	cout << "|" << setw(3) << "time (x)|" << setw(5) << "temperature (y)|" << endl; // ����� ������� 
	for (int i = 0, j = 1; i < temperatures.size() && j <= time; i++, j++) {
		cout << "|" << setw(5) << j << setw(4) << "|";
		cout << setw(9) << temperatures[i] << setw(7) << "|" << endl; // ����� �������� � ��������� �����
		times.push_back(i); // ���������� ������� �� ��������
	}
	cout << "���������������� ������: a = ";
	pair<double, double> approximatingLine = aprox(times, temperatures); // ���������� ���� �� ��������� ���������������� ������
	cout << approximatingLine.first << " b = " << approximatingLine.second << endl;
	cout << "����������� ����������: r = " << korrel(times, temperatures);
	return 0;
}
