
#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H
#include <iostream>
namespace sdds {
    class IOAble {
    public:
        virtual std::ostream& csvWrite(std::ostream& os) const = 0;
        virtual std::istream& csvRead(std::istream& is) = 0;
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual ~IOAble() {};
    };
    std::ostream& operator<<(std::ostream& os, const IOAble& io);
    std::istream& operator>>(std::istream& is, IOAble& io);
}
#endif // !SDDS_IOABLE_H