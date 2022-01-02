#include "Header\Menu.h"
#include "Header\Year.h"
#include "Header\Class.h"
#include "Header\File.h"
#include "Header\Convert.h"
#include "Header\Node Process.h"
#include "Header\Vector.h"

//*Kiểm tra lớp có bị trùng trong danh sách của năm hay không.
//@param year_name (tên năm học) @param check_class_name (lớp cần kiểm tra)
//@return true (lớp bị trùng)
bool Duplicated_Class(string year_name, string check_class_name)
{
	//Tạo đường dẫn tới lớp học
	string class_folder = ".\\Classes\\" + year_name + "\\";
	string class_path = Make_Path(class_folder, check_class_name);
	return File_Exist(class_path);
}
//*Nhập hàng loạt lớp từ file
//@param year_name (tên năm học)
//@return True nếu cần recycle, false nếu ngược lại
bool Class_Import(string year_name)
{
	//Cho người dùng nhập tên file cần import
	string import_folder = ".\\Classes\\";
	string import = File_Import(import_folder);
	if(import=="OUT") return true;
	//Lưu danh sách lớp vào vector
	ifstream file(import);
	vector <string> class_list;

	while (!file.eof())
	{
		string class_name;
		getline(file,class_name);
		//Loại các trường hợp chuỗi rỗng
		if(class_name=="") continue;
		//Loại các trường hợp lớp bị trùng lặp
		if (Duplicated_Class(year_name, class_name)) continue;
		//Thêm các tên lớp vào mảng động
		class_list.push_back(class_name);
		//Tạo một file lớp mới
		string class_path = ".\\Classes\\" + year_name + "\\" + Extension(class_name,1);
		File_Create(class_path);
	}
	file.close();

	//Thêm tên lớp vào file CSV của năm
	string year_path = ".\\Years\\" + Extension(year_name, 1);
	Vector_ToFile(year_path,class_list);
	return false;
}
//*Xử lý tên các khoa trong trường
//@param depart Số thứ tự khoa @param system Số thứ tự của hệ đào tạo
//@return Mã Khoa - Hệ đào tạo hoặc "OUT" (nếu muốn thoát ra)
string Faculty_Name(int depart,int system)
{
	string faculty_name;
	switch (depart)
	{
	case 1: {faculty_name= "CTT"; break; }
	case 2: {faculty_name= "DCH"; break; }
	case 3: {faculty_name= "DTV"; break; }
	case 4: {faculty_name= "HOH"; break; }
	case 5: {faculty_name= "KVL"; break; }
	case 6: {faculty_name= "KMT"; break; }
	case 7: {faculty_name= "SHH"; break; }
	case 8: {faculty_name= "TTH"; break; }
	case 9: {faculty_name= "VLH"; break; }
	default: {faculty_name="OUT"; break; }
	}
	if (system == 2)
	{
		faculty_name = faculty_name + "_CLC";
	}
	return faculty_name;
}
//*Tạo tên lớp
//@param year_name Tên năm
//@return Một chuỗi có tên lớp hoàn chỉnh hoặc "OUT" (nếu muốn thoát ra)
string Make_ClassName(string year_name)
{
	//Tạo số niên khóa
	int first_year = Year_ToInt(year_name);
	string class_name, faculty, period = to_string(first_year % 100);
	//Tạo mã khoa - hệ đào tạo
	faculty = Faculty_Name(Department_Menu_Disp(), Training_System_Menu_Disp());
	if(faculty =="OUT") return "OUT";
	//Nhập số thứ tự lớp (1 đến 5)
	bool check = true;
	int n = 0;
	do {
		cout << "\t\t Enter order of class: ";
		cin >> n;

		class_name = period + faculty + to_string(n);
		check = Duplicated_Class(year_name, class_name);

	} while (n < 0 || n > 5 || check == true);
	return class_name;
}
//*Tạo một lớp thủ công
//@param year_name Tên năm
//@return True: nếu cần dùng lại
bool Class_Create_Single(string year_name)
{
	//Tạo tên lớp học
	string class_name = Make_ClassName(year_name);
	if(class_name =="OUT") return false;
	//Tạo đường dẫn và file của lớp học
	string class_folder = ".\\Classes\\" + year_name + "\\";
	string class_path = Make_Path(class_folder, class_name);
	File_Create(class_path);
	//Lưu lớp học vào file năm học
	string year_path = ".\\Years\\" + Extension(year_name,1);
	File_Append(year_path, class_name);
	return true;
}
//*Xóa một lớp
//@param year_path Đường dẫn của file năm @param quanti Số lượng lớp hiện có
bool Class_Delete(string year_path)
{
	//Chọn lớp cần xóa
	int line_number;
	string class_path = Class_Select(year_path,line_number);
	if(class_path=="OUT") return false;
	//Xóa thư mục của lớp
	remove(class_path.c_str());
	//Xóa lớp trong file năm
	string year_path_in_library = Make_Path(".\\Years\\", year_path);
	File_Line_Delete(year_path_in_library,0,line_number);
	return true;
}
//*Xóa tất cả các lớp của một năm
//Param: đường dẫn tới file năm
void Class_Clear(string year_path)
{
	cout << "\t\t All classes will be deleted !!!!" << endl;
	cout << "\t\t Are you sure ???" << endl;
	cout << "\t\t Press 0 for accepting, 1 for not:  ";
	int n;cin>>n;cin.ignore();
	if(n!=0) return;
	//Xóa thư mục lớp của năm học đó
	string year_name = Path_ToName(year_path);
	string dir = ".\\Classes\\" + year_name +"\\";
	Directory_Delete(dir);
	//Remake một file year mới
	File_Clear(year_path);
}
//*Hiển thị các lớp
//@param: đường dẫn đến file năm
//Return: Số lượng năm hiện có
int Class_Display(string year_path)
{
	system("cls");
	fstream f(year_path, ios::in);
	int count = 1;

	cout << "\t\t CREATED CLASS: " << endl;
	cout <<"\t\t 0. Back"<<endl;
	while (!f.eof())
	{
		string reader;
		f >> reader;
		if (reader != "")
		{
			cout << "\t\t " << count++ << ". " << reader << endl;
		}
	}
	f.close();
	cout<<"\t\t This year has "<< count-1 <<" class(es)"<<endl;
	cout<<"\t\t -----------------------------------"<<endl;
	return count-1;
}
//*Chọn lựa lớp
//@param year_name Tên của năm cần truy cập
//@returns Đường dẫn tới lớp đó hoặc "OUT" nếu muốn thoát ra
string Class_Select(string year_name,int &line_number)
{
    string year_path = Make_Path(".\\Years\\",year_name);
	string class_folder = ".\\Classes\\" + year_name + "\\";
	//Hiển thị lớp
    int limited_classes = Class_Display(year_path);
    if(limited_classes<1)
    {
        cout<<"\t\t This year does not have any classes"<<endl;
        cout<<"\t\t ";system("pause");
        return "OUT";
    }
	//Chọn lớp cần chỉnh sửa
	cout<<"\t\t You can press '-1' to exit!"<<endl;
    cout<<"\t\t Choose class to modify: ";
    line_number =  Valid_Data(limited_classes);
	if(line_number<1) return "OUT";
	//Tạo đường dẫn tới lớp
	string class_name = File_Line_Seek(year_path,0,line_number);
	string class_path = Make_Path(class_folder, class_name);
	return class_path;
}

