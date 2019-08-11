#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "time.h"
using namespace std;
////////////////////////////            CONSTRUCTORS          ////////////////////////////
Time::Time(void)
{
    Currentdate = "";
    index = 0;     //default
    numDays = 366;
};
Time::Time(string theCurrentdate, int indexnumber)
{
    Currentdate = theCurrentdate;
    index = indexnumber;
};
////////////////////////////            INITIALIZE TIME DATABASE           ////////////////////////////
int Time::split(string str, char c, string array[], int size)
{
//  str is a line of data
//  char c is the delimeter
    if (str.length() == 0) 
    {
         return 0;
    }
    string word = "";
    int count = 0;
    str = str + c;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            if (word.length() == 0)
                continue;
            array[count++] = word;
            word = "";
        } else {
            word = word + str[i];
        }
    }
    return count;
};
int Time::readDates(string readfilename)
{
    char c = ',';
    string str = "";
    string temp_array[2];
    int size = 366;
    ifstream thefile;
    thefile.open(readfilename);
    if(thefile.fail())
    {
        return -1;
    }
    else
    {
        int numDays = 0;
        while(getline(thefile, str))
        {
            if(str != "")
            {
                split(str, c, temp_array, size);
                IndexNum[numDays] = stoi(temp_array[0]);      //index number
                Currentdates[numDays] = temp_array[1];       //date
                //cout << IndexNum[numDays] << endl;
                //cout << Currentdates[numDays] << endl;
                numDays++;
            }
        }
    }
    thefile.close();
    return numDays;
};
int Time::helper_function_findthestartdate(string theCurrentdate)
{
    Time timeobject;
    int index = 0;
    for(int i = 0; i < numDays; i++)
    {
        if (theCurrentdate == Currentdates[i])
        {
            index = i;
            //cout << theCurrentdate << endl;
            //cout << index << endl;
            return index;
        }
    }
    //cout << theCurrentdate << endl;
    //cout << index << endl;
    return -2;
};
////////////////////////////            TIME FUNCTION           ////////////////////////////
string Time::getCurrentdate(int index)
{
    return Currentdates[index];
};