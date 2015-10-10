#include "list.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

/*
Default constructor. It initializes the list to be empty.
*/
list::list()
{
	headByName = NULL;
	headByRating = NULL;
	size = 0;
}

/*
The list constructor with fileName as parameter.
Precondition: filename is the name of a file in the source code directory. 
Postcondition: headByName and headByRating are initialized to point to NULL. The file name is sent as the parameters of loadMemory. 
*/
list::list(const char fileName[])
{
	headByName = NULL;
	headByRating = NULL;
	loadMemory(fileName);
}

/*
Destructor.
*/
list ::~list()
{
	node *temp;
	while (headByName != NULL)
	{
		temp = headByName;
		headByName = headByName->nextByName;
		delete temp;
	}
}

/*
loadMemory opens and reads a line from the the file, loads it into a winery object, sends the address of that object to insertWinery, and repeats until the end of the file is reached.
Precondition: fileName is a char array containing the name of a file that exists in the program's  directory. It contains data in this format:
"name of winery (string);rating(float);year(int);acres(int);location(string) \n" for an unlimited number of lines.
Postcondition: Each line fills a winery object and is sent to insertWinery.
*/
void list::loadMemory(const char fileName[])
{
	ifstream inFile;
	winery item;
	char name[101];
	char location[101];
	int year, acres;
	float rating;

	inFile.open(fileName);
	if (inFile.good() != true)
	{
		cout << "The file " << fileName << " failed to open: "
			<< strerror(errno) //This shows the error if file fails to open.
			<< endl;
		return;
	}

	inFile.get(name, 101, ';');
	while (inFile.eof() != true)
	{
		inFile.ignore(100, ';');
		inFile >> rating;
		inFile.ignore(101, ';');
		inFile >> year;
		inFile.ignore(101, ';');
		inFile >> acres;
		inFile.ignore(101, ';');
		inFile.get(location, 101, '\n');
		inFile.ignore(100, '\n');

		item.setName(name); //item's set functions are called to fill the loadMemory's local char arrays
		item.setRating(rating);
		item.setLocation(location);
		item.setYear(year);
		item.setAcres(acres);

		insertWinery(item); //this insert function is called to put our node where it goes

		inFile.get(name, 101, ';'); //start reading next
	}
	inFile.close();
}

/*
insertWinery inserts a winery before the first matching name that it finds after traversing the list from headByName.
Precondition: newWinery is a winery object containing valid data. 
Postcondition: newWinery is linked to other nodes in order of rating and grouped by name. The list variable size is incremented by one.  
*/
void list::insertWinery(const winery &newWinery)
{
	char name[101];
	char currName[101];
	float rating, currRating;
	int acres, currAcres;
	node *curr, *prev, *curr2, *prev2, *newNode;

	newWinery.getName(name); //call getName to read name from newWinery into local char array
	rating = newWinery.getRating();
	acres = newWinery.getAcres();
	newNode = new node(newWinery); //a new node is initialized from the passed in winery object, and newNode now points to it.
	prev = NULL;
	prev2 = NULL;
	curr = headByName;
	curr2 = headByRating;

	while (curr != NULL)
	{
		curr->item.getName(currName); //Copy name from the node that curr is pointing at into a local char array.
		if (strcmp(name, currName) < 0) //If name and currName match, break the while loop.
		{
			break;
		}
		prev = curr; //prev now points to the same node that curr points to
		curr = curr->nextByName; //curr now points to the node the node it was just pointing to was linked to.
	}

	newNode->nextByName = curr; //the new node now links to the node that curr is pointing to

	while (curr2 != NULL)
	{
		currRating = curr2->item.getRating();
		currAcres = curr2->item.getAcres();
		if ((rating > currRating) || rating == currRating && acres <= currAcres)
		{
			break;
		}
		prev2 = curr2;
		curr2 = curr2->nextByRating;
	}
	newNode->nextByRating = curr2;

	if (prev == NULL) //if the while loop didn't execute, because headByName is still null (meaning the list is blank)...
	{
		headByName = newNode;
	}
	else //if prev does point to something...
	{
		prev->nextByName = newNode; //prev links to the new node. "The node pointed to by prev links to new node" so the previous node is linked to it now.
	}
	if (prev2 == NULL)
	{
		headByRating = newNode;
	}
	else
	{
		prev2->nextByRating = newNode;
	}
	prev = NULL;
	curr = headByName;
	while (curr != NULL)
	{
		prev = curr;
		curr = curr->nextByName;
	}
	prev2 = NULL;
	curr2 = headByRating;
	while (curr2 != NULL)
	{
		prev2 = curr2;
		curr2 = curr2->nextByRating;
	}
	size++;
}

/*
Removes a node with a "name" variable that matches the char array sent in.
Precondition: name is a char array that matches the name variable of at least one winery object.
Postcondition: The first winery object with a matching name is removed.
*/
void list::remove(const char name[])
{
	node *currPtr, *prevPtr, *prevPtr2, *currPtr2;
	char currName[101];
	int loopIndex = 0;

	currPtr = headByName;
	currPtr->item.getName(currName);
	if (strcmp(name, currName) != 0){
		for (loopIndex = 0; loopIndex > size; loopIndex++)
		{
			prevPtr = currPtr;
			currPtr = currPtr->nextByName;
			currPtr->item.getName(currName);

			if (strcmp(name, currName) == 0) //when match is found...
			{
				break;
			}
		}
		prevPtr->nextByName = currPtr->nextByName;
	}
	else{ //if headByName is the one being removed
		headByName = headByName->nextByName;
	}
	currPtr2 = headByRating;
	currPtr2->item.getName(currName);
	if (strcmp(name, currName) != 0){

		for (loopIndex = 0; loopIndex > size; loopIndex++)
		{
			prevPtr2 = currPtr2;
			currPtr2 = currPtr2->nextByRating;
			currPtr2->item.getName(currName);

			if (strcmp(name, currName) == 0)
			{
				break;
			}
		}
		prevPtr2->nextByRating = currPtr->nextByRating;
	}
	else{ //if headByRating is the one being removed
		headByRating = currPtr2->nextByRating;
	}
	delete currPtr;
}

