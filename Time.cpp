
#include <iostream>
#include "Time.h"
#include "utils.h"
using namespace std;

namespace sdds {
	Time& Time::setToNow() {
		m_min = getTime();
		return *this;
	}

	Time::Time(unsigned int min) {
		m_min = min;
	}

	std::ostream& Time::write(std::ostream& ostr) const {
		ostr.width(2);
		ostr.fill('0');
		ostr << (m_min / 60);
		ostr << ":";
		ostr.width(2);
		ostr.fill('0');
		ostr << (m_min % 60);
		return ostr;
	}

	std::istream& Time::read(std::istream& istr) {
		int hour = 0;
		int min = 0;
		char del = 'X';
		istr >> hour >> del >> min;
		if (hour < 0 || min < 0 || del != ':') {
			istr.setstate(ios::failbit);
		}
		else {
			m_min = hour * 60 + min;
		}
		return istr;
	}
	//
	Time& Time::operator -= (const Time& D) {
		while (D.m_min > m_min) {
			m_min += 24 * 60;
		}
		m_min -= D.m_min;
		return *this;
	}

	Time Time::operator - (const Time& D) const {
		Time time;
		time.m_min = m_min;
		while (D.m_min > time.m_min) {
			time.m_min += 1440;
		}
		time.m_min -= D.m_min;
		return time;
	}

	Time& Time::operator += (const Time& D) {
		this->m_min += D.m_min;
		return *this;
	}

	Time Time::operator + (const Time& D) const {
		Time time;
		time.m_min = this->m_min + D.m_min;
		return time;
	}

	Time& Time::operator = (unsigned int val) {
		this->m_min = val;
		return *this;
	}

	Time& Time::operator *= (unsigned int val) {
		this->m_min *= val;
		return *this;
	}

	Time Time::operator * (unsigned int val) const {
		Time time;
		time.m_min = this->m_min * val;
		return time;
	}

	Time& Time::operator /= (unsigned int val) {
		this->m_min /= val;
		return *this;
	}

	Time Time::operator / (unsigned int val) const {
		Time time;
		time.m_min = this->m_min / val;
		return time;
	}

	Time::operator int() const {
		return (int)m_min;
	}

	Time::operator unsigned int() const {
		return (unsigned int)m_min;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& D) {
		return D.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, Time& D) {
		return D.read(istr);
	}


}