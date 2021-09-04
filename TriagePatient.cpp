
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include "TriagePatient.h"
#include "utils.h"
using namespace std;
namespace sdds {
    int nextTriageTicket = 1;

    TriagePatient::TriagePatient() : Patient(nextTriageTicket) {
        symptom = nullptr;
        nextTriageTicket++;
    }

    char TriagePatient::type() const {
        return 'T';
    }

    ostream& TriagePatient::csvWrite(ostream& os) const {
        Patient::csvWrite(os) << ',' << symptom;
        return os;
    }

    istream& TriagePatient::csvRead(istream& is) {
        string str;
        delete[] symptom;
        symptom = nullptr;
        Patient::csvRead(is);
        is.ignore(200, ',');
        getline(is, str, '\n');
        symptom = new char[strlen(str.c_str()) + 1];
        strcpy(symptom, str.c_str());
        nextTriageTicket = Patient::number() + 1;
        return is;
    }

    ostream& TriagePatient::write(ostream& os) const {
        if (Patient::fileIO()) {
            csvWrite(os);
        }
        else {
            os << "TRIAGE" << endl;
            Patient::write(os) << endl;
            os << "Symptoms: " << symptom << endl;
        }
        return os;
    }

    istream& TriagePatient::read(istream& is) {
        char* str;

        if (Patient::fileIO()) {
            csvRead(is);
        }
        else {
            delete[] symptom;
            symptom = nullptr;
            Patient::read(is);
            str = getcstr("Symptoms: ", is);
            symptom = new char[strlen(str) + 1];
            strcpy(symptom, str);
            delete[] str;
        }
        return is;
    }

    TriagePatient::~TriagePatient() {
        delete[] symptom;
        symptom = nullptr;
    }
}