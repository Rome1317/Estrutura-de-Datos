#pragma once
#include <fstream>
using namespace std;

char archives[MAX_PATH] = "";
ofstream career_file;
ifstream career_loadfile;
char career_filepath[MAX_PATH] = "";
char career_acronym[MAX_PATH] = "";


bool career_exits; // Existente carrera o clave, 1 = si | 0 = no

#ifndef Profession
#define Profession

class Career {
public:
	char career_coord[1024] = ""; // Usuario del coordinador
	char keyword[7] = ""; // Clave
	char acronym[7] = ""; // Siglas
	char descr[1024] = "";
	Career* next;
	Career* prev;
	Career() {}
	~Career() {}

	void Files();
	void AddCareer(Career data);
	void DeleteCareer(Career* node);
	void SaveAcronyms();
	void SaveCareersFile();
	void LoadCareersFile();

};

Career* first = NULL; // Origen
Career* career_aux = NULL; // Temporal
Career* last = NULL; // Ultimo
Career* ll_career; // Lista Ligada de carreras

void Career::Files() {

	strcpy_s(career_filepath, archives);
	strcpy_s(career_acronym, archives);

	strcat_s(career_filepath, "\\Career_File.txt");
	strcat_s(career_acronym, "\\Archives\\Acronyms.txt");

}

void Career::AddCareer(Career data) {

	Career* new_career = new Career;
	*new_career = data;

	career_aux = first;

	if (first == NULL) {

		first = new_career;
		first->next = NULL;
		first->prev = NULL;

	    career_aux = first;
		last = first;
	}
	else {

		while (career_aux != NULL) {

			if (strcmp(career_aux->descr, data.descr) == 0 || strcmp(career_aux->keyword, data.keyword) == 0 || strcmp(career_aux->acronym, data.acronym) == 0) { // Carrera existente
				career_exits = 1;
				break;
			}
			else {
				career_aux = career_aux->next;
			}
		}

		if (career_exits == 0) {

			career_aux = first;

		    while (career_aux->next != NULL) {

				career_aux = career_aux->next;
		    }


			career_aux->next = new_career;
			career_aux->next->prev = career_aux;
			career_aux = career_aux->next;
			last = career_aux;

			career_aux->next = NULL;
		}
	}
}

void Career::DeleteCareer(Career* node) {


	if (first == career_aux) {

		first = career_aux->next;
		if (career_aux->next != NULL) {
			career_aux->next->prev = NULL;
		}
	}
	else {
		career_aux->prev->next = career_aux->next;
		if (career_aux->next != NULL) {
			career_aux->next->prev = career_aux->prev;
		}
	}

	delete career_aux;
}

void Career::SaveCareersFile() {

	Career* aux = 0, * borrar;
	career_file.open(career_filepath, ios::binary | ios::trunc);
	if (career_file.is_open())
	{
		aux = first;
		
		while (aux != 0)
		{
			career_file.write((char*)aux, sizeof(Career));
			borrar = aux;
			aux = aux->next;
			delete borrar;
			
		}
		career_file.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}

void Career::SaveAcronyms() {

	Career* aux = 0;
	career_file.open(career_acronym, ios::out | ios::trunc);
	if (career_file.is_open())
	{
		aux = first;

		while (aux != 0)
		{

			career_file << aux->acronym << endl;
			aux = aux->next;
		}

		career_file.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}

void Career::LoadCareersFile() {

	Career* info = 0;

	career_loadfile.open(career_filepath, ios::binary);
	if (career_loadfile.is_open())
	{
		info = new Career;
		career_loadfile.read((char*)info, sizeof(Career));
		info->prev = 0;
		info->next = 0;

		while (!career_loadfile.eof())
		{
			if (first == NULL) {
				first = info;
				last = info;
			}
			else {
				last->next = info;
				info->prev = last;
				last = info;
			}

			info = new Career;
			career_loadfile.read((char*)info, sizeof(Career));
			info->prev = 0;
			info->next = 0;

		}

		career_loadfile.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}
}

#endif
