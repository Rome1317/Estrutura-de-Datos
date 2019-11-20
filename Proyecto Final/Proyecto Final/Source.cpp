#include <Windows.h>
#include <fstream>
#include <iostream>
#include <commctrl.h>
#include "resource.h"
#include "Careers.h" // Lista Ligada de Carreras
#include "Subjects.h" // Lista Ligada de Materias
#include "Semesters.h" // Lista Ligada de Semestres
#include "Tree.h" // Arbol
#include "Students.h" // Lista Ligada de Alumnos
#include "Inscription.h" // Lista Ligada de Inscripcion

using namespace std;

void Image(HWND hWnd, WPARAM wParam, char *imagen, int m, int n); // Funcion para cargar imagenes

void UserRead(); // Funcion para obtener el usuario del .txt

void FillCb(HWND object, UINT message, char* filename); // Funcion para llenar un combobox con txt

#pragma region GeneralUser
char user[1024] = ""; // Coordinador General
char password[1024] = ""; // Coordinador General
char _user[1024] = "";
char _password[1024] = "";
#pragma endregion

#pragma region Archives
char usertype[MAX_PATH] = ""; 
char periods[MAX_PATH] = "";
char entities[MAX_PATH] = "";
char login[MAX_PATH] = "";
char university[MAX_PATH] = "";
char oxford[MAX_PATH] = "";
char campus[MAX_PATH] = "";
# pragma endregion

bool access = 0; // Inciar sesion , 1 = CG | 0 = CC

TCHAR buff[1] = TEXT(""); // Para limpiar los edits

char career_co[1024] = "1"; // Carrera
int total; // total de creditos
int total2; // creditos por semestre

HINSTANCE hInst;

SYSTEMTIME lt; // Fecha Local

int index; // Uint
int showMSG;
HWND hWnd;

#pragma region Callbacks
BOOL CALLBACK LOGIN(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK GENERAL_BROWSER(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MAIN(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK USERS(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SUBJECTS(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SEMESTER(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SEMESTER_STATUS(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SEMESTER_BROWSER(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK COORDINATOR_BROWSER(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SUBJECT_BROWSER(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK SUBJECT_LIST(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK STUDENTS(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK STUDENT_BROWSER(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK INSCRIPTION(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK GRADES(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK GRADE_SUBJECT(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK INSCRIPTION_BROWSER(HWND, UINT, WPARAM, LPARAM);
#pragma endregion

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) 
{
	GetCurrentDirectory(MAX_PATH, archives); // Obtiene la direccion de los archivos
	user_tree->Files(); 
	ll_career->Files();
	ll_subject->Files();
	ll_student->Files();
	ll_semester->Files();
	ll_inscription->Files();
	strcpy_s(usertype, archives);
	strcpy_s(periods, archives);
	strcpy_s(entities, archives);
	strcpy_s(login, archives);
	strcpy_s(university, archives);
	strcpy_s(oxford, archives);
	strcpy_s(campus, archives);
	
	strcat_s(usertype, "\\Archives\\UserType.txt");
	strcat_s(periods, "\\Archives\\Periods.txt");
	strcat_s(entities, "\\Archives\\Entities.txt");
	strcat_s(login, "\\Oxford University\\login.bmp");
	strcat_s(university, "\\Oxford University\\university.bmp");
	strcat_s(oxford, "\\Oxford University\\oxford_.bmp");
	strcat_s(campus, "\\Oxford University\\campus.bmp");
	
	
	hInst = hInstance;
	showMSG = nCmdShow;

	UserRead();

	hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN),NULL,MAIN);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ll_career->SaveCareersFile();
	ll_subject->SaveSubjectsFile();
	ll_semester->SaveSemesterFile();
	ll_student->SaveStudentsFile();
	ll_inscription->SaveInscriptionFile();
	user_data->~Coordinator();

	return (int)msg.wParam;
}

BOOL CALLBACK LOGIN(HWND hWnd, UINT message, WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		HWND hType;
		hType = GetDlgItem(hWnd, IDC_COMBO1);

		FillCb(hType, CB_ADDSTRING, usertype);

		index = SendMessage(hType, CB_SETCURSEL, 0, 0); // Pone el primer elemento del combobox

		Image(hWnd, IDC_STATIC6, login, 270, 100);

		ll_career->LoadCareersFile();
		ll_subject->LoadSubjectsFile();
		ll_student->LoadStudentsFile();
		ll_semester->LoadSemesterFile();
		ll_semester->AvaibleSemester();
		ll_inscription->LoadInscriptionsFile();

	}
	break;
	case WM_CTLCOLORDLG:
	{
		HBRUSH g_hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); // Color del Dialogo, Oxford Blue (0,33,71)
		return (LONG)g_hbrBackground;
	}
	break;
	case WM_CTLCOLORSTATIC:
	{

		switch (GetDlgCtrlID((HWND)lParam))
		{
		case IDC_STATIC1:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, RGB(255, 255, 255));

		}
		break;
		case IDC_STATIC2:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, RGB(255, 255, 255));

		}
		break;
		case IDC_STATIC3:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, RGB(255, 255, 255));
		}
		break;
		case IDC_STATIC5:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(30, 180,255)); // Cambia el color del texto del static
			SetBkColor(hdcStatic, RGB(255, 255, 255)); // Cambia el color del bg del static
		}
		break;
		}

		return (LRESULT)GetStockObject(NULL_BRUSH);
		break;
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDC_EDIT1: {

			HWND username = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(username, _user, 1024);

		}
		break;
		case IDC_EDIT2: {

			HWND pass = GetDlgItem(hWnd, IDC_EDIT2);
			GetWindowText(pass, _password, 1024);

		}
		break;
		case IDOK:
		{
			char temp[1024] = "";

			HWND combobox;
			combobox = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(combobox, CB_GETCURSEL,0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(combobox,  CB_GETLBTEXT, index, (LPARAM)temp); // Asigna el elemento del combobox a un temporal


			if (strcmp("Coordinador General",temp) == 0) {

				if (strcmp(user,_user) == 0 && strcmp(password,_password) == 0) {

					access = 1;

					EndDialog(hWnd, 0);
					DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), hWnd, MAIN);

				}
				else {
	
					MessageBox(NULL, "Datos ingresados incorrectos.", "Error", NULL);
					SetDlgItemText(hWnd, IDC_EDIT1, buff); // Limpia el edit
					SetDlgItemText(hWnd, IDC_EDIT2, buff);

				}	
			}
			else {

				Coordinator* name_data = new Coordinator;

				HWND user = GetDlgItem(hWnd, IDC_EDIT1);
				GetWindowText(user, name_data->username, 1024);

				user_tree->FindUser(name_data);

				if (strcmp(user_data->username, _user) == 0 && strcmp(user_data->password, _password) == 0) {

					access = 0;

					strcpy_s(career_co, user_data->role);

					EndDialog(hWnd, 0);
					DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN), hWnd, MAIN);

				}
				else {

					MessageBox(NULL, "Datos ingresados incorrectos.", "Error", NULL);
					SetDlgItemText(hWnd, IDC_EDIT1, buff); // Limpia el edit
					SetDlgItemText(hWnd, IDC_EDIT2, buff);
				}

			}

		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK MAIN(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		Image(hWnd, IDC_STATIC1, university, 570, 340);

		if (access == 1) {

			
			EnableMenuItem(GetMenu(hWnd), ID_REGISTRAR_CARRERAS, MF_BYCOMMAND | MF_ENABLED); // Habilita item del menu
			EnableMenuItem(GetMenu(hWnd), ID_REGISTRAR_COORDINADORES, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(GetMenu(hWnd), ID_CAREERS, MF_BYCOMMAND | MF_ENABLED);
            EnableMenuItem(GetMenu(hWnd), ID_CREAR_SEMESTRE, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(GetMenu(hWnd), ID_SEMESTER_CLOSE, MF_BYCOMMAND | MF_ENABLED);
		}
		else {

			EnableMenuItem(GetMenu(hWnd), ID_REGISTRAR_ALUMNOS, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(GetMenu(hWnd), ID_PROCESS, MF_BYCOMMAND | MF_ENABLED);
			EnableMenuItem(GetMenu(hWnd), ID_CALIFICACIONES_CAPTURA, MF_BYCOMMAND | MF_ENABLED);
			
		}

		ll_career->LoadCareersFile();
		ll_subject->LoadSubjectsFile();
		ll_student->LoadStudentsFile();
		ll_semester->LoadSemesterFile();
		ll_semester->AvaibleSemester();
		ll_inscription->LoadInscriptionsFile();
		
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_REGISTRAR_COORDINADORES:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_USERS), hWnd, USERS);
		}
		break;
		case ID_REGISTRAR_ALUMNOS:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_STUDENTS), hWnd, STUDENTS);
		}
		break;
		case ID_CAREERS:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SUBJECTS), hWnd, SUBJECTS);
		}
		break;
		case ID_CREAR_SEMESTRE:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SEMESTER), hWnd, SEMESTER);
		}
		break;
		case ID_SEMESTER_CLOSE:
		{
			if (ayd_first != NULL) {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SEMESTER_STATUS), hWnd, SEMESTER_STATUS);
			}
			else {

				MessageBox(NULL, "No ha creado ningun semestre.", "Semestre Status", MB_ICONINFORMATION);
			}
		}
		break;
		case ID_PROCESS:
		{
			if (ayd_first == NULL) {

				MessageBox(NULL, "No hay ningun semestre abierto.", "Semestre Status", MB_ICONINFORMATION);

			}
			else if (ayd_aux->finals == 0) {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_INSCRIPTION_BROWSER), hWnd, INSCRIPTION_BROWSER);
			}
			else {

				MessageBox(NULL, "El semestre actual esta en finales.", "Semestre Status", MB_ICONINFORMATION);
			}
		}
		break;
		case ID_CALIFICACIONES_CAPTURA:
		{
			if (ayd_aux->finals == 1) {
				DialogBox(hInst, MAKEINTRESOURCE(IDD_STUDENT_BROWSER), hWnd, STUDENT_BROWSER);

				if (student_found == 1) {

					DialogBox(hInst, MAKEINTRESOURCE(IDD_GRADES), hWnd, GRADES);
				}
			}
			else {

				MessageBox(NULL, "El semestre actual no esta en finales.", "Semestre Status", MB_ICONINFORMATION);
			}
		}
		break;
		case ID_INSCRIPCION_VER:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_STUDENT_BROWSER), hWnd, STUDENT_BROWSER);
		}
		break;
		case ID_CALIFICACIONES_VER:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SUBJECT_LIST), hWnd, SUBJECT_BROWSER);
		}
		break;
		case ID_GRADES_VIEWBYSTUDENT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_STUDENT_BROWSER), hWnd, SEMESTER_BROWSER);
		}
		break;
		case ID_GRADES_VIEWBYSEMESTER:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SEMESTER_BROWSER), hWnd, SEMESTER_BROWSER);
		}
		break;
		case ID_BROWSER_SEARCH:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_GENERAL_BROWSER), hWnd, GENERAL_BROWSER);
		}
		break;
		case ID_SALIR:
		{

			EndDialog(hWnd, 0);
			DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGIN), hWnd, LOGIN);
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

