#pragma once
#include"identity.h"
#include<vector>
#include"ComputerRoom.h"
#include"Orderfile.h"
using namespace std;

class Student: public Identity{
	int m_id;//ѧ��
public:

	Student();

	Student(int id, string name, string pwd);

	void operMenu() final;

	void applyOrder();//����ԤԼ

	void showMyorder();//�鿴ԤԼ

	void showAllorder();//��ʾ����ԤԼ

	void cancelOrder();//ȡ��ԤԼ

	void set_id(int a) { this->m_id = a; }
	int get_id() { return m_id; }

	vector<ComputerRoom>vCom;




};
