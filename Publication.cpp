/*
 * Name: Shashank Nanda
 * Email: snanda9@myseneca.ca
 * Student Id: 145827234
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#include <iostream>
#include <cstring>
#include <string>
#include "Lib.h"
#include "Streamable.h"
#include "Publication.h"

namespace seneca
{
    void Publication::set(int member_id)
    {
        this->m_membership = member_id;
    }

    void Publication::setRef(int value)
    {
        this->m_libRef = value;
    }

    void Publication::resetDate()
    {
        this->date.resetDate();
    }

    char Publication::type() const
    {
        return 'P';
    }

    bool Publication::onLoan() const
    {
        return this->m_membership != 0;
    }

    Date Publication::checkoutDate() const
    {
        return this->date;
    }

    bool Publication::operator==(const char *title) const
    {
        return strstr(this->m_title, title);
    }

    Publication::operator const char *() const
    {
        if(m_title != nullptr){
            return m_title;
        }else{
            return "";
        }
    }

    void Publication::setCheckoutDate(Date date){
        this->date = date;
    }

    int Publication::getRef() const
    {
        return this->m_libRef;
    }

    bool Publication::conIO(std::ios &io) const
    {
        return &io == &std::cout || &io == &std::cin;
    }

    void Publication::setMembership(int membership){
        this->m_membership = membership;
    }

    std::ostream &Publication::write(std::ostream &os) const
    {
        if (this->conIO(os))
        {
            os << "| ";
            os.width(4);
            os << this->m_shelfId;
            os << " | ";
            os.width(30);
            os.fill('.');
            os.setf(std::ios::left);
            
            int titlelen = strlen(this->m_title);
            if(titlelen > SENECA_TITLE_WIDTH){
                // print only trimmed name
                char temp[SENECA_TITLE_WIDTH + 1];
                strncpy(temp, this->m_title, SENECA_TITLE_WIDTH);

                os << temp;
            }else{
                // print the entire name
                os << this->m_title;
            }

            os << " | ";

            if (m_membership == 0)
            {
                os << " N/A ";
            }
            else
            {
                os << this->m_membership;
            }

            os << " | ";
            os << this->date;
            os << " |";
        }
        else
        {
            os
                << this->type() << '\t'
                << this->m_libRef << '\t'
                << this->m_shelfId << '\t'
                << this->m_title << '\t'
                << this->m_membership << '\t'
                << this->date;
        }
        return os;
    }

    std::istream &Publication::read(std::istream &istr)
    {
        char title[255];
        std::string titleFromFile;
        char shelfid[64];
        int membership = 0;
        int libref = -1;
        Date date;

        bool isConsole = false;

        delete[] this->m_title;

        if (conIO(istr))
        {
            isConsole = true;

            std::cout << "Shelf No: ";
            istr >> shelfid;

            if (strlen(shelfid) > SENECA_SHELF_ID_LEN)
            {
                istr.setstate(std::ios::failbit);
            }

            std::cout << "Title: ";
            istr.ignore();
            istr.getline(title, 255);

            std::cout << "Date: ";
            istr >> date;
        }
        else
        {
            isConsole = false;

            istr >> libref;
            istr.ignore(1, '\t');
            istr >> shelfid;
            istr.ignore(1, '\t');
            std::getline(istr, titleFromFile, '\t');
            // istr.ignore(1, '\t');
            istr >> membership;
            istr.ignore(1, '\t');
            istr >> date;
        }

        if (!date)
        {
            // in bad state
            istr.setstate(std::ios::failbit);
        }

        if (!istr.fail())
        {
            strcpy(this->m_shelfId, shelfid);
            this->m_membership = membership;
            this->m_libRef = libref;
            this->date = date;

            if (isConsole)
            {
                this->m_title = new char[strlen(title) + 1];
                strcpy(this->m_title, title);
            }
            else
            {
                this->m_title = new char[strlen(titleFromFile.c_str()) + 1];
                strcpy(this->m_title, titleFromFile.c_str());
            }


        }
        return istr;
    }

    Publication::operator bool() const
    {
        if (this->m_title != nullptr && strlen(this->m_shelfId) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    std::ostream &operator<<(std::ostream &os, const Streamable &streamable)
    {
        if (streamable.operator bool())
        {
            streamable.write(os);
        }
        return os;
    }

    std::istream &operator>>(std::istream &in, Streamable &streamable)
    {
        streamable.read(in);
        return in;
    }

    Publication::Publication()
    {
        this->m_title = nullptr;
        strcpy(this->m_shelfId, "");
        this->m_membership = 0;
        this->m_libRef = -1;
        this->date.resetDate();
    }

    Publication::~Publication()
    {
        delete[] this->m_title;
    }

    Publication::Publication(const Publication &publication)
    {
        strcpy(this->m_shelfId, publication.m_shelfId);
        this->m_membership = publication.m_membership;
        this->m_libRef = publication.m_libRef;

        this->m_title = new char[strlen(publication.m_title) + 1];
        strcpy(this->m_title, publication.m_title);
        this->date = publication.date;
    }

    Publication &Publication::operator=(const Publication &publication)
    {
        // check for objects being not same
        if (this != &publication)
        {
            if (publication)
            {
                // delete previous memory
                delete[] this->m_title;

                strcpy(this->m_shelfId, publication.m_shelfId);
                this->m_membership = publication.m_membership;
                this->m_libRef = publication.m_libRef;

                this->m_title = new char[strlen(publication.m_title) + 1];
                strcpy(this->m_title, publication.m_title);
                this->date = publication.date;
            }
        }
        return *this;
    }
}
