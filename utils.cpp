
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>

#include "utils.h"
#include "Time.h"

using namespace std;

namespace sdds
{
    bool debug = false; 
    int getTime()
    {
        int mins = -1;
        if (debug) {
            Time t(0);
            cout << "Enter current time: ";
            do {
                cin.clear();
                cin >> t; 
                if (!cin) {
                    cout << "Invlid time, try agian (HH:MM): ";
                    cin.clear();
                }
                else {
                    mins = int(t);
                }

                cin.ignore(1000, '\n');
            } while (mins < 0);
        }
        else {
            time_t t = time(NULL);
            tm lt = *localtime(&t);
            mins = lt.tm_hour * 60 + lt.tm_min;
        }

        return mins;
    }
//
    int getInt(const char* prompt)
    {
        int res;
        char ch;
        bool done = false;
        if (prompt) {
            cout << prompt;
        }
        while(!done){   
            cin >> res;

            if (cin.fail()) {
                cout << "Bad integer value, try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else {
                
                ch = cin.get();

                if (ch != '\n') {
                    cout << "Enter only an integer, try again: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else {
                    done = true;
                }

            }
        } 

        return res;
    }

    int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
    {
        int res = getInt(prompt);
        while (res < min || res > max) {
            if (errorMessage)
            {
                cout << errorMessage;
            }
            if (showRangeAtError)
            {
                cout << "[" << min << " <= value <= " << max << "]: ";
            }
            res = getInt();
        }
        return res;
    }

    char* getcstr(const char* prompt, std::istream& istr, char delimiter)
    {
        if (prompt) {
            cout << prompt;
        }
		string temp;
		char* str = nullptr;
		getline(istr, temp);
		str = new char[temp.length() + 2];
		strcpy(str, temp.c_str());
		str[temp.length()] = '\0';
		str[temp.length() + 1] = delimiter;
		return str;
	}

}