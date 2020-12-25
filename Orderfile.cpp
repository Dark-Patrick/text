#include"Orderfile.h"
#include<fstream>
#include<string>

Orderfile::Orderfile() {
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;
	string interval;
	string stuid;
	string name;
	string room;
	string status;

	this->order_size = 0;

	while (ifs >> date && ifs >> interval && ifs >> room && ifs >> stuid && ifs >> name && ifs >> status) {
		string key;
		string value;
		map<string, string>m;

	//    date:123
	//     |    |
	//    key value
		int pos=date.find(":");
		if (pos != -1) {
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		
		 pos = interval.find(":");
		if (pos != -1) {
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		 pos = room.find(":");
		if (pos != -1) {
			key = room.substr(0, pos);
			value = room.substr(pos + 1, room.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		 pos = stuid.find(":");
		if (pos != -1) {
			key = stuid.substr(0, pos);
			value = stuid.substr(pos + 1, stuid.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		 pos = name.find(":");
		if (pos != -1) {
			key = name.substr(0, pos);
			value = name.substr(pos + 1, name.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		 pos = status.find(":");
		if (pos != -1) {
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//懒得封装，有点冗余，凑合用吧

		this->m_orderData.insert(make_pair(this->order_size, m));
		this->order_size++;
	}
	ifs.close();

	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++) {
		cout << "count: " << it->first << " value=" << endl;
		for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++) {
			cout << "key=" << mit->first << " value=" << mit->second << endl;
		}
	}*/
}

void Orderfile::updateOrder() {
	if (this->order_size == 0) {
		return;
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->order_size; i++) {
		ofs << "date:" << this->m_orderData[i]["date"]
			<< " interval:" << this->m_orderData[i]["interval"]
			<< " room:" << this->m_orderData[i]["room"]
			<< " stuid:" << this->m_orderData[i]["stuid"]
			<< " name:" << this->m_orderData[i]["name"]
			<< " status:" << this->m_orderData[i]["status"]<< endl;
	}
	ofs.close();
}