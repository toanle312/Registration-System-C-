#include "Header/MainSource.h"
//Initialize//
strings Init_List();
str* Create_Node(string info);
//Operation//
void Add_Last(strings& list, str* node);
bool Output_List(strings l);
void SortAscen_YearList(strings& list);
void ReInput_fromList(string store, strings list);
void removeHead(strings& l);
void removeTail(strings& l);
void removeNode(strings& l, str* pDel);
Score* init(int number);
void Display_ScoreList(List_score score_list);
List_score init_ListScore();
List_course init_ListCourse();