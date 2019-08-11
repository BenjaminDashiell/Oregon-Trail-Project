#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "raiders.h"
using namespace std;

////////////////////////////            THE "NO GAME BREAKING" FUNCTIONS          ////////////////////////////
bool Raiders::helper_function_stoicheck(string input)
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
////////////////////////////            RAIDER FUCTIONS           ////////////////////////////
bool Raiders::getRaidersProbability(int miles_traveled)
{
    double step_one = ((pow((miles_traveled/(100-4)), 2)) + 72);
    double step_two = ((pow((miles_traveled/(100-4)), 2)) + 12);
    double calculation = (((step_one/step_two) - 1) / 10);
    raider_probability =  calculation * 100;
    //cout << miles_traveled << endl;
    //cout << raider_probability << endl;
    int min = 1;
    int max = 100;
    int random_number = rand()%(max-min+1)+min;
    //cout << random_number << endl;
    if(random_number <= raider_probability)
    {
        return true;
    }
    else
    {
        return false;
    }
};
void Raiders::displayraidersmenu(void)
{
    cout << "RIDERS AHEAD! THEY LOOK HOSTILE!" << endl;
    cout << "Select a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Run" << endl;
    cout << "2. Attack" << endl;
    cout << "3. Surrender" << endl;
};
int Raiders::raiderchoice(void)
{
    displayraidersmenu();
    string choice;
    int integer_check = false;
    while (integer_check == false)
    {
        cin >> choice;
        integer_check = helper_function_stoicheck(choice);
        if (integer_check == true)
        {
            if(stoi(choice) < 4)
            {
                integer_check = true;
            }
            else
            {
                cout << "invalid input" << endl;
                integer_check =  false;
            }
        }
    }
        switch (stoi(choice)) {
        case 1:
            return 1;            
        case 2:
            {
                bool result = puzzle();
                if(result == true)
                {
                    return 2;
                }
                else
                {
                    return 3;
                }
            }
        case 3:
            return 4;
        default:
            cout << "invalid input" << endl;
            cout << endl;
                          }
};
bool Raiders::puzzle(void)
{
    int min = 1;
    int max = 10;
    int random = rand()%(max-min+1)+min;
    //cout << random << endl;
    cout << "----welcome to the puzzle!-----" << endl;
    cout << "In order to win the battle, you must correctly guess a number between 1 to 10. You will be given at most 3 tries. Good luck!." << endl;
    for(int i = 0; i <3; i++)
    {
        string guess;
        int integer_check = false;
        while (integer_check == false)
        {
            cout << "Enter A Number Between 1 & 10" << endl;
            cin >> guess;
            integer_check = helper_function_stoicheck(guess);
            if (integer_check == true)
            {
                if(stoi(guess) < 1 || stoi(guess) > 10)
                {
                    cout << "Input is not between 1 to 10. It counts as a guess. Please try again!" << endl;
                    integer_check =  true;                    
                }
                else
                {
                    integer_check =  true;
                }
            }
        }
        if(stoi(guess) == random)
        {
            cout << "You have passed the puzzle! You fended off the raiders!!" << endl;
            cout << "You gained 50 lbs. of food and 50 bullets" << endl;
            return true;
        }
    }
    cout << "You failed passed the puzzle! The Raiders Won!" << endl;
    cout << "The Raiders decided to have mercy on you!" << endl;
    cout << "You lost a quarter of their cash reserves and 50 bullets. Better luck next time." << endl;
    return false;
};