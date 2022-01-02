#include "Header\Enroll.h"
#include "Header\File.h"
#include "Header\Menu.h"
#include "Header\Convert.h"
#include "Header\Node Process.h"
#include "Header\Course.h"
#include "Header\Vector.h"
#include "Header\Date.h"

//Cắt chuỗi đăng ký thành bốn phần thông tin
//Chuỗi môn học đã đăng ký
//Mảng chứa bốn thông tin môn học
string *Split_String_4(string name)
{
	string *s = new string[7 + 1];
	int k = 0;
	string s1, s2, s3, s4,s5,s6,s7;
	for (int i = 0; i < size(name); i++)
	{
		if (k == 0 && name[i] != ',')
		{
			s1 += name[i];
			if (name[(uint64_t)i + 1] == ',')
			{
				i++;
				k = 1;
			}
		}
		else if (k == 1 && name[i] != ',')
		{
			s2 += name[i];
			if (name[(uint64_t)i + 1] == ',')
			{
				i++;
				k = 2;
			}
		}
		else if (k == 2 && name[i] != ',')
		{
			s3 += name[i];
			if (name[(uint64_t)i + 1] == ',')
			{
				i++;
				k = 3;
			}
		}
		else if (k == 3 && name[i] != ',')
		{
			s4 += name[i];
			if (name[(uint64_t)i + 1] == ',')
			{
				i++;
				k = 4;
			}
		}
		else if (k == 4 && name[i] != ',')
		{
			s5 += name[i];
			if (name[(uint64_t)i + 1] == ',')
			{
				i++;
				k = 5;
			}
		}
		else if (k == 5 && name[i] != ',')
		{
			s6 += name[i];
			if (name[(uint64_t)i + 1] == ',')
			{
				i++;
				k = 7;
			}
		}
		else
		{
			s7 += name[i];
		}
	}
	s[0] = s1;
	s[1] = s2;
	s[2] = s3;
	s[3] = s4;
	s[4] = s5;
	s[5] = s6;
	s[6] = s7;
	return s;
}

//*Tiết học của môn học dạng int
//@param s Chuỗi ký tự tiết học
//@return Tiết học bắt đầu và kết thúc
int *Sessesion(string s)
{
	int *num = new int[2];
	//init num array
	num[0] = -1;
	num[1] = -1;
	int k = 0;
	for (int i = 0; i < size(s); i++)
	{
		if (s[i] == 'S' || s[i] == ' ')
		{
			continue;
		}
		else
		{
			if (s[i] == '1')
			{
				num[k++] = 1;
			}
			else if (s[i] == '2')
			{
				num[k++] = 2;
			}
			else if (s[i] == '3')
			{
				num[k++] = 3;
			}
			else if (s[i] == '4')
			{
				num[k++] = 4;
			}
		}
	}
	if (size(s) == 2)
	{
		num[1] = num[0];
	}
	return num;
}

//*Kiểm tra sự xung đột khi đăng ký học phần
//File máy chủ lưu các môn học đã đăng ký, môn học cần kiểm tra
//True nếu xung đột, False nếu không xung đột
bool Conflicted_Course(string store, string name)
{
	fstream f;
	f.open(store, ios::in);
	int n = Count_line(store);
	int k = 0;
	while (!f.eof())
	{
		string read;
		getline(f, read);
		string *s1 = Split_String_4(read);
		string *s2 = Split_String_4(name);
		if (s1[0] == s2[0])
		{
			cout << "\t\tThis course has been enrolled" << endl;
			cout << "\t\t";
			system("pause");
			return true;
			break;
		}
		else
		{
			if (s1[5] != s2[5])
			{
				k++;
			}
			else
			{
				int *a = Sessesion(s1[6]);
				int *b = Sessesion(s2[6]);
				if (b[0] <= a[1] && b[0] >= a[0])
				{
					cout << "\t\tConflicted with existing enrolled course sessions" << endl;
					cout << "\t\t";
					system("pause");
					return true;
				}
				else if (b[1] <= a[1] && b[1] >= a[0])
				{
					cout << "\t\tConflicted with existing enrolled course sessions" << endl;
					cout << "\t\t";
					system("pause");
					return true;
				}
			}
			if (k == n)
			{
				return false;
			}
		}
	}
	f.close();
	return false;
}

