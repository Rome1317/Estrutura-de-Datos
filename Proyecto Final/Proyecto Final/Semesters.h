#pragma once
#include <fstream>
using namespace std;

ofstream semester_file;
ifstream semester_loadfile;
char semester_filepath[MAX_PATH] = "";
char semesters[MAX_PATH] = "";

bool semester_exits; // Existente , 1 = si | 0 = no
bool avaible = 1; // Semestres cerrados, 1 = si | 0 = no
char actual_semester[1024] = ""; // Guarda el semestre actual

#ifndef AcademicYearDivision
#define AcademicYearDivision

class Semester {

public:

	char period[50] = "";
	char year[5] = "";
	char semester[50] = "";
	bool open; // Semestre Abierto, 1 = si | 0 = no
	bool opened; // Semestre Ya Abierto
	bool finals; // Semestre en Finales
	Semester* next;
	Semester* prev;
	Semester(){}
	~Semester(){}

	void Files();
	void AddSemester(Semester data);
	void AvaibleSemester();
	void FindSemester(Semester data);
	void DeleteSemester(Semester* node);
	void SaveSemesterFile();
	void SaveSemesters();
	void LoadSemesterFile();
};

Semester* ayd_first = NULL; // Origen
Semester* ayd_aux = NULL; // Temporal
Semester* ayd_last = NULL; // Ultimo
Semester* ll_semester; // Lista Ligada de Semestres

void Semester::Files (){

	strcpy_s(semester_filepath, archives);
	strcpy_s(semesters, archives);

	strcat_s(semester_filepath, "\\Semester_File.txt");
	strcat_s(semesters, "\\Archives\\Semesters.txt");

}

void Semester::AddSemester(Semester data) {

	Semester* new_semester = new Semester;
	*new_semester = data;

	ayd_aux = ayd_first;

	if (ayd_first == NULL) {

		ayd_first = new_semester;
		ayd_first->next = NULL;
		ayd_first->prev = NULL;

		ayd_aux = ayd_first;
		ayd_last = ayd_first;
	}
	else {

		while (ayd_aux != NULL) {

			if (strcmp(ayd_aux->semester, data.semester) == 0) { // Semestre existente
				semester_exits = 1;
				break;
			}
			else {
				ayd_aux = ayd_aux->next;
			}
		}

		if (semester_exits == 0) {

		    ayd_aux = ayd_first;

		    while (ayd_aux->next != NULL) {
		
			    ayd_aux = ayd_aux->next;

		    }

			ayd_aux->next = new_semester;
			ayd_aux->next->prev = ayd_aux;
			ayd_aux = ayd_aux->next;
			ayd_last = ayd_aux;

			ayd_aux->next = NULL;
		}
	}

}

void Semester::AvaibleSemester() {

	ayd_aux = ayd_first;

	if (ayd_first != NULL) {

		while (ayd_aux != NULL) {

			if (ayd_aux->open == 1) {
				avaible = 0;
				ayd_aux->finals = 1;
				strcpy_s(actual_semester, ayd_aux->semester);
				break;
			}
			else {
				ayd_aux = ayd_aux->next;
			}
		}
	}

}

void Semester::FindSemester(Semester data) {

	ayd_aux = ayd_first;

	if (ayd_first != NULL) {

		while (ayd_aux != NULL) {

			if (strcmp(ayd_aux->semester, data.semester) == 0) { // Buscador de Semestre
				break;
			}
			else {
				if (ayd_aux != ayd_last) { // Mientras aux no sea el ultimo
					ayd_aux = ayd_aux->next;
				}
			}
		}
	}

}

void Semester::DeleteSemester(Semester* node) {


	if (ayd_first == ayd_aux) {

		ayd_first = ayd_aux->next;
		if (ayd_aux->next != NULL) {
			ayd_aux->next->prev = NULL;
		}
	}
	else {
		ayd_aux->prev->next = ayd_aux->next;
		if (ayd_aux->next != NULL) {
			ayd_aux->next->prev = ayd_aux->prev;
		}
	}

	delete ayd_aux;
}

void Semester::SaveSemesterFile() {

	Semester info;
	Semester* aux = 0, * borrar;
	semester_file.open(semester_filepath, ios::binary | ios::trunc);
	if (semester_file.is_open())
	{
		aux = ayd_first;

		while (aux != 0)
		{
			semester_file.write((char*)aux, sizeof(Semester));
			borrar = aux;
			aux = aux->next;
			delete borrar;
		}
		semester_file.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}

void Semester::SaveSemesters() {

	Semester* aux = 0;
	semester_file.open(semesters, ios::out | ios::trunc);
	if (semester_file.is_open())
	{
		aux = ayd_first;
		
		while (aux != 0)
		{
			semester_file << aux->semester << endl;
			aux = aux->next;
		}

		semester_file.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}

void Semester::LoadSemesterFile() {

	Semester* info = 0;

	semester_loadfile.open(semester_filepath, ios::binary);
	if (semester_loadfile.is_open())
	{
		info = new Semester;
		semester_loadfile.read((char*)info, sizeof(Semester));
		info->prev = 0;
		info->next = 0;

		while (!semester_loadfile.eof())
		{
			if (ayd_first == NULL) {
				ayd_first = info;
				ayd_last = info;
			}
			else {
				ayd_last->next = info;
				info->prev = ayd_last;

				ayd_last = info;
			}

			info = new Semester;
			semester_loadfile.read((char*)info, sizeof(Semester));
			info->prev = 0;
			info->next = 0;

		}

		semester_loadfile.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}
}

#endif
