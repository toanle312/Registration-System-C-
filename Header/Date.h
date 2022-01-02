#include "Header\MainSource.h"
void output_dmy(date dmy);
bool check_leap_year(int year);
int day_of_month(int month, int year);
bool check_dmy(date dmy);
void enter_dmy(date& dmy);
void choose_schoolyear(date& dmy);

void enter_SemesterTime(TimeRange timeline[3],date dmy);
void init_SemesterTime(TimeRange timeline[3]);
void enter_RegsTime(TimeRange regtime[3], string seasons[3]);

string get_semester(string folder, date dmy);
string get_time_to_Enroll(string folder, date dmy);
bool check_registration_date(date& dmy);