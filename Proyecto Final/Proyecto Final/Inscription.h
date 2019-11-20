#pragma once
#include <fstream>
using namespace std;

ofstream enrolled_file;
ifstream enrolled_loadfile;
char enrolled_filepath[MAX_PATH] = "";

bool inscription_exits; // Existente, 1 = si | 0 = no
bool inscription_found; // Encontrado, 1 = si | 0 = no	

#ifndef Enroll
#define Enroll

class Inscription {
public:

	char student[1024] = ""; // Matricula
	char semester[1024] = "";
	char subject[1024] = ""; // Materia
	char credits[3] = ""; // Credito
	char grade[3] = "";
	Inscription* prev;
	Inscription* next;
	Inscription(){}
	~Inscription(){}

	void Files();
	void AddInscription(Inscription data);
	void FindInscription(Inscription data);
	void DeleteInscription(Inscription* node);
	void SaveInscriptionFile();
	void LoadInscriptionsFile();

};


Inscription* enroll_first = NULL; // Origen
Inscription* enroll_aux = NULL; // Temporal
Inscription* enroll_last = NULL; // Ultimo
Inscription* ll_inscription; // Lista Ligada de Inscripcion

void Inscription::Files() {

	strcpy_s(enrolled_filepath, archives);
	strcat_s(enrolled_filepath, "\\Inscription_File.txt");
}

void Inscription::AddInscription(Inscription data) {

	Inscription* new_inscription = new Inscription;
	*new_inscription = data;

	enroll_aux = enroll_first;

	if (enroll_first == NULL) {

		enroll_first = new_inscription;
		enroll_first->next = NULL;
		enroll_first->prev = NULL;

		enroll_aux = enroll_first;
		enroll_last = enroll_first;
	}
	else {

		while (enroll_aux != NULL) {

			if (strcmp(enroll_aux->student, data.student) == 0 && strcmp(enroll_aux->semester, data.semester) == 0 && strcmp(enroll_aux->subject, data.subject) == 0) { // Inscripcion existente
				inscription_exits = 1;
				break;
			}
			else {
				enroll_aux = enroll_aux->next;
			}
		}

		if (inscription_exits == 0) {

			enroll_aux = enroll_first;

			while (enroll_aux->next != NULL) {

				enroll_aux = enroll_aux->next;
			}

			enroll_aux->next = new_inscription;
			enroll_aux->next->prev = enroll_aux;
			enroll_aux = enroll_aux->next;
			enroll_last = enroll_aux;

			enroll_aux->next = NULL;
		}
	}
}

void Inscription::FindInscription(Inscription data) {


	enroll_aux = enroll_first;

	if (enroll_first != NULL) {

		while (enroll_aux != NULL) {

			if (strcmp(enroll_aux->subject, data.subject) == 0 && strcmp(enroll_aux->student, data.student) == 0 && strcmp(enroll_aux->semester, data.semester) == 0) { // Buscador de Inscripcion
				break;
			}
			else {
				if (enroll_aux != enroll_last) { // Mientras aux no sea el ultimo
					enroll_aux = enroll_aux->next;
				}
				else {
					break;
				}
			}
		}
	}

}

void Inscription::DeleteInscription(Inscription* node) {


	if (enroll_first == enroll_aux) {

		enroll_first = enroll_aux->next;
		if (enroll_aux->next != NULL) {
			enroll_aux->next->prev = NULL;
		}
	}
	else {
		enroll_aux->prev->next = enroll_aux->next;
		if (enroll_aux->next != NULL) {
			enroll_aux->next->prev = enroll_aux->prev;
		}
	}

	delete enroll_aux;

}


void Inscription::SaveInscriptionFile() {

	Inscription info;
	Inscription* aux = 0, * borrar;
	enrolled_file.open(enrolled_filepath, ios::binary | ios::trunc);
	if (enrolled_file.is_open())
	{
		aux = enroll_first;
		while (aux != 0)
		{
			enrolled_file.write((char*)aux, sizeof(Inscription));
			borrar = aux;
			aux = aux->next;
			delete borrar;
		}
		enrolled_file.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}


void Inscription::LoadInscriptionsFile() {

	Inscription* info = 0;

	enrolled_loadfile.open(enrolled_filepath, ios::binary);
	if (enrolled_loadfile.is_open())
	{
		info = new Inscription;
		enrolled_loadfile.read((char*)info, sizeof(Inscription));
		info->prev = 0;
		info->next = 0;

		while (!enrolled_loadfile.eof())
		{
			if (enroll_first == NULL) {
				enroll_first = info;
				enroll_last = info;
			}
			else {
				enroll_last->next = info;
				info->prev = enroll_last;

				enroll_last = info;
			}

			info = new Inscription;
			enrolled_loadfile.read((char*)info, sizeof(Inscription));
			info->prev = 0;
			info->next = 0;

		}

		enrolled_loadfile.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}

#endif