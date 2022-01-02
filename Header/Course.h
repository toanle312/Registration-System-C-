#include "MainSource.h"
bool Course_Init(string& semester_path, string year_name);
int Courses_Display(string semester_path, string faculty);
bool Course_Proc(int option, string semester_path,int mod);
int Course_Select(string semester_path, string faculty);
string Get_Course_Path(string course_string, string faculty);
List_course get_ListCourse(string path);
int Course_Find_in_Student(string student_path, string course_name);
void Student_inCourse(string semester_path, string faculty);