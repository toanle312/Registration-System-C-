#include "Header\Vector.h"
//*Lưu mảng động vào file
//@param path (đường dẫn tới file) @param mảng động chứa file
void Vector_ToFile(string file_path,vector<string>list)
{
	fstream file(file_path,ios::app);
	if(file.is_open())
	{
		for(int i=0;i<list.size();i++)
		{
			if(list[i]=="") continue;
			file<<list[i]<<endl;
		}
	}
	file.close();
}
//*Lấy lên các chuỗi trong file lưu vào mảng động
//@param file_path (đường dẫn file) 
//@return Mảng động lưu các chuỗi
vector<string> File_ToVector(string file_path)
{
	vector<string> string_list;
	ifstream file(file_path);
	if(file.is_open())
	{
		while(!file.eof()){
			string reader;	
			getline(file,reader);
			if (reader == "" || reader == "OUT") continue;
			string_list.push_back(reader);
		}
	}
	else {
		cout << "Cannot open file. Try again!";
	}
	file.close();
	return string_list;
}
//*Kiểm tra phần tử check có trùng trong vector
//@param arr Mảng @param check Phần tử cần kiểm tra
//@return True nếu trùng
bool String_Vector_Duplicate(vector<string> arr, string check)
{
	for(int i=0;i<arr.size();i++)
	{
		if(arr[i]==check)
		return true;
	}
	return false;
}
//*Xuất ra màn hình các phần tử của vector
//@param arr Mảng động
void String_Vector_Display(vector<string> arr)
{
	for(int i=0;i<arr.size();i++)
	{
		cout<<arr[i]<< " ";
	}
}