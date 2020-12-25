#pragma once
#include<iostream>
#include<string>

using namespace std;
class Identity {
	string m_name;
	string m_password;
public:
	virtual void operMenu() = 0;//´¿Ðéº¯Êý

	void set_name(string str) { this->m_name = str; }
	void set_password(string str) { this->m_password = str; }
	string get_name()const { return this->m_name; }
	string get_password()const { return this->m_password; }

	virtual ~Identity()
	{

	}
};
