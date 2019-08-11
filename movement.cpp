#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "stats.h"
#include "movement.h"
using namespace std;
////////////////////////////            CONSTRUCTORS          ////////////////////////////
Movement::Movement(void)
{
    current_mileage = 0;
    index_number = 0;
};
Movement::Movement(int currentmiles, int index)
{
    current_mileage = currentmiles;
    index_number = index;
};
////////////////////////////            THE "NO GAME BREAKING" FUNCTIONS          ////////////////////////////
bool Movement::helper_function_stoicheck(string input)
{
    //check for empty string
    if (input == ""){
        cout << "Input is empty. Please enter something else" << endl;
        return false;
    }
    //traverse the string
    for(int i = 0; i < input.length(); i++)
    {
        if (input[i] != '0' && input[i] != '1' && input[i] != '2' && input[i] != '3' && input[i] != '4' && input[i] != '5' && input[i] != '6' && input[i] != '7' && input[i] != '8' && input[i] != '9')
        {
            //Does it contain non integer 0-9
            //cout << "false " << false << endl;
            cout << "Invalid input. Please stop trying to break my game!"  << endl;
            return false;
        }
    }
    //cout << "true " << true << endl;
    return true;
};
////////////////////////////            INITIALIZE MOVEMENT DATABASE           ////////////////////////////
int Movement::split(string str, char c, string array[], int size)
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
int Movement::readmilestones(string readfilename)
{
    char c = ',';
    string str = "";
    string temp_array[3];
    int size = 10;
    ifstream thefile;
    thefile.open(readfilename);
    if(thefile.fail())
    {
        return -1;
    }
    else
    {
        int index = 0;
        while(getline(thefile, str))
        {
            if(str != "")
            {
                split(str, c, temp_array, size);
                milestone_name[index] = temp_array[0];      //name of milestone
                milestone_miles[index] = stoi(temp_array[1]);       //miles located
                milestone_depth[index] = stoi(temp_array[2]);       //depth (0 if a fort)
                milestone_checkpoint[index] = false;
                //cout << milestone_name[index] << endl;
                //cout << milestone_miles[index] << endl;
                //cout << milestone_depth[index] << endl;
                index++;
            }
        }
    thefile.close();
    return index;
    }
};
string Movement::getmilestonename(int index)
{
    return milestone_name[index];
};
int Movement::getmilestonemiles(int index)
{
    return milestone_miles[index];
};
int Movement::getmilestonedepth(int index)
{
    return milestone_depth[index];
};
bool Movement::getmilestonecheck(int index)
{
    return milestone_checkpoint[index];
};
bool Movement::setmilestonecheck(int index)
{
    milestone_checkpoint[index] = true;
};
int Movement::milestone_status(void)
{
    int milestone_prompt = 0;
    bool kansas_river = getmilestonecheck(0);    //Kansas River Crossing
    bool blue_river = getmilestonecheck(1); //Big Blue River Crossing
    bool fort_kearney = getmilestonecheck(2); //Fort Kearney
    bool fort_laramie = getmilestonecheck(3); //Fort Laramie
    bool fort_bridger = getmilestonecheck(4); //Fort Bridger
    bool green_river = getmilestonecheck(5); //Green River Crossing
    bool fort_hall = getmilestonecheck(6); //Fort Hall
    bool snake_river = getmilestonecheck(7); //Snake River Crossing
    bool fort_boise = getmilestonecheck(8); //Fort Boise
    bool fort_walla_walla = getmilestonecheck(9);  //Fort Walla Walla
    bool oregon_city = getmilestonecheck(10);
    if(kansas_river == false && getMileage() < 102)
    {
        return 0;
    }
    setmilestonecheck(0);
    if(blue_river == false && getMileage() < 185)
    {
        return 1;
    }
    setmilestonecheck(1);
    if(fort_kearney == false && getMileage() < 304)
    {
        return 2;
    }
    setmilestonecheck(2);
    if(fort_laramie == false && getMileage() < 640)
    {
        return 3;
    }
    setmilestonecheck(3);
    if(fort_bridger == false && getMileage() < 989)
    {
        return 4;
    }
    setmilestonecheck(4);
    if(green_river == false && getMileage() < 1151)
    {
        return 5;
    }
    setmilestonecheck(5);
    if(fort_hall == false && getMileage() < 1395)
    {
        return 6;
    }
    setmilestonecheck(6);
    if(snake_river == false && getMileage() < 1534)
    {
        return 7;
    }
    setmilestonecheck(7);
    if(fort_boise == false && getMileage() < 1648)
    {
        return 8;
    }
    setmilestonecheck(8);
    if(fort_walla_walla == false && getMileage() < 1863)
    {
        return 9;
    }
    setmilestonecheck(9);
    if(oregon_city == false && getMileage() < 2040)
    {
        setmilestonecheck(10);
        return 10;
    }
    setmilestonecheck(10);
};
int Movement::setMileage(int traveled)
{
    current_mileage = traveled;
};
int Movement::getMileage(void)
{
    return current_mileage;
};
////////////////////////////            MOVEMENT FUCTIONS           ////////////////////////////
int Movement::displaychoices(void)
{
    cout << "Select a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Rest" << endl;
    cout << "2. Travel" << endl;
    cout << "3. Hunt" << endl;
    cout << "4. Quit" << endl;
    cout << "What would you like to do?" << endl;
};
int Movement::playgame(void)
{
    string choice;
    while (choice != "4"){
        displaychoices();
        int integer_check = false;
        while (integer_check == false)
        {
            cin >> choice;
            integer_check = helper_function_stoicheck(choice);
            if (integer_check == true)
            {
                integer_check =  true;
            }
        }
        switch (stoi(choice)) {
            case 1:
                return 1;            
            case 2:
                return 2;           
            case 3:
                return 3;
            case 4:
                return 4;
            default:
                cout << "invalid input" << endl;
                cout << endl;
                              }
        }
};