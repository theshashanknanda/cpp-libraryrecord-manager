#ifndef SENECA_PUBLICATION_H
#define SENECA_PUBLICATION_H

#include <iostream>
#include "Date.h"
#include "Streamable.h"

namespace seneca
{
    class Publication: public Streamable
    {
        char *m_title;
        char m_shelfId[4 + 1];
        int m_membership;
        int m_libRef;
        Date date;

    public:
        Publication();
        ~Publication();

        // METHODS
        virtual void set(int member_id);
        // Sets the membership attribute to either zero or a five-digit integer.
        void setRef(int value);
        // Sets the **libRef** attribute value
        void resetDate();
        // Sets the date to the current date of the system.

        // QUERIES
        virtual char type() const;
        // Returns the character 'P' to identify this object as a "Publication object"
        bool onLoan() const;
        // Returns true is the publication is checkout (membership is non-zero)
        Date checkoutDate() const;
        // Returns the date attribute
        bool operator==(const char *title) const;
        // Returns true if the argument title appears anywhere in the title of the
        // publication. Otherwise, it returns false; (use strstr() function in <cstring>)
        operator const char *() const;
        // Returns the title attribute
        int getRef() const;
        // Returns the libRef attirbute.

        void setMembership(int membership);
        void setCheckoutDate(Date date);

        // STREAMABLE IMPLEMENATION FUNCTIONS
        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& in);

        bool conIO(std::ios &i) const;

        operator bool() const;

        // copy assignment & copy constructor
        Publication(const Publication& publication);
        Publication& operator=(const Publication& publication);
    };

    std::ostream& operator<<(std::ostream& os,const Streamable& streamable);
    std::istream& operator>>(std::istream& in, Streamable& streamable);
}

#endif