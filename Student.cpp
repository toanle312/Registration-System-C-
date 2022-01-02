#include "Header\Year.h"
#include "Header\Class.h"
#include "Header\Node Process.h"
#include "Header\Login.h"
#include "Header\File.h"
#include "Header\Convert.h"
#include "Header\Student.h"
#include "Header\Menu.h"
#include "Header\Vector.h"
#include "Header\Course.h"
#include "Header\Enroll.h"

//*Dùng đường dẫn đến file lớp để tìm thông tin học sinh (dùng cho việc đăng nhập)
//@param class_path Đường dẫn đến lớp học
//@param user Thông tin tài khoản và mật khẩu
//@return Kiểu dữ liệu thông tin sinh viên
Student Get_Student_Info(string class_path, Account user)
{
    Student s;
	string arr[7];
	fstream f(class_path, ios::in);
	if(File_Exist(class_path))
	{
		while(!f.eof())
		{
			string reader;
			getline(f,reader);
            if(reader=="") continue;
			string id = reader.substr(2,8);
			if(id == user.username)
			{
                s = String_ToStudent(reader,arr);
                break;
			}
		}
	}
	f.close();
	return s;
}
//*Tìm thông tin đầy đủ của học sinh
//@param course_path Đường dẫn file môn học @param lines Số dòng (số học sinh) có trong môn học
//@return Mảng các thông tin của học sinh
Student *Get_Students_Info(string course_path, int lines)
{
    Student *list = new Student[lines];
    int k = 0;
    ifstream f(course_path);
    while (!f.eof())
    {
        string ID;
        getline(f, ID, '\n');
        if (ID == "")
            continue;
        //Lấy MSSV
        ID = ID.substr(0, 8);
        //Dò trong file tài khoản để lấy đường dẫn đến lớp
        ifstream acc(".\\Accounts\\acc_sv.csv");
        string path;
        while (getline(acc, path, '\n'))
        {
            if (path.substr(0, 8) != ID || path == "") {
                path = "";
                continue;
            }
            //Lấy đường dẫn
            string class_path = split_acc_stu(path);
            //Lấy thông tin đầy đủ của một học sinh
            Student sv = Get_Student_Info(path, {ID, ""});
            list[k++] = sv;
            break;
        }
        acc.close();
    }
    f.close();
    return list;
}
//*Nhập học sinh vào danh sách lớp và các thư mục cần thiết
//@param class_path Đường dẫn đến file lớp học
void Student_Import(string class_path)
{
    if(class_path=="OUT") return;
    //Nhập file cần import học sinh
    string folder = ".\\Students\\Students' Info\\";
    string import = File_Import(folder);
    if(import=="OUT") return;
    
    ifstream read(import);
    while(!read.eof())
    {
        //Đọc file import
        string student;
        getline(read,student);
        if(student=="") continue;
        //Tạo file học sinh
        string arr[8];
        Student s = String_ToStudent(student,arr);
        string student_folder = ".\\Students\\Students for Enrollment\\";
        string student_file_name = arr[1]+"_"+arr[2];
        string student_file_path = Make_Path(student_folder,student_file_name);
        if(File_Exist(student_file_path)) continue;
        File_Create(student_file_path);
        //Ghi học sinh vào file lớp
        File_Append(class_path,student);
        //Sắp xếp lại số thứ tự học sinh
        Student_Arrange(class_path);
        //Ghi tài khoản mật khẩu vào file Account
        string account=".\\Accounts\\acc_sv.csv";
        string user_pass_path = arr[1] +","+ arr[7] + ","+class_path;
        File_Append(account,user_pass_path);
    }
    read.close();
}
//*Xóa một học sinh đơn lẻ có trong lớp
//@param class_path Đường dẫn tới lớp
//@return True nếu cần recycle
bool Student_Delete(string class_path){
    
    //Xuất danh sách học sinh
    int limited_student = Student_Display(class_path);
    if(limited_student<1) return false;
    //Chọn học sinh để xóa
    cout<<"\t\t Press '-1' if you want to exit!"<<endl;
    cout<<"\t\t Choose student to modify: ";
    int choice = Valid_Data(limited_student);
    if(choice<1) return false;
    //Xóa học sinh trong file lớp
    string student_string = File_Line_Delete(class_path,0,choice);
    //Xóa học sinh trong file account
    string account = ".\\Accounts\\acc_sv.csv";
    ifstream f (account,ios::in);
    int count = 1;
    int line = -1;
    while(!f.eof())
    {
        string reader;
        getline(f,reader);
        if(reader.substr(0,8)==student_string.substr(2,8))
            {
                line = count;
                break;
            }
        count+=1;
    }
    f.close();
    File_Line_Delete(account,0,line);
    //Xóa file học sinh
    string arr[8];
    Student s = String_ToStudent(student_string,arr);
    string student_folder = ".\\Students\\Students for Enrollment\\";
    string student_file_path = Make_Path(student_folder,arr[1]+"_"+arr[2]);
    remove(student_file_path.c_str());

    return true;
}
//*Sắp xếp lại số thứ tự trong file học 
//@param class_path Đường dẫn tới lớp
void Student_Arrange(string class_path)
{
	//Cho học sinh vào vector
    vector<string> students = File_ToVector(class_path);
    //Thay số thứ tự
	for(int i=0;i<students.size();i++)
	{
		students[i].replace(0,1,to_string(i+1));
	}
    //Clear file cũ
    File_Clear(class_path);
    //Cho danh sách học sinh mới vào
	Vector_ToFile(class_path,students);
}
//*Hiển thị học sinh có trong lớp
//@param class_path Đường dẫn của lớp cần truy cập
//@return Số lượng học sinh đếm được
int Student_Display(string class_path)
{
    system("cls");
    //Sắp xếp lại số thứ tự học sinh
    Student_Arrange(class_path);
    cout<<"\t\t Current Students in class: "<<endl;
    cout<<"\t\t (No-ID-Name-Gender-Faculty-Birthdate-Social ID)"<<endl;
    cout<<"\t\t -----------------------------------------------"<<endl;
    
    int count=0; 
    fstream f(class_path,ios::in);
    while(!f.eof())
    {
        string reader;
        getline(f,reader);
        if(reader=="") continue;
        count+=1;
        //Thay dấu phẩy thành dấu gạch ngang
        String_Replace(reader,",","  -  ");
        cout<<reader<<endl;
    }
    f.close();
    if(count<1)
    {
        cout<<"\t\t This class does not have any students"<<endl;
    }
    cout<<"\t\t ";system("pause");
    return count;
}
//*Xuất danh sách học sinh có trong môn học
//@param semester_path Đường dẫn đến học kỳ @param faculty Khoa đang chọn hiện tại
void Student_Export(string semester_path,string faculty)
{
    string courses = ".\\Courses\\" + faculty + "\\Courses.csv";
    int choice = Course_Select(semester_path,faculty);
    if (choice == 0) return;
    //Tạo đường dẫn đến file môn học
    string course_string = File_Line_Seek(courses, 0, choice);
    string course_path = Get_Course_Path(course_string,faculty);
    //Copy file đến tại đường dẫn cần export
    string new_course_path = File_Copy(course_path,".\\Students\\Students_Export\\");

    //Tìm thông tin đầy đủ của từng học sinh
    int lines = Count_line(course_path);
    Student *list = Get_Students_Info(course_path,lines);

    //Chép danh sách sinh viên vào file mới tạo
    ofstream write(new_course_path);
    for(int i=0; i<lines; i++){
        write << list[i].number << "," << list[i].id << "," << list[i].name << endl;
    }
    write.close();
    
    Student_Arrange(new_course_path);
}
//*Hiển thị danh sách sinh viên có trong file môn học
void Student_inCourse(string semester_path,string faculty)
{
    int line = Course_Select(semester_path, faculty);
    if (line < 5)
        return;
    //Tạo đường dẫn đến file môn học
    string course_string = File_Line_Seek(semester_path, 0, line);
    string course_path = Get_Course_Path(course_string, faculty);

    //Tìm thông tin đầy đủ của từng học sinh
    vector<string> list = File_ToVector(course_path);
    cout<<"\t\t Student(s) in this course: "<<endl;
    //Xuất thông tin ra màn hình
    for(int i=0;i<list.size();i++)
    {
        String_Replace(list[i],"_"," - ");
        cout<<"\t\t "<<i+1<<". "<<list[i]<<endl;
    }

}
//*Cập nhật môn học có trong file sinh viên (lấy DS SV từ file môn học).
//!Hàm này giữ cho thứ tự môn học không đổi
//@param course_path Đường dẫn đến học kỳ.
//@param new_course_teacher Giáo viên mới của môn học.
void Student_Course_Update(string new_course_path,string new_string)
{
	//Lấy ra tên môn học
	string student_folder = ".\\Students\\Students for Enrollment\\";
    int pos = new_string.find_first_of(",", 0);
    int pos2 = new_string.find_first_of(",", pos + 1);
    string course_name = new_string.substr(pos + 1, pos2 - pos - 1);
    //
    ifstream f(new_course_path);
    if(f.is_open()){
		while(!f.eof())
		{
			//Đọc sinh viên từ file môn học
			string student;
			getline(f,student);
			//Nếu như chuỗi rỗng thì bỏ qua đoạn dưới
            if(student=="") continue;
			string student_path = Make_Path(student_folder,student);
			//Tìm môn học trong file student
			int line = Course_Find_in_Student(student_path,course_name);
			if(line!=0)
			{
				//Cập nhật (nói khác đi là chèn) vào tên môn học cũ
				File_Line_Update(student_path,0,line,new_string);
            }
		}
	}
	f.close();
}
//*Khởi tạo đường dẫn cần thiết cho các tính năng của students
//@return Đường dẫn của lớp học
string Student_Init(string year_name)
{
    //Kiểm tra sự tồn tại của lớp
    string year_path = Make_Path(".\\Years\\",year_name);
	if(File_Exist(year_path)==false) 
	{
		cout<<"\t\t This year was not created"<<endl;
		cout<<"\t\t ";system("pause");
		return "OUT";
	}
    //Chọn lớp 
    int line_number ;
    string class_path=Class_Select(year_name,line_number);
    if(class_path=="OUT") return "OUT"; 
    return class_path;
}
//*Xử lý các tính năng của Student
//Sự lựa chọn tính năng
//True nếu hàm cần dùng lại, false nếu không
bool Student_Proc_Active(int option,string class_path,int mod)
{
    if(option==1 && mod==1)
    {
        Student_Import(class_path);
        system("cls");
        return true;
    }
    else if(option==2 && mod==1)
    {
        bool run =true;
        while(run)
        {
            run = Student_Delete(class_path);
        }
        system("cls");
        return true;
    }
    else if(option ==3)
    {
        Student_Display(class_path);
        system("cls");
        return true;
    }
    else if(mod==0){
        return true;
    }
    else if(option==4 || option ==0){
        return false;
    }
}
//*Xử lý menu của học sinh
bool Student_Proc_Passive(int option, Student info, date dmy, int mod)
{
    if (option == 1)
    {
        bool run = true;
        while (run)
        {
            run = Enroll_MenuProc(Enroll_MenuDisp(info), info, dmy, mod);
        }
        return true;
    }
    else
    {
        return false;
    }
}