void Image(HWND hWnd, WPARAM wParam, char *imagen, int m, int n) {

	static HBITMAP bmp1, bmp2;

	bmp1 = (HBITMAP)SendDlgItemMessage(hWnd, wParam, STM_GETIMAGE, IMAGE_BITMAP, 0);
	bmp2 = (HBITMAP)LoadImage(NULL, imagen, IMAGE_BITMAP, m, n, LR_LOADFROMFILE);

	SendDlgItemMessage(hWnd, wParam, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);

}

void UserRead() {

	ifstream Userfile;

	Userfile.open("MainUser.txt", ios::in);
	if (Userfile.is_open()) {

		while (!Userfile.eof()) {

			Userfile >> user; // Asigna lo que contiene la primera linea del .txt a una variable
			Userfile >> password; // Asigna lo que contiene la segunda linea del .txt a una variable

		}

	}
	else {
	
		MessageBox(NULL, "No se pudo abrir el archivo.", "Error", NULL);
		exit(1); // Cierra el programa

	}
	
	Userfile.close();
}

void FillCb(HWND object, UINT message, char* filename)
{
	ifstream archive;
	char row[30] = "";
	archive.open(filename);
	if (archive.is_open())
	{
		archive.getline(row, 30);
		while (!archive.eof())
		{
			SendMessage(object, message, 0, (LPARAM)row);
			archive.getline(row, 30);
			
		}

	}

	archive.close();
}

