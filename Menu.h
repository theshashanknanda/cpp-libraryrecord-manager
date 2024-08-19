/*
 * Name: Shashank Nanda
 * Email: snanda9@myseneca.ca
 * Student Id: 145827234
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>
#include <cstring>

const unsigned int MAX_MENU_ITEMS = 20;

namespace seneca{
    class Menu;

    class MenuItem{
        friend class Menu;

        private:
        char *content;

        MenuItem(const char *description = nullptr);
        ~MenuItem();

        MenuItem(MenuItem &menu) = delete;
        MenuItem operator=(MenuItem m) = delete;

        operator bool();

        operator const char*();

        void display();
    };

    class Menu{
        Menu(Menu &menu) = delete;
        Menu operator=(Menu menu) = delete;

        private:
        char *title = nullptr;
        int counter = 0;
        MenuItem *items[MAX_MENU_ITEMS]{nullptr};

        public:
        Menu(const char *title = nullptr);
        ~Menu();

        void displayTitle(std::ostream& os);
        void displayMenu();

        unsigned int run();
        int operator~();
        Menu& operator<<(const char* menuitemContent);
        Menu& operator<<(char *content);
        operator int();
        operator unsigned int();
        operator bool();
        const char* operator[](int i) const;
        void setTitle(const char*);
    };

    std::ostream& operator<<(std::ostream& os, Menu &menu);
}

#endif