#include "MainSource.h"
string Extension(string str, int option);
string Make_Path(string pre_folder, string file_name);
string Path_ToName(string s);
int String_ToInt(string s);
int Year_ToInt(string);
string Date_toString(date dmy);
date String_ToDate(string dmy);
Student String_ToStudent(string info,string arr[8]);
string Student_ToString(Student s);
Course String_ToCourse(string info);
string Course_ToString(Course c);
string CourseString_To_CourseName(string course_string);
void String_Replace(string &s,string target,string change);
vector<string> File_toStringArray(string path);
strings File_to_LinkList(string path);
string Score_toString(Score my_score);
