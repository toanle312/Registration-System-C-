#include "Header\Menu.h"
#include "Header\Student.h"
#include "Header\File.h"
#include "Header\Login.h"
#include "Header\Password.h"
#include "Header\Date.h"
string delete_last(string s)
{
	string ss = s;
	int n = size(s) - 1;
	s = "";
	for (int i = 0; i < n; i++)
	{
		s += ss[i];
	}
	return s;
}
int pass_mode()
{
	cout << "\t\t 1.Show your password !!!" << endl;
	cout << "\t\t 2.Hide your password !!!" << endl;
	cout << "\t\t ";
	return Valid_Data(2);
}
bool pass_mode_proc(int option, Account& info)
{
	if (option == 1)
	{
		enter_showpass(info);
		return true;
	}
	else if (option == 2)
	{
		enter_hidepass(info);
		cout << endl;
		return true;
	}
	else
	{
		return false;
	}
}
void enter_showpass(Account &info)
{
	cout << "\t\t Enter password (No spacebar and special symbols in your password): ";
	enter_data(info.password);
}
void enter_hidepass(Account &info)
{
	cout << "\t\t Enter password (No spacebar and special symbols in your password): ";
	string ss = "";
	char a = _getch();
	int i = 0;
	while (a != 13)
	{
		if (a >= 65 && a <= 90 || a >= 97 && a <= 122)
		{
			ss += a;
			cout << "*";
		}
		if (a >= 48 && a <= 57)
		{
			ss += a;
			cout << "*";
		}
		if (a == 8)
		{
			system("cls");
			cout << "\t\t Enter username: "; cout << info.username << endl;
			cout << "\t\t 1.Show your password !!!" << endl;
			cout << "\t\t 2.Hide your password !!!" << endl;
			cout << "\t\t Select your option: "; cout << 2;
			cout << "\n\n";
			cout << "\t\t Enter password (No spacebar and special symbols in your password): ";
			ss = delete_last(ss);
			for (int i = 0; i < size(ss); i++)
			{
				cout << "*";
			}
		}
		a = _getch();
	}
	info.password = ss;
}
void enter_data(string& param)
{
	getline(cin, param);
}
bool enter_acc(Account& info)
{
	cout << "\t\t Enter username: ";
	enter_data(info.username);
	bool k = pass_mode_proc(pass_mode(), info);
	return k;
}

// Count line in csv file
int count_acc(string acc_path)
{
	ifstream f;
	f.open(acc_path);
	int c = 0;
	while (!f.eof())
	{
		string s1 = "";
		f >> s1;
		c++;
	}
	f.close();
	return c - 1;
}
// Create account
string account(Account info)
{
	return info.username + ',' + info.password;
}
string split_acc_stu(string &s)
{
	int n=size(s);
	int c=0;
	for(int i=n-1;i>=0;i--)
	{
		c++;
		if(s[i]==',')
		{
			break;
		}
	}
	string ss;
	for(int i=0;i<n-c;i++)
	{
		ss+=s[i];
	}
	s=s.substr(n-c+1,n);
	return ss;
}
// Login as Student
bool check_acc_student(Account user, Student &info)
{
	ifstream f;
	string acc_name = "acc_sv";
	string acc_path = ".\\Accounts\\";
	acc_path += (acc_name + ".csv");
	f.open(acc_path);
	string acc = account(user);
	int c = 0;
	int n = Count_line(acc_path);
	while (!f.eof())
	{
		c++;
		string acc1; //Cả dòng trong file tk & mk
		f >> acc1;
		//acc2 chứa tk & mk, acc1 lúc này chứa đường dẫn tới file lớp
		string acc2 = split_acc_stu(acc1);
		if (acc.compare(acc2) != 0)
		{
			if (c < n)
			{
				continue;
			}
			else if (c == n)
			{
				cout << "\t\t Wrong password or username !!!" << endl;
				cout << "\t\t ";
				system("pause");
				return false;
			}
		}
		else
		{
			info = Get_Student_Info(acc1, user);
			cout << "\t\t Login sucessed !!!" << endl;
			cout << "\t\t ";
			system("pause");
			return true;
			break;
		}
	}
	f.close();
}
bool login_as_student(Account &user,Student &info)
{
	cout << "\t\t Login as Student" << endl;
	if (enter_acc(user))
	{
		return check_acc_student(user,info);
	}
}
// Login as Admin
bool check_acc_ad(Account info)
{
	if (info.password[0] == 'A' && info.password[1] == 'D')
	{
		ifstream f;
		string acc_name = "acc_ad";
		string acc_path = ".\\Accounts\\";
		acc_path += (acc_name + ".csv");
		f.open(acc_path);
		string acc = account(info);
		int c = 0;
		int n = Count_line(acc_path);
		while (!f.eof())
		{
			c++;
			string acc1;
			f >> acc1;
			if (acc.compare(acc1) != 0)
			{
				if (c < n)
				{
					continue;
				}
				else if (c == n)
				{
					cout << "\t\t Wrong password or username !!!" << endl;
					cout << "\t\t"; system("pause");
					return false;

				}
			}
			else
			{
				cout << "\t\t Login sucessed !!!" << endl;
				cout << "\t\t"; system("pause");
				return true;
				break;
			}
		}
		f.close();
	}
	else
	{
		cout << "\t\t Wrong password or username !!!" << endl;
		cout << "\t\t"; system("pause");
		return false;
	}
}
bool login_as_admin(Account& info)
{
	cout << "\t\t Login as Admin" << endl;
	if (enter_acc(info))
	{
		return check_acc_ad(info);
	}
}
//*Xử lý menu đăng nhập
bool Login_Proc(int option)
{
	bool run = true;
	Account user;
	date dmy;
	Student info;
	//If user is administrator
	if (option == 1)
	{
		enter_dmy(dmy);
		choose_schoolyear(dmy);
		run = login_as_admin(user);
		//!Login system: off
		system("cls");
		while (run)
		{
			run = Display_Mode_Admin(user, dmy);
		}
		return true;
	}
	else if (option == 2)
	{
		enter_dmy(dmy);
		choose_schoolyear(dmy);
		run = login_as_student(user, info);
		//Login system: on
		system("cls");
		while (run)
		{
			run = Display_Mode_Student(info, dmy);
		}
		return true;
	}
	else if (option == 3)
	{
		cin.ignore();
		change_pass();
		cout << "\t\t ";
		system("pause");
		return true;
	}
	else if (option == 4)
	{
		cin.ignore();
		forgot_pass();
		cout << "\t\t ";
		system("pause");
		return true;
	}
	else
	{
		return false;
	}
}
