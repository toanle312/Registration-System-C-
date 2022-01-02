#include "Header\MainSource.h"
int pass_mode();
void enter_data(string& param);
void enter_showpass(Account &info);
void enter_hidepass(Account& info);
bool pass_mode_proc(int option, Account &info);
bool enter_acc(Account& info);
int count_acc(string str);
bool check_acc_ad(Account info);
bool login_as_admin(Account& info);
bool check_acc_student(Account user,Student &info);
bool login_as_student(Account &user,Student &info);
string split_acc_stu(string &s);
