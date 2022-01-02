#include "Header\Menu.h"
#include "Header\Year.h"
#include "Header\Class.h"
#include "Header\Node Process.h"
#include "Header\Login.h"
#include "Header\Password.h"
#include "Header\Course.h"
#include "Header\Convert.h"
#include "Header\File.h"
#include "Header\Semester.h"
#include "Header\Enroll.h"
#include "Header\Student.h"
#include "Header\Date.h"
#include "Header\Vector.h"
#include "Header\Score.h"

int Valid_Data(int limit)
{
	int n = 0;
	do
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "\t\t Invalid Input !!!!!!!!" << endl;
			cout << "\t\t Type input again: "; cin >> n;
		}
		else {
			cin >> n;
			cin.ignore();
		}
		if (n > limit)
		{
			cout << "\t\t Input data is Over Limited" << endl;
			cout<<"\t\t ";
		}
		if (n == -1) {
			cout << "\t\t You have pressed the hidden button to stop the proccess " << endl;
			cout << "\t\t "; system("pause");
			return n;
		}
	} while (n > limit || n < 0);
	cout << endl;
	return n;
}
int Main_Menu_Disp()
{
	system("cls");
	cout << "\t\t---- Welcome to course registration system ----" << endl;
	cout << "\t\t\t\t 1. Login" << endl;
	cout << "\t\t\t\t 2. About Us" << endl;
	cout << "\t\t\t\t 3. Exit" << endl;
	cout << "\t\t Your choice is (choose from 1 to 4): ";
	return Valid_Data(3);
}
int Login_Disp()
{
	system("cls");
	cout << "\t\t LOGIN" << endl;
	cout << "\t\t 1. As Admin" << endl;
	cout << "\t\t 2. As Student" << endl;
	cout << "\t\t 3. Change Password(Only student)" << endl;
	cout << "\t\t 4. Forgot password(Only student)" << endl;
	cout << "\t\t 5. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(5);
}
void AboutUs()
{
	cout << "\t\t Do an ky thuat lap trinh - Registration System" << endl;
	cout << "\t\t Cac thanh vien: " << endl;
	cout << "\t\t 20120344 - Vuong Tan Phat - vuongtanphat139@gmail.com\n\t\t 20120356 - Le Minh Quan - marucube@gmail.com\n\t\t 20120369 - Nguyen Thanh Tan - tan.personal.mail@gmail.com\n\t\t 20120386 - Le Phuoc Toan - toanle3122002@gmail.com" << endl;
	system("pause");
}
//*Phân loại tính năng có thể thực thi dựa vào thời gian
//@param info Thông tin admin
//@param dmy ngày tháng hiện tại
bool Display_Mode_Admin(Account info, date& dmy)
{
	string years = dmy.schoolyear;
	string sem_folder = ".\\Semesters\\" + years + "\\";
	dmy.semester = get_semester(sem_folder, dmy);
	if (dmy.semester == "OUT")
	{
		return Admin_Proc(Admin_Disp(), info, dmy, 0);
	}
	//Trường hợp trong các học kỳ
	else
	{
		return Admin_Proc(Admin_Disp(), info, dmy, 1);
	}
}
//*Các thao tác của admin
int Admin_Disp()
{
	system("cls");
	cout << "\t\t YOU ARE ADMIN NOW	" << endl;
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Year Section" << endl;
	cout << "\t\t 2. Class Section" << endl;
	cout << "\t\t 3. Student Section" << endl;
	cout << "\t\t 4. Semester Section" << endl;
	cout << "\t\t 5. Course Section" << endl;
	cout << "\t\t 6. Score Board" << endl;
	cout << "\t\t 7. Log Out" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(7);
}
//*Year Menu
int Year_Menu_Disp()
{
	//system("cls");
	cout << "\t\t YEAR SECTION" << endl;
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Create new year" << endl;
	cout << "\t\t 2. Delete year" << endl;
	cout << "\t\t 3. Delete all years" << endl;
	cout << "\t\t 4. Exit" << endl;
	cout << "\t\t ----------------------------" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(4);
}
//*Class Menu
int Class_Menu_Disp()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new class" << endl;
	cout << "\t\t 2. Delete class" << endl;
	cout << "\t\t 3. Clear class(es)" << endl;
	cout << "\t\t 4. View class(es)" << endl;
	cout << "\t\t 5. Exit" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(5);
}
//*Phân loại cách tạo lớp học
int Class_Create_Mod_Menu()
{
	system("cls");
	cout << "\t\t CREATE CLASS SECTION " << endl;
	cout << "\t\t 1. Import classes from files" << endl;
	cout << "\t\t 2. Add single class" << endl;
	cout << "\t\t 3. Exit" << endl;
	cout << "\t\t ----------------------------" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(3);
}
//*Department
int Department_Menu_Disp()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Information Technology" << endl;
	cout << "\t\t 2. Geology" << endl;
	cout << "\t\t 3. Electronics & Telecommunication" << endl;
	cout << "\t\t 4. Chemistry" << endl;
	cout << "\t\t 5. Material Science & Technology" << endl;
	cout << "\t\t 6. Environment" << endl;
	cout << "\t\t 7. Biology" << endl;
	cout << "\t\t 8. Mathematics" << endl;
	cout << "\t\t 9. Physics" << endl;
	cout << "\t\t 10. Exit" << endl;
	cout << "\t\t ----------------------------" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(10);
}
//*Training System 
int Training_System_Menu_Disp()
{
	system("cls");
	cout << "\t\t Choose your training system: " << endl;
	cout << "\t\t 1. Popular" << endl;
	cout << "\t\t 2. High Quality" << endl;
	cout << "\t\t ----------------------------" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(2);
}
//*Semester Menu
int Semester_Menu_Disp()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new semester" << endl;
	cout << "\t\t 2. Delete semesters" << endl;
	cout << "\t\t 3. Exit" << endl;
	cout << "\t\t ----------------------------" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(3);
}
//*Phân loại tính năng của học sinh 
//@param info Thông tin học sinh
//@param dmy Thời gian hiện tại
//@return True nếu cần recycle
bool Display_Mode_Student(Student &info, date &dmy)
{
	if(check_registration_date(dmy)){
		return Student_Proc_Passive(Student_Menu_Passive(), info, dmy,1);
	}
	else
	{
		return Student_Proc_Passive(Student_Menu_Passive(), info, dmy, 0);
	}
}
//*Student Menu
int Student_Menu_Active()
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new student(s)" << endl;
	cout << "\t\t 2. Delete student(s)" << endl;
	cout << "\t\t 3. View student(s)" << endl;
	cout << "\t\t 4. Exit" << endl;
	cout << "\t\t ----------------------------" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(4);
}
//*Menu tính năng của học sinh
int Student_Menu_Passive()
{
	//system("cls");
	cout << "\t\t YOU ARE STUDENT NOW	" << endl;
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Enrollment" << endl;
	cout << "\t\t 2. Log out" << endl;
	cout << "\t\t ----------------------------" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(2);
}
//*Course Menu
int Course_Menu_Disp() 
{
	cout << "\t\t Choose your option: " << endl;
	cout << "\t\t 1. Add new course" << endl;
	cout << "\t\t 2. Delete course" << endl;
	cout << "\t\t 3. Update course" << endl;
	cout << "\t\t 4. View course" << endl;
	cout << "\t\t 5. View student in course" << endl;
	cout << "\t\t 6. Exit" << endl;
	cout << "\t\t ----------------------------" << endl;
	cout << "\t\t Select option: ";
	return Valid_Data(6);
}
//*Menu chọn ngày cho môn học
int Course_Day()
{
	cout << "\t\t Day of the week: " << endl;
	cout << "\t\t 1. Monday " << endl;
	cout << "\t\t 2. Tuesday" << endl;
	cout << "\t\t 3. Wednesday" << endl;
	cout << "\t\t 4. Thursday" << endl;
	cout << "\t\t 5. Friday" << endl;
	cout << "\t\t 6. Saturday" << endl;
	cout << "\t\t Select day: ";
	return Valid_Data(6);
}
//*Menu chọn tiết học cho môn học
int* Course_Session()
{
	int s1,s2;
	do
	{
		cout << "\t\t Session: " << endl;
		cout << "\t\t 1. S1 (07:30)" << endl;
		cout << "\t\t 2. S2 (09:30)" << endl;
		cout << "\t\t 3. S3 (13:30)" << endl;
		cout << "\t\t 4. S4 (15:30)" << endl;
		cout << "\t\t Select first session: ";
		s1 = Valid_Data(4);
		cout << "\t\t Select second session: ";
		s2 = Valid_Data(4);
	}while(s1>=s2);
	int* arr =new int[2];
	arr[0]=s1;arr[1]=s2;
	return arr;
}
//*Menu cập nhật môn học
//@param choices Mảng các chọn lựa cập nhật
//@return Số lựa chọn đã chọn hoặc số 0 khi muốn thoát ra
int Course_Update_Menu(vector<string> &choices)
{
	system("cls");
	string choice;
	int count=0;
	do{
		system("cls");
		cout<<"\t\t UPDATE TABLE"<<endl;
		cout<<"\t\t You have choosen: "; String_Vector_Display(choices);
		cout<<endl<<"\t\t 0. Back"<<endl;
		cout<<"\t\t 1. ID"<<endl;
		cout<<"\t\t 2. Teacher"<<endl;
		cout<<"\t\t 3. Number of credits"<<endl;
		cout<<"\t\t 4. Capacity"<<endl;
		cout<<"\t\t 5. Day"<<endl;
		cout<<"\t\t 6. Session"<<endl;
		cout<<"\t\t If you want to apply update(s), press 'Y'."<<endl;
		cout<<"\t\t Select field for update: ";
		getline(cin,choice);
		if(choice!="0" && choice!="Y")
		{
			if(String_Vector_Duplicate(choices,choice)==false)
			{
				choices.push_back(choice);
				count+=1;
			}
		}
	}while(choice !="Y" && choice !="0" && count<6);

	if(choice =="Y" || count==6)
	{
		return count;
	}
	else{
		return 0;
	}
}
int Score_Menu()
{
	cout << "\t\t Score Board Menu: " << endl;
	cout << "\t\t 1. Export Student in a Course" << endl;
	cout << "\t\t 2. Import Score Board" << endl;
	cout << "\t\t 3. View Score Board" << endl;
	cout << "\t\t 4. Update Score Board" << endl;
	cout << "\t\t 5. View Score Board of a class" << endl;
	cout << "\t\t Select session: ";
	return Valid_Data(5);
}
//*Xử lý menu chính
bool Main_Menu_Proc(int option)
{
	if (option == 1)//Login
	{
		bool run = true;
		while (run)
		{
			run = Login_Proc(Login_Disp());
		}
		return true;
	}
	else if (option == 2)//About Us
	{
		AboutUs();
		return true;
	}
	else if (option == 3)//Exit
	{
		cout << "\t\t EXIT !!!" << endl;
		return false;
	}
}
//*Xử lý menu admin
bool Admin_Proc(int option, Account info, date dmy,int mod)
{
	//!Ngoài Year ra thì các option khác đều bị giới hạn trong năm nhập vào
	string year_name = dmy.schoolyear;
	if (option == 1)
	{
		bool run = true;
		while (run)
		{
			Years_Display();
			run = Year_Proc(dmy.year,Year_Menu_Disp());
		}
		return true;
	}
	else if (option == 2)
	{
		bool run = true;
		while (run)
		{
			//Xử lý các tính năng lớp học
			run = Class_Proc(year_name,Class_Menu_Disp(),mod);
		}
		return true;
	}
	else if (option == 3)
	{
		bool run = true;
		while (run)
		{
			string class_path = Student_Init(year_name);
			if(class_path=="OUT") {
				run = false;
				continue;
			}
			run = Student_Proc_Active(Student_Menu_Active(),class_path,mod);
		}
		return true;
	}
	else if (option == 4)
	{
		bool run = true;
		while(run)
		{
			Semester_Display(year_name);
			run = Semester_Proc(year_name,dmy,Semester_Menu_Disp());
		}
		return true;
	}
	else if (option == 5)
	{
		bool run = true;
		while (run)
		{
			//Chọn năm học và học kỳ
			string semester_path;
			run = Course_Init(semester_path,dmy.schoolyear);
			if(run == false) continue;
			run = Course_Proc(Course_Menu_Disp(),semester_path,mod);
		}
		return true;
	}
	else if (option == 6)
	{
		bool run = true;
		while (run)
		{
			//Chọn năm học và học kỳ
			string semester_path;
			run = Course_Init(semester_path,dmy.schoolyear);
			if(run == false) continue;
			run = Score_Proc(Score_Menu(),semester_path, year_name);
		}
		return true;
	}
	else
	{
		return false;
		system("cls");
	}
}


