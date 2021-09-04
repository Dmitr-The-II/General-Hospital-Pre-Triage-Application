
#define _CRT_SECURE_NO_WARNINGS
#include "CovidPatient.h"
using namespace std;
namespace sdds {
    int nextCovidTicket = 1;

    CovidPatient::CovidPatient() : Patient(nextCovidTicket) {
        nextCovidTicket++;
    }

    char CovidPatient::type() const {
        return 'C';
    }

    istream& CovidPatient::csvRead(istream& is) {
        Patient::csvRead(is);
        nextCovidTicket = Patient::number() + 1;
        is.ignore();
        return is;
    }

    ostream& CovidPatient::write(ostream& os) const {
        if (Patient::fileIO()) {
            Patient::csvWrite(os);
        }
        else {
            os << "COVID TEST" << endl;
            Patient::write(os) << endl;
        }
        return os;
    }

    istream& CovidPatient::read(istream& is) {
        if (fileIO()) {
            csvRead(is);
        }
        else {
            Patient::read(is);
        }
        return is;
    }
}