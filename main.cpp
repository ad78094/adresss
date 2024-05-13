addressBookType.cpp:

#include <iostream>
#include <fstream>
#include "addressBookType.h"
#include "extPersonType.h"

using namespace std;

void addressBookType::initEntries()
{
int length = 0;
ifstream inData;
inData.open("AddressBookData.txt");
string name1, name2, address1, address2, address3, phoneNum, relation;
int zip, bday1, bday2, bday3;

while (!inData.eof())
{
inData >> name1 >> name2;
inData >> bday1 >> bday2 >> bday3;
inData.get();
getline (inData, address1);
getline (inData, address2);
inData >> address3;
inData >> zip;
inData.get();
getline (inData, phoneNum);
inData >> relation;
extPersonType newEntry (name1, name2, bday1, bday2, bday3, address1, address2, address3, zip, phoneNum, relation);

addEntry(newEntry, length);
}
inData.close();
}


void addressBookType::addEntry(extPersonType newEntry, int &length)
{
maxLength = 500;

if (length < maxLength)
{
addressList[length] = newEntry;
length ++;
}
else
cout << "Address book full " << endl;
}

void addressBookType::print()
{
for (int i = 0; i < 6; i++)
{
addressList[i].print();
cout << endl;
}
}

void addressBookType::findPerson(string lastName)
{
for (int i = 0; i < 6; i++)
{
string foundName = addressList[i].getLastName();
if (foundName == lastName)
{
addressList[i].print();
cout << endl;
}
}
}

void addressBookType::findBirthdays(int month)
{
for (int i = 0; i < 6; i++)
{
int foundMonth = addressList[i].getBirthMonth();
if (foundMonth == month)
{
addressList[i].print();
cout << endl;
}
}
}

void addressBookType::findRelations(string relation)
{
for (int i = 0; i < 6; i++)
{
string foundRelation = addressList[i].getRelationship();
if (foundRelation == relation)
{
addressList[i].print();
cout << endl;
}
}
}

void addressBookType::sortEntries()
{
int current = 1;
while (current < 6)
{
int index = current;
bool placeFound = false;
while (index > 0 && !placeFound)
{
if (addressList[index].getLastName() < addressList[index-1].getLastName())
{
extPersonType temp = addressList[index];
addressList[index] = addressList[index-1];
addressList[index-1] = temp;
index --;
}
else
placeFound = true;
}
current ++;
}
}

addressBookType.h:

#ifndef ADDRESSBOOKTYPE_H_INCLUDED
#define ADDRESSBOOKTYPE_H_INCLUDED

#include "extPersonType.h"

class addressBookType
{
public:
void addEntry(extPersonType, int&);
//this function checks that the length has not exceeded the
// maxLength, adds a new extPersonType entry to the addressList
//this function should also call sortEntries function each time
// a new entry is added to addressList
//postcondition: length is incremented

void findPerson(string);
//this function finds a person entry given last name and prints
// the entry for the person if found
//postcondition: output the entry if found in addressList with
// the given last name

void findBirthdays(int);
//this function finds a person entry given the month number and
// prints the entry for each person found with that birthmonth
//postcondition: output the entries found in adressList with the
// given birthmonth

void findRelations(string);
//this function finds a person entry given the relationship and
// prints the entries for each person with that relationship
//postconditon: output the entries found in addressList with the
// given relationship

void print();
//this function prints all entries in the addressList array

void sortEntries();
//this function is called in addEntry and sorts the new entry
// compared to the other entries already in the addressList
//postconditon: updates the location of the new entry

void initEntries();
//this function adds an entry to addressList from the file when
// called from the menu


private:
extPersonType newEntry;
personType person;
addressType address;
dateType birthdate;
extPersonType addressList[500];
int length;
int maxLength;
};

#endif

addressType.cpp:

#include <iostream>
#include "addressType.h"

using namespace std;

void addressType::setAddress (string address)
{
dAddress = address;
}

void addressType::setCity (string city)
{
dCity = city;
}

void addressType::setState (string state)
{
if (state.length() > 2)
dState = "XX";
else
dState = state;
}

void addressType::setZipcode (int zipcode)
{
if (11111 <= zipcode && zipcode <= 99999)
dZipcode = zipcode;
else
dZipcode = 10000;
}

string addressType::getAddress ()
{
return dAddress;
}

string addressType::getCity()
{
return dCity;
}

string addressType::getState()
{
return dState;
}

int addressType::getZipcode()
{
return dZipcode;
}

void addressType::print()
{
cout << dAddress << endl;
cout << dCity << ", " << dState << " " << dZipcode << endl;
}

