#include "Header\Menu.h"
#include "Header\Year.h"
#include "Header\Class.h"
#include "Header\Convert.h"
#include "Header\File.h"
#include "Header\Node Process.h"
#include "Header\Vector.h"

//*Hàm tạo năm
//@param year (năm lớn nhất có thể tạo)
void Year_Create(int limited_year)
{
	int begin, end;
	string year_path, year_name, year_folder = ".\\Years\\";

	cout << "\t\t CREATE YEAR SECTION " << endl;
	do {
		//Tạo tên & đường dẫn của năm
		cout <<"\t\t You can type '-1' to exit!"<<endl;
		cout << "\t\t Created school year from: ";
		begin = Valid_Data(limited_year);
		end = begin + 1;
		year_name = to_string(begin) + "-" + to_string(end);
		year_path = Make_Path(year_folder,year_name);
		//Nếu như người dùng chọn -1 thì không tạo năm nữa
		if(begin==-1) return;
		//Năm được tạo không được bé hơn 2002
		if(begin<2002)  {cout<<"\t\t New School Year must be after 2002"<<endl;}
	} while (File_Exist(year_path)== true || begin <2002);

	//Tạo ra file năm mới
	File_Create(year_path);
	//Lưu tên năm vào file Years.csv
	File_Append("Years.csv", year_name.c_str());
	cout << "\t\t School year created successfully" << endl;
	cout << "\t\t "; system("pause");
}
//*Xóa các file liên quan đến năm
//@param year_path Đường dẫn của năm
void Year_File_Delete(string year_path)
{
	string year_name = Path_ToName(year_path);
	//Xóa file năm
	remove(year_path.c_str());
	//Xóa thư mục năm trong thư mục Classes
	string class_folder = ".\\Classes\\"
		+ year_name + "\\"; //Cần có ký hiệu cuối cùng này để hoàn thành đường dẫn thư mục
	Directory_Delete(class_folder);
	//Xóa thư mục năm trong semester
	string semester_folder = ".\\Semesters\\"
		+ year_name + "\\";
	Directory_Delete(semester_folder);
}
//*Xóa một năm
void Year_Delete()
{
	int quanti = Years_Display();
	cout << "\t\t Choose option: ";
	int choice = Valid_Data(quanti);
	if(choice<1) return;

	string years_path = "Years.csv", year_folder = ".\\Years\\";
	//Xóa tên năm trong file lưu các "Years.csv"
	string year_name = File_Line_Delete(years_path,0,choice);
	string year_path = Make_Path(year_folder,year_name);
	//Xóa các file liên quan đến năm
	Year_File_Delete(year_path);
}
//*Xóa toàn bộ năm
void Year_Clear()
{
	cout << "\t\t All years will be deleted !!!!" << endl;
	cout << "\t\t Are you sure ???" << endl;
	cout << "\t\t Press 0 for accepting, 1 for not:  ";
	int n; cin >> n;cin.ignore();

	string year_name, year_path;
	if (n == 0)
	{
		fstream f("Years.csv", ios::in | ios::out);
		int i = 1;

		while (!f.eof()) {
			
			f>>year_name;
			//Xóa file
			year_path = Make_Path(".\\Years\\", year_name);
			Year_File_Delete(year_path);
		}
		f.close();
		//Remake a new "Years.csv"
		File_Clear("Years.csv");
	}
}
//*Sắp xếp các năm học tăng dần
//@param year_list (danh sách các chuỗi năm học)
void Year_Sort(string years_path)
{
	//Lấy các chuỗi từ file năm học chính
	vector<string> years_list = File_ToVector(years_path);
	vector<int> years_int;
	//Convert sang int năm đầu tiên và cho vào mảng int
	for(int i=0;i<years_list.size();i++)
	{
		years_int.push_back(Year_ToInt(years_list[i]));
	}
	//Sắp xếp mảng int
	sort(years_int.begin(),years_int.end());
	//Convert mảng int sang string và cho vào lại mảng string
	for(int i=0;i<years_list.size();i++)
	{
		years_list[i]=to_string(years_int[i]) + "-" + to_string(years_int[i]+1);
	}
	//Remake file lưu các năm học
	File_Clear(years_path);
	//Cho mảng string vào lại file
	Vector_ToFile(years_path,years_list);
}
//*Hiển thị năm
//@return Số năm hiện có
int Years_Display()
{
	system("cls");
	Year_Sort("Years.csv");
	cout << "\t\t CREATED YEARS: " << endl;
	fstream f("Years.csv", ios::in);
	int i = 1;
	//Đọc các năm từ file "Years.csv"
	while (!f.eof()) {
		string read;
		f >> read;
		if (read != "") {
			cout << "\t\t " << i++ << ". " << read << endl;
		}
	}
	f.close();
	return i-1;
}
//*Chọn năm
//@return Tên của năm đã chọn hoặc "OUT" (nếu muốn thoát ra hoặc không có năm nào để chọn)
string Year_Select()
{
	int limit = Years_Display();
	cout << "\t\t Which year do you want to process ?" << endl;
	cout << "\t\t Select option: ";
	int choice = Valid_Data(limit);
	if(choice==0) return "OUT";

	ifstream f("Years.csv");
	string year_name;
	int i = 1;

	while (!f.eof()) {
		//Đọc các năm từ file "Years.csv"
		string read;
		f >> read;
		//Nếu đó là năm có số thứ tự được chọn 
		if (i++ == choice)
		{
			year_name = read;
			//thì trả về tên của năm đó
			return year_name;
		}
	}
	f.close();
	return "OUT";
}
//*Xử lý và điều hướng các hàm tính năng của năm
//@param limited_year Năm giới hạn @param option Lựa chọn tính năng
//@return True nếu cần dùng tiếp, false nếu muốn thoát ra hẳn
bool Year_Proc(int limited_year,int option)
{
	if (option == 1)
	{
		Year_Create(limited_year);
		system("cls");
		return true;
	}
	else if (option == 2)
	{
		Year_Delete();
		system("cls");
		return true;
	}
	else if (option == 3)
	{
		Year_Clear();
		system("cls");
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}