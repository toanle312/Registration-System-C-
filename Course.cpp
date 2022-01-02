#include "Header\Course.h"
#include "Header\Class.h"
#include "Header\Year.h"
#include "Header\Menu.h"
#include "Header\File.h"
#include "Header\Semester.h"
#include "Header\Convert.h"
#include "Header\Node Process.h"
#include "Header\Vector.h"
#include "Header\Student.h"

bool Valid_Course(Course c)
{
	if (c.cre < 0 || c.capacity < 0 ||c.cre > 4 ||c.capacity >50)
	{
			return false;
	}
	return true;
}
string Course_Day_Classify(int day)
{
	switch (day)
	{
	case 1: return "Monday";
	case 2: return "Tuesday";
	case 3: return "Wednesday";
	case 4: return "Thursday";
	case 5: return "Friday";
	default:
		return "Saturday";
	}
}
string Course_Session_Classify(int session[2])
{
	string str;
	for(int i=0;i<2;i++)
	{
		switch (session[i])
		{
		case 1:
			str += "S1";
			break;
		case 2:
			str += "S2";
			break;
		case 3:
			str += "S3";
			break;
		case 4:
			str += "S4";
			break;
		default:
			str+="";
		}
		if(i!=1)
		{
			str+=" ";
		}
		cout<<str<<endl;
	}
	return str;
}
Course Course_Input(){
	Course new_course;
	do {
		cout << "\t\t ID: "; getline(cin, new_course.id);
		cout << "\t\t Course Name: "; getline(cin, new_course.name); 
		cout << "\t\t Teacher Name: "; getline(cin, new_course.teacher);
		cout << "\t\t Number of credits: "; cin >> new_course.cre;
		cout << "\t\t Maximum students: "; cin >> new_course.capacity;
		new_course.day=Course_Day_Classify(Course_Day());
		new_course.session = Course_Session_Classify(Course_Session());
	} while (Valid_Course(new_course) == false);
	return new_course;
}
//*Tạo đường dẫn môn học
//@param course_string Thông tin môn học //@param faculty Khoa hiện hành
//@return Đường dẫn môn học
string Get_Course_Path(string course_string, string faculty)
{
	string course_folder = ".\\Courses\\" + faculty + "\\";
	Course info = String_ToCourse(course_string);
	string course_name = info.name + "_" + info.teacher;
	return Make_Path(course_folder, course_name);
}
//*Tạo môn học mới
//@param semester_path Đường dẫn đến học kỳ
//@param faculty Tên của khoa 
void Course_Create(string semester_path,string faculty)
{
	//Nhập môn học bằng tay
	string new_course = Course_ToString(Course_Input());
	//Tạo file cho môn học
	string course_path = Get_Course_Path(new_course, faculty);
	//Loại đi trường hợp course đã tạo
	if(File_Exist(course_path)) return;
	File_Create(course_path);
	//Cho môn học vào file lưu giữ của khoa
	new_course+=("," +faculty);
	File_Append(semester_path, new_course);
}
//*Lấy ra khoa hiện tại của chuỗi môn học
string Get_Course_Faculty(string course)
{
	size_t pos = course.find_last_of(",", course.length());
	return course.substr(pos + 1, course.length() - pos - 1);
}
//*Hiển thị các môn học
//@param semester_path Đường dẫn tới học kỳ
//@param faculty Khoa hiện hành
//@return Số môn học đếm được
int Courses_Display(string semester_path, string faculty)
{
	ifstream f(semester_path);
	string reader;
	//Đọc 4 dòng thời gian
	for(int i=0;i<4;i++){
		getline(f,reader);
	}
	//Đọc các môn học của khoa
	int i=1;
	cout<<"\t\t CREATED COURSE(S): "<<endl;
	cout<<"\t\t 0. Back"<<endl;
	while(!f.eof())
	{
		getline(f,reader);
		if(reader=="") continue;
		if(Get_Course_Faculty(reader)==faculty){
			String_Replace(reader,",","  -  ");
			cout<<"\t\t "<<i++<<". "<<reader<<endl;
		}
	}
	f.close();
	return i;
}
//*Chọn lựa môn học
//@param semester_path Đường dẫn tới học kỳ @param faculty
//@return số dòng của môn học trong file semester (Bằng 0 nếu không có môn nào)
int Course_Select(string semester_path, string faculty)
{
	//Xuất danh sách các môn học
	int limited_course = Courses_Display(semester_path, faculty);
	if(limited_course<1) return 0;
	cout<<"\t\t Choose course for modify: ";
	//Chọn môn học cần chỉnh sửa
	int choice =  Valid_Data(limited_course);
	if(choice == 0) return 0;
	ifstream f(semester_path);
	int line=0;
	int count=0;
	while(!f.eof())
	{
		line+=1;
		string reader;
		getline(f,reader);
		//Kiểm tra có phải khoa có môn cần chọn
		if(Get_Course_Faculty(reader)==faculty)
		{
			count+=1;
			if(count==choice) 
			{
				return line;
			}
		}
	
	}
	f.close();
}
bool Course_Delete(string semester_path, string faculty)
{
	int line = Course_Select(semester_path,faculty);
	if(line < 5) return false ;//Luôn có 4 dòng thời gian
	//Vừa xóa môn học trong file semester vừa lấy ra được môn học dạng string
	string course_string = File_Line_Delete(semester_path, 0, line);
	//Tạo đường dẫn cho việc xóa môn học trong file sinh viên và xóa file
	string course_path = Get_Course_Path(course_string, faculty);
	string course_name = Path_ToName(course_path);
	//Xóa môn học trong file sinh viên
	ifstream f(course_path);
	while(!f.eof()){
		string reader;
		getline(f,reader);
		if(reader=="") continue;//Chuỗi rỗng thì bỏ qua
		string student_folder = ".\\Students\\Students for Enrollment\\";
		string student_path = Make_Path(student_folder,reader);
		//Tìm môn học trong file sinh viên
		int line = Course_Find_in_Student(student_path,course_name);
		//Và xóa môn học đó
		File_Line_Delete(student_path,0,line);
	}
	f.close();
	//Xóa file môn học
	remove(course_path.c_str());
	return true;
}

