/*
 * Name: Shashank Nanda
 * Email: snanda9@myseneca.ca
 * Student Id: 145827234
 * I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "LibApp.h"
#include "Menu.h"
#include "Book.h"
#include "PublicationSelector.h"

namespace seneca
{
    bool LibApp::confirm(const char *message)
    {
        Menu m(message);
        m << "Yes";

        return m.run();
    }

    void LibApp::load()
    {
        std::cout << "Loading Data" << std::endl;

        char type{};
        std::ifstream infile(this->m_fileName);
        for (int i = 0; infile; i++)
        {
            infile >> type;

            if (infile)
            {
                if (type == 'P')
                {
                    this->m_publications[i] = new Publication;
                }
                else if (type == 'B')
                {
                    this->m_publications[i] = new Book;
                }

                if (this->m_publications[i])
                {
                    infile >> *this->m_publications[i];

                    this->m_loadedPublications++;
                    this->m_lastLibraryReferenceNumber = this->m_publications[i]->getRef();
                }
            }
        }
    }

    void LibApp::save()
    {
        std::cout << "Saving Data" << std::endl;

        std::ofstream outFile(this->m_fileName);

        for (int i = 0; i < this->m_loadedPublications; i++)
        {
            if (this->m_publications[i]->getRef() != 0)
            {
                outFile << *this->m_publications[i] << std::endl;
            }
        }
    }

    int LibApp::search(int searchType)
    {
        PublicationSelector ps("Select one of the following found matches:", 15);

        char titleToSearch[256];

        int selectionType = this->m_publicationTypeMenu.run();
        std::cout << "Publication Title: ";
        // std::cin >> titleToSearch;
        std::cin.ignore();
        std::cin.getline(titleToSearch, sizeof(titleToSearch));

        if (selectionType == 0)
        {
            std::cout << "Aborted!";
            return -1;
        }
        else
        {
            switch (searchType)
            {
            case 1:
                // search all
                for (int i = 0; i < this->m_loadedPublications; i++)
                {
                    if (this->m_publications[i]->getRef() != 0)
                    {
                        if ((strstr(*this->m_publications[i], titleToSearch)))
                        {
                            if ((this->m_publications[i]->type() == 'B' && selectionType == 1) || (this->m_publications[i]->type() == 'P' && selectionType == 2))
                            {
                                ps << this->m_publications[i];
                            }
                        }
                    }
                }

                if (ps)
                {
                    ps.sort();
                    int ref = ps.run();

                    return ref;
                }
                else
                {
                    std::cout << "No matches found!" << std::endl;

                    return -1;
                }

                break;
            case 2:
                // search publications on loan
                for (int i = 0; i < this->m_loadedPublications; i++)
                {
                    if (this->m_publications[i]->getRef() != 0)
                    {
                        if (this->m_publications[i]->onLoan())
                        {
                            if ((strstr(*this->m_publications[i], titleToSearch)))
                            {
                                if ((this->m_publications[i]->type() == 'B' && selectionType == 1) || (this->m_publications[i]->type() == 'P' && selectionType == 2))
                                {
                                    ps << this->m_publications[i];
                                }
                            }
                        }
                    }
                }

                if (ps)
                {
                    ps.sort();
                    int ref = ps.run();

                    return ref;
                }
                else
                {
                    std::cout << "No matches found!" << std::endl;

                    return -1;
                }

                break;
            case 3:
                // search available publications
                for (int i = 0; i < this->m_loadedPublications; i++)
                {
                    if (this->m_publications[i]->getRef() != 0)
                    {
                        if (!(this->m_publications[i]->onLoan()))
                        {
                            if ((strstr(*this->m_publications[i], titleToSearch)))
                            {
                                if ((this->m_publications[i]->type() == 'B' && selectionType == 1) || (this->m_publications[i]->type() == 'P' && selectionType == 2))
                                {
                                    ps << this->m_publications[i];
                                }
                            }
                        }
                    }
                }

                if (ps)
                {
                    ps.sort();
                    int ref = ps.run();

                    return ref;
                }
                else
                {
                    std::cout << "No matches found!" << std::endl;

                    return -1;
                }
                break;
            }
            return -1;
        }
    }

    Publication *LibApp::getPub(int libRef)
    {
        int ref = -1;
        for (int i = 0; i < this->m_loadedPublications; i++)
        {
            if (this->m_publications[i]->getRef() == libRef)
            {
                return this->m_publications[i];
            }
        }

        // double check in future
        return nullptr;
    }

    void LibApp::returnPub()
    {
        std::cout << "Return publication to the library" << std::endl;
        int selectedRef = this->search(2);

        if(selectedRef == 0){
            std::cout << "Aborted!" << std::endl;
            return;
        }

        for (int i = 0; i < this->m_loadedPublications; i++)
        {
            if (selectedRef == this->m_publications[i]->getRef())
            {
                std::cout << *this->m_publications[i] << std::endl;
            }
        }

        if (this->confirm("Return Publication?"))
        {
            for (int i = 0; i < this->m_loadedPublications; i++)
            {
                if (this->m_publications[i]->getRef() == selectedRef)
                {
                    int daysSinceCheckOut = Date() - this->m_publications[i]->checkoutDate();
                    if (daysSinceCheckOut > 15)
                    {
                        int penaltyDays = daysSinceCheckOut - 15;
                        double penalty = penaltyDays * 0.50;

                        std::cout << std::fixed << std::setprecision(2);
                        std::cout << "Please pay $" << penalty << " penalty for being " << penaltyDays << " days late!" << std::endl;
                    }

                    this->m_publications[i]->setMembership(0);
                    this->m_changed = true;

                    if(this->m_publications[i]->type() == 'B'){
                        this->m_publications[i]->setCheckoutDate(Date());
                    }

                    std::cout << "Publication returned" << std::endl;
                }
            }
        }
    }

    void LibApp::newPublication()
    {
        if (this->m_loadedPublications == SENECA_LIBRARY_CAPACITY)
        {
            std::cout << "Library is at its maximum capacity!" << std::endl;
            return;
        }
        else
        {
            std::cout << "Adding new publication to the library" << std::endl;

            Publication *publication;

            int selectionType = this->m_publicationTypeMenu.run();
            if (selectionType == 1)
            {
                publication = new Book();
            }
            else if (selectionType == 2)
            {
                publication = new Publication();
            }else if(selectionType == 0){
                std::cout << "Aborted!" << std::endl;
                return;
            }

            std::cin >> *publication;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Aborted!";
            }
            else
            {
                int selection = this->confirm("Add this publication to the library?");
                if (selection)
                {
                    if (publication)
                    {
                        if (publication == nullptr)
                        {
                            std::cout << "nullptr";
                        }

                        this->m_lastLibraryReferenceNumber++;
                        publication->setRef(this->m_lastLibraryReferenceNumber);
                        this->m_publications[this->m_loadedPublications] = publication;
                        this->m_loadedPublications++;

                        this->m_changed = true;

                        std::cout << "Publication added" << std::endl;
                    }
                    else
                    {
                        std::cout << "Failed to add publication!";
                        delete publication;
                    }
                }
                else
                {
                    std::cout << "Aborted!";
                    return;
                }
            }
        }
    }

    void LibApp::removePublication()
    {
        std::cout << "Removing publication from the library" << std::endl;

        int selectedRef = this->search(1);
        if(selectedRef == 0){
            std::cout << "Aborted!" << std::endl;
            return;
        }

        for (int i = 0; i < this->m_loadedPublications; i++)
        {
            if (selectedRef == this->m_publications[i]->getRef())
            {
                std::cout << *this->m_publications[i] << std::endl;
            }
        }

        if (this->confirm("Remove this publication from the library?"))
        {
            for (int i = 0; i < this->m_loadedPublications; i++)
            {
                if (selectedRef == this->m_publications[i]->getRef())
                {
                    this->m_publications[i]->setRef(0);
                    this->m_changed = true;
                    std::cout << "Publication removed" << std::endl;
                }
            }
        }
    }

    void LibApp::checkOutPub()
    {
        std::cout << "Checkout publication from the library" << std::endl;
        int selectedRef = this->search(3);
        for (int i = 0; i < this->m_loadedPublications; i++)
        {
            if (selectedRef == this->m_publications[i]->getRef())
            {
                std::cout << *this->m_publications[i] << std::endl;
            }
        }

        if(selectedRef == -1){
            return;
        }

        if (this->confirm("Check out publication?"))
        {
            int number;
            std::cout << "Enter Membership number: ";
            do
            {
                std::cin >> number;

                if (number < 10000 || number > 99999)
                {
                    std::cout << "Invalid membership number, try again: ";
                }
            } while (number < 10000 || number > 99999);

            for (int i = 0; i < this->m_loadedPublications; i++)
            {
                if (selectedRef == this->m_publications[i]->getRef())
                {
                    this->m_publications[i]->setMembership(number);
                    this->m_changed = true;

                    this->m_publications[i]->setCheckoutDate(Date());

                    std::cout << "Publication checked out" << std::endl;
                }
            }
        }
    }

    LibApp::LibApp(const char *filename)
    {
        strcpy(this->m_fileName, filename);
        this->m_fileName[strlen(this->m_fileName)] = '\0';

        this->m_changed = false;

        this->m_mainMenu.setTitle("Seneca Library Application");
        this->m_mainMenu << "Add New Publication";
        this->m_mainMenu << "Remove Publication";
        this->m_mainMenu << "Checkout publication from library";
        this->m_mainMenu << "Return publication to library";

        this->m_exitMenu.setTitle("Changes have been made to the data, what would you like to do?");
        this->m_exitMenu << "Save changes and exit";
        this->m_exitMenu << "Cancel and go back to the main menu";

        this->m_publicationTypeMenu.setTitle("Choose the type of publication:");
        this->m_publicationTypeMenu << "Book";
        this->m_publicationTypeMenu << "Publication";

        this->load();
    }

    void LibApp::run()
    {
        int main_run_flag = 1;
        int exit_run_flag = 0;
        int final_exit_flag = 1;
        do
        {
            main_run_flag = this->m_mainMenu.run();

            switch (main_run_flag)
            {
            case 1:
                this->newPublication();
                break;
            case 2:
                this->removePublication();
                break;
            case 3:
                this->checkOutPub();
                break;
            case 4:
                this->returnPub();
                break;
            default:
                if (this->m_changed)
                {
                    exit_run_flag = this->m_exitMenu.run();
                    switch (exit_run_flag)
                    {
                    case 1:
                        exit_run_flag = 0;
                        this->save();
                        break;
                    case 0:
                        final_exit_flag = this->confirm("This will discard all the changes are you sure?");
                    default:
                        // do nothing
                        break;
                    }
                }
                else
                {
                    // do nothing
                }
                break;
            }
            std::cout << std::endl;
        } while (main_run_flag || exit_run_flag || !final_exit_flag);

        // goodbye message
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Thanks for using Seneca Library Application" << std::endl;
    }
}
