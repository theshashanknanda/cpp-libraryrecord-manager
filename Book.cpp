#include <iostream>
#include <cstring>
#include <string>
#include "Book.h"
#include "Lib.h"

namespace seneca{
    Book::Book(){
        this->authorname = nullptr;
    }

    Book::~Book(){
        delete[] this->authorname;
    }

    Book::Book(const Book& book): Publication(book){
        strcpy(this->authorname, book.authorname);
    }

    Book& Book::operator=(const Book& book){
        if (this != &book)
        {
            if(book){
                // call base class operator
                (Publication&)*this = book;

                // delete previous memory
                delete[] this->authorname;
                this->authorname = new char[strlen(book.authorname) + 1];
                strcpy(this->authorname, book.authorname);
            }
        }
        return *this;
    }

    char Book::type() const{
        return 'B';
    }

    std::ostream& Book::write(std::ostream& os) const{
        Publication::write(os);

        if(this->conIO(os)){
            os << " ";
            int authorlen = strlen(this->authorname);
            os.width(SENECA_AUTHOR_WIDTH);
            os.fill(' ');
            if(authorlen > SENECA_AUTHOR_WIDTH){
                // print only trimmed name
                char temp[SENECA_AUTHOR_WIDTH + 1];
                strncpy(temp, this->authorname, SENECA_AUTHOR_WIDTH);

                os << temp;
            }else{
                // print the entire name
                os << this->authorname;
            }
            os << " |";
        }else{
            os << '\t';
            os << this->authorname;
        }

        return os;
    }

    std::istream& Book::read(std::istream& in){
        Publication::read(in);

        delete[] this->authorname;

        char tempauthor[255];
        if(conIO(in)){
            std::cout << "Author: ";
            in.ignore(1, '\n');
            in.getline(tempauthor, 255);
        }else{
            std::streampos initial_pos = in.tellg();

            std::string temp;
            in.ignore(1, '\t');
            std::getline(in, temp, '\n');
            strcpy(tempauthor, temp.c_str());

            // in.seekg(initial_pos);
        }

        if(!in.fail()){
            this->authorname = new char[strlen(tempauthor) + 1];
            strcpy(this->authorname, tempauthor);
        }

        return in;
    }

    void Book::set(int member_id){
        Publication::set(member_id);

        this->resetDate();
    }

    Book::operator bool() const{
        if((this->authorname != nullptr) && (strlen(this->authorname) > 0)
        && (Publication::operator bool())){
            return true;
        }
        else{
            return false;
        }
    }
}
