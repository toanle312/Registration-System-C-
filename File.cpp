#include "Header\File.h"
#include "Header\Convert.h"
#include "Header\Login.h"
#include "Header\Node Process.h"
#include "Header\Vector.h"

//*Kiểm tra sự tồn tại của file (có xuất kết quả check)
//@param path Đường dẫn file
//@return True nếu file tồn tại, false nếu ngược lại
bool File_Exist_Display(string path)
{
	fstream file(path);
	if (file.fail()) {
		cout << "\t\t File does not exist" << endl;
		file.close();
		return false;
	}
	else {
		cout << "\t\t File exists" << endl;
		file.close();
		return true;
	}
}

//*Kiểm tra sự tồn tại của file
//@param path Đường dẫn file
//@return True nếu file tồn tại, false nếu ngược lại
bool File_Exist(string path)
{
	fstream file(path);
	return file.is_open();
}

//*Kiểm tra file có rỗng
//@param path Đường dẫn file
//@return True nếu file rỗng, false nếu ngược lại
bool File_isEmpty(string path)
{
	ifstream file(path);
	string checker;
	getline(file,checker);
	if(checker=="")
	{
		file.close();
		return true;
	}
	file.close();
	return false;
}

//*Tạo file mới
//@param file_path Đường dẫn file
void File_Create(string file_path) 
{
	if(File_Exist(file_path)) return;
	FILE* fileInput = fopen(file_path.c_str(), "a+");
	fclose(fileInput);
}

//*Làm rỗng file
//@param file_path Đường dẫn file
void File_Clear(string file_path)
{
	remove(file_path.c_str());
	ofstream f(file_path, ios::out);
	f.close();
}

//*Nhập file 
//@param folder Thư mục chứa file
//@return Đường dẫn file cần import hoặc "OUT" (nếu không có file hoặc muốn thoát ra)
string File_Import(string folder)
{
	string path;
	bool flag =false;
	do {
		//Nhập tên file cần import
		cout <<"\t\t Press '!' if you want to exit"<<endl;
		cout <<"\t\t Enter file str for importing: ";
		string str;
		getline(cin, str);
		if(str=="!") return "OUT";
		//Tạo đường dẫn file import
		path = folder + Extension(str, 1);
		cout << "\t\t Import file from: " << path << endl;
		if (!File_Exist(path)) {
			cout << "Cannot open file. Try again, make sure you type right filename" << endl;
		}
	} while (File_Exist(path)==false);
	if(File_isEmpty(path)) return "OUT";
	cout << "\t\t "; system("pause");
	return path;
}
//*Sao chép file sang một thư mục khác
//@param path đường dẫn file được chép @param dest folder cần sao chép đến
//@return Đường dẫn của file mới copy
string File_Copy(string path, string dest)
{
	vector<string> list;
	list = File_ToVector(path);
	//Tạo file mới với tên tương tự
	string file = Path_ToName(path);
	string copy_path = Make_Path(dest,file);
	File_Create(copy_path);
	Vector_ToFile(copy_path,list);
	return copy_path;
}

//*Thêm chuỗi mới vào cuối file
//@param file_path đường dẫn tới file @param newstring chuỗi cần thêm
void File_Append(string file_path,string newstring)
{
	fstream f(file_path,ios::app);
	if(!File_Exist(file_path))
	{
		cout << "Create file completely!" << endl;
		f.close();
		f.open(file_path, ios::out);
	}
	else {
		cout << "Appended to file completely" << endl;
	}
	f << newstring << endl;
	f.close();
}
//*Kiểm tra chuỗi ký tự có trong file chưa
//@param file_path File cần kiểm tra @param check_string Chuỗi cần kiểm tra trùng
//@return true Chuỗi bị trùng
bool String_InFile(string file_path, string check_string)
{
	fstream file(file_path, ios::in);
	while (!file.eof())
	{
		string reader;
		getline(file,reader);
		if (reader == check_string)
		{
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

//*Đếm số dòng trong file
//@param path Đường dẫn file
//@return Số dòng trong file
int Count_line(string path)	
{
	ifstream f;
	f.open(path);
	int c = 0;
	while (!f.eof())
	{
		string s1="";
		getline(f,s1);
		if (s1 == "") break;
		c++;
	}
	f.close();
	return c;
}

//*Xóa một dòng với số thứ tự dòng cho trước trong file
//@param path Đường dẫn file 
//@param start Số dòng bỏ qua (tức là vị trí dòng bắt đầu)
//@param line Số thứ tự dòng cần xóa
//@return Chuỗi của dòng bị xóa
string File_Line_Delete(string path,int start,int line)
{
	int count=1;
	vector<string> list;
	string returner;
	ifstream f(path);

	if(f.is_open())
	{
		while(!f.eof())
		{
			string reader;
			getline(f,reader);
			if(count-start!=line)
			{
				list.push_back(reader);
			}
			else{
				returner = reader;
			}
			count+=1;
		}
	}
	f.close();
	File_Clear(path);
	Vector_ToFile(path,list);
	return returner;
}
//*Cập nhật thông tin cho một dòng (thật ra là chèn)
//@param path Đường dẫn file 
//@param start Số dòng bỏ qua (tức là vị trí dòng bắt đầu)
//@param line Số thứ tự dòng cần chèn
void File_Line_Update(string path,int start,int line,string update)
{
	fstream f(path,ios::in|ios::out);
	int count=1;
	vector<string> list;
	string reader;
	if(f.is_open()){
		while(getline(f, reader)){
			if(count-start==line){
				list.push_back(update);
			}
			else {
				list.push_back(reader);
			}
			count+=1;
		}
	}
	f.close();
	File_Clear(path);
	Vector_ToFile(path,list);
}
//*Lấy ra một chuỗi trong file từ số dòng cho trước
//@param path Đường dẫn file 
//@param start Số dòng bỏ qua (tức là vị trí dòng bắt đầu)
//@param line Số thứ tự dòng cần tìm
//@return Chuỗi của dòng cần tìm - Không tìm được sẽ là chuỗi null
string File_Line_Seek(string path,int start,int line)
{
	line = line - 4;
	int count=1;
	ifstream f(path);
	if(f.is_open())
	{
		while(!f.eof())
		{
			string reader;
			getline(f,reader);
			if(count-start==line)
			{
				f.close();
				return reader;
			}
			count+=1;
		}
	}
	f.close();
	return "";
}
//*Xóa một thư mục (Xóa file đã có hàm remove)
//@param: dir Thư mục cần xóa
void Directory_Delete(string dir)
{
	
	dir = "rmdir /s /q " + dir;
	system(dir.c_str());
}

//*Tạo một thư mục mới
//@param dir Đường dẫn thư mục
void Directory_Create(string dir)
{
	_mkdir(dir.c_str());
	// if (_mkdir(dir.c_str()) == -1)
	// 	cerr << "\t\t Error :  " << strerror(errno) << endl;

	// else
	// 	cout << "\t\t Directory created" << endl;
}







