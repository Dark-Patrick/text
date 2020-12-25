#include"Student.h"
#include"globalFile.h"
#include<fstream>
#include"ComputerRoom.h"
#include<iomanip>
using namespace std;

Student::Student() {

	vCom.clear();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_Comid&& ifs >> com.m_Max)
		vCom.push_back(com);
	ifs.close();

}

Student::Student(int id, string name, string paw) {
	this->m_id = id;

	this->set_name(name);

	this->set_password(paw);

	vCom.clear();
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_Comid&& ifs >> com.m_Max)
		vCom.push_back(com);
	ifs.close();
}

void Student::operMenu() {
	int choice;
	while (true)
	{
		cout << "Student:" << this->get_name() << "welcome!\n" << endl;
		cout << "Enter your choice" << endl;
		cout << "\t\t------------------------------------------\n"
			<< "\t\t|                                        |\n"
			<< "\t\t|              1.Apply Order             |\n"
			<< "\t\t|                                        |\n"
			<< "\t\t|              2.Show my order           |\n"
			<< "\t\t|                                        |\n"
			<< "\t\t|              3.Show all order          |\n"
			<< "\t\t|                                        |\n"
			<< "\t\t|              4.Cancel Order            |\n"
			<< "\t\t|                                        |\n"
			<< "\t\t|              0.Log out                 |\n"
			<< "\t\t|                                        |\n"
			<< "\t\t------------------------------------------\n"
			<< endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			this->applyOrder();
			break;
		case 2:
			this->showMyorder();
			break;
		case 3:
			this->showAllorder();
			break;
		case 4:
			this->cancelOrder();
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

void Student::applyOrder() {
	cout << "The computer room is open from Monday to Friday!\n" << endl;
	cout << "Select the date to be reserved" << endl;
	cout << "1.Monday \n2.Tuesday \n3.Wednesday \n4.Thursday \n5.Friday" << endl;
	int date, interval, room;
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
			break;
		cout << "Error:Invalid input!" << endl;
	}

	cout<<"Select the interval to be reserved" << endl;
	cout << "\t1.AM \n\t2.PM" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
			break;
		cout << "Error:Invalid input!" << endl;
	}

	cout<< "Select the room to be reserved" << endl;
	cout << "Room nuber:" << vCom[0].m_Comid << " Capacity:" << vCom[0].m_Max << '\n'
		<< "Room nuber:" << vCom[1].m_Comid << " Capacity:" << vCom[1].m_Max << '\n'
		<< "Room nuber:" << vCom[2].m_Comid << " Capacity:" << vCom[2].m_Max << endl;
	while (true)
	{
		cin >>room;
		if (room >= 1 && room <= 3)
			break;
		cout << "Error:Invalid input!" << endl;
	}

	cout << "Appointment successful, under review!" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date
		<< " interval:" << interval
		<< " room:" << room
		<< " stuid:" << this->m_id
		<< " name:" << this->get_name()
		<< " status:" << 1 << endl;//1 代表状态：审核中
	ofs.close();

	system("pause");
	system("cls");
}

string date(string a) {
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
void Student::showMyorder() {
	Orderfile ord;
	if (ord.order_size == 0){ 
		cout << "No appointment record" << endl; 
	
		system("pause");
		system("cls");
		return;
	}
	int count = 0;
	for(int i=0;i<ord.order_size;i++){
		if (atoi(ord.m_orderData[i]["stuid"].c_str()) == this->get_id()) {
			// int atoi(const char* _String)
			//c_str: c style string(const char*)
			count++;
			cout << "Student:" << setiosflags(ios_base::left) << setw(6) << this->get_name()
				<< "ID:" << setw(10) << this->get_id()
				<< "DATE:" << setw(10) << date(ord.m_orderData[i]["date"])
				<< "Interval:" <<setw(5)<<(ord.m_orderData[i]["interval"] == "1" ? "AM" : "PM")
				<< " Room:" << setw(4)<<ord.m_orderData[i]["room"];
			string status = "Status:";
			//1.审核中 2.已预约 3.预约失败 0.取消预约
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
	}
	if(count==0) cout << "No appointment record" << endl;

	system("pause");
	system("cls");
}

void Student::showAllorder() {
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
			<< "DATE:" << setw(10) << date(ord.m_orderData[i]["date"])
			<< "Interval:" <<setw(5)<< (ord.m_orderData[i]["interval"] == "1" ? "AM" : "PM")
			<< " Room:" <<setw(4)<< ord.m_orderData[i]["room"];
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

void Student::cancelOrder() {
	Orderfile ord;
	if (ord.order_size == 0) {
		cout << "No appointment record" << endl;

		system("pause");
		system("cls");
		return;
	}
	cout << "Records under review or successful appointment can be cancelled. \nPlease select the records to be cancelled" << endl;
	vector<int>v;
	int count=1;
	for (int i = 0; i < ord.order_size; i++) {
		if (atoi(ord.m_orderData[i]["stuid"].c_str()) == this->get_id()) {
			if (ord.m_orderData[i]["status"] == "1" || ord.m_orderData[i]["status"] == "2") {
				cout << '\n' << count++ << ":";

				cout << "Student:" << setiosflags(ios_base::left) << setw(6) << ord.m_orderData[i]["name"]
					<< "ID:" << setw(10) << ord.m_orderData[i]["stuid"]
					<< "DATE:" << setw(10) << date(ord.m_orderData[i]["date"])
					<< "Interval:" << setw(5)<<(ord.m_orderData[i]["interval"] == "1" ? "AM" : "PM")
					<< " Room:" << setw(4)<<ord.m_orderData[i]["room"];
				string status = "Status:";

				if (ord.m_orderData[i]["status"] == "1") {
					status += "Under review";
				}
				else if (ord.m_orderData[i]["status"] == "2") {
					status += "Reserved";
				}
				cout << " " << status << endl;

				v.push_back(i);
			}
		}
	}
		cout << "\nChoose a record you want to cancel" << endl;
		cout << "Enter 0 to give up" << endl;
		int select;
		cin >> select;
		while (true)
		{
			if (select == 0) {
				system("cls");
				return;
			}
			if (select >= 1 && select <= v.size()) {
				ord.m_orderData[v[select - 1]]["status"]="0";

				ord.updateOrder();

				cout << "Record cancelled!" << endl;
				system("pause");
				system("cls");
				return;
			}
			cout << "Error:Invalid input!" << endl;
		}
	
	
}