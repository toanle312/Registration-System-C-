#include"Header\Password.h"
#include"Header\Login.h"
#include"Header\Node Process.h"
//String proccess
bool compare(string s1, string s2)
{
	int n = size(s1);
	int m = size(s2);
	if (n == m)
	{
		for (int i = 0; i < n; i++)
		{
			if (s1[i] != s2[i])
			{
				return false;
			}
		}
	}
	else return false;
	return true;
}
void split_string(string s, string& s1, string& s2)
{
	int k = 0;
	int j = 0;
	int n = size(s);
	for (int i = 0; i < n; i++)
	{
		if ((s[i] != ',') && (k == 0))
		{
			s1 += s[i];
			if (s[size_t(i) + 1] == ',') //Convert int to size_t
			{
				i++;
				k = 1;
			}
		}
		else if ((s[i] != ',') && (k == 1))
		{
			s2 += s[i];
		}
	}
}
//Account checking
bool check_usrname(string name, string path,int &count)
{
	ifstream file;
	file.open(path, ios::in);
	while (!file.eof())
	{
		count++;
		string f,usr,psw;
		file >> f;
		split_string(f, usr, psw);
		if (compare(usr, name) == true)
		{
			return true;
			break;
		}
	}
	file.close();
	return false;
}
bool check_pass(string pass,int count)
{
	fstream f;
	int k = 0;
	string acc_name = "acc_sv";
	string acc_path = ".\\Accounts\\";
	acc_path += (acc_name + ".csv");
	f.open(acc_path, ios::in | ios::out);
	while (!f.eof())
	{
		k++;
		string nf,usr,psw;
		getline(f,nf);
		split_string(nf, usr, psw);
		if (compare(psw,pass)==true && (k == count))
		{
			return true;
		}
	}
	f.close();
	return false;
}
bool check_key(string key,int count)
{
	ifstream f;
	int k = 0;
	f.open("Key.csv");
	while (!f.eof())
	{
		k++;
		string f1;
		f >> f1;
		if (compare(key, f1) == true && k == count)
		{
			return true;
			break;
		}
	}
	f.close();
	return false;
}
bool check_newpass(string pass)
{
	string newpass_again = "";
	cout << "\t\t Enter new password again: ";
	enter_data(newpass_again);
	
	if (compare(pass, newpass_again) == true)
	{
		return true;
	}
	return false;
}
//Change Password & Recover Password
void change_pass_in_file(string username, string pass)
{
	strings list;
	fstream f;
	int k = 0;
	list = Init_List();
	string acc_name = "acc_sv";
	string acc_path = ".\\Accounts\\";
	acc_path += (acc_name + ".csv");
	f.open(acc_path, ios::in | ios::out);
	while (!f.eof())
	{
		string f1;
		f >> f1;
		//
		string usr = "", psw = "";
		if (k == 0)
		{
			split_string(f1, usr, psw);
			//
			psw = "";
			if (compare(usr,username) == true)
			{
				f1 = "";
				int n = size(pass);
				for (int i = 0; i < n; i++)
				{
					psw += pass[i];
				}
				f1 = username + "," + psw;
				k = 1;
			}
		}
		str* n1 = new str;
		n1 = Create_Node(f1);
		Add_Last(list, n1);
	}
	f.close();
	remove(acc_path.c_str());
	f.open(acc_path, ios::out);
	ReInput_fromList(acc_path,list);
	cout << "\t\t New password has been updated !!!" << endl;
}
void forgot_pass()
{
	string name;
	int c = 0; string acc_name = "acc_sv";
	string acc_path = ".\\Accounts\\";
	acc_path += (acc_name + ".csv");
	string pf = acc_path;
	do {
		name = "";
		c = 0;
		cout << "\t\t Type '/' for exit! " << endl;
		cout << "\t\t Enter your username: ";
		enter_data(name);
		if (compare(name, "/"))
		{
			return;
		}
	} while (check_usrname(name, pf, c) != true);
	string key;
	do {
		key = "";
		cout << "\t\t Enter your key for password retrieval: ";
		enter_data(key);
		if (compare(key, "/"))
		{
			return;
		}
	} while (check_key(key, c) != true);
	string pass;
	cout << "\t\t Enter new password: ";
	enter_data(pass);
	if (compare(pass, "/"))
	{
		return;
	}
	change_pass_in_file(name, pass);
}
void change_pass()
{
	string name="",pass="";
	string acc_name = "acc_sv";
	string acc_path = ".\\Accounts\\";
	acc_path += (acc_name + ".csv");
 	int count = 0;
	do
	{
		count = 0; name = "";
		cout << "\t\t Type '/' for exit! " << endl;
		cout << "\t\t Enter username: ";
		enter_data(name);
		if (compare(name, "/"))
		{
			return;
		}
	} while (check_usrname(name, acc_path, count) != true);
	do
	{
		pass = "";
		cout << "\t\t Enter old password: ";
		enter_data(pass);
		if (compare(pass, "/"))
		{
			return;
		}
	} while (check_pass(pass,count) != true);
	string newpass;
	do {
		newpass = "";
		cout << "\t\t Enter new password: ";
		enter_data(newpass);
		if (compare(newpass, "/"))
		{
			return;
		}
	} while (check_newpass(newpass) != true);

	change_pass_in_file(name, newpass);
}
