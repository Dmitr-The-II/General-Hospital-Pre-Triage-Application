
#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_
#include "Patient.h"

namespace sdds
{
    class CovidPatient : public Patient
    {
    public:
        CovidPatient();
        char type() const;
        std::istream& csvRead(std::istream& is);
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& is);
    };
}
#endif // !SDDS_COVIDPATIENT_H_



