#pragma once
#include<iostream>
#include<map>
#include"globalFile.h"
using namespace std;

class Orderfile {
public:

	Orderfile();

	void updateOrder();

	map<int, map<string, string>>m_orderData;
	//����key:int �����¼������ key:string ����date interval ������
	int order_size;
};
