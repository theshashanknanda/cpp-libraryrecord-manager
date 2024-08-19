#ifndef SENECA
#define SENECA
#include <iostream>

namespace seneca{
    class Streamable{
        public:
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& in) = 0;

        bool conIO(std::ios &i) const;

        virtual operator bool() const = 0;  
        virtual ~Streamable() = 0;

        // friend std::ostream& operator<<(std::ostream& os, const Streamable& streamable);
        // friend std::istream& operator>>(std::istream& in, const Streamable& streamable);
    };
}
#endif
