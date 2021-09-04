
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "IOAble.h"

using namespace std;
namespace sdds {
    ostream& IOAble::csvWrite(ostream& os)const {
        return os;
    }

    istream& IOAble::csvRead(istream& is) {
        return is;
    }

    ostream& IOAble::write(ostream& os)const {
        return os;
    }

    istream& IOAble::read(istream& is) {
        return is;
    }
    std::ostream& operator<<(std::ostream& os, const IOAble& io) {
        return io.write(os);
    }

    std::istream& operator>>(std::istream& is, IOAble& io) {
        return io.read(is);
    }
}