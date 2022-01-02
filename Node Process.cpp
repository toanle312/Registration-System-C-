#include "Header\Node Process.h"
#include "Header\Semester.h"
#include "Header\Convert.h"
#include "Header\File.h"

//Kiểm tra danh sách liên kết rỗng
//Param: một DSLK
//Return: true nếu list rỗng, false nếu list có phần tử
bool CheckEmpty(strings list)
{
	if (list.head == nullptr)
		return true;
	return false;
}
//Khởi tạo danh sách liên kết
//Return: danh sách liên kết đã khởi tạo
strings Init_List()
{
	strings l;
	l.head = nullptr;
	l.tail = nullptr;
	return l;
}
//Khởi tạo node
//Param: thông tin của node, ở đây là một chuỗi chứa tên
//Return: con trỏ node chứa name
str* Create_Node(string info)
{
	str* s = new str;
	s->info = info;
	s->next = nullptr;
	return s;
}
//Thêm node vào cuối list
//Param: một danh sách chứa name, một con trỏ trỏ đến stuct name
void Add_Last(strings& list, str* node)
{
	if (CheckEmpty(list))
	{
		list.head = node;
		list.tail = node;
	}
	else
	{
		list.tail->next = node;
		list.tail = node;
	}
}
//Xóa node ở đầu
//Param: một danh sách liên kết chứa tên
void removeHead(strings& l)
{
	str* p = l.head;
	l.head = p->next;
	p->next = nullptr;
	delete p;
	p = nullptr;
}
//Xóa node ở cuối
//Param: một dánh sách liên kết chứa tên
void removeTail(strings& l)
{
	str* p = l.head;
	str* pDel = l.tail;
	while (p->next->next != nullptr)
	{
		p = p->next;
	}
	l.tail = p;
	p->next = nullptr;
	delete pDel;
	pDel = nullptr;
}
//Xóa một node bất kỳ
//Param: danh sách liên kết chứa tên, một node chứa tên
void removeNode(strings& l, str* pDel)
{
	if (pDel == l.head)
	{
		removeHead(l);
	}
	else if (pDel == l.tail)
	{
		removeTail(l);
	}
	else
	{
		str* nptr = l.head;
		while (nptr->next != pDel)
		{
			nptr = nptr->next;
		}
		nptr->next = pDel->next;
		pDel->next = nullptr;
		delete pDel;
		pDel = nullptr;
	}
}
//Sao chép thông tin danh sách liên kết sang một danh sách khác không cùng địa chỉ
//Param: một list name
//Return: một list name khác đã copy
strings Copy_List(strings l)
{
	str* move = l.head;
	strings temp = Init_List();
	while (move != nullptr)
	{
		str* add = Create_Node({ move->info });
		Add_Last(temp, add);
		move = move->next;
	}
	return temp;
}
//Truyền thông tin từ list vào file
//Param: file cần truyển thông tin, danh sách liên kết chứa thông tin
void ReInput_fromList(string store, strings list)
{
	str* move = list.head;
	fstream f(store, ios::in | ios::app);
	while (move->next != nullptr)
	{
		if (!String_InFile(store, move->info))
		{
			f << move->info << endl;
		}
		move = move->next;
	}
	f.close();
}

//Sắp xếp tăng dần cho năm
//Param: DSLK chứa tên năm cần sort
void SortAscen_YearList(strings & list)
{
	//Create new list with different address
	strings result = Copy_List(list);
	str * curr = result.head;

	str* move = list.head;
	//Create flags
	int min;
	int before = 0;

	while (curr != nullptr)
	{
		min = 100000;
		//Set up the flag of smallest number
		while (move != nullptr)
		{
			int num = Year_ToInt(move->info);
			if (num < min && num> before)
			{
				min = num;
			}
			move = move->next;
		}
		//Reset pointer
		move = list.head;
		bool check = false;
		//Compare node with flag and copy to new list
		while (move != nullptr)
		{
			int num = Year_ToInt(move->info);
			if (num == min)
			{
				curr->info = move->info;
				check = true;
				curr = curr->next;
			}

			move = move->next;
		}
		move = list.head;
		before = min;
		if (check == false) { curr = curr->next; }
	}
	list = result;
}
//Xuất danh sách liên kết
//Param: list
//Return: trả về false nếu danh sách rỗng
bool Output_List(strings l)
{
	if (CheckEmpty(l))
	{
		cout << "Empty List !!" << endl;
		return false;
	}

	cout << "List of Node: " << endl;
	cout << "----------------------------------------------------------------------------" << endl;

	str* move = l.head;
	int count = 1;
	while (move != nullptr)
	{
		if(move->info=="") break;
		cout << "\tThe " << count++ << " object: ";
		cout << move->info << " " << endl;
		move = move->next;
	}
	return true;
}

List_score init_ListScore() {
	List_score mylist;
	mylist.data = NULL;
	mylist.capacity = 0;
	return mylist;
}

List_course init_ListCourse() {
	List_course my_list;
	my_list.data = NULL;
	my_list.number = 0;
	return my_list;
}