//constructor with paramaters
addressType::addressType (string address, string city, string state, int zipcode)
{
dAddress = address;
dCity = city;

if (state.length() > 2)
dState = "XX";
else
dState = state;

if (11111 <= zipcode && zipcode <= 99999)
dZipcode = zipcode;
else
dZipcode = 10000;
}

addressType.h:

#ifndef ADRESSTYPE_H_INCLUDED
#define ADRESSTYPE_H_INCLUDED

using namespace std;

class addressType
{
public:
void setAddress (string address);
//this function sets the address
//postcondition: dAddress = address

void setCity (string city);
//this function sets the city
//postcondition: dCity = address

void setState (string state);
//this function sets the state, checking for valid value length
//postcondition: dState = state

void setZipcode (int zipcode);
//this function sets the zipcode, checking for valid input value
//postcondition: dZipcode = zipcode

string getAddress();
//this function returns the address
//postcondition: the value of dAddress is returned

string getCity ();
//this function returns the city
//postcondition: the value of dCity is returned

string getState ();
//this function returns the state
//postconditon: the value of dState is returned

int getZipcode ();
//this function returns the value of zipcode
//postcondition: the value of dZipcode is returned

void print ();
//function to output the address on line one, and on the next line
//output the city, state zipcode in that format

addressType (string address = "", string city = "", string state = "XX", int zipcode = 10000);
//this is the constructor with default values assigned
//postcondition: if no values are given for dAddress, dCity,
// dState, or dZipcode, the default values will be set

private:
string dAddress; //variable to store the address
string dCity; //variable to store the city
string dState; //variable to store the state
int dZipcode; //variable to store the zipcode
};

#endif // ADRESSTYPE_H_INCLUDED
dateType.cpp:

//Implementation file date

#include <iostream>
#include "dateType.h"

using namespace std;

void dateType::setDate(int month, int day, int year)
{
if (year >= 1900)
dYear = year;
else
dYear = 1900;

if (1 <= month && month < 12)
dMonth = month;
else
dMonth = 1;

if (1 <= day && day <= 28)
{
dDay = day;
}
else if (day == 29)
{
if (month == 2 && isLeapYear(year))
dDay = day;
else if (month != 2)
dDay = day;
else
dDay = 1;
}
else if ((day == 30) && ((month == 4) || (month == 5) || (month == 6) || (month == 9) || (month == 11)))
{
dDay = day;
}
else if ((day == 31) && ((month == 1) || (month == 3) || (month == 7) || (month == 8) || (month == 10) || (month == 12)))
{
dDay = day;
}
else
dDay = 1;
}

int dateType::getDay() const
{
return dDay;
}

int dateType::getMonth() const
{
return dMonth;
}

int dateType::getYear() const
{
return dYear;
}

void dateType::print() const
{
cout << dMonth << "-" << dDay << "-" << dYear;
}

bool dateType::isLeapYear(int year)
{
if ((year % 4 == 0) && (year %100 == 0))
return true;
else if ((year %100 == 0) && (year %400 == 0))
return true;
else if (year %400 == 0)
return true;
else
return false;
}

//Constructor with parameters
dateType::dateType(int month, int day, int year)
{
dateType::setDate(month, day, year);
dMonth = month;
dDay = day;
dYear = year;

}

dateType.h:

#ifndef dateType_H
#define dateType_H

class dateType
{
public:
void setDate(int month, int day, int year);
//Function to set the date.
//The member variables dMonth, dDay, and dYear are set
//according to the parameters.
//Postcondition: dMonth = month; dDay = day;
// dYear = year

int getDay() const;
//Function to return the day.
//Postcondition: The value of dDay is returned.

int getMonth() const;
//Function to return the month.
//Postcondition: The value of dMonth is returned.

int getYear() const;
//Function to return the year.
//Postcondition: The value of dYear is returned.

void print() const;
//Function to output the date in the form mm-dd-yyyy.

bool isLeapYear(int year);
//checks if the year is a leap year and returns true/false

dateType(int month = 1, int day = 1, int year = 1900);
//Constructor to set the date
//The member variables dMonth, dDay, and dYear are set
//according to the parameters.
//Postcondition: dMonth = month; dDay = day; dYear = year;
// If no values are specified, the default
// values are used to initialize the member
// variables.

private:
int dMonth; //variable to store the month
int dDay; //variable to store the day
int dYear; //variable to store the year
};

#endif

extPersonType.cpp:

#include <iostream>
#include "extPersonType.h"
#include "addressType.h"
#include "dateType.h"

using namespace std;

void extPersonType::setPhoneNumber (string phoneNumber)
{
number = phoneNumber;
}

