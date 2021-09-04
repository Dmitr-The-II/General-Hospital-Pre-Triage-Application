
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include <iostream>
#include "Menu.h"
#include "utils.h"

using namespace std;

namespace sdds {
    Menu::Menu(const char* MenuContent, int NoOfSelections) {
        m_text = new char[strlen(MenuContent) + 1];
        strcpy(m_text, MenuContent);
        m_noOfSel = NoOfSelections;
    }

    Menu::~Menu() {
        delete[] m_text;
        m_text = nullptr;
    }

    void Menu::display() const {
        cout << m_text << endl << "0- Exit" << endl;
    }

    int& Menu::operator>>(int& Selection) {
        display();
        return Selection = getInt(0, m_noOfSel, "> ", "Invalid option ");
    }

    Menu::Menu(const Menu& Cpy) {
        if(Cpy.m_text) {
            this->m_text = new char[strlen(Cpy.m_text) + 1];
            strcpy(this->m_text, Cpy.m_text);
            this->m_noOfSel = Cpy.m_noOfSel;
        }
    }
}