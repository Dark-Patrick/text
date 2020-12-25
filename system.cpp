#include<iostream>
#include"globalFile.h"
#include"Student.h"
#include"Teacher.h"
#include"Admin.h"
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

//�������Ա�Ӳ˵�����
//void AdminMenu(Identity* admin){
//	while (true) {
//		admin->operMenu();
//
//		Admin* min = (Admin*)admin;//������ָ��תΪ����ָ�룬�Ե��������еĽӿ�
//
//		int choice;
//		cin >> choice;
//		switch (choice)
//		{
//		case 1:
//			cout << "seccess 1" << endl;
//			min->addPerson();
//			break;
//		case 2:
//			cout << "seccess 2" << endl;
//			min->showPerson();
//			break;
//		case 3:
//			cout << "seccess 3" << endl;
//			min->showComputer();
//			break;
//		case 4:
//			cout << "seccess 4" << endl;
//			min->cleanFile();
//			break;
//		case 0:
//			break;
//		default:
//			cout << "Error:Invalid input!" << endl;
//			system("pause");
//			system("cls");
//			break;
//		}
//	}
//}

//��¼����
void LoginIN(string FileName, int type) {
	//����ָ�룬ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(FileName, ios::in);
	if (!ifs.is_open()) { 
		cout << "ERROR:Unable to find target file " << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string paw;

	if (type == 1) {
		cout << "Please enter your id" << endl;
		cin >> id;
	}
	else if (type == 2) {
		cout << "Please enter your Employee Id" << endl;
		cin >> id;
	}
	cout << "Please enter your Name " << endl;
	cin >> name;
	cout << "Please enter your Password" << endl;
	cin >> paw;
	if (type == 1) {//ѧ�������֤
		int tid;
		string tname;
		string tpaw;
		while (ifs >> tid && ifs >> tname && ifs >> tpaw) {
			if (id == tid && name == tname && paw == tpaw) {
				cout << "Verify login success" << endl;
				system("pause");
				system("cls");
				person = new Student(id,name,paw);
				Student* man = (Student*)person;
				man->operMenu();

				system("pause");
				system("cls");
				return;
				//person->operMenu();
			}
		}

	}
	else if (type == 2) {//��ʦ�����֤
		int tid;
		string tname;
		string tpaw;
		while (ifs >> tid && ifs >> tname && ifs >> tpaw) {
			if (id == tid && name == tname && paw == tpaw) {
				cout << "Verify login success" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, paw);

				Teacher* man = (Teacher*)person;
				man->operMenu();

				system("pause");
				system("cls");
				return;
			}
		}
	}
	else if (type == 3) {//����Ա�����֤
		string tname;
		string tpaw;
		while ( ifs >> tname && ifs >> tpaw) {
			if (name == tname && paw == tpaw) {
				cout << "Verify login success" << endl;
				system("pause");
				system("cls");
				person = new Admin( name, paw);

				Admin* man = (Admin*)person;//������ָ��תΪ����ָ�룬�Ե��������еĽӿ�
				man->operMenu();


				system("pause");
				system("cls");
				return;
				//AdminMenu(person);
			}
		}

	}

	cout << "Failed to verify login" << endl;
	system("pause");
	system("cls");
	return;
}

int main() {
	int choice;
	while (true)
	{
		cout << "================Computer room reservation system simulation================" << '\n'<< endl;
		cout << "Enter your choice" << endl;
		cout << '\t'<< "\t----------------------------------------------" << '\n'
			<<'\t'  << "\t|                                            |" <<'\n'
			<< '\t' << "\t|           1.Student Entrance               |" << '\n'
			<< '\t' << "\t|                                            |" << '\n'
			<< '\t' << "\t|           2.Teacher Entrance               |" << '\n'
			<< '\t' << "\t|                                            |" << '\n'
			<< '\t' << "\t|           3.Admin   Entrance               |" << '\n'
			<< '\t' << "\t|                                            |" << '\n'
			<< '\t' << "\t|           0.Quit System                    |" << '\n'
			<< '\t' << "\t|                                            |" << '\n'
			<< '\t' << "\t----------------------------------------------" << '\n' << endl;
			cin >> choice;

			switch (choice)
			{
			case 1:
				LoginIN(STUDENT_FILE, 1);
				break;
			case 2:
				LoginIN(TEACHER_FILE,2);
				break;
			case 3:
				LoginIN(ADMIN_FILE, 3);
				break;
			case 0:
				cout << "Exit successfully, welcome to use next time" << endl;
				system("pause");
				return 0;
				break;

			default:
				cout << "Error:Invalid input!" << endl;
				system("pause");
				system("cls");
				break;
			}
	}
}