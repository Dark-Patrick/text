#pragma once
#include"identity.h"
#include<vector>
#include"ComputerRoom.h"
#include"Orderfile.h"
using namespace std;

class Student: public Identity{
	int m_id;//学号
public:

	Student();

	Student(int id, string name, string pwd);

	void operMenu() final;

	void applyOrder();//申请预约

	void showMyorder();//查看预约

	void showAllorder();//显示所有预约

	void cancelOrder();//取消预约

	void set_id(int a) { this->m_id = a; }
	int get_id() { return m_id; }

	vector<ComputerRoom>vCom;




};
