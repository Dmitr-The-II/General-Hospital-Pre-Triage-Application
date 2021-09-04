
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include "Patient.h"
#include "utils.h"

using namespace std;
namespace sdds {
	Patient::Patient(int ticket, bool flag) : ticket(ticket) {
		this->ticket = ticket;
		this->flag = flag;
	}

	Patient::~Patient() {
		delete[] pat_name;
		pat_name = nullptr;
	}

	const bool Patient::fileIO() const {
		return flag;
	}

	void Patient::fileIO(bool flag) {
		this->flag = flag;
	}

	bool Patient::operator==(const char ch) const{
		return this->type() == ch;
	}

	bool Patient::operator==(const Patient& second_obj) const{
		return this->type() == second_obj.type();
	}

	void Patient::setArrivalTime() {
		ticket.resetTime();
	}

	Patient::operator Time() const {
		return Time(ticket);
	}

	int Patient::number() const {
		return ticket.number();
	}

	ostream& Patient::csvWrite(ostream& os) const {
		os << this->type() << ',' << pat_name << ',' << OHIP_num << ',';
		ticket.csvWrite(os);
		return os;
	}

	istream& Patient::csvRead(istream& is) {
		string str;
		getline(is, str, ',');
		delete[] pat_name;
		pat_name = nullptr;
		pat_name = new char[strlen(str.c_str()) + 1];
		strcpy(pat_name, str.c_str());
		is >> OHIP_num;
		is.ignore(100, ',');
		ticket.csvRead(is);
		return is;
	}

	ostream& Patient::write(ostream& os) const {
		ticket.write(os);
		os << endl;
		if (strlen(pat_name) > 25) {
			for (int i = 0; i < 25; i++) {
				os << pat_name[i];
			}
		}
		else {
			os << pat_name;
		}
		os << ", OHIP: " << OHIP_num;
		return os;
	}

	istream& Patient::read(istream& is) {
		char* str = getcstr("Name: ", is);
		delete[] pat_name;
		pat_name = nullptr;
		pat_name = new char[strlen(str) + 1];
		strcpy(pat_name, str);
		delete[] str;
		OHIP_num = getInt(100000000, 999999999, "OHIP:", "Invalid OHIP Number, ");
		return is;
	}

}
