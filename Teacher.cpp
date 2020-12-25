#include"Teacher.h"
#include"globalFile.h"
#include<fstream>
#include"ComputerRoom.h"
#include<iomanip>
#include"Orderfile.h"
#include<vector>
using namespace std;

Teacher::Teacher() {

}

Teacher::Teacher(int id, string name, string paw) {
	this->m_Empid = id;

	this->set_name(name);

	this->set_password(paw);
}

void Teacher::operMenu() {
	int choice;
	while (true)
	{
		cout << "Techer:" << this->get_name() << "welcome!\n" << endl;
		cout << "Enter your choice" << endl;
		cout << "\t\t------------------------------------------\n"
			<< "\t\t|                                        |\n"
			<< "\t\t|              1.Vali Order              |\n"
			<< "\t\t|                                        |\n"
			<< "\t\t|              2.Show all order          |\n"
			<< "\t\t|                                        |\n"
			<< "\t\t|              0.Log out                 |\n"
			<< "\t\t|                                        |\n"
			<< "\t\t------------------------------------------\n"
			<< endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			this->valiOrder();
			break;
		case 2:this->showAllorder();
			break;
		case 0:
			delete this;
			cout << "Log out" << endl;
			return;
		default:
			cout << "Error:Invalid input!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

string date1(string a) {
	if (a == "1") {
		return "Monday";
	}
	if (a == "2") {
		return "Tuesday";
	}
	if (a == "3") {
		return "Wednesday";
	}
	if (a == "4") {
		return "Thursday";
	}
	if (a == "5") {
		return "Friday";
	}
}
void Teacher::showAllorder() {
	Orderfile ord;
	if (ord.order_size == 0) {
		cout << "No appointment record" << endl;

		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < ord.order_size; i++) {
		cout << "Student:" << setiosflags(ios_base::left) << setw(6) << ord.m_orderData[i]["name"]
			<< "ID:" << setw(10) << ord.m_orderData[i]["stuid"]
			<< "DATE:" << setw(10) << date1(ord.m_orderData[i]["date"])
			<< "Interval:" << setw(5) << (ord.m_orderData[i]["interval"] == "1" ? "AM" : "PM")
			<< " Room:" << setw(4) << ord.m_orderData[i]["room"];
		string status = "Status:";

		if (ord.m_orderData[i]["status"] == "1") {
			status += "Under review";
		}
		else if (ord.m_orderData[i]["status"] == "2") {
			status += "Reserved";
		}
		else if (ord.m_orderData[i]["status"] == "3") {
			status += "Appointment failure";
		}
		else if (ord.m_orderData[i]["status"] == "0") {
			status += "Cancelled";
		}
		cout << " " << status << endl;
	}
	system("pause");
	system("cls");
}

void Teacher::valiOrder() {
	Orderfile ord;
	if (ord.order_size == 0) {
		cout << "No appointment record" << endl;

		system("pause");
		system("cls");
		return;
	}
	
	/*vector<int>v;
	int count = 1;
	for (int i = 0; i < ord.order_size; i++) {
		
			if (ord.m_orderData[i]["status"] == "1" ) {
				cout << '\n' << count++ << ":";

				cout << "Student:" << setiosflags(ios_base::left) << setw(6) << ord.m_orderData[i]["name"]
					<< "ID:" << setw(10) << ord.m_orderData[i]["stuid"]
					<< "DATE:" << setw(10) << date1(ord.m_orderData[i]["date"])
					<< "Interval:" << setw(5) << (ord.m_orderData[i]["interval"] == "1" ? "AM" : "PM")
					<< " Room:" << setw(4) << ord.m_orderData[i]["room"];
				cout << "Status:Under review" << endl;

				v.push_back(i);
			}
		
	}*/

	int select;
	int act;
	while (true)
	{
		vector<int>v;
		v.clear();
		int count = 1;
		for (int i = 0; i < ord.order_size; i++) {

			if (ord.m_orderData[i]["status"] == "1") {
				cout << '\n' << count++ << ":";

				cout << "Student:" << setiosflags(ios_base::left) << setw(6) << ord.m_orderData[i]["name"]
					<< "ID:" << setw(10) << ord.m_orderData[i]["stuid"]
					<< "DATE:" << setw(10) << date1(ord.m_orderData[i]["date"])
					<< "Interval:" << setw(5) << (ord.m_orderData[i]["interval"] == "1" ? "AM" : "PM")
					<< " Room:" << setw(4) << ord.m_orderData[i]["room"];
				cout << "Status:Under review" << endl;

				v.push_back(i);
			}

		}
		cout << "\nSelect the information you want to review" << endl;
	    cout << "Enter 0 to quit" << endl;
		cin >> select;
		if (select == 0) { 
			cout << "QUIT!" << endl;
			system("pause");
			system("cls");
			return;
		}
		if (select >= 1 && select <= v.size()) {
			cout << "Enter your choice" << endl;
			cout << "\t1.Pass\n\t2.Fail" << endl;
			cin >> act;
			if (act == 1) {
				ord.m_orderData[v[select - 1]]["status"] = "2";

				ord.updateOrder();
				cout << "Appointment passed" << endl;
				system("pause");
				system("cls");
				//return;
			}
			else if (act == 2) {
				ord.m_orderData[v[select - 1]]["status"] = "3";

				ord.updateOrder();
				cout << "Appointment failure" << endl;
				system("pause");
				system("cls");
				//return;
			}
		}
	}
}