//Xem danh sách các môn đã đăng ký
//Dữ liệu sinh viên
void View_Enrolled_Courses(Student sv)
{
	system("cls");
	cout << "\t\t\tList of enrolled courses" << endl;
	string folder = ".\\Students\\Students for Enrollment\\";
	string filename = to_string(sv.id) + "_" + sv.name;
	string path = Make_Path(folder, filename);
	int n = Count_line(path);
	ifstream f;
	f.open(path);
	int i = 0;
	while (!f.eof())
	{
		i++;
		if (i <= n)
		{
			string f1;
			getline(f, f1);
			cout << "\t\t" << i << ". " << f1 << endl;
		}
		else
			break;
	}
	f.close();
}

//Hiển thị yêu cầu xóa môn học
//Dữ liệu sinh viên
//Sự lựa chọn môn học cần xóa
int Delete_course_Dis(Student sv)
{
	string folder = ".\\Students\\Students for Enrollment\\";
	string filename = to_string(sv.id) + "_" + sv.name;
	string path = Make_Path(folder, filename);
	View_Enrolled_Courses(sv);
	cout << "\t\t" << Count_line(path) + 1 << ". Exit" << endl;
	cout << "\t\tYour choice is: ";
	return Valid_Data(Count_line(path) + 1);
}

//Xử lý xóa môn học
//Dữ liệu sinh viên, sự lựa chọn môn học cần xóa
//True nếu cần dùng hàm lần nữa, false nếu ngược lại
bool Delete_course_Proc(Student sv, int option)
{
	string folder = ".\\Students\\Students for Enrollment\\";
	string filename = to_string(sv.id) + "_" + sv.name;
	string path = Make_Path(folder, filename);
	strings list = File_to_LinkList(path);
	if (option == Count_line(path) + 1 || option <1)
	{
		return false;
	}
	else
	{
		// Xóa môn học khỏi file sinh viên

		int c = 0;
		str *p = list.head;
		while (p != NULL)
		{
			c++;
			if (c == option)
			{
				break;
			}
			p = p->next;
		}
		str *pDEl = p;
		string s = pDEl->info;
		removeNode(list, pDEl);
		File_Clear(path);
		File_Create(path);
		ReInput_fromList(path, list);

		//Xóa tên sinh viên khỏi file môn học
		string *s1 = Split_String_4(s);
		string pre_folder = ".\\Courses\\" + sv.faculty + "\\";
		string path1 = pre_folder + s1[1] + "_" + s1[2] + ".csv";
		strings list1 = File_to_LinkList(path1);
		str *n1 = list1.head;
		while (n1 != NULL)
		{
			string ss = to_string(sv.id) + "_" + sv.name;
			if (n1->info == ss)
			{
				break;
			}
			n1 = n1->next;
		}
		removeNode(list1, n1);
		File_Clear(path1);
		File_Create(path1);
		ReInput_fromList(path1, list1);
		return true;
	}
}
//Hiển thị các môn học được đăng ký hiện tại
//Dữ liệu sinh viên
//Số thứ tự của môn học đã chọn
int Enroll_Dis(Student sv,date dmy)
{
	string years = dmy.schoolyear;
	string folder = ".\\Semesters\\";
	folder += years + "\\";
	string sems = dmy.semester;
	if (sems == "OUT")
	{
		cout << "\t\t It is not registration time!" << endl;
		cout << "\t\t ";
		system("pause");
		return 0;
	}
	string semester_path = Make_Path(folder, years + "-" + sems);
	int n;
	if (File_Exist(semester_path))
	{
		return Course_Select(semester_path,sv.faculty);
	}
	else
	{
		cout << "\t\t This semester haven't been created !!!" << endl;
		cout << "\t\t ";system("pause");
		return 0;
	}
	cout << "\t\tYour choice is : ";
}

