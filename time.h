#ifndef TIME_H
#define TIME_H
#include <string>
using namespace std;

//Note: Every date is assoicated with a custom indexnumber in ascending order in a custom txt file I created to keep track of the dates
class Time
{
private:
    string Currentdate;
    int index;
    string Currentdates[366];
    int IndexNum[366];
    const int sizeDates = 366;
    const int sizeIndex = 366;
    int numDays;
public:
////    CONSTRUCTORS   ////
    //default constructor
    Time(void);
     //parameterized consturctor
    Time(string theCurrentdate, int indexnumber);
////    INITIALIZE TIME DATABASE   ////
    int split (string str, char c, string array[], int size);   //split function
    int readDates(string filename);
    int helper_function_findthestartdate(string theCurrentdate);
////    TIME FUNCTION   ////
    string getCurrentdate(int indexnumber);
};
#endif