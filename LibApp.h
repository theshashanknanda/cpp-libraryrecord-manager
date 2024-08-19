#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H

#include "Menu.h"
#include "Publication.h"
#include "Lib.h"

namespace seneca
{
   class LibApp
   {
   private:
      Publication *m_publications[SENECA_LIBRARY_CAPACITY];
      Menu m_mainMenu;
      Menu m_exitMenu;
      Menu m_publicationTypeMenu;

      char m_fileName[256];
      int m_loadedPublications;
      int m_lastLibraryReferenceNumber;

      bool m_changed;

      bool confirm(const char *message);

      void load();   // prints: "Loading Data"<NEWLINE>
      void save();   // prints: "Saving Data"<NEWLINE>
      int search(int searchType = 0); // prints: "Searching for publication"<NEWLINE>

      void returnPub(); /*  Calls the search() method.
                            prints "Returning publication"<NEWLINE>
                            prints "Publication returned"<NEWLINE>
                            sets m_changed to true;
                        */

      void newPublication();
      void removePublication();
      void checkOutPub();

      Publication* getPub(int libRef);

   public:
   // constructors
      LibApp(const char *filename);

      // run method
      void run();
   };
}
#endif // !SENECA_LIBAPP_H
