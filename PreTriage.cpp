
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

#include "PreTriage.h"
#include "utils.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "utils.h"

using namespace std;

namespace sdds {
    PreTriage::PreTriage(const char* dataFilename) :
        m_averCovidWait(15), m_averTriageWait(5),
        m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2),
        m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2) {
        m_dataFilename = new char[strlen(dataFilename) + 1];
        strcpy(m_dataFilename, dataFilename);

        load();
    }

    PreTriage::~PreTriage() {
        ofstream fout;
        fout.open(m_dataFilename);

        if (fout.is_open()) {
            cout << "Saving Average Wait Times," << endl;
            cout << "   COVID Test: " << m_averCovidWait << endl;
            cout << "   Triage: " << m_averTriageWait << endl;
            cout << "Saving m_lineup..." << endl;
            fout << m_averCovidWait << "," << m_averTriageWait << endl;
            for (int i = 0; i < m_lineupSize; i++) {
                m_lineup[i]->fileIO(true);
                cout << (i + 1) << "- " << *m_lineup[i] << endl;
                fout << *m_lineup[i] << endl;
            }
        }
        for (int i = 0; i < m_lineupSize; i++) {
            delete m_lineup[i];
            m_lineup[i] = nullptr;
        }

        delete[] m_dataFilename;
        m_dataFilename = nullptr;
        cout << "done!" << endl;
    }

    const Time PreTriage::getWaitTime(const Patient& p) const {
        int count = 0;
        Time t;
        for (int i = 0; i < m_lineupSize; i++) {
            if (p == *m_lineup[i]) {
                count++;
            }
        }
        t *= count;
        return t;
    }
    // check
    void PreTriage::setAverageWaitTime(const Patient& p) {
        int a = Time(p);

        if (p == 'C') {
            m_averCovidWait = ((getTime() - a) + (int(m_averCovidWait) * (p.number() - 1))) / p.number();
        }
            
        else {
            m_averTriageWait = ((getTime() - a) + (int(m_averTriageWait) * (p.number() - 1))) / p.number();
        }
            
    }

    void PreTriage::removePatientFromLineup(int index) {
        removeDynamicElement(m_lineup, index, m_lineupSize);
    }

    int PreTriage::indexOfFirstInLine(char type) const {
        int i = 0;
        int res = -1;

        for (i = 0; i < m_lineupSize && res == -1; i++) {
            if (m_lineup[i]->type() == type) {
                res = i;
            }
        }
        return res;
    }
    // not done
    void PreTriage::load() {
        int _index = 0;
        char _comma = '\0';
        bool done = false;

        cout << "Loading data..." << endl;

        ifstream readfile(m_dataFilename);

        if(readfile) {
            readfile >> m_averCovidWait;
            if (!readfile) done = true;
            readfile >> _comma >> m_averTriageWait;
            readfile.ignore(32767, '\n');
            while (_index < maxNoOfPatients && !readfile.eof() && !done) {
                char type = '\0';
                Patient* _temp = nullptr;
                readfile >> type >> _comma;
                if (type == 'C') {
                    _temp = new CovidPatient();
                }
                else if (type == 'T') { 
                    _temp = new TriagePatient(); 
                }
                if (_temp != nullptr) {
                    _temp->fileIO(true);
                    readfile >> *_temp;       
                    _temp->fileIO(false);
                    m_lineup[_index] = _temp; 
                    m_lineupSize++;          
                }

                _index++;
            }

            if (!readfile.eof()) {
                cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;
                cout << m_lineupSize << " Records imported..." << endl << endl;
            }
            else if (done)
                cout << "No data or bad data file!" << endl << endl;
            else
                cout << m_lineupSize << " Records imported..." << endl << endl;
        }
    }

    void PreTriage::reg() {
        if (m_lineupSize == maxNoOfPatients) {
            cout << "Line up full!" << endl;
        }
        else {
            int num;
            m_pMenu >> num;
            switch (num) {
                case 1:
                    m_lineup[m_lineupSize] = new CovidPatient();
                    break;

                case 2:
                    m_lineup[m_lineupSize] = new TriagePatient();
                    break;
                default:
                    break;
            }
            m_lineup[m_lineupSize]->setArrivalTime(); 
            cout << "Please enter patient information: " << endl;
            m_lineup[m_lineupSize]->fileIO(false);
            cin >> *m_lineup[m_lineupSize]; 
            cout << endl << "******************************************" << endl;
            cout << *m_lineup[m_lineupSize];
            cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << endl;
            cout << "******************************************" << endl << endl;
            m_lineupSize++;
        }
    }

    void PreTriage::admit() {
        int num;
        int ind;
        char type = '\0';

        m_pMenu >> num;
        switch (num) {
            case 1:
                type = 'C';
                break;
            case 2:
                type = 'T';
                break;
            default:
                break;
        }

        ind = indexOfFirstInLine(type);
        if (ind != -1) {
            cout << endl;
            cout << "******************************************" << endl;
            m_lineup[ind]->fileIO(false);
            cout << "Calling for " << *m_lineup[ind]; 
            cout << "******************************************" << endl << endl;
            setAverageWaitTime(*m_lineup[ind]);
            removePatientFromLineup(ind);
        }
    }

    void PreTriage::run(void) {
        int num;
        int done = 0;
        do {
            m_appMenu >> num;
            switch (num) {
            case 0:
                done = 1;
                break;
            case 1:
                reg();
                break;
            case 2:
                admit();
                break;
            }
        } while (done == 0);
    }
    
}