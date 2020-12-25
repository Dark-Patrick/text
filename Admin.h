#pragma once
#include"identity.h"
#include"Student.h"
#include"Teacher.h"
#include"ComputerRoom.h"
#include<vector>
using namespace std;

class Admin :public Identity {
public:
	Admin();

	Admin(string name, string paw);

	void operMenu()final;

	void addPerson();

	void showPerson();

	void showComputer();
	vector<ComputerRoom>vcom;

	void cleanFile();
	//查重实现
	void initVector();
	vector<Student>vstu;
	vector<Teacher>vtea;
	bool checkRepeat(int id,int type);

	

};