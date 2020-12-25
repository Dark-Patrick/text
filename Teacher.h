#pragma once
#include"identity.h"
using namespace std;

class Teacher :public Identity {
	int m_Empid;//Ö°¹¤ºÅ
public:
	Teacher();

	Teacher(int id,string name,string paw);

	void operMenu()final;

	void showAllorder();

	void valiOrder();

	void set_id(int a) { this->m_Empid = a; }
	int get_id() { return m_Empid; }
};