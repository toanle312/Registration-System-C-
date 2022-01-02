#include "Header/MainSource.h"
int Valid_Data(int limit);

int Main_Menu_Disp();
int Login_Disp();
void AboutUs();

bool Display_Mode_Admin(Account info, date& dmy);
void TimeLine_Disp();
int Admin_Disp();

int Year_Menu_Disp();

int Class_Menu_Disp();
int Class_Create_Mod_Menu();
int Department_Menu_Disp();
int Training_System_Menu_Disp();

int Semester_Menu_Disp();

bool Display_Mode_Student(Student &info, date& dmy);
int Student_Menu_Active();
int Student_Menu_Passive();

int Course_Menu_Disp();
int Course_Day();
int *Course_Session();
int Course_Update_Menu(vector<string> &choices);

bool Main_Menu_Proc(int option);
bool Login_Proc(int option);
bool Admin_Proc(int option, Account info, date dmy, int mod);
bool Student_Proc_Passive(int option, Student info, date dmy, int mod);
