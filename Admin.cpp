#include"Admin.h"
#include<fstream>
#include"globalFile.h"
#include<algorithm>
#include<iomanip>
using namespace std;

Admin::Admin() {

}

Admin::Admin(string name, string paw) {
	this->set_name(name);

	this->set_password(paw);
	//初始化文件，获得文件信息
	this->initVector();

	//初始化机房信息
	//此信息不会修改，故没有封装函数
	vcom.clear();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_Comid&& ifs >> com.m_Max)
		vcom.push_back(com);
	ifs.close();

	//cout << "count computer room" << vcom.size();
}

void Admin::operMenu() {
	while (true) {

	cout << "Admin:"<<this->get_name() << " Welcome! \n" << endl;
	cout << "Enter your choice" << endl;
	cout << "\t\t------------------------------------------\n"
		<< "\t\t|                                        |\n"
		<< "\t\t|              1.Add Person              |\n"
		<< "\t\t|                                        |\n"
		<< "\t\t|              2.Show Person             |\n"
		<< "\t\t|                                        |\n"
		<< "\t\t|              3.Show Computer           |\n"
		<< "\t\t|                                        |\n"
		<< "\t\t|              4.Clean File              |\n"
		<< "\t\t|                                        |\n"
		<< "\t\t|              0.Log out                 |\n"
		<< "\t\t|                                        |\n"
		<< "\t\t------------------------------------------\n"
		<< endl;
	

		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			//cout << "seccess 1" << endl;
			this->addPerson();
			break;
		case 2:
			//cout << "seccess 2" << endl;
			this->showPerson();
			break;
		case 3:
			//cout << "seccess 3" << endl;
			this->showComputer();
			break;
		case 4:
			//cout << "seccess 4" << endl;
			this->cleanFile();
			break;
		case 0:
			delete this;
			cout << "Log out" << endl;
			return;
			break;
		default:
			cout << "Error:Invalid input!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

void Admin::addPerson() {
	cout << "Enter your select:" << endl;
	cout << "1.Add new teacher \n"
		<< "2.Add new student" << endl;
	string filename;
	string tip;
	ofstream ofs;
	int select;
	cin >> select;
	if (select == 1) {
		filename = TEACHER_FILE;
		tip = "Please enter Employee id";
	}
	else if (select == 2) {
		filename = STUDENT_FILE;
		tip = "Please enter Id";
	}

	ofs.open(filename, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;
	cin >> id;
	cout << "Enter name" << endl;
	cin >> name;
	cout << "Enter password" << endl;
	cin >> pwd;

	if (this->checkRepeat(id,select)) {
		cout << "ERROR:Duplicate records exist" << endl;
		system("pause");
		system("cls");
		return;
	}

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "SUCESS" << endl;
	ofs.close();

	this->initVector();

	system("pause");
	system("cls");
}

//利用STL仿函数实现
void printStudent(Student &s) {
	cout << setiosflags(ios_base::left)<<setw(4)<<"ID:"
		<<resetiosflags(ios_base::left)<<setw(10)<< s.get_id()
		<<setiosflags(ios_base::left)<<setw(5)<< " Name:" 
		<<resetiosflags(ios_base::left)<<setw(10)<<s.get_name()
		<< setiosflags(ios_base::left) << setw(10) << " Password:" 
		<< setw(10) << s.get_password() << endl;
}
void printTeacher(Teacher& s) {
	cout << setiosflags(ios_base::left) << setw(4) << "ID:"
		<< resetiosflags(ios_base::left) << setw(10) << s.get_id()
		<< setiosflags(ios_base::left) << setw(5) << " Name:"
		<< resetiosflags(ios_base::left) << setw(10) << s.get_name()
		<< setiosflags(ios_base::left) << setw(10) << " Password:"
		<< setw(10) << s.get_password() << endl;
}
//调用以上仿函数
void Admin::showPerson() {
	cout << "Enter your select:" << endl;
	cout << "1.Show teacher \n"
		<< "2.Show student" << endl;

	int select;
	cin >> select;

	if (select == 1) {
		cout << "All teachers information is as follows:" << endl;
		for_each(vtea.begin(), vtea.end(),printTeacher );

	}
	else if (select == 2) {
		cout << "All students information is as follows:" << endl;
		for_each(vstu.begin(), vstu.end(),printStudent );
	}

	system("pause");
	system("cls");
}

void Admin::showComputer() {
	cout << "All computer room information is as follows:" << endl;
	for (vector<ComputerRoom>::iterator it = vcom.begin(); it != vcom.end(); it++) {
		cout << "Room number:" << it->m_Comid << " Capacity:" << it->m_Max << endl;
	}

	system("pause");
	system("cls");
}

void Admin::cleanFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "File clear!" << endl;
	system("pause");
	system("cls");

}

void Admin::initVector() {

	this->vstu.clear();
	this->vtea.clear();
	ifstream ifs;

	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "ERROR:Unable to find target file " << endl;
		ifs.close();
		return;
	}
	
	int id;
	string name;
	string pwd;
	while (ifs >> id && ifs >> name && ifs >> pwd) {
		Student s(id, name, pwd);
		vstu.push_back(s);
	}
	//cout << "count student:" << vstu.size()<<endl;
	ifs.close();
	///////////////////////////////////////////////////
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "ERROR:Unable to find target file " << endl;
		ifs.close();
		return;
	}

	
	while (ifs >> id && ifs >> name && ifs >> pwd) {
		Teacher s(id, name, pwd);
		vtea.push_back(s);
	}
	//cout << "count teacher:" << vtea.size() << endl;
	ifs.close();
}

bool Admin::checkRepeat(int id, int type) {
	if (type == 2) {
		for (vector<Student>::iterator it = vstu.begin(); it != vstu.end(); it++) {
			if (id == it->get_id())
				return true;
		}
	}
	else {
		for (vector<Teacher>::iterator it =vtea.begin(); it != vtea.end(); it++) {
			if (id == it->get_id())
				return true;
		}
	}
	return false;
}

