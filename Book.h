#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include "Publication.h"

namespace seneca{
    class Book: public Publication{
        public:
        char *authorname;

        public:
        Book();
        Book(const Book& book);
        ~Book();

        char type() const;
        virtual void set(int member_id);
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& in);

        operator bool() const;
        Book &operator=(const Book& book);
    };
}
#endif