//*Tìm môn học có trong file sinh viên
//@param student_path File sinh viên
//@param course_name Tên môn học
//@return Số thứ tự dòng tìm thấy môn học (0 nếu không tìm được)
int Course_Find_in_Student(string student_path,string course_name)
{
	ifstream f(student_path);
	int count=1;
	if(f.is_open())
	{
		while(!f.eof()){
			string course_string;
			getline(f,course_string);
			int pos = course_string.find_first_of(",",0);
			int pos2 = course_string.find_first_of(",",pos+1);
			string course = course_string.substr(pos+1,pos2-pos-1);
			//Đọc tên môn học và so sánh với môn học cần thay đổi
			if(course == course_name)
			{
				return count;
			}
			count+=1;
		}
		return 0;
	}
}
void Course_Update(string semester_path,string faculty)
{
	//Cho người dùng chọn môn học cần cập nhật
	int line = Course_Select(semester_path,faculty);
	if(line<5) return;
	vector <string> choices;
	//Cho người dùng chọn lựa các field cần cập nhật
	int choice_number = Course_Update_Menu(choices);
	if(choice_number==0) return; 
	//Xóa dòng đó trong file học kỳ và lấy ra để cập nhật
	string course_string = File_Line_Seek(semester_path, 0, line);
	cout<<"\t\t ---------------------------------"<<endl;
	cout<<"\t\t Old Course Name:  "<<course_string<<endl;
	Course c = String_ToCourse(course_string);
	string teacher_temp = c.teacher;//Lưu tên giáo viên cũ
	
	//Thực thi việc cập nhật
	for(int i=0;i<choices.size();i++)
	{
		cout<<"Current option: "<<choices[i]<<endl;
		switch (stoi(choices[i]))
		{
		case 1: {
			cout<<"\t\t Type new ID: "<<endl;
			cout<<"\t\t ";getline(cin,c.id);
			break;
		}
		case 2:{
			cout<<"\t\t Type new Course's Teacher: "<<endl;
			cout<<"\t\t ";getline(cin,c.teacher);
			break;
		}
		case 3:{
			cout<<"\t\t Type new Course's Credits: "<<endl;
			cout<<"\t\t ";cin>>c.cre;
			cin.ignore();
			break;
		}
		case 4:{
			cout<<"\t\t Type new Maximum Students: "<<endl;
			cout<<"\t\t ";cin>>c.capacity;
			cin.ignore();
			break;
		}
		case 5:{
			cout<<"\t\t Type new Course's Day: "<<endl;
			cout<<"\t\t ";getline(cin,c.day);
			break;
		}
		case 6:{
			string temp;c.session="";
			cout<<"\t\t Type new Course's first session: "<<endl;
			cout<<"\t\t ";getline(cin,temp);
			c.session+=temp+" ";
			cout<<"\t\t Type new Course's second session: "<<endl;
			cout<<"\t\t ";getline(cin,temp);
			c.session+=temp;
			break;
		}
		default:
			break;
		}
	}
	//Chuyển kiểu dữ liệu môn học đã thay đổi lại thành chuỗi
	course_string = Course_ToString(c);
	course_string+=","+faculty;
	//Cập nhật trong file học kỳ
	File_Line_Update(semester_path, 0, line, course_string);
	//Thực hiện đổi tên file môn học trong thư mục gốc với teacher mới
	string course_folder = ".\\Courses\\" + faculty + "\\";
	string course_name = c.name + "_" + teacher_temp;
	string course_path =  Make_Path(course_folder,course_name);
	string new_course_path = Make_Path(course_folder,c.name+"_"+c.teacher);
	int check = rename(course_path.c_str(),new_course_path.c_str());
	if (check == 1)
		cout << "Error to rename!";
	//Đổi tên giáo viên trong file đăng ký của Sinh viên
	if(teacher_temp==c.teacher) return; //Tên giáo viên không đổi thì out
	Student_Course_Update(new_course_path,course_string);
}

