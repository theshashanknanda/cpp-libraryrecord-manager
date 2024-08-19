/*
 * Name: Shashank Nanda
 * Email: snanda9@myseneca.ca
 * Student Id: 145827234
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include <iostream>
#include <cstring>
#include "Menu.h"

namespace seneca
{
    MenuItem::MenuItem(const char *description)
    {
        int length = strlen(description);
        this->content = new char[length + 1];
        strcpy(this->content, description);
        this->content[length] = '\0';
    }

    MenuItem::~MenuItem()
    {
        delete[] this->content;
    }

    MenuItem::operator bool()
    {
        return this->content != nullptr;
    }

    MenuItem::operator const char *()
    {
        return this->content;
    }

    void MenuItem::display()
    {
        if(this->content != nullptr){
            std::cout << this->content;
        }
    }

    Menu::Menu(const char *title)
    {
        if(title != nullptr){
            this->title = new char[strlen(title) + 1];
            strcpy(this->title, title);
        }
    }

    Menu::~Menu(){
        delete[] this->title;
        for(int i = 0; i < MAX_MENU_ITEMS; i++){
            delete this->items[i];
        }
    }

    void Menu::displayTitle(std::ostream &os)
    {
        if (title != nullptr)
        {
            os << this->title;
        }
    }
    void Menu::displayMenu()
    {
        if (counter > 0)
        {
            if(title != nullptr){
                std::cout << this->title << std::endl;
            }
            int prevWidth = std::cout.width();
            int prevChar = std::cout.fill();

            for (int i = 0; i < this->counter; i++)
            {
                std::cout.fill(' ');
                std::cout.width(2);
                std::cout.setf(std::ios::right);
                std::cout << i + 1;
                std::cout.unsetf(std::ios::right);
                std::cout.width(prevWidth);
                std::cout.fill(prevChar);

                std::cout << "- " << items[i]->content << std::endl;
            }
            std::cout << " 0- Exit" << std::endl
                      << "> ";
        }
    }

    unsigned int Menu::run()
    {
        this->displayMenu();

        int selection;
        int flag = 0;

        do
        {
            std::cin >> selection;
            if (selection < 0 || selection > this->counter || std::cin.fail())
            {
                std::cout << "Invalid Selection, try again: ";
                flag = 1;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else
            {
                flag = 0;
            }
        } while (flag);

        return selection;
    }

    int Menu::operator~()
    {
        return this->run();
    }

    Menu &Menu::operator<<(const char *menuitemContent)
    {
        if (!(this->counter == MAX_MENU_ITEMS))
        {
            MenuItem *item = new MenuItem(menuitemContent);
            this->items[this->counter] = item;
            this->counter++;
        }

        return *this;
    }

    Menu::operator int()
    {
        return this->counter;
    }

    Menu::operator unsigned int()
    {
        return this->counter;
    }

    Menu::operator bool()
    {
        return this->counter > 1;
    }

    std::ostream &operator<<(std::ostream &os, Menu &menu)
    {
        menu.displayTitle(os);
        return os;
    }

    const char* Menu::operator[](int i) const
    {
        // using index + 1 to by pass division by zero in the first index during mod operation
        int indexToReturn;
        if (i == 0)
        {
            indexToReturn = (i + 1) % (this->counter);
            // decrementing by 1 to get the orignal index to fetch the element from the array
            indexToReturn--;
        }
        else
        {
            indexToReturn = (i) % (this->counter);
        }

        return this->items[indexToReturn]->content;
    }

    void Menu::setTitle(const char* title){
        this->title = new char[strlen(title)];
        strcpy(this->title, title);
    }
}
