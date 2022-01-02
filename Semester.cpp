#include "Header\Semester.h"
#include "Header\Menu.h"
#include "Header\Year.h"
#include "Header\Class.h"
#include "Header\File.h"
#include "Header\Convert.h"
#include "Header\Node Process.h"
#include "Header\Date.h"
//*Xem ngày tháng của học kỳ
//@param time Chuỗi ngày tháng
void View_Semester_Time(string semester_path) 
{
	cout<<"\t\t Semester time: "<<endl;
	ifstream f(semester_path);
	string reader;
	getline(f, reader);
	cout<<"\t\t Begining time: "<<reader<<endl;
	getline(f, reader);
	cout<<"\t\t Ending time: "<<reader<<endl;
}
//*Xem ngày tháng đăng ký học phần
//@param time Chuỗi ngày tháng
void View_Registration_Time(string semester_path)
{
	cout<<"\t\t Registration time: "<<endl;
	ifstream f(semester_path);
	string reader;
	for(int i=0;i<2;i++){
		getline(f,reader);
	}
	getline(f,reader);
	cout << "\t\t Begining time: " << reader << endl;
	getline(f, reader);
	cout << "\t\t Ending time: " << reader << endl;
}
//*Tạo học kỳ
//@param year_name Năm hiện tại cần tạo học kỳ
//@param dmy Thời gian hiện tại
//!Chỉ có thể tạo một lần 3 học kỳ
void Semester_Create(string year_name, date dmy)
{
	//Tạo tên của các học kỳ
	string semester_folder = ".\\Semesters\\" + year_name + "\\";
	string autumn_path = semester_folder + Extension(year_name + "-Autumn",1);
	string spring_path = semester_folder + Extension(year_name + "-Spring",1);
	string summer_path = semester_folder + Extension(year_name + "-Summer",1);
	if(File_Exist(autumn_path)==true && File_Exist(spring_path)==true && File_Exist(summer_path)==true) return;
	//Nếu không thì tạo file semester
	File_Create(autumn_path);
	File_Create(spring_path);
	File_Create(summer_path);
	//Tạo các thời gian liên quan
	TimeRange semTime[3];
	init_SemesterTime(semTime);
	enter_SemesterTime(semTime,dmy);
	string seasons[3] = {autumn_path,spring_path,summer_path};
	for(int i = 0; i < 3; i++)
	{
	//Tạo thời gian cho semester
		File_Append(seasons[i],Date_toString(semTime[i].begin));
		File_Append(seasons[i],Date_toString(semTime[i].end));
	}
	TimeRange regTime[3];
	enter_RegsTime(regTime,seasons);
	for(int i = 0; i < 3; i++)
	{
	//Tạo thời gian đăng ký học phần
		File_Append(seasons[i],Date_toString(regTime[i].begin));
		File_Append(seasons[i],Date_toString(regTime[i].end));
	}
}
//*Xóa một học kỳ
//@param limited_semester Số học kỳ giới hạn
//@param year_name Năm hiện tại cần xóa học kỳ
//@return True nếu cần dùng lại hàm, false nếu không
//!Chỉ xóa được một học kỳ mỗi lần
bool Semester_Delete(string year_name)
{
	//Chọn học kỳ cần xóa
	string semester_path = Semester_Select(year_name);
	if(semester_path=="OUT") return false;
	remove(semester_path.c_str());
	//Kiểm tra xem nếu đã xóa hết học kỳ của năm thì xóa luôn thư mục
	string pre_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Spring","-Summer" };
	for(int i=1;i<=3;i++)
	{
		string semester_name = Extension(year_name + seasons[i-1],1);
		string semester_path = pre_folder + semester_name;
		if(File_Exist(semester_path)) return true;
	}
	Directory_Delete(pre_folder);
	return true;
}
//*Hiển thị semester hiện có trong năm
//@param year_name Năm hiện tại
//@return Số semester đếm được
int Semester_Display(string year_name)
{
	system("cls");
	string semester_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Spring","-Summer" };
	int count=0;
	bool check=false;
	
	cout<<"\t\t CREATED SEMESTER OF "<<year_name<<endl;
	cout<<"\t\t 0. Back"<<endl;
	for(int i=1;i<=3;i++)
	{
		//Tạo tên và đường dẫn để kiểm tra sự tồn tại của học kỳ
		string semester_name = year_name+seasons[i-1];
		string semester_path = semester_folder+Extension(semester_name,1);
		if(File_Exist(semester_path))
		{
			//Nếu tồn tại thì xuất ra
			cout<<"\t\t "<<++count<<". "<<semester_name<<endl;
			check=true;
		}
	}
	if(check!=true)
	{
		cout<<"\t\t Can not find any semester"<<endl;
		cout<<"\t\t ";system("pause");
	}
	return count;
}
//*Hàm chọn semester để thao tác
//@param limited_semester Số semester hiện có trong năm @param year_name năm hiện tại
//@return Đường dẫn semester hoặc "OUT" (nếu không có sem nào hoặc muốn thoát ra)
string Semester_Select(string year_name)
{
	//Hiển thị semester
	int limited_semester = Semester_Display(year_name);
	if(limited_semester==0) return "OUT";
	//Chọn lựa semester
	cout<<"\t\t Choose semester to modify: ";
	int option  = Valid_Data(limited_semester);
	if(option <1) return "OUT";

	string semester_folder = ".\\Semesters\\" + year_name + "\\";
	string seasons[3] = { "-Autumn","-Spring","-Summer" };
	int count=0;
	
	for(int i =1;i<=3;i++)
	{
		//Tạo đường dẫn tới semester và lấy đường dẫn của nó
		string semester_name = Extension(year_name + seasons[i-1],1);
		string semester_path = semester_folder + semester_name;
		if(File_Exist(semester_path))
		{
			count+=1;
			if(count==option)
			{
				return semester_path;
			}
		}
	}
}
//*Xử lý các tính năng của semester	
//@param year_name Năm hiện tại @param dmy Dữ liệu thời gian hiện tại
//@param option Sự lựa chọn tính năng 
//@return True nếu cần dùng tiếp, false nếu ngược lại
bool Semester_Proc(string year_name, date dmy, int option)
{
	//!Năm học này là năm học hiện tại (không phải được chọn)
	string year_path = Make_Path(".\\Years\\",year_name);
	if(File_Exist(year_path)==false && option !=3)
	{
		cout<<"\t\t This year was not created"<<endl;
		cout<<"\t\t ";system("pause");
		return false;
	}
	if (option == 1)
	{
		//Kiểm tra năm học có tồn và tạo ra thư mục con của Semester chứa năm học đó
		if(String_InFile("Years.csv",year_name)) 
		{
			string dir = ".\\Semesters\\" + year_name + "\\";
			Directory_Create(dir);
		}
		Semester_Create(year_name,dmy);
		system("cls");
		return true;
	}
	else if (option == 2)
	{
		bool run = true;
		while(run){
		
			run  = Semester_Delete(year_name);
		}
		system("cls");
		return true;
	}
	else
	{
		system("cls");
		return false;
	}
}