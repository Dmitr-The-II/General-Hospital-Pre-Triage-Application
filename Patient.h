
#ifndef SDDS_PATIENT_H_
#define SDDS_PATIENT_H_
#include <iostream>
#include "IOAble.h"
#include "Ticket.h"
using namespace std;
namespace sdds
{
    class Patient : public IOAble
    {
        char* pat_name{nullptr};
        int OHIP_num{0};
        Ticket ticket{ 0 };
        bool flag;                   
    public:
        Patient(int ticket = 0, bool flag = false);
        ~Patient();
        Patient(const Patient&) = delete;
        Patient& operator=(const Patient&) = delete;
        virtual char type() const = 0;
        const bool fileIO() const;
        void fileIO(bool flag);
        bool operator==(const char ch) const;
        bool operator==(const Patient& second_obj) const;
        void setArrivalTime();
        operator Time() const;
        int number() const;
        virtual ostream& csvWrite(ostream& os) const;
        virtual istream& csvRead(istream& is);
        virtual ostream& write(ostream& os) const;
        virtual istream& read(istream& is);
    };

}
#endif // !SDDS_PATIENT_H_
