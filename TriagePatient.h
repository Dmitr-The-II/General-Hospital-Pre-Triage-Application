
#ifndef SDDS_TRIAGEPATIENT_H
#define SDDS_TRIAGEPATIENT_H
#include "Patient.h"
using namespace std;
namespace sdds {
    class TriagePatient : public Patient {
        char* symptom;

    public:
        TriagePatient();
        virtual char type() const;
        virtual ostream& csvWrite(ostream& os) const;
        virtual istream& csvRead(istream& is);
        virtual ostream& write(ostream& os) const;
        virtual istream& read(istream& is);
        ~TriagePatient();
    };
}
#endif // !SDDS_TRIAGEPATIENT_H


