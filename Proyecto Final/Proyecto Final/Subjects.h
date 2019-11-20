#pragma once
#include <fstream>
using namespace std;

ofstream subject_file;
ifstream subject_loadfile;
char subject_filepath[MAX_PATH] = "";

bool subject_found; // Encontrado, 1 = si | 0 = no	
bool subject_exits;	// Existente materia o clave, 1 = si | 0 = no

#ifndef Branch
#define Branch

class Subject {
public:
	char career[7] = ""; // Siglas de la carrera
	char keyword[7] = "";
	char descr[1024] = "";
	char credits[2] = "";
	char hours[3] = "";
	Subject* next;
	Subject* prev;
	Subject(){}
	~Subject(){}

	void Files();
	void AddSubject(Subject data);
	void FindSubject(Subject data);
	void DeleteSubject(Subject* node);
	void SaveSubjectsFile();
	void LoadSubjectsFile();
};

Subject* s_first = NULL; // Origen
Subject* subject_aux = NULL; // Temporal
Subject* s_last = NULL; // Ultimo
Subject* ll_subject; // Lista Ligada de Materias

void Subject::Files() {

	strcpy_s(subject_filepath, archives);
	strcat_s(subject_filepath, "\\Subject_File.txt");

}

void Subject::AddSubject(Subject data) {

	Subject* new_subject = new Subject;
	*new_subject = data;

	subject_aux = s_first;

	if (s_first == NULL) {

		s_first = new_subject;
		s_first->next = NULL;
		s_first->prev = NULL;

		subject_aux = s_first;
		s_last = s_first;
	}
	else {

		while (subject_aux != NULL) { 

			if (strcmp(subject_aux->descr, data.descr) == 0 || strcmp(subject_aux->keyword, data.keyword) == 0) { // Materia o clave existente
				subject_exits = 1;
				break;
			}
			else {
				subject_aux = subject_aux->next;
			}
		}

		if (subject_exits == 0) {

			subject_aux = s_first;

			while (subject_aux->next != NULL) {

				subject_aux = subject_aux->next;
			}

			subject_aux->next = new_subject;
			subject_aux->next->prev = subject_aux;
			subject_aux = subject_aux->next;
			s_last = subject_aux;

			subject_aux->next = NULL;
		}
	}

}

void Subject::FindSubject(Subject data) {

	subject_aux = s_first;

	if (s_first != NULL) {

			while (subject_aux != NULL) {

				if (strcmp(subject_aux->keyword, data.keyword) == 0 || strcmp(subject_aux->descr, data.descr) == 0) { // Buscador de Materia
					subject_found = 1;
					break;
				}
				else {
					if (subject_aux != s_last) { // Mientras aux no sea el ultimo
						subject_aux = subject_aux->next;
					}
					else {
						subject_found = 0;
						break;
					}
				}
			}

			if (subject_found == 0) {

				MessageBox(NULL, "No existe materia con esa clave", "Error", MB_ICONINFORMATION);
			}
	}
	else {

	    subject_found = 0;
		MessageBox(NULL, "No ha ingresado ninguna materia.", "Error", MB_ICONINFORMATION);
	}
}


void Subject::DeleteSubject(Subject* node) {


	if (s_first == subject_aux) {

		s_first = subject_aux->next;
		if (subject_aux->next != NULL) {
			subject_aux->next->prev = NULL;
		}
	}
	else {
		subject_aux->prev->next = subject_aux->next;
		if (subject_aux->next != NULL) {
			subject_aux->next->prev = subject_aux->prev;
		}
	}

	delete subject_aux;

}

void Subject::SaveSubjectsFile() {

	Subject* aux = 0, * borrar;
	subject_file.open(subject_filepath, ios::binary | ios::trunc);
	if (subject_file.is_open())
	{
		aux = s_first;
		while (aux != 0)
		{
			subject_file.write((char*)aux, sizeof(Subject));
			borrar = aux;
			aux = aux->next;
			delete borrar;
		}
		subject_file.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}

void Subject::LoadSubjectsFile() {

	Subject* info = 0;

	subject_loadfile.open(subject_filepath, ios::binary);
	if (subject_loadfile.is_open())
	{
		info = new Subject;
		subject_loadfile.read((char*)info, sizeof(Subject));
		info->prev = 0;
		info->next = 0;

		while (!subject_loadfile.eof())
		{
			if (s_first == NULL) {
				s_first = info;
				s_last = info;
			}
			else {
				s_last->next = info;
				info->prev = s_last;

				s_last = info;
			}

			info = new Subject;
			subject_loadfile.read((char*)info, sizeof(Subject));
			info->prev = 0;
			info->next = 0;

		}

		subject_loadfile.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}
#endif