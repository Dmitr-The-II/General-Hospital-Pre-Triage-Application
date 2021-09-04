
#ifndef SDDS_MENU_H_
#define SDDS_MENU_H_
using namespace std;
namespace sdds {
    class Menu {
        char* m_text{ nullptr }; 
        int m_noOfSel{ 0 };      
        void display() const;
    public:
        Menu(const char* MenuContent, int NoOfSelections);
        virtual ~Menu();
        int& operator>>(int& Selection);

        Menu(const Menu& Cpy);
        Menu& operator=(const Menu&) = delete;
    };
}
#endif //!SDDS_MENU_H_