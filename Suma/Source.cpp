#include <iostream>

using namespace std;

int suma(int n);
int addpairs(int n);
double addsub(double n);

void main() {

	int y;
	double x;

	cout << "Numero: ";
	cin >> y;

	y = suma(y);

	cout << "Resultado: " << y << endl;

	cout << "Numero: ";
	cin >> y;

	y = addpairs(y);

	cout << "Resultado: " << y << endl;

	cout << "Numero: ";
	cin >> x;

	x = addsub(x);

	cout << "Resultado: " << x << endl;

	system("pause > nul");
}

//Suma de los primeros N numeros
int suma(int n) {

	if (n == 0)
		return 0;
	else
		return n + suma(n - 1);
}

//Suma de los enteros positivos pares desde N hasta 2
int addpairs(int n) {

	if (n <= 1)
		return 0;
	else if (n % 2 == 0)
		return n + addpairs(n - 1);
	else
		return addpairs(n - 1);
}

//Suma los impares y resta los pares
//De forma directa 
double addsub(double n) {

	if (n == 0)
		return 1;
	else if ( fmod(n,2) == 0) //fmod para sacar el modulo con doubles
		return (1 / (n) + addsub(n - 1));
	else
		return (1 / (n) - addsub(n - 1));
}