/*
searchItem displays info for the winery passed to it and returns the number of times that "name" was matched.
Precondition: name is the name associated with a winery object, and data is a winery object.
Postcondition: The information on the winery object that matches the name entered is displayed in the console window.
*/
int list::searchItem(const char name[], winery &data) const
{
	node *curr; //a node pointer named curr is declared
	char currentName[101];
	char currentLocation[101];
	float currentRating;
	int currentYear, currentAcres;
	int loopIndex = 0;
	int matchIndex = 1;

	for (curr = headByName; curr != NULL; curr = curr->nextByName)
	{
		curr->item.getName(currentName);
		currentRating = curr->item.getRating();
		currentYear = curr->item.getYear();
		currentAcres = curr->item.getAcres();
		curr->item.getLocation(currentLocation);
		while (strcmp(name, currentName) == 0)
		{
			if (loopIndex == 0){
				cout << endl << "Here is the information on " << name << ": " << endl << endl;
			}

			data.setRating(currentRating);
			cout << "Rating: " << currentRating << endl;
			data.setYear(currentYear);
			cout << "First year of production: " << currentYear << endl;
			data.setAcres(currentAcres);
			cout << "Acres: " << currentAcres << endl;
			data.setLocation(currentLocation);
			cout << "Location: " << currentLocation << endl;
			matchIndex++;
			loopIndex++;
			break;
		}
	}
	if (matchIndex == 1){
		cout << endl << endl << "No matches were found for the winery name " << name << ". "
			<< endl << endl << "You will now be returned to the main menu." << endl << endl;
	}
	if (matchIndex > 1){
		cout << endl << "You will now be returned to the main menu." << endl << endl;
	}
	return matchIndex;
}

/*
displayListByName prints all winery items into the console window, with like-names next to each other.
Precondition: headByRating points to a winery object. 
*/
void list::displayListByName() const
{
	node *current;
	char name[101];
	float rating;
	int year;
	int acres;
	char location[101];

	cout << setw(20) << "NAME: " << setw(9) << "    RATING:" << setw(13) << "YEAR: " << setw(9) << "ACRES: " << setw(18) << "LOCATION: " << endl;
	for (current = headByName; current != NULL; current = current->nextByName)//first set current to headByName, then traverse the list until current points to nothing (the last nextByName points to null)
	{
		current->item.getName(name);
		rating = current->item.getRating(); //DO I NEED CHANGE THIS>
		year = current->item.getYear();
		acres = current->item.getAcres();
		current->item.getLocation(location);
		cout << setw(20) << name << setw(9) << rating << setw(13) << year << setw(9) << acres << setw(18) << location << endl;
	}
	cout << endl << "You will now be returned to the main menu." << endl << endl;
}

/*
displayListByName prints all winery items into the console window
Precondition: headByRating points to a winery object. 
*/
void list::displayListByRating() const
{
	node *current;
	char name[101];
	float rating;
	int year;
	int acres;
	char location[101];

	cout << setw(20) << "NAME: " << setw(9) << "    RATING: " << setw(13) << "YEAR: " << setw(9) << "ACRES: " << setw(18) << "LOCATION: " << endl;
	for (current = headByRating; current != NULL; current = current->nextByRating) //first set current to headByName, then traverse the list until current points to nothing (the last nextByName points to null)
	{
		current->item.getName(name);
		rating = current->item.getRating(); //DO I NEED &? COULD BE EASIER JUST PRINT
		year = current->item.getYear();
		acres = current->item.getAcres();
		current->item.getLocation(location);
		cout << setw(20) << name << setw(9) << rating << setw(13) << year << setw(9) << acres << setw(19) << location << endl;
	}
	cout << endl << "You will now be returned to the main menu." << endl << endl;
}

/*
saveAll retreives the winery info from each node and writes it to an output file.
Precondition: filename is a valid file name, including extention. 
Postcondition: If the file already exists, the data from all winery are saved to the file in their order by name. If the file doesn't exist, it is created in the source code directory. 
*/
void list::saveAll(const char fileName[]) const
{
	ofstream out;
	node *curr;
	char name[101];
	float rating;
	int year, acres;
	char location[101];

	out.open(fileName);
	if (out.good() != true)
	{
		cout << "The file " << fileName << " failed to open: "
			<< strerror(errno) //This shows the error if file fails to open.
			<< endl << endl;
		return;
	}

	for (curr = headByName; curr != NULL; curr = curr->nextByName) //curr is set to headByName, and as long as curr doesn't contain NULL (like the last node's nextByName does) the list continues
	{
		curr->item.getName(name); //winery variables are retreived from the node that curr points to to be printed into the output file
		curr->item.getLocation(location);

		out << name << ';' << curr->item.getRating() << ';' << curr->item.getYear() << ';' << curr->item.getAcres() << ';' << location << endl;
	}
	out.close();

	return;
}