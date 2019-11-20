#pragma once
#include <fstream>
using namespace std;

ofstream student_file;
ifstream student_loadfile;
char student_filepath[MAX_PATH] = "";

bool student_found; // Encontrado, 1 = si | 0 = no	
bool student_exits;	// Existente matricula, 1 = si | 0 = no

#ifndef Undergraduate
#define Undergraduate

class Student {
public:
	char ID[10] = "";
	char name[1024] = "";
	char lastname[1024] = "";
	char completename[1024] = "";
	char career[1024] = "";
	char total_credits[3] = ""; // Suma Total de Creditos
	Student* prev;
	Student* next;
	Student(){}
	~Student(){}

	void Files();
	void AddStudent(Student data);
	void FindStudent(Student data);
	void DeleteStudent(Student* node);
	void SaveStudentsFile();
	void LoadStudentsFile();
};

Student* undergrad_first = NULL; // Origen
Student* undergrad_aux = NULL; // Temporal
Student* undergrad_last = NULL; // Ultimo
Student* ll_student; // Lista Ligada de Alumnos

void Student::Files() {

	strcpy_s(student_filepath, archives);
	strcat_s(student_filepath, "\\Student_File.txt");

}

void Student::AddStudent(Student data) {

	Student* new_student = new Student;
	*new_student = data;

	undergrad_aux = undergrad_first;

	if (undergrad_first == NULL) {

		undergrad_first = new_student;
		undergrad_first->next = NULL;
		undergrad_first->prev = NULL;

	}
	else {

		while (undergrad_aux != NULL) {

			if (strcmp(undergrad_aux->ID, data.ID) == 0) { // Matricula existente
				student_exits = 1;
				break;
			}
			else {
				undergrad_aux = undergrad_aux->next;
			}
		}

		if (student_exits == 0) {

			undergrad_aux = undergrad_first;

			while (undergrad_aux->next != NULL) {

				undergrad_aux = undergrad_aux->next;
			}

			undergrad_aux->next = new_student;
			undergrad_aux->next->prev = undergrad_aux;
			undergrad_aux = undergrad_aux->next;
			undergrad_last = undergrad_aux;

			undergrad_aux->next = NULL;
		}
	}

}

void Student::FindStudent(Student data) {

	undergrad_aux = undergrad_first;

	if (undergrad_first != NULL) {

		while (undergrad_aux != NULL) {

			if (strcmp(undergrad_aux->ID, data.ID) == 0) { // Buscador de Alumno
				student_found = 1;
				break;
			}
			else {
				if (undergrad_aux != undergrad_last) { // Mientras aux no sea el ultimo
					undergrad_aux = undergrad_aux->next;
				}
				else {
					student_found = 0;
					break;
				}
			}
		}

		if (student_found == 0) {

			MessageBox(NULL, "No existe alumno con esa matricula", "Error", MB_ICONINFORMATION);
		}
	}
	else {

		student_found = 0;
		MessageBox(NULL, "No ha ingresado ningun alumno.", "Error", MB_ICONINFORMATION);
	}
}

void Student::DeleteStudent(Student* node) {


	if (undergrad_first == undergrad_aux) {

		undergrad_first = undergrad_aux->next;
		if (undergrad_aux->next != NULL) {
			undergrad_aux->next->prev = NULL;
		}
	}
	else {
		undergrad_aux->prev->next = undergrad_aux->next;
		if (undergrad_aux->next != NULL) {
			undergrad_aux->next->prev = undergrad_aux->prev;
		}
	}

	delete undergrad_aux;

}

void Student::SaveStudentsFile() {

	Student* aux = 0, * borrar;
	student_file.open(student_filepath, ios::binary | ios::trunc);
	if (student_file.is_open())
	{
		aux = undergrad_first;
		while (aux != 0)
		{
			student_file.write((char*)aux, sizeof(Student));
			borrar = aux;
			aux = aux->next;
			delete borrar;
		}
		student_file.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}

void Student::LoadStudentsFile() {

	Student* info = 0;

	student_loadfile.open(student_filepath, ios::binary);
	if (student_loadfile.is_open())
	{
		info = new Student;
		student_loadfile.read((char*)info, sizeof(Student));
		info->prev = 0;
		info->next = 0;

		while (!student_loadfile.eof())
		{
			if (undergrad_first == NULL) {
				undergrad_first = info;
				undergrad_last = info;
			}
			else {
				undergrad_last->next = info;
				info->prev = undergrad_last;

				undergrad_last = info;
			}

			info = new Student;
			student_loadfile.read((char*)info, sizeof(Student));
			info->prev = 0;
			info->next = 0;

		}

		student_loadfile.close();
	}
	else
	{
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

}

#endif