BOOL CALLBACK USERS(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hWnd, IDC_EDIT2, "Coordinador de Carrera");
		
		Image(hWnd, IDC_STATIC7, oxford, 190, 190);

	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON3:
		{
			OPENFILENAME ofn;       // Estructura de Dialogo
			TCHAR szFile[260] = { 0 };

			char photo[1024] = ""; // Almacena temporalmente foto del coordinador

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			// Solo acepta imagenes .bmp
			ofn.lpstrFilter = "Bitmap\0*.bmp";
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileName(&ofn) == TRUE)
			{

				SetDlgItemText(hWnd, IDC_EDIT8, ofn.lpstrFile); // Pone la ubicacion de la foto en un edit
				
				HWND location = GetDlgItem(hWnd, IDC_EDIT8);
				GetWindowText(location, photo, 1024);

				Image(hWnd, IDC_STATIC7, photo, 190, 190);
			}
		}return true;
		break;
		case ID_SEARCH:
		{
			SetDlgItemText(hWnd, IDC_EDIT1, buff);
			SetDlgItemText(hWnd, IDC_EDIT3, buff);
			SetDlgItemText(hWnd, IDC_EDIT4, buff);
			SetDlgItemText(hWnd, IDC_EDIT5, buff);
			SetDlgItemText(hWnd, IDC_EDIT6, buff);
			SetDlgItemText(hWnd, IDC_EDIT7, buff);
			SetDlgItemText(hWnd, IDC_EDIT8, buff);

			EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), TRUE); // Deshabilita los edits
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT3), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT7), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT8), TRUE);

			Image(hWnd, IDC_STATIC7, oxford, 190, 190);

			DialogBox(hInst, MAKEINTRESOURCE(IDD_BROWSER), hWnd, COORDINATOR_BROWSER);
													  
			if (found == 1) {

				SetDlgItemText(hWnd, IDC_EDIT1, user_data->completename); // Muestra los datos
				SetDlgItemText(hWnd, IDC_EDIT3, user_data->username);
				SetDlgItemText(hWnd, IDC_EDIT4, user_data->password);
				SetDlgItemText(hWnd, IDC_EDIT8, user_data->photo);
				SetDlgItemText(hWnd, IDC_EDIT5, career_aux->descr);
				SetDlgItemText(hWnd, IDC_EDIT6, career_aux->keyword);
				SetDlgItemText(hWnd, IDC_EDIT7, career_aux->acronym);

				Image(hWnd, IDC_STATIC7, user_data->photo, 190, 190);

				EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), FALSE); // Deshabilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT3), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT7), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT8), FALSE);

				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_SHOW); // Hace visible un boton
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_SHOW); // Hace visible un boton
			}
			
		}
		break;
		case ID_EDIT:
		{
			if (found == 0) {
				MessageBox(NULL, "No ha buscado a ningun coordinador.", "Error", MB_ICONINFORMATION);

			}
			else {

				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_SHOW); // Hace visible un boton

				EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), TRUE); // Habilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT3), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT7), TRUE);
				
			}


		}
		break;
		case ID_SAVE:
		{
			Coordinator data; // Almacenar datos del coordinador
		    Career careerdata; // Almacenar datos de la carrera

			HWND name = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(name, data.completename, 1024);

			HWND user = GetDlgItem(hWnd, IDC_EDIT3);
			GetWindowText(user, data.username, 1024);
			GetWindowText(user, careerdata.career_coord, 1024);

			HWND pass = GetDlgItem(hWnd, IDC_EDIT4);
			GetWindowText(pass, data.password, 1024);

			HWND picture = GetDlgItem(hWnd, IDC_EDIT8);
			GetWindowText(picture, data.photo, 1024);

			HWND career = GetDlgItem(hWnd, IDC_EDIT5);
			GetWindowText(career, careerdata.descr, 1024);

			HWND key = GetDlgItem(hWnd, IDC_EDIT6);
			GetWindowText(key, careerdata.keyword, 7);
			
			HWND initials = GetDlgItem(hWnd, IDC_EDIT7);
			GetWindowText(initials, careerdata.acronym, 7);
			GetWindowText(initials, data.role, 7);
		

			if (data.completename[0] == NULL || data.password[0] == NULL || data.username[0] == NULL|| data.photo[0] == NULL || data.role[0] == NULL || careerdata.descr[0] == NULL || careerdata.acronym[0] == NULL) {

				MessageBox(NULL, "Completa todos los campos.", "Error", MB_ICONEXCLAMATION);
			}
			else{

				if (found != 1) {

					user_tree->AddUser(data); // Crea nuevo coordinador
					ll_career->AddCareer(careerdata);

					if (exits == 1) {

						MessageBox(NULL, "Usuario no disponible", "Usuario", MB_ICONEXCLAMATION);
						exits = 0;
					}
					else if (career_exits == 1) {

						MessageBox(NULL, "Carrera, clave o siglas no disponible", "Carrera", MB_ICONEXCLAMATION);
						career_exits = 0;

					}
					else {

						MessageBox(NULL, "Usuario creado con éxito", "Usuario", MB_ICONINFORMATION);
					}
				}
				else {

					GetWindowText(name, user_data->completename, 1024); // Guarda los cambios
					GetWindowText(user, career_aux->career_coord, 1024);
					GetWindowText(user, user_data->username, 1024);
					GetWindowText(pass, user_data->password, 1024);
					GetWindowText(picture, user_data->photo, 1024);
					GetWindowText(career, user_data->role, 7);
					GetWindowText(career, career_aux->descr, 1024);
					GetWindowText(key, career_aux->keyword, 5);
					GetWindowText(initials, career_aux->acronym, 5);

					MessageBox(NULL, "Usuario guardado con éxito", "Usuario", MB_ICONINFORMATION);

					ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
					ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
				}

				SetDlgItemText(hWnd, IDC_EDIT1, buff); 
				SetDlgItemText(hWnd, IDC_EDIT3, buff);
				SetDlgItemText(hWnd, IDC_EDIT4, buff);
				SetDlgItemText(hWnd, IDC_EDIT5, buff);
				SetDlgItemText(hWnd, IDC_EDIT6, buff);
				SetDlgItemText(hWnd, IDC_EDIT7, buff);
				SetDlgItemText(hWnd, IDC_EDIT8, buff);

				Image(hWnd, IDC_STATIC7, oxford, 190, 190);

			}
		}
		break;
		case IDC_BUTTON4: // Okay
		{
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), TRUE); // Habilita los edits
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT3), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT7), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT8), TRUE);

			SetDlgItemText(hWnd, IDC_EDIT1, buff);
			SetDlgItemText(hWnd, IDC_EDIT3, buff);
			SetDlgItemText(hWnd, IDC_EDIT4, buff);
			SetDlgItemText(hWnd, IDC_EDIT5, buff);
			SetDlgItemText(hWnd, IDC_EDIT6, buff);
			SetDlgItemText(hWnd, IDC_EDIT7, buff);
			SetDlgItemText(hWnd, IDC_EDIT8, buff);

			Image(hWnd, IDC_STATIC7, oxford, 190, 190);

			ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
			ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
		}
		break;
		case IDC_BUTTON5: // Delete
		{
			int msgboxID = MessageBox(NULL, "Eliminara todos los datos del coordinador y la carrera.\n¿Desea continuar?", "Confirmación", MB_ICONEXCLAMATION | MB_YESNO);

			if (msgboxID == IDYES)
			{
				user_tree->DeleteUser(user_data);
				ll_career->DeleteCareer(career_aux);

				SetDlgItemText(hWnd, IDC_EDIT1, buff);
				SetDlgItemText(hWnd, IDC_EDIT3, buff);
				SetDlgItemText(hWnd, IDC_EDIT4, buff);
				SetDlgItemText(hWnd, IDC_EDIT5, buff);
				SetDlgItemText(hWnd, IDC_EDIT6, buff);
				SetDlgItemText(hWnd, IDC_EDIT7, buff);
				SetDlgItemText(hWnd, IDC_EDIT8, buff);

				EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), TRUE); // Habilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT3), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT7), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT8), TRUE);

				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);

				Image(hWnd, IDC_STATIC7, oxford, 190, 190);

				MessageBox(NULL, "Coordinador eliminado con exito.", "Usuario", MB_ICONINFORMATION);
			}
		}
		break;
		case ID_BACK:
		{

			int msgboxID = MessageBox(NULL, "Se perderán todos los cambios no guardados.\n¿Desea continuar?", "Confirmación", MB_ICONEXCLAMATION | MB_YESNO);

			if (msgboxID == IDYES)
			{
				ll_career->SaveAcronyms();
				EndDialog(hWnd, 0);
			}

		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		ll_career->SaveAcronyms();
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK SUBJECTS(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		Image(hWnd, IDC_STATIC7, oxford, 190, 185);

		HWND Careers;
		Careers = GetDlgItem(hWnd, IDC_COMBO1);

		FillCb(Careers, CB_ADDSTRING, career_acronym);

		index = SendMessage(Careers, CB_SETCURSEL, 0, 0);
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_SAVE:
		{
			Subject data; // Almacenar datos de la materia

			HWND career;
			career = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(career, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(career, CB_GETLBTEXT, index, (LPARAM)data.career); // Asigna el elemento del combobox a un temporal


			HWND name = GetDlgItem(hWnd, IDC_EDIT2);
			GetWindowText(name, data.descr, 1024);

			HWND key = GetDlgItem(hWnd, IDC_EDIT4);
			GetWindowText(key, data.keyword, 5);

			HWND credit = GetDlgItem(hWnd, IDC_EDIT5);
			GetWindowText(credit, data.credits, 2);

			HWND time = GetDlgItem(hWnd, IDC_EDIT5);
			GetWindowText(time, data.hours, 2);

			if (data.descr[0] == NULL || data.keyword[0] == NULL || data.credits[0] == NULL || data.hours[0] == NULL || data.career[0] == NULL) {

				MessageBox(NULL, "Completa todos los campos.", "Error", MB_ICONEXCLAMATION);
			}
			else {

				if (subject_found != 1) {

					ll_subject->AddSubject(data); // Crea nueva materia

					if (subject_exits == 1) {

						MessageBox(NULL, "Materia o clave no disponible", "Materia", MB_ICONEXCLAMATION);
						subject_exits = 0;
					}
					else {

						MessageBox(NULL, "Materia creada con éxito", "Materia", MB_ICONINFORMATION);

					}

				}
				else {

					GetWindowText(career, subject_aux->career, 5); // Guarda los cambios
					GetWindowText(name, subject_aux->descr, 1024); // Guarda los cambios
					GetWindowText(key, subject_aux->keyword, 5);
					GetWindowText(credit, subject_aux->credits, 1);
					GetWindowText(time, subject_aux->hours, 2);

					MessageBox(NULL, "Materia guardada con éxito", "Materia", MB_ICONINFORMATION);

					ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
					ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
				}

	
				index = SendMessage(career, CB_SETCURSEL, 0, 0);
				SetDlgItemText(hWnd, IDC_EDIT2, buff);
				SetDlgItemText(hWnd, IDC_EDIT4, buff);
				SetDlgItemText(hWnd, IDC_EDIT5, buff);
				SetDlgItemText(hWnd, IDC_EDIT6, buff);

			}
		}
		break;
		case ID_SEARCH:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SUBJECT_BROWSER), hWnd, SUBJECT_BROWSER);

			SetDlgItemText(hWnd, IDC_EDIT2, buff);
			SetDlgItemText(hWnd, IDC_EDIT4, buff);
			SetDlgItemText(hWnd, IDC_EDIT5, buff);
			SetDlgItemText(hWnd, IDC_EDIT6, buff);

			EnableWindow(GetDlgItem(hWnd, IDC_COMBO1), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), TRUE); // Deshabilita los edits
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), TRUE);

			if (subject_found == 1) {

				SetDlgItemText(hWnd, IDC_COMBO1, subject_aux->career);
				SetDlgItemText(hWnd, IDC_EDIT2, subject_aux->descr); // Muestra los datos
				SetDlgItemText(hWnd, IDC_EDIT4, subject_aux->keyword);
				SetDlgItemText(hWnd, IDC_EDIT5, subject_aux->credits);
				SetDlgItemText(hWnd, IDC_EDIT6, subject_aux->hours);

				EnableWindow(GetDlgItem(hWnd, IDC_COMBO1), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), FALSE); // Deshabilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), FALSE);

				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_SHOW); // Hace visible un boton
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_SHOW); // Hace visible un boton
			}

		}
		break;
		case ID_EDIT:
		{
			if (subject_found == 0) {
				MessageBox(NULL, "No ha buscado ninguna materia.", "Error", MB_ICONINFORMATION);
			}
			else {

				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_SHOW); 

				EnableWindow(GetDlgItem(hWnd, IDC_COMBO1), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), TRUE); // Habilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), TRUE);
				
			}
		}
		break;
		case IDC_BUTTON4: // Okay
		{
			EnableWindow(GetDlgItem(hWnd, IDC_COMBO1), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), TRUE); // Habilita los edits
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), TRUE);

			HWND Careers;
			Careers = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(Careers, CB_SETCURSEL, 0, 0);

			SetDlgItemText(hWnd, IDC_EDIT2, buff);
			SetDlgItemText(hWnd, IDC_EDIT4, buff);
			SetDlgItemText(hWnd, IDC_EDIT5, buff);
			SetDlgItemText(hWnd, IDC_EDIT6, buff);

			ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
			ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
		}
		break;
		case IDC_BUTTON5: // Delete
		{
			int msgboxID = MessageBox(NULL, "Eliminara todos los datos de la materia.\n¿Desea continuar?", "Confirmación", MB_ICONEXCLAMATION | MB_YESNO);

			if (msgboxID == IDYES)
			{
				ll_subject->DeleteSubject(subject_aux);

				HWND Careers;
				Careers = GetDlgItem(hWnd, IDC_COMBO1);
				index = SendMessage(Careers, CB_SETCURSEL, 0, 0);

				SetDlgItemText(hWnd, IDC_EDIT2, buff);
				SetDlgItemText(hWnd, IDC_EDIT4, buff);
				SetDlgItemText(hWnd, IDC_EDIT5, buff);
				SetDlgItemText(hWnd, IDC_EDIT6, buff);

				EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), TRUE); // Habilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT5), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT6), TRUE);


				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);


				MessageBox(NULL, "Materia eliminada con exito.", "Materia", MB_ICONINFORMATION);
			}
		}
		break;
		case ID_BACK:
		{
			int msgboxID = MessageBox(NULL, "Se perderán todos los cambios no guardados.\n¿Desea continuar?", "Confirmación", MB_ICONEXCLAMATION | MB_YESNO);

			if (msgboxID == IDYES)
			{
				EndDialog(hWnd, 0);
			}

		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK SEMESTER(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)

{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		Image(hWnd, IDC_STATIC7, campus, 450, 150);

		HWND hPeriod;
		hPeriod = GetDlgItem(hWnd, IDC_COMBO1);

		FillCb(hPeriod, CB_ADDSTRING, periods);

		index = SendMessage(hPeriod, CB_SETCURSEL, 0, 0);
	}
	break;
	case WM_CTLCOLORDLG:
	{
		HBRUSH g_hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); // Color del Dialogo, Oxford Blue (0,33,71)
		return (LONG)g_hbrBackground;
	}
	break;
	case WM_CTLCOLORSTATIC:
	{

		switch (GetDlgCtrlID((HWND)lParam))
		{
		case IDC_STATIC1:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, RGB(255, 255, 255));

		}
		break;
		case IDC_STATIC2:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, RGB(255, 255, 255));

		}
		break;
		}

		return (LRESULT)GetStockObject(NULL_BRUSH);
		break;
	}
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			Semester data;

			HWND period;
			period = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(period, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(period, CB_GETLBTEXT, index, (LPARAM)data.period); // Asigna el elemento del combobox a un temporal

			HWND year;
			year = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(year, data.year, 5);

			strcpy_s(data.semester, data.period); // Concatena el periodo con el año
			strcat_s(data.semester, " ");
			strcat_s(data.semester, data.year);

			GetLocalTime(&lt);
			char yearok[1024];
			snprintf(yearok, 1024, "% 02d", lt.wYear);

			int selected_year;
			int actual_year;

			selected_year = atoi(data.year);
			actual_year = atoi(yearok);

			if (data.year[0] == NULL) {

				MessageBox(NULL, "Completa todos los campos.", "Error", MB_ICONEXCLAMATION);
			}
			else if (selected_year < actual_year) {

				MessageBox(NULL, "Año no disponible.", "Error", MB_ICONEXCLAMATION);
				SetDlgItemText(hWnd, IDC_EDIT1, buff);
			}
			else {

				ll_semester->AddSemester(data); // Crea nueva materia

				if (semester_exits == 1) {

					MessageBox(NULL, "Semestre no disponible", "Materia", MB_ICONEXCLAMATION);
					semester_exits = 0;
				}
				else {

					MessageBox(NULL, "Semestre creado con éxito", "Materia", MB_ICONINFORMATION);

				}

			}

			SetDlgItemText(hWnd, IDC_EDIT1, buff);
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		
		EndDialog(hWnd, 0);
		
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK SEMESTER_STATUS(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_INITDIALOG:
	{
		ll_semester->SaveSemesters();
		
		HWND semester;
		semester = GetDlgItem(hWnd, IDC_COMBO1);

		FillCb(semester, CB_ADDSTRING, semesters);

		SetDlgItemText(hWnd, IDC_EDIT3, actual_semester);

		index = SendMessage(semester, CB_SETCURSEL, 0, 0);
		
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOPEN:
		{
			Semester wanted;

			HWND semester = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(semester, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(semester, CB_GETLBTEXT, index, (LPARAM)wanted.semester); // Asigna el elemento del combobox a un temporal

			ll_semester->AvaibleSemester();

			if (avaible == 0) {
				
				if (ayd_aux->open == 1) {

					MessageBox(NULL, "Semestre ya abierto.", "Error", MB_ICONEXCLAMATION);
				}
				else {

					MessageBox(NULL, "El semestre actual sigue abierto.", "Error", MB_ICONEXCLAMATION);

				}
				
			}
			else {

				ll_semester->FindSemester(wanted); // Busca el semestre

				if (avaible == 1 && ayd_aux->opened == 0) {
					ayd_aux->open = 1;
					MessageBox(NULL, "Semestre Abierto.", "Status", MB_ICONINFORMATION);

					strcpy_s(actual_semester, ayd_aux->semester);

					SetDlgItemText(hWnd, IDC_EDIT3, actual_semester);

				}
				else {
					MessageBox(NULL, "Semestre seleccionado ya está cerrado.", "Error", MB_ICONEXCLAMATION);
				}

			}

	}
	break;
	case IDCLOSE:
		{
			Semester wanted;

			HWND semester = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(semester, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(semester, CB_GETLBTEXT, index, (LPARAM)wanted.semester); // Asigna el elemento del combobox a un temporal

			ll_semester->FindSemester(wanted);

			if (ayd_aux->open == 1 && ayd_aux->opened == 0 && ayd_aux->finals == 1) {
				ayd_aux->open = 0;
				ayd_aux->opened = 1;
				avaible = 1;
				MessageBox(NULL, "Semestre Cerrado.", "Status", MB_ICONINFORMATION);

				strcpy_s(actual_semester, buff);

				SetDlgItemText(hWnd, IDC_EDIT3, actual_semester);

			}
			else if (ayd_aux->open == 0 && ayd_aux->opened == 0) {

				int msgboxID = MessageBox(NULL, "Este semestre nunca ha sido abierto. \n¿Desea eliminarlo?", "Confirmación", MB_ICONEXCLAMATION | MB_YESNO);

				if (msgboxID == IDYES)
				{
					ll_semester->DeleteSemester(ayd_aux);
					ll_semester->SaveSemesters();

					MessageBox(NULL, "Semestre eliminado con éxito.", "Semestre", MB_ICONINFORMATION);

					if (ayd_first != NULL) {
						SendDlgItemMessage(hWnd, IDC_COMBO1, CB_RESETCONTENT, 0, 0);
						FillCb(semester, CB_ADDSTRING, semesters);
						index = SendMessage(semester, CB_SETCURSEL, 0, 0);
					}
					else {
						EndDialog(hWnd, 0);
					}

				}
			}
			else if (ayd_aux->open == 1 && ayd_aux->opened == 0 && ayd_aux->finals == 0) {
			
				MessageBox(NULL, "El semestre no está en finales.", "Status", MB_ICONEXCLAMATION);
			}
			else{

				MessageBox(NULL, "Semestre seleccionado ya está cerrado.", "Status", MB_ICONEXCLAMATION);
			}

		}
		break;
	case IDFINALS:
	{
		Semester wanted;

		HWND semester = GetDlgItem(hWnd, IDC_COMBO1);
		index = SendMessage(semester, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

		SendMessage(semester, CB_GETLBTEXT, index, (LPARAM)wanted.semester); // Asigna el elemento del combobox a un temporal

		ll_semester->FindSemester(wanted); // Busca el semestre
		

		if (ayd_aux->open == 1) {
			ayd_aux->finals = 1;
			MessageBox(NULL, "Semestre en Finales.", "Semestre Status", MB_ICONINFORMATION);
		}
		else  {

			MessageBox(NULL, "El semestre no está en curso", "Error", MB_ICONEXCLAMATION);
		}


	}
	break;
	}
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
	    break;
	default:
		return FALSE;
	    break;
	}
	return FALSE;
}

BOOL CALLBACK COORDINATOR_BROWSER(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			Coordinator* name_data = new Coordinator;

			HWND user = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(user, name_data->username,1024);

			if (name_data->username[0] == NULL) {
				MessageBox(NULL, "Completa el campo.", "Error", NULL);
			}
			else {

				user_tree->FindUser(name_data); // Busca el coordinador

				if (found == 1) {
					EndDialog(hWnd, 0);
				}
				else {
					SetDlgItemText(hWnd, IDC_EDIT1, buff);
				}
			}
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK SUBJECT_BROWSER(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			Subject wanted;

			HWND key = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(key, wanted.keyword, 7);

			if (wanted.keyword[0] == NULL) {
				MessageBox(NULL, "Completa el campo.", "Error", NULL);
			}
			else {

				ll_subject->FindSubject(wanted); // Busca el coordinador

				if (subject_found == 1) {
					EndDialog(hWnd, 0);
				}
				else {
					SetDlgItemText(hWnd, IDC_EDIT1, buff);
				}
			}
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK STUDENTS(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hWnd, IDC_COMBO1, career_co);
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDC_EDIT1:
		{
			Student data;

			HWND name = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(name, data.name, 1024);

			HWND last = GetDlgItem(hWnd, IDC_EDIT2);
			GetWindowText(last, data.lastname, 1024);

			HWND fullname = GetDlgItem(hWnd, IDC_EDIT3);

			strcpy_s(data.completename, data.lastname);
			strcat_s(data.completename, " ");
			strcat_s(data.completename, data.name);

			SetDlgItemText(hWnd, IDC_EDIT3, data.completename);

		}
		break;
		case IDC_EDIT2:
		{
			Student data;

			HWND name = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(name, data.name, 1024);

			HWND last = GetDlgItem(hWnd, IDC_EDIT2);
			GetWindowText(last, data.lastname, 1024);

			HWND fullname = GetDlgItem(hWnd, IDC_EDIT3);

			strcpy_s(data.completename, data.lastname);
			strcat_s(data.completename, " ");
			strcat_s(data.completename, data.name);

			SetDlgItemText(hWnd, IDC_EDIT3, data.completename);

		}
		break;
		case ID_SAVE:
		{
			Student data;
		
			HWND name = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(name, data.name, 1024);

			HWND last = GetDlgItem(hWnd, IDC_EDIT2);
			GetWindowText(last, data.lastname, 1024);

			HWND fullname = GetDlgItem(hWnd, IDC_EDIT3);

			strcpy_s(data.completename, data.lastname);
			strcat_s(data.completename, " ");
			strcat_s(data.completename, data.name);

			SetDlgItemText(hWnd, IDC_EDIT3, data.completename);

			HWND id = GetDlgItem(hWnd, IDC_EDIT4);
			GetWindowText(id, data.ID, 10);

			strcpy_s(data.career, career_co);


			if (data.name[0] == NULL || data.lastname[0] == NULL || data.ID[0] == NULL) {

				MessageBox(NULL, "Completa todos los campos.", "Error", MB_ICONEXCLAMATION);
			}
			else {

				if (student_found != 1) {

					ll_student->AddStudent(data); // Crea nuevo estudiante

					if (student_exits == 1) {

						MessageBox(NULL, "Matricula no disponible", "Alumno", MB_ICONEXCLAMATION);
						subject_exits = 0;
					}
					else {

						MessageBox(NULL, "Alumno creado con éxito", "Alumno", MB_ICONINFORMATION);

					}
				}
				else {

					GetWindowText(name, undergrad_aux->name, 1024); // Guarda los cambios
					GetWindowText(last, undergrad_aux->lastname, 1024); // Guarda los cambios
					GetWindowText(fullname, undergrad_aux->completename, 1024);
					GetWindowText(id, undergrad_aux->ID, 7);

					MessageBox(NULL, "Alumno guardado con éxito", "Alumno", MB_ICONINFORMATION);

					ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
					ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
				}


				SetDlgItemText(hWnd, IDC_EDIT1, buff);
				SetDlgItemText(hWnd, IDC_EDIT2, buff);
				SetDlgItemText(hWnd, IDC_EDIT3, buff);
				SetDlgItemText(hWnd, IDC_EDIT4, buff);
			
			
			}

		}
		break;
		case ID_SEARCH:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_STUDENT_BROWSER), hWnd, STUDENT_BROWSER);

			SetDlgItemText(hWnd, IDC_EDIT1, buff);
			SetDlgItemText(hWnd, IDC_EDIT2, buff);
			SetDlgItemText(hWnd, IDC_EDIT3, buff);
			SetDlgItemText(hWnd, IDC_EDIT4, buff);

			EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), TRUE); // Deshabilita los edits
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);

			if (student_found == 1) {

				SetDlgItemText(hWnd, IDC_COMBO1, undergrad_aux->career);
				SetDlgItemText(hWnd, IDC_EDIT1, undergrad_aux->name); // Muestra los datos
				SetDlgItemText(hWnd, IDC_EDIT2, undergrad_aux->lastname);
				SetDlgItemText(hWnd, IDC_EDIT3, undergrad_aux->completename);
				SetDlgItemText(hWnd, IDC_EDIT4, undergrad_aux->ID);

				EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), FALSE); // Deshabilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), FALSE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), FALSE);

				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_SHOW); // Hace visible un boton
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_SHOW); // Hace visible un boton
			}
			
		}
		break;
		case ID_EDIT:
		{
			if (student_found == 0) {
				MessageBox(NULL, "No ha buscado ningun alumno.", "Error", MB_ICONINFORMATION);
			}
			else {

				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_SHOW);

				EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), TRUE); // Habilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);

			}

		}
		break;
		case IDC_BUTTON4: // Okay
		{
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), TRUE); // Habilita los edits
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), TRUE);
			EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);

			SetDlgItemText(hWnd, IDC_EDIT1, buff);
			SetDlgItemText(hWnd, IDC_EDIT2, buff);
			SetDlgItemText(hWnd, IDC_EDIT3, buff);
			SetDlgItemText(hWnd, IDC_EDIT4, buff);

			ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
			ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);
		}
		break;
		case IDC_BUTTON5: // Delete
		{
			int msgboxID = MessageBox(NULL, "Eliminara todos los datos del alumno.\n¿Desea continuar?", "Confirmación", MB_ICONEXCLAMATION | MB_YESNO);

			if (msgboxID == IDYES)
			{
				ll_student->DeleteStudent(undergrad_aux);


				SetDlgItemText(hWnd, IDC_EDIT1, buff);
				SetDlgItemText(hWnd, IDC_EDIT2, buff);
				SetDlgItemText(hWnd, IDC_EDIT3, buff);
				SetDlgItemText(hWnd, IDC_EDIT4, buff);

				EnableWindow(GetDlgItem(hWnd, IDC_EDIT1), TRUE); // Habilita los edits
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT2), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_EDIT4), TRUE);
				EnableWindow(GetDlgItem(hWnd, IDC_COMBO1), TRUE);


				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON4), SW_HIDE);// Hace invisible el boton
				ShowWindow(GetDlgItem(hWnd, IDC_BUTTON5), SW_HIDE);


				MessageBox(NULL, "Alumno eliminado con exito.", "Alumno", MB_ICONINFORMATION);
			}
		}
		break;
		case ID_BACK:
		{
			int msgboxID = MessageBox(NULL, "Se perderán todos los cambios no guardados.\n¿Desea continuar?", "Confirmación", MB_ICONEXCLAMATION | MB_YESNO);

			if (msgboxID == IDYES)
			{
				EndDialog(hWnd, 0);
			}
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK STUDENT_BROWSER(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		HWND hstudents;
		hstudents = GetDlgItem(hWnd, IDC_COMBO1);

		undergrad_aux = undergrad_first;

		while (undergrad_aux != NULL) {
			
			if (access == 0) {
				if (strcmp(undergrad_aux->career, career_co) == 0) {
					SendMessage(hstudents, CB_ADDSTRING, 0, (LPARAM)TEXT(undergrad_aux->ID));
				}
				
			}
			else {
				SendMessage(hstudents, CB_ADDSTRING, 0, (LPARAM)TEXT(undergrad_aux->ID));
			}

			undergrad_aux = undergrad_aux->next;
		}

		index = SendMessage(hstudents, CB_SETCURSEL, 0, 0); // Pone el primer elemento del combobox

	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			Student wanted;

			HWND students;
			students = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(students, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(students, CB_GETLBTEXT, index, (LPARAM)wanted.ID); // Asigna el elemento del combobox a un temporal

		
			ll_student->FindStudent(wanted); // Busca el alumno

			if (student_found == 1) {
				EndDialog(hWnd, 0);
			}
			
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK INSCRIPTION(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hWnd, IDC_EDIT3, undergrad_aux->completename);
		SetDlgItemText(hWnd, IDC_EDIT5, undergrad_aux->career);
		SetDlgItemText(hWnd, IDC_STATIC7, undergrad_aux->total_credits);
		SetDlgItemText(hWnd, IDC_EDIT4, actual_semester);

		HWND hsubjects;
		hsubjects = GetDlgItem(hWnd, IDC_COMBO1);

		subject_aux = s_first;

		while (subject_aux != NULL) {

			if (strcmp(subject_aux->career, career_co) == 0) {
				SendMessage(hsubjects, CB_ADDSTRING, 0, (LPARAM)TEXT(subject_aux->descr));
			}
			subject_aux = subject_aux->next;
		}

		index = SendMessage(hsubjects, CB_SETCURSEL, 0, 0);

	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			total = atoi(undergrad_aux->total_credits);

			char creditstemp[4] = "";

			Subject data;

			HWND combobox;
			combobox = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(combobox, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(combobox, CB_GETLBTEXT, index, (LPARAM)data.descr); // Asigna el elemento del combobox a un temporal

			ll_subject->FindSubject(data);

			Inscription info;

			strcpy_s(info.student, undergrad_aux->ID);
			strcpy_s(info.semester, actual_semester);
			strcpy_s(info.subject, subject_aux->descr);
			strcpy_s(info.credits, subject_aux->credits);

			ll_inscription->AddInscription(info);

			if (inscription_exits == 1) {

				inscription_exits = 0;
				MessageBox(NULL, "Materia ya inscrita.", "Error", NULL);

			}
			else {

				total2 = total2 + atoi(subject_aux->credits); // Total Creditos por Semestre
				total = total + atoi(subject_aux->credits); // Total de creditos

				_itoa_s(total2, creditstemp, 10);
				_itoa_s(total, undergrad_aux->total_credits, 10);

				SetDlgItemText(hWnd, IDC_STATIC8, creditstemp);
				SetDlgItemText(hWnd, IDC_STATIC7, undergrad_aux->total_credits);
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)data.descr);

				MessageBox(NULL, "Materia Inscrita con éxito.", "Calificación", MB_ICONINFORMATION);
			}

			
			
		}
		break;
		case IDCANCEL:
		{
			total = atoi(undergrad_aux->total_credits);

			char creditstemp[4] = "";

			Inscription info;

			strcpy_s(info.student, undergrad_aux->ID);
			strcpy_s(info.semester, actual_semester);

			HWND list;
			list = GetDlgItem(hWnd, IDC_LIST1);

			index = SendMessage(list, LB_GETCURSEL, 0, 0);

			SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETTEXT, index, (LPARAM)info.subject);

			ll_inscription->FindInscription(info);

			total2 = total2 - atoi(enroll_aux->credits); // Total Creditos por Semestre
			total = total - atoi(enroll_aux->credits); // Total de creditos

			_itoa_s(total2, creditstemp, 10);
			_itoa_s(total, undergrad_aux->total_credits, 10);

			SetDlgItemText(hWnd, IDC_STATIC8, creditstemp);
			SetDlgItemText(hWnd, IDC_STATIC7, undergrad_aux->total_credits);

			ll_inscription->DeleteInscription(enroll_aux);
			SendDlgItemMessage(hWnd, IDC_LIST1, LB_DELETESTRING, index, 0);

			MessageBox(NULL, "Materia Inscrita eliminada con éxito.", "Calificación", MB_ICONINFORMATION);
			EndDialog(hWnd, 0);

		}
		break;
		case IDC_LIST1:
		{
			EnableWindow(GetDlgItem(hWnd, IDCANCEL), TRUE);
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:

		total2 = 0;
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK GRADES(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hWnd, IDC_EDIT3, undergrad_aux->completename);
		SetDlgItemText(hWnd, IDC_EDIT5, undergrad_aux->career);
		SetDlgItemText(hWnd, IDC_EDIT4, actual_semester);

		enroll_aux = enroll_first;

		while (enroll_aux != NULL) {

			if (strcmp(enroll_aux->student, undergrad_aux->ID) == 0 && strcmp(enroll_aux->semester, actual_semester) == 0) {
				SendDlgItemMessage(hWnd, IDC_LIST2, LB_ADDSTRING, 0, (LPARAM)enroll_aux->subject);
			}
			enroll_aux = enroll_aux->next;
		}

	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			Inscription data;

			HWND list;
			list = GetDlgItem(hWnd, IDC_LIST2);

			index = SendMessage(list, LB_GETCURSEL, 0, 0);

			SendDlgItemMessage(hWnd, IDC_LIST2, LB_GETTEXT, index, (LPARAM)data.subject);

			strcpy_s(data.student, undergrad_aux->ID);
			strcpy_s(data.semester, actual_semester);

			ll_inscription->FindInscription(data);
		
			DialogBox(hInst, MAKEINTRESOURCE(IDD_GRADE_SUBJECT), hWnd, GRADE_SUBJECT);
		
		}
		break;
		case IDC_LIST2:
		{

			EnableWindow(GetDlgItem(hWnd, IDOK), TRUE);

		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK SEMESTER_BROWSER(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
		{

			DialogBox(hInst, MAKEINTRESOURCE(IDD_GRADE_SUBJECT), hWnd, GRADES);

		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK GRADE_SUBJECT(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SetDlgItemText(hWnd, IDC_EDIT3, enroll_aux->subject);
		SetDlgItemText(hWnd, IDC_EDIT1, enroll_aux->grade);
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK2:
		{
			
			HWND grade = GetDlgItem(hWnd, IDC_EDIT1);
			GetWindowText(grade, enroll_aux->grade, 4);

			MessageBox(NULL, "Calificación guardada con éxito.", "Calificación", MB_ICONINFORMATION);

		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK SUBJECT_LIST(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			
		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK GENERAL_BROWSER(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		HWND type;
		type = GetDlgItem(hWnd, IDC_COMBO1);

		FillCb(type, CB_ADDSTRING, entities);

		index = SendMessage(type, CB_SETCURSEL, 0, 0);
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
		{
			HWND list;
			list = GetDlgItem(hWnd, IDC_LIST1);

			if (HIWORD(wParam) == LBN_DBLCLK) {

				int idx;
			
				index = SendMessage(list, LB_GETCURSEL, 0, 0);
				//idx = SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETITEMDATA, index, undergrad_aux);
			
			}
		}
		break;
		case IDC_BUTTON1:
		{
			char temp[1024] = "";

			HWND combobox;
			combobox = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(combobox, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(combobox, CB_GETLBTEXT, index, (LPARAM)temp); // Asigna el elemento del combobox a un temporal

			if (strcmp(temp, "Alumnos") == 0) {

				undergrad_aux = undergrad_first;
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
				while (undergrad_aux != NULL) {
					SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)undergrad_aux->completename);
					undergrad_aux = undergrad_aux->next;
				}
				
			}
			else if (strcmp(temp, "Carreras") == 0) {

				career_aux = first;
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
				while (career_aux != NULL) {
					SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)career_aux->descr);
					//SendDlgItemMessage(hWnd, IDC_LIST1, LB_SETITEMDATA, (WPARAM)actual, career_aux->descr);
					career_aux = career_aux->next;
				}

			}
			else if (strcmp(temp, "Coordinadores") == 0) {

				user_data = root;
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);

			}
			else {

				subject_aux = s_first;
				SendDlgItemMessage(hWnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
				while (subject_aux != NULL) {
					SendDlgItemMessage(hWnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)subject_aux->descr);
					//SendDlgItemMessage(hWnd, IDC_LIST1, LB_SETITEMDATA, (WPARAM)actual, career_aux->descripcion);
					subject_aux = subject_aux->next;
				}
			}

		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}

BOOL CALLBACK INSCRIPTION_BROWSER(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		HWND hstudents;
		hstudents = GetDlgItem(hWnd, IDC_COMBO1);

		undergrad_aux = undergrad_first;

		while (undergrad_aux != NULL) {

			if (strcmp(undergrad_aux->career, career_co) == 0) {
				SendMessage(hstudents, CB_ADDSTRING, 0, (LPARAM)TEXT(undergrad_aux->ID));
			}
			undergrad_aux = undergrad_aux->next;
		}

		index = SendMessage(hstudents, CB_SETCURSEL, 0, 0); // Pone el primer elemento del combobox
	}
	break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK3:
		{
			Student wanted;

			HWND students;
			students = GetDlgItem(hWnd, IDC_COMBO1);
			index = SendMessage(students, CB_GETCURSEL, 0, 0); // Guarda el indice del elemento seleccionado

			SendMessage(students, CB_GETLBTEXT, index, (LPARAM)wanted.ID); // Asigna el elemento del combobox a un temporal


			ll_student->FindStudent(wanted); // Busca el alumno

			if (student_found == 1) {
				EndDialog(hWnd, 0);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_INSCRIPTION), hWnd, INSCRIPTION);
			}

		}
		break;
		case IDOK4:
		{

		}
		break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow;
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
		break;
	}
	return FALSE;
}




