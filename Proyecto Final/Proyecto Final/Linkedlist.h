#pragma once
#include <fstream>

using namespace std;

#ifndef List
#define List

class Student {
public:
	int ID;
	char name[1024] = "";
	char lastname[1024] = "";
	char completename[1024] = "";
	char career[1024] = "";
	int total_credits;
};

class Subject {
public:
	char career[1024] = "";
	char keyword[1024] = "";
	char descr[1024] = "";
	int credits;
	int hours;
};

template <class U> class Node
{
public:
	U data;
	Node* prev;
	Node* next;

	Node(U data) {
		this->data = data;
	}
	~Node(){}
};

template <class T, class U> class LL  // Template de Linked List
{
	T* origin = NULL;
	T* last = NULL;
	
	char file[_MAX_PATH] = "";
public:
	//LL(char* archive);
	//~LL();
	void AddNode(U info, bool txt); // Agregar datos, 1 = .txt | 0 = console
};
 
template <class T, class U> void LL <T, U> ::AddNode(U info, bool txt) {

	T* aux = NULL;
	aux = new T(info);
	aux->prev = NULL;
	aux->next = NULL;

	if (txt) {
		aux->data.id = info.id;
	}

	if (origin == NULL) {
		origin = aux;
		last = aux;

		if (!txt) {

		}
	}
	else {

		last->next = aux;
		aux->prev = last;
		last = aux;
		
		if (!txt) {

		}

	}
}


class Semester {

	char period[1024] = "";
	char year[1024] = "";
	char semester[1024] = "";

};

class Inscription {

	char student[1024] = ""; // Matricula
	char semester[1024] = ""; 
	char career[1024] = "";

	class Subjects {
		char keyword[1024] = ""; // Clave
		int credits; 
		int grade;
	}*first,*aux,*last;

	int total_credits; // Suma de creditos

}*i_fisrt,*i_aux,*i_last;

class Career {
	char keyword[1024] = "";
	char acronym[1024] = "";
	char descr[1024] = "";
};

#endif
