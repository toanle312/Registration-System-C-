#include"MainSource.h"

//String proccess
bool compare(string s1, string s2);
void split_string(string s, string& s1, string& s2);
//Account checking
bool check_usrname(string str, string path, int& count);
bool check_pass(string pass,int count);
bool check_key(string key, int count);
bool check_newpass(string pass);
//Change Password & Recover Password
void change_pass_in_file(string username, string pass);
void forgot_pass();
void change_pass();