//*Khởi tạo các đường dẫn cần thiết cho các tính năng của class
//@return Đường dẫn tới năm học hoặc "OUT" nếu muốn thoát ra
string Class_Init()
{
	string year_folder = ".\\Years\\";
	string class_folder = ".\\Classes\\";
	//Lựa chọn và khởi tạo đường dẫn tới năm
	string year_name = Year_Select();
	if (year_name == "OUT") return "OUT";
	string year_path = Make_Path(year_folder, year_name);
	//Hiển thị các lớp có trong năm đó
	Class_Display(year_path);
	//Tạo thư mục cho lớp
	if(String_InFile("Years.csv",year_name))
	{
		string dir = class_folder + year_name + "\\";
		Directory_Create(dir);//Dir đã tồn tại thì không tạo
	}
	return year_name;
}

//*Xử lý và điều hướng các hàm tính năng của lớp
//@param option Lựa chọn tính năng
//@return True nếu hàm cần recycle, false nếu ngược lại
bool Class_Proc(string year_name,int option,int mod)
{
	//Khởi tạo các đường dẫn & thư mục cần thiết
	//!Năm học này là năm học cần chọn, có thể không phải năm học hiện tại
	string year_path = Make_Path(".\\Years\\",year_name);
	//Mod 1 là được thao tác
	if (option == 1 && mod==1){
		bool run = true;
		while(run)
		{
			//Lựa chọn cách tạo lớp
			int choice = Class_Create_Mod_Menu();
			if(choice ==3) return true;

			//Option 1: Nhập từ file
			if (choice == 1) {
				run = Class_Import(year_name);
				system("cls");
			}
			//Option 2: Thủ công
			else if(choice == 2) {
				Class_Create_Single(year_name);
			}
		}
		system("cls");
		return true;
	}
	else if (option == 2 && mod == 1)
	{
		bool run = true;
		while(run)
		{
			run = Class_Delete(year_name);
		}
		system("cls");
		return true;
	}
	else if (option == 3 && mod == 1)
	{
		Class_Clear(year_path);
		system("cls");
		return true;
	}
	else if(option ==4)
	{
		system("cls");
		Class_Display(year_path);
		cout<<"\t\t ";system("pause");
		return true;
	}
	else if (option == 5)
	{
		system("cls");
		return false;
	}
	else
	{
		system("cls");
		return true;
	}

}
