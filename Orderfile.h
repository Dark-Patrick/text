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
	//！！key:int 代表机录的条数 key:string 代表date interval 等属性
	int order_size;
};