//*Khởi tạo cho các tính năng của môn học
//@param &semester_path Đường dẫn đến học kỳ
//@param dmy Ngày tháng hiện tại
bool Course_Init(string &semester_path,string year_name)
{
	//Tạo đường dẫn cho năm và kiểm tra xem nó có tồn tại hay không 
	string year_path = Make_Path(".\\Years\\",year_name);
	if (File_Exist(year_path)==false) 
	{
		cout<<"\t\t This year was not created !"<<endl;
		cout<<"\t\t ";system("pause");
		return false;
	}
	//Nếu năm tồn tại thì cho chọn học kỳ của năm đó
	int limited_semester = Semester_Display(year_name);
	semester_path = Semester_Select(year_name);
	if(semester_path=="OUT")
		return false;
	return true;
}

bool Course_Proc(int option,string semester_path,int mod)
{
	if (option == 1 && mod == 1)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
		//Tạo môn học
		Course_Create(semester_path,faculty);
		system("cls");
		return true;
	}	
	else if(option ==2 && mod == 1)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
		//Xóa môn học
		bool run = true;
		while(run){
			run  = Course_Delete(semester_path,faculty);
		}
		system("cls");
		return true;
	}
	else if(option ==3 && mod == 1)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
		//Cập nhật môn học
		Course_Update(semester_path,faculty);
		system("cls");
		return true;
	}
	else if(option ==4)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(),1);
		if(faculty=="OUT") return false;
			
		Courses_Display(semester_path,faculty);
		cout<<"\t\t ";system("pause");
		system("cls");
		return true;
	}
	else if(option ==5)
	{
		string faculty = Faculty_Name(Department_Menu_Disp(), 1);
		if (faculty == "OUT")
			return false;
		Student_inCourse(semester_path,faculty);
		
		cout<<"\t\t ";system("pause");
		system("cls");
		return true;
	}
	else if(mod==0)
	{
		system("cls");
		return true;
	}
	else {
		system("cls");
		return false;
	}
}