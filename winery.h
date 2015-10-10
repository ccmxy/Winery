#ifndef WINERY
#define WINERY

class winery
{
public:
        //constructor
       winery();

        //destructor
       ~winery();

        //accessor functions
        void getName( char name[]) const;
        float getRating( void) const;
        void getLocation( char location[]) const;
        int getYear( void) const;
        int getAcres( void) const;

        //mutator functions
        void setName( const char name[]);
        void setRating( float rating);
        void setLocation( const char location[]);
        void setYear( int year);
        void setAcres( int acres);

private:
        char *name;
        char *location;
        float rating;
        int year;
        int acres;
};

#endif
