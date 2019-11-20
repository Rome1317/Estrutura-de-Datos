#pragma once
#include <fstream>

//Ctrl + B compilar para ver si hay errores

using namespace std; 

bool found; // Encontrado, 1 = si | 0 = no
bool exits; // Existente, 1 = si | 0 = no

ofstream file;
ifstream loadfile;
char user_filepath[MAX_PATH] = "";

#ifndef tree
#define tree

class Coordinator {

public:
	char username[1024] = "";
	char password[1024] = "";
	char completename[1024]= "";
	char role[7] = ""; // Siglas de carrera
	char photo[1024] = "";
	Coordinator* father = NULL;
	Coordinator* left = NULL;
	Coordinator* right = NULL;

	Coordinator(){}
	~Coordinator();

	void Files();
	void AddUser(Coordinator userdata);
	void _AddUser(Coordinator** node, Coordinator* n, Coordinator* dad);
	void FindUser(Coordinator* wanted);
	Coordinator* _FindUser(Coordinator* node, Coordinator* wanted);
	void DeleteUser(Coordinator* node);
	Coordinator* Smallest(Coordinator* node);
	void Replace(Coordinator* node, Coordinator* replacement);
	void _DeleteUser(Coordinator* node);
	void _SaveToFile(Coordinator** node, ofstream* archive);
	void LoadFile(Coordinator** node);

	
};

Coordinator* root = NULL; // Raiz
Coordinator* user_tree = NULL; // Arbol de Coordindores
Coordinator* user_data = NULL; // Temporal

void Coordinator::Files() {

	strcpy_s(user_filepath, archives);
	strcat_s(user_filepath, "\\User_File.txt");

}

void Coordinator::AddUser(Coordinator userdata) {

		Coordinator* new_user = new Coordinator;
		*new_user = userdata;

		if (root == NULL ) {

			root = new_user;
		
		}
		else {

			Coordinator::_AddUser(&root, new_user, root);
		}
}

void Coordinator::_AddUser(Coordinator** node, Coordinator* n, Coordinator* dad) {

	Coordinator* aux;
	aux = *node;

	if (aux == NULL) {

		n->father = dad; // Guarda el papa del nodo
		*node = n; // Guarda la informacion en el nodo

	}
	else {

		if (strcmp(aux->username, n->username) != 0) {

			if (strcmp(n->username, aux->username) > 0) { // Z > A
				_AddUser(&aux->right, n, aux);
			}
			if (strcmp(n->username, aux->username) < 0) {
				_AddUser(&aux->left, n, aux);

			}
		}
		else {
			exits = 1;
		}

	}
}

void Coordinator::FindUser(Coordinator* temp) {

	user_data = NULL;
	user_data = _FindUser(root, temp);
	
}

Coordinator* Coordinator::_FindUser(Coordinator* node, Coordinator* wanted) {

	career_aux = first;

	if (node != NULL) {
		if (strcmp(wanted->username, node->username) == 0) {

			while (career_aux != NULL) {

				if (strcmp(career_aux->career_coord, node->username) == 0) { // Buscador de Carrera
					break;
				}
				else {
					if (career_aux != last) { // Mientras aux no sea el ultimo
						career_aux = career_aux->next;
					}
					else {
						break;
					}
				}
			}

			found = 1;
			return node;
		}
		else if (node->left == NULL && node->right == NULL) {
			found = 0;
			MessageBox(NULL, "No existe coordinador con ese usuario", "Error", MB_ICONINFORMATION);
		}
		else {

			if (strcmp(wanted->username, node->username) > 0) {
				Coordinator::_FindUser(node->right, wanted);
			}
			else {
				Coordinator::_FindUser(node->left, wanted);
			}
		}

	}
	else {

		found = 0;
		MessageBox(NULL, "No ha ingresado a ningun coordinador.", "Error", MB_ICONINFORMATION);
	}
}

void Coordinator::DeleteUser(Coordinator* node) {

	if(node->left == NULL && node->right == NULL && node->father == NULL){ // Elimina contenido de la raiz
		root = NULL;
	}
	else if (node->left != NULL && node->right != NULL) {
		Coordinator* minor = Smallest(node->right);
		*node->completename = *minor->completename;// Se pasa el contenido del menor a el nodo que se quiere eliminar
		*node->username = *minor->username;
		*node->password = *minor->password;
		*node->photo = *minor->photo;
		*node->role = *minor->role;
		DeleteUser(minor); // Se elimina el menor
	}
	else if (node->left != NULL) {
		Replace(node, node->left);
		_DeleteUser(node);
	}
	else if (node->right != NULL) {
		Replace(node, node->right);
		_DeleteUser(node);
	}
	else {
		Replace(node, NULL);
		_DeleteUser(node);
	}

}

Coordinator* Coordinator::Smallest(Coordinator* node) {
	if (node == NULL) {
		return NULL;
	}
	if (node->left != NULL) {
		return Coordinator::Smallest(node->left);
	}
	else {
		return node;
	}

}

void Coordinator::Replace(Coordinator* node, Coordinator* replacement) {

	if (node->father != NULL) {
		if (node->father->left != NULL) {
			if (strcmp(node->username, node->father->left->username) == 0) {
				node->father->left = replacement; //Reemplaza al nodo izquierdo del padre por su sustito
			}
		}
		if (node->father->right != 0) {
			if (strcmp(node->username, node->father->right->username) == 0) {
				node->father->right = replacement; //Reemplaza al nodo derecgo del padre por su sustito
			}
		}

	}
	if (replacement != NULL) {

		replacement->father = node->father;// Enlaza al nodo padre 

		if (node == root && node->right == NULL) {
			root = node->left; // Se pasa la raiz al nodo izquierdo
		}
		else if (node == root && node->left == NULL) {
			root = node->right; // Se pasa la raiz al nodo derecho
		}
	}
}

void Coordinator::_DeleteUser(Coordinator* node) {
	node->right = NULL;
	node->left = NULL;
	delete node;

}

Coordinator::~Coordinator() {

	file.open(user_filepath, ios::out | ios::binary | ios::trunc);
	if (file.is_open()) {

		_SaveToFile(&root, &file);	
	}
	else {

		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
	}

	file.close();
}

void Coordinator::_SaveToFile(Coordinator** node, ofstream* archive) {

	Coordinator* aux;
	aux = *node;

	if (aux != NULL)
	{
		archive->write((char*)aux, sizeof(Coordinator));
		_SaveToFile(&aux->left, archive);
		_SaveToFile(&aux->right, archive);
	}
}

void Coordinator::LoadFile(Coordinator** node) { // Lectura cuando cierres el programa

	Coordinator* aux;
	aux = *node;

	if (aux == NULL) {
		return;
	}

	loadfile.open(user_filepath, ios::binary);

	if (!loadfile.is_open()) {

		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", MB_ICONINFORMATION);
		return;
	}

	Coordinator* file_user = new Coordinator;
	loadfile.read((char*)file_user, sizeof(Coordinator));


	AddUser(*file_user);
	loadfile.read((char*)file_user, sizeof(Coordinator));


	loadfile.close();
}
#endif



