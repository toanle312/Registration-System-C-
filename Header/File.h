#include "MainSource.h"

bool File_Exist_Display(string path);
bool File_Exist(string path);
bool File_isEmpty(string path);
void File_Create(string file_path);
void File_Clear(string file_path);
string File_Import(string folder);
string File_Copy(string path, string dest);
void File_Append(string file_path, string newstring);
string File_Line_Delete(string path,int start,int line);
void File_Line_Update(string path,int start,int line,string update);
string File_Line_Seek(string path,int start,int line);
void Directory_Delete(string dir);
void Directory_Create(string dir);
bool String_InFile(string file_path, string check_string);
int Count_line(string path);