string extPersonType::getPhoneNumber ()
{
return number;
}

void extPersonType::setRelationship (string relationship)
{
if (relationship == "Friend" || relationship == "Family" || relationship == "Business")
dRelationship = relationship;
else
dRelationship = "None";
}

string extPersonType::getRelationship()
{
return dRelationship;
}

int extPersonType::getBirthMonth()
{
int birthMonth = birthdate.getMonth();
return birthMonth;
}

void extPersonType::print()
{
personType::print();
cout << endl;
address.print();
cout << number << endl;
cout << "Birthday: ";
birthdate.print();
cout << endl;
cout << "Relationship: " << dRelationship << endl;
}

extPersonType::extPersonType (string first, string last, int month, int day, int year, string address, string city, string state, int zipcode, string phoneNumber, string relationship) : personType (first, last), address (address, city, state, zipcode), birthdate (month, day, year)
{
number = phoneNumber;
if (relationship == "Friend" || relationship == "Family" || relationship == "Business")
dRelationship = relationship;
else
dRelationship = "None";
}

extPersonType.h:

#ifndef extPersonType_H
#define extPersonType_H

#include "personType.h"
#include "addressType.h"
#include "dateType.h"

class extPersonType: public personType
{
public:
void setPhoneNumber (string phoneNumber);
//this function sets the phone number
//postcondition: number = phoneNumber

string getPhoneNumber ();
//this function returns the phone number
//postcondition: the value of phoneNumber is returned

void setRelationship (string relationship);
//this function sets the relationship
//postcondition: dRelationship = relationship

string getRelationship();
//this function returns the relationship
//postcondition: the value of relationship is returned

int getBirthMonth ();
//this function gets birth month from dateType function
//postcondition: the value of birthMonth is returned

void print();
//This function prints the values for name (first last)
//birthdate (mm-dd-yyyy), address (address /n city, state
//zipcode), phone number (XXX-XXX-XXXX), and relationship

extPersonType (string first = "", string last = "", int month = 1, int day = 1, int year = 1900, string address = "", string city = "", string state = "XX", int zipcode = 10000, string phoneNumber = "None", string relationship = "None");

private:
addressType address;
dateType birthdate;
string number;
string dRelationship;

};

#endif

personType.cpp:

//personType.cpp

#include <iostream>
#include <string>
#include "personType.h"

using namespace std;

void personType::setFirstName(string name)
{
firstName = name;
}

void personType::setLastName(string name)
{
lastName = name;
}

string personType::getFirstName() const
{
return firstName;
}

string personType::getLastName() const
{
return lastName;
}

void personType::print() const
{
cout << firstName << " " << lastName;
}

personType::personType(string first, string last)

{
firstName = first;
lastName = last;
}
personType.h:

// personType.h

#ifndef PERSONTYPE_H
#define PERSONTYPE_H

#include <string>

using namespace std;

class personType
{
public:
// Getters and setters
void setFirstName(string);
void setLastName(string);
string getFirstName() const;
string getLastName() const;

void print() const;
//Postcondition: outputs the first name and last name
//in the form firstName lastName.

personType(string first = "", string last = "");
//Constructor
//Sets firstName and lastName according to the parameters.
//The default values of the parameters are null strings.
//Postcondition: firstName = first; lastName = last

private:
string firstName; //variable to store the first name
string lastName; //variable to store the last name
};

#endif
main.cpp​​​​​​​:

#include <iostream>
#include "addressBookType.h"

using namespace std;

int main()
{
int choice = 0;
string relation;
string lastName;
int birthMonth;
addressBookType newEntry;

do
{
cout << "MAIN MENU" << endl;
cout << endl;
cout << "Select an option " << endl;
cout << "1 - Get entries from data file" << endl;
cout << "2 - Find entry by last name" << endl;
cout << "3 - Find entry by birth month" << endl;
cout << "4 - Find entry by relationship" << endl;
cout << "5 - Print entire address book" << endl;
cout << "6 - Quit" << endl;
cin >> choice;

switch (choice)
{
case 1:
newEntry.initEntries();
newEntry.sortEntries();
break;
case 2:
cout << "Enter last name: ";
cin >> lastName;
newEntry.findPerson(lastName);
break;
case 3:
cout << "Enter birth month: ";
cin >> birthMonth;
newEntry.findBirthdays(birthMonth);
break;
case 4:
cout << "Enter relationship: ";
cin >> relation;
newEntry.findRelations(relation);
break;
case 5:
newEntry.print();
break;
case 6:
break;
default:
cout << "Invalid choice" << endl;
}
} while (choice != 6);


return 0;
}
