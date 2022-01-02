#include "Header\Convert.h"
#include "Header\File.h"
#include "Header\Node Process.h"

//*Thêm phần mở rộng (.csv) vào tên file hoặc cắt nó đi
//@param name Tên file @param option Loại hành động muốn thực thi (thêm/cắt)
//@return kết quả của chuỗi sau khi thêm/cắt
string Extension(string name, int option)
{
	if (option == 1) {
		size_t found = name.find(".csv");
		if (found == -1) {
			return name + ".csv";
		}
		else {
			return name;
		}
	}
	else {
		size_t pos = 0;
		pos = name.find_last_of(".");
		return name.substr(0, pos);
	}
}

//*Tạo ra một đường dẫn từ đường dẫn thư mục chứa nó và tên file (ko có đuôi ".csv")  
//@param pre_folder một đường dẫn thư mục @param file_name một tên của file
//@return Đường dẫn hoàn chỉnh
string Make_Path(string pre_folder, string file_name)
{
	return  pre_folder + Extension(file_name, 1);
}

//*Cắt ra một tên (không có đuôi ".csv") từ một đường dẫn hoàn chỉnh
//@param path Một đường dẫn hoàn chỉnh
//@return Tên của file (không có extension)
string Path_ToName(string path)
{
	size_t pos = path.find_last_of("\\", path.length());
	return Extension(path.substr(pos + 1), 2);
}

//*Chuyển từ kiểu String sang kiểu Int
//@param s Chuỗi cần chuyển
//@return Giá trị int sau khi chuyển
int String_ToInt(string s)
{
	stringstream ss;
	int number;
	ss << s;
	ss >> number;
	ss.str("");
	ss.clear();
	return number;
}
//*Chuyển từ một tên năm sang kiểu int (lấy năm đầu tiên)(VD: 2002-2003 thì lấy 2002)
//@param year_name tên năm
//@return Dạng số int của năm đầu tiên trong tên năm
int Year_ToInt(string year_name)
{
	size_t pos = year_name.find_first_of("-", 0);
	string first_year = year_name.substr(0, pos);
	return String_ToInt(first_year);
}
//*Chuyển đổi từ ngày tháng sang chuỗi ngày tháng
//@param dmy Kiểu dữ liệu ngày tháng năm
//@return Chuỗi ngày tháng năm
string Date_toString(date dmy)
{
	return to_string(dmy.day)   + "/"
		  +to_string(dmy.month) + "/"
		  +to_string(dmy.year);
}

//*Chuyển đổi từ chuỗi ngày tháng sang kiểu ngày tháng
//@param dmy Chuỗi ngày tháng
//@return Kiểu dữ liệu ngày tháng
date String_ToDate(string dmy)
{
	date result;
	int pos = dmy.find_first_of("/",0);
	int pos2 = dmy.find_first_of("/",pos+1);
	int pos3 = dmy.find_first_of("/",pos2+1);
	result.day = String_ToInt(dmy.substr(0,pos));
	result.month = String_ToInt(dmy.substr(pos+1,pos2-pos-1));
	result.year = String_ToInt(dmy.substr(pos2+1,pos3-pos2-1));
	return result;
}

//*Chuyển đổi từ chuỗi thông tin học sinh sang kiểu học sinh
//@param info Chuỗi thông tin
//@param arr[8] mảng lưu thông tin nếu cần dùng kiểu mảng
//@return Thông tin học sinh dạng struct
Student String_ToStudent(string info, string arr[8])
{
	Student s;
	int length = info.length();
	int k = 0;
	string temp = info;
	string a[8];
	while (k < 7)
	{
		int pos = info.find_first_of(",", 0);
		string temp2 = info.substr(0, pos);
		info = info.substr((uint64_t)pos + 1, length);
		a[k++] = temp2;
	}
	s.number = String_ToInt(a[0]);
	s.id = String_ToInt(a[1]);
	s.name = a[2];
	s.gender = a[3];
	s.faculty = a[4];
	s.birthdate = a[5];
	s.socialID = stoi(a[6]);
	s.user.username = a[1];
	int pos = temp.find_last_of(",", temp.size());
	s.user.password = temp.substr((uint64_t)pos + 1, temp.size() - pos);
	return s;
}
//*Chuyển từ kiểu học sinh sang chuỗi học sinh
//@param info kiểu học sinh
//@return chuỗi học sinh
string Student_ToString(Student s)
{
	string result;
	result += (to_string(s.number) + "," + to_string(s.id) + "," + s.name + "," + s.gender + "," + s.faculty + ",");
	result += (s.birthdate + "," + to_string(s.socialID) + "," + s.user.username + "," + s.user.password);
	return result;
}
//*Chuyển từ kiểu chuỗi sang kiểu môn học
//@param info Dữ liệu môn học dạng chuỗi
//@param arr[7] Mảng lưu dữ liệu khi tách ra nếu cần dùng
//@return Kiểu dữ liệu môn học
Course String_ToCourse(string info)
{
	Course c;
	int length = info.size();
	int i = 0;
	string a[7];
	string temp = info;
	while (i < 7)
	{
		int pos = info.find_first_of(",", 0);
		string temp2 = info.substr(0, pos);
		info = info.substr((uint64_t)pos + 1, length);
		a[i++] = temp2;
	}
	c.id = a[0];
	c.name = a[1];
	c.teacher = a[2];
	c.cre = String_ToInt(a[3]);
	c.capacity = String_ToInt(a[4]);
	c.day = a[5];
	c.session = a[6];
	return c;
}
//*Chuyển từ môn học sang kiểu chuỗi
//@param Kiểu môn học
//@return Chuỗi môn học
string Course_ToString(Course c)
{
	return c.id + "," + c.name + "," + c.teacher + "," + 
		   to_string(c.cre) + "," + to_string(c.capacity) + "," + c.day + "," + 
		   c.session;
}
//*Thay đổi 1 ký tự trong chuỗi thành ký tự khác
//@param &s chuỗi cần thay thế ký tự
//@param target Chuỗi được thay 
//@param change Chuỗi cần thay 
void String_Replace(string &s, string target, string change)
{
	string temp = s;
	int pos = 0;
	while(pos != string::npos)
	{
		pos = temp.find_first_of(target, 0);
		if(pos == string::npos) break;
		temp.replace(pos, 1, change);
	}
	s = temp;
}

//*Lưu các string từ file sang danh sách liên kết
//@param path Đường dẫn chứa file
//@return Danh sách liên kết chứa các chuỗi
strings File_to_LinkList(string path)
{
	strings l = Init_List();
	ifstream f;
	f.open(path);
	while (!f.eof())
	{
		string f1="";
		getline(f, f1);
		str* p = Create_Node(f1);
		Add_Last(l, p);
	}
	f.close();
	return l;
}


