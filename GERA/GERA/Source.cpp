#include <iostream>
using namespace std;

class Nodo {
public:
	int usuario;
	Nodo* izq;
	Nodo* der;
	Nodo* padre;
	Nodo(){}
	~Nodo(){}
};

void menu();

Nodo* crearNodo(int us, Nodo* apa);
void insertarNodo(Nodo*& arbol, int dato, Nodo* apa);
bool BucarUs(Nodo* arbol, int dato);
void MostrarArbol(Nodo* arbol, int contador);
#pragma region Eliminar
void EliminarUs(Nodo* arbol, int dato);
void EliminarNodo(Nodo* nodoEliminar);
Nodo* minimo(Nodo* arbol);
void Reemplazar(Nodo *arbol, Nodo *nuevoNodo);
void DestruirNodo(Nodo* nodo);
#pragma endregion

Nodo* arbol = NULL;

void main() {
	menu();
}

void menu() {
	int usu;
	int op, cont = 0;
	do {
		cout << "---MENU---" << endl;
		cout << "1.- Insertar un nuevo nodo" << endl;
		cout << "2.- Mostrar Arbol" << endl;
		cout << "3.- Buscar elemento en el arbol" << endl;
		cout << "4.- Eliminar Nodo" << endl;
		cout << "5.- salir" << endl;
		cout << "opcion: ";
		cin >> op;
		switch (op) {
		case 1:
			cout << "Escribe usuario: ";
			cin >> usu;
			insertarNodo(arbol, usu, NULL);
			cout << "\n";
			system("pause");
			break;
		case 2:
			cout << "Mostrando: " << endl;
			MostrarArbol(arbol, cont);
			cout << "\n";
			system("pause");
			break;
		case 3:
			cout << "Dato a buscar: ";
			cin >> usu;
			if (BucarUs(arbol, usu) == true) {
				cout << "El dato " << usu << " se encontro en el arbol";
			}
			else {
				cout << "El dato no se encontro en el arbol";
			}
			cout << "\n";
			system("pause");
			break;
		case 4:
			cout << "Eliminar nodo: ";
			cin >> usu;
			EliminarUs(arbol, usu);
			cout << "\n";
			system("pause");
			break;
		}

		system("cls");
	} while (op != 5);

}

Nodo* crearNodo(int us, Nodo* apa) {
	Nodo* nuevo_nodo = new Nodo();
	nuevo_nodo->usuario = us;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->der = NULL;
	nuevo_nodo->padre = apa;
	return nuevo_nodo;
}

void insertarNodo(Nodo*& arbol, int dato, Nodo* apa) {
	if (arbol == NULL) {
		Nodo* nuevo_nodo = crearNodo(dato, apa);
		arbol = nuevo_nodo;
	}
	else {
		int vRaiz = arbol->usuario;
		if (dato < vRaiz) {
			insertarNodo(arbol->izq, dato, arbol);
		}
		else {
			insertarNodo(arbol->der, dato, arbol);
		}
	}
}
void MostrarArbol(Nodo* arbol, int contador) {
	if (arbol == NULL) {
		return;
	}
	else {
		if (arbol->der != NULL) {
			MostrarArbol(arbol->der, contador + 1);
			for (int i = 0; i < contador; i++) {
				cout << "  ";
			}
			cout << arbol->usuario << endl;
		}
		
		if (arbol->izq != NULL) {
			MostrarArbol(arbol->izq, contador + 1);
			for (int i = 0; i < contador; i++) {
				cout << "  ";
			}
			cout << arbol->usuario << endl;
		}
	}

};

bool BucarUs(Nodo* arbol, int dato) {
	if (arbol == NULL) {
		return false;
	}
	else if (arbol->usuario == dato) {
		return true;
	}
	else if (dato < arbol->usuario) {
		return BucarUs(arbol->izq, dato);
	}
	else {
		return BucarUs(arbol->der, dato);
	}
}
void EliminarUs(Nodo* arbol, int dato) {
	if (arbol == NULL) {
		return;
	}
	else if (dato < arbol->usuario) {
		EliminarUs(arbol->izq, dato);
	}
	else if (dato > arbol->usuario) {
		EliminarUs(arbol->der, dato);
	}
	else {
		EliminarNodo(arbol);
	}
}

Nodo* minimo(Nodo* arbol) {
	if (arbol == NULL) {
		return NULL;
	}
	if (arbol->izq) {
		return minimo(arbol->izq);
	}
	else {
		return arbol;
	}
}

void EliminarNodo(Nodo* nodoEliminar) {
	if (nodoEliminar->izq && nodoEliminar->der) {
		Nodo* menor = minimo(nodoEliminar->der);
		nodoEliminar->usuario = menor->usuario;
		EliminarNodo(menor);
	}
	else if (nodoEliminar->izq) {
		Reemplazar(nodoEliminar, nodoEliminar->izq);
		DestruirNodo(nodoEliminar);
	}
	else if (nodoEliminar->der) {
		Reemplazar(nodoEliminar, nodoEliminar->der);
		DestruirNodo(nodoEliminar);
	}
	else {
		Reemplazar(nodoEliminar, NULL);
		DestruirNodo(nodoEliminar);
	}
}

void Reemplazar(Nodo *arbol, Nodo *nuevoNodo) {
	if (arbol->padre) {
		if (arbol->usuario == arbol->padre->izq->usuario) {
			arbol->padre->izq = nuevoNodo;
		}
		else if (arbol->usuario == arbol->padre->der->usuario) {
			arbol->padre->der = nuevoNodo;
		}
	}
	if (nuevoNodo) {
		nuevoNodo->padre = arbol->padre;
	}
}

void DestruirNodo(Nodo* nodo) {
	nodo->der = NULL;
	nodo->izq = NULL;
	delete nodo;
}