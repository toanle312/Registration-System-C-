#include "Header/MainSource.h"
bool Score_Proc(int option, string semester_path, string year_name);
List_score Admin_ViewScoreBoard(string& course_file, string year_name);
int Choose_Courses(vector<string> courses);
void Display_List(vector<string> list);
void Admin_UpdateScore(string year_name);
void Update_Score(Score& chosen_score);
void Input_Valid(double& num);
List_score get_ListScore(string course_file);
void delete_List_Course(List_course& courses);
Semester_CourseInfo get_CourseShorInfo(List_course courses, List_score scores);
void view_ClassScoreBoard(string year_name, string semester_path);