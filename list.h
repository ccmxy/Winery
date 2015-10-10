#ifndef _LIST
#define _LIST
#include "winery.h"

class list
{
public:
        //constructors
       list();
       list( const char fileName[]);

        //destructor
       ~list();

        //accessor functions
        int searchItem( const char name[], winery &data) const;
        void displayListByName() const;
        void displayListByRating() const;
        void saveAll( const char fileName[]) const;

        //mutator functions
        void loadMemory( const char fileName[]);
        void insertWinery( const winery& newWinery);
        void remove( const char name[]);

private:
        struct node
       {
               winery item; //item is the winery object
               node *nextByName; //nextByName stores the address of the next node
               node *nextByRating;

               //constructor for node when winery item is passed in
              node( const winery& data)
              {
                      char name[101];
                      float rating;
                      char location[101];
                      int year;
                      int acres;

                      data.getName(name); //the winery item accesses getName, which copies the winery name from the instance variable into the allocated char array that was sent in from this function.
                     rating = data.getRating();
                      data.getLocation(location);
                     year = data.getYear();
                     acres = data.getAcres();
                     item.setName(name); //name is copied from the local char array into the winery item belonging to the node
                     item.setRating(rating);
                     item.setLocation(location);
                     item.setYear(year);
                     item.setAcres(acres);
                     nextByName = 0;
                     nextByRating = 0;
              }
       };
        node *headByName;
        node *headByRating;
        int size;
};

#endif
