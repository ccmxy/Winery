#include "winery.h"
#include <iostream>

/*
Default constructor
*/
winery::winery()
{
	name = new char[strlen("no name") + 1]; //name now contains address of an uninitalized char array of 10 chars
	strcpy(name, "no name"); //"no name" + null char are copied into the contents of the char array that name points to
	location = new char[strlen("no location") + 1];
	strcpy(location, "no location");
	rating = 0;
	year = 0;
	acres = 0;
}

/*
Destructor.
*/
winery::~winery()
{
	if (name != NULL)
		delete[] name;
	if (location != NULL)
		delete[] location;
}

/*
The getVariable functions copy from the instance variable into char variables that are sent in.
*/
void winery::getName(char name[]) const
{
	strcpy(name, this->name);
}

float winery::getRating(void) const
{
	return rating;
}

void winery::getLocation(char location[]) const
{
	strcpy(location, this->location);
}

int winery::getYear(void) const
{
	return year;
}

int winery::getAcres(void) const
{
	return acres;
}

/*
The setVariable functions delete the default array of the instance variables, allocate one of the proper size, and load it with the contents of the array passed into it.
*/
void winery::setName(const char name[])
{
	if (this->name != NULL){ //deletes the "no name" chars in the instance variable
		delete[] this->name; //calls the destructor
	}
	this->name = new char[strlen(name) + 1]; //allocates a char array the length of the "name" array passed in + 1 for null char
	strcpy(this->name, name); //copies the name array passed into it into the instance variable
}

void winery::setRating(float rating)
{
	this->rating = rating;
}

void winery::setLocation(const char location[])
{
	if (this->location != NULL){
		delete[] this->location;
	}
	this->location = new char[strlen(location) + 1];
	strcpy(this->location, location);
}

void winery::setYear(int year)
{
	this->year = year;
}

void winery::setAcres(int acres)
{
	this->acres = acres;
}