string* Split_manyCourse(string path, int k)
{
	fstream f;
	f.open(path, ios::in | ios::out);
	int c = 0;
	int n = Count_line(path);
	string* ss = new string[n];
	int u = 0;
	while (!f.eof())
	{
		c++;
		string s;
		getline(f, s);
		int p = 0;
		string s1;
		if (c <= n && c >= 3)
		{
			for (int i = 0; i < size(s); i++)
			{
				if (p != k && s[i] != ',')
				{
					if (s[i + 1] == ',')
					{
						p++;
						i++;
					}
				}
				else if (p == k)
				{
					s1 += s[i];
					if (i != size(s) - 1)
					{
						if (s[i + 1] == ',')
						{
							break;
						}
					}
					else break;
				}
			}
			ss[u++] = s1;
		}
		else if(c>n) break;
	}
	f.close();
	return ss;

}
//*Xử lý đăng ký môn học
//Số thứ tự của môn học đã lựa chọn, dữ liệu sinh viên
//Sẽ có hàm gọi hàm này: True sẽ chạy tiếp, False thì không chạy
bool Enroll_Proc(int option, Student sv,date dmy)
{
	if (option == 0)
	{
		return false;
	}
	else
	{
		string years = dmy.schoolyear;
		string sem_folder = ".\\Semesters\\" + years + "\\";
		string sems = dmy.semester;
		string semester_name = years + "-" + sems;
		string semester_path = Make_Path(sem_folder,semester_name);
		cout<<semester_path<<endl;
		//
		vector <string> list  = File_ToVector(semester_path);
		string course_info = list[option-1];
		Course c = String_ToCourse(course_info);
		//
		string folder = ".\\Students\\Students for Enrollment\\";
		string filename = to_string(sv.id) + "_" + sv.name;
		string path = Make_Path(folder, filename);
		int k = Count_line(path);
		//
		string course_folder = ".\\Courses\\" + sv.faculty + "\\";
		string filename1 = c.name + "_" + c.teacher;
		string path1 = Make_Path(course_folder, filename1);

		int k1 = Count_line(path1);
		
		//
		if (k < 5)
		{
			if (k1 < 50)
			{
				if (Conflicted_Course(path, course_info) == false)
				{
					File_Append(path, course_info);
					File_Append(path1, to_string(sv.id) + "_" + sv.name);
					cout << "\t\tEnroll for the course successfully" << endl;
					cout << "\t\t";
					system("pause");
					return true;
				}
			}
			else
			{
				cout << "\t\tThe course is full !!!" << endl;
				cout << "\t\t";
				system("pause");
				return true;
			}
		}
		else
		{
			cout << "\t\tThe maximum number of courses that can be enrolled has been reached !!!" << endl;
			system("pause");
			return false;
		}
		return true;
	}
}

//Menu các tính năng đăng ký học phần
//Dữ liệu sinh viên
//Sự lựa chọn tính năng
int Enroll_MenuDisp(Student sv)
{
	system("cls");
	cout << "\t\t\t----Menu of Enrollment----" << endl;
	cout << "\t\t1. Enroll" << endl;
	cout << "\t\t2. View list of courses have been enrolled" << endl;
	cout << "\t\t3. Delete a course from enrolled list" << endl;
	cout << "\t\t4. Exit" << endl;
	cout << "\t\tYour choice is: ";
	return Valid_Data(4);
}

//Menu xử lý các tính năng ĐKHP
//Sự lựa chọn tính năng, dữ liệu sinh viên
//True nếu dùng lại hàm, false nếu không
bool Enroll_MenuProc(int option, Student sv,date dmy,int mod)
{
	if (option == 1)
	{
		if(mod==0){
			cout<<"\t\tYou can not register during this time!"<<endl;
			cout<<"\t\t";system("pause");
			return true;
		}
		bool run = true;
		while (run)
		{
			run = Enroll_Proc(Enroll_Dis(sv,dmy), sv,dmy);
		}
		return true;
	}
	else if (option == 2)
	{
		View_Enrolled_Courses(sv);
		cout << "\t\t";
		system("pause");
		return true;
	}
	else if (option == 3)
	{
		if (mod == 0)
		{
			cout << "\t\tYou can not delete course(s) during this time!" << endl;
			cout<<"\t\t";system("pause");
			return true;
		}
		bool run = true;
		while (run)
		{
			run = Delete_course_Proc(sv, Delete_course_Dis(sv));
		}
		return true;
	}
	else return false;
}