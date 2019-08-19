#include <iostream>

using namespace std;

int factorial(int n);

void main(){

	int y;

	cout << "Factorial de: ";
	cin >> y;

	y = factorial(y);

	cout << "Resultado: " << y;

	system("pause > nul");

}

int factorial(int n) {
	
	if (n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}