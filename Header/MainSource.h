#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <direct.h>
#include <filesystem>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
struct date {
    int day, month, year;
	string semester;
	string schoolyear;
};
struct TimeRange
{
	date begin, end;
};
struct Account {
    string username;
    string password;
};
struct str {
	string info;
	str* next;
};
struct strings {
	str* head;
	str* tail;
};
struct Course {
	string id,name,teacher;
	string day,session;
	int cre,capacity;
};
struct Student {
	int number;
	int id;
	string name, gender, faculty, birthdate;
	int socialID;
	Account user;
};
struct Student_node {
	Student info;
	Student_node*next;
};
struct Class {
	Student_node* head;
	Student_node* tail;
};
struct Score {
	int number;
	string id;
	string name;
	double total_mark, final_mark, midterm_mark, other_mark;
};
struct List_score {
	Score* data;
	int capacity;
};
struct List_course {
	Course* data;
	int number;
};
struct Course_info {
	string id;
	int credits;
	double total_mark;
};
struct Semester_CourseInfo {
	Course_info* GPA;
	int number;
};