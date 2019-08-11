#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "stats.h"
#include "time.h"
#include "movement.h"
#include "raiders.h"
#include "misfortunes.h"
using namespace std;

/*sources:
1.
http://www.cplusplus.com/reference/cstdlib/rand/
#used to find examples for how to generate a random number from a certain range

2.
https://www.youtube.com/watch?v=13TrhiKLZg8
C++ Tutorial for Beginners 42 -Create a Text File and Write in It
#used to learn how to writing a text file

3.
https://stackoverflow.com/questions/23599708/how-do-i-resolve-this-error-jump-to-case-label-crosses-initialization/23599822
#used as reference for fixing the case crosses initialization error
*/

bool helper_function_stoicheck(string input)
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
}
void OregonTrail()
{
    //////  OBJECTS     //////
    Stats statsobject;
    Time timeobject;
    Movement movementobject;
    Raiders raidersobject;
    Misfortunes misfortunesobject;
    ///////////////////////////////                 BEGINNING                   ///////////////////////////////
    string choice;
    cout << "Welcome to the Orgeon Trail simulator!" << endl;
    cout << "Would you like to play?" << endl;
    cout << "Type y or Y for Yes. Type n or N for No" << endl;
    cin >> choice;
    if(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
    {
        while(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
        {
            cout << "Invalid input. Please stop trying to break my game!"  << endl;
            cin >> choice;
        }
    }
    if(choice == "n" || choice == "N")
    {
        cout << "Then why are you here? ... Ending program" << endl;
    }
    if(choice == "y" || choice == "Y")
    {
        int rungame = 0;
        while(rungame == 0)
        {
            string username;
            string startdate;
            string readfilename;
            ///////////////////////////////                 INITIALIZE NAMES            ///////////////////////////////
            cout << "Before the game starts, we need to initialze some parameters first..." << endl;
            cout << "Please enter the names of your party members. FIRST NAMES ONLY!" << endl;
            int members = 0;
            while (members < 5)
            {
                int beginning_health = 0;
                cout << "Name: ";
                cin >> username;
                statsobject.setPlayerName(members, username);
                statsobject.setHealthStatus(members, beginning_health);
                //cout << statsobject.getPlayerName(members) << endl;     //test if array is storing values correctly
                //cout << statsobject.getHealthStatus(members) << endl;     //test if array is storing values correctly
                members++;
            }
            ///////////////////////////////                 INITIALIZE START DATE       ///////////////////////////////
            cout << endl << "The default date is 03/27/1847. Would you like to change it?" << endl;
            cout << "Type y or Y for Yes. Type n or N for No" << endl;
            cin >> choice;
            int time_index = 0;
            timeobject.readDates("days.txt");
            if(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
            {
                while(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                {
                    cout << "Invalid input. Please stop trying to break my game!"  << endl;
                    cin >> choice;      
                }
            }
            if(choice == "n" || choice == "N")
            {
                cout << "Your Oregon Trail Journey will begin on 03/27/1847." << endl;
                time_index = timeobject.helper_function_findthestartdate("03/27/1847");
                cout << time_index << endl;
            }
            if(choice == "y" || choice == "Y")
            {
                int date_check = 0;
                while(date_check == 0)
                {
                    cout << "Enter a start date: range of 03/01/1847 to 05/01/1847 (in the format as shown)" << endl;
                    cout << "Start date: ";
                    cin >> startdate;
                    time_index = timeobject.helper_function_findthestartdate(startdate);
                    if (time_index >=0 && time_index < 62)
                    {
                        cout << "Your input is valid" << endl;
                        cout << "Your Oregon Trail Journey will begin on " << startdate << endl;
                        time_index = time_index;
                        //cout << time_index << endl;
                        date_check++;
                    }
                    else
                    {
                        cout << "The date you entered is not valid in the database. Please try again!" << endl;
                    }
                }
            }
            ///////////////////////////////                 BEGINNING: STARTING STORE            ///////////////////////////////
            cout << "Before you leave, we recommend you buy some supplies" << endl << endl;
            cout << "Stores are located at the start and Forts you'll encounter on your journey" << endl;
            cout << "You Had Saved $1200 To Spend For The Trip, And You've Just Paid $200 For A Wagon. You Will Need To Spend The Rest Of Your Money On The Following Items:" << endl;
            cout << "- Oxen. You NEED To Spend $100-$200 On Oxen At The Beginning Of The Game. The More You Spend, The Faster You'll Go Because You'll Have Better Animals" << endl;
            cout << "- Food. The More You Have, The Less Chance There Is Of Getting Sick. If you run out of food, your game ends!" << endl;
            cout << "- Ammunition. You Will Need Bullets For Attacks By Animals And Bandits, And For Hunting Food" << endl;
            cout << "- Miscellaneous Supplies. This Includes Medicine And Wagon Parts You Will Need For Sickness And Emergency Repairs." << endl << endl;
            cout << "You Can Spend All Your Money Before You Start Your Trip, Or You Can Save Some Of Your Cash To Spend At Forts Along The Way When You Run Low." << endl;
            cout << "However, Items Cost More At The Forts. You Can Also Go Hunting Along The Way To Get More Food" << endl << endl;
            cout << "Your current items are:" << endl;
            statsobject.beginninginventory();
            statsobject.prices();
            int check = 0;            
            statsobject.main_buyfromstore();
            while (statsobject.getinventory(1) < 6 && check == 0)
            {
                if(statsobject.getinventory(0) <= 0)
                {
                    cout << "You needed to spend at least $100 on oxen before traveling (meaning you needed at least 6 Oxen in your party)" << endl;
                    cout << "And now you're broke. No more money for oxen." << endl;
                    cout << "Sorry, your game ends here." << endl;
                    check++;
                    rungame++;
                }
                else
                {
                    cout << endl << "Whoa! Hold On! You Need To Spend At Least $100 On Oxen before traveling (meaning you need at least 6 Oxen in your party)" << endl;
                    cout << "Current oxen count: " << statsobject.getinventory(1) << endl;
                    statsobject.main_buyfromstore();
                }
            }
            statsobject.setprices(0, 1);
            cout << endl << "Congrats! Now your journey can begin! Good luck! You'll need it!" << endl;
            movementobject.readmilestones("milestones.txt");
            int food_check = -1;
            int win = 0;
            int milestone_index = 0;
            int milestone_checkpoint = 0;
            ///////////////////////////////                 THE ACTUAL GAME                   ///////////////////////////////
            //The game runs as long as the party has food (after the first day), the party has ox(en), player leader is not dead, wagon isn't broken and no way to fix, date is not past 11/30/1847 , miles is under 2040)
            while(food_check == -1 && statsobject.getinventory(1) > 0 && statsobject.getHealthStatus(0) != 2 && statsobject.getinventory(8) != 1 && time_index <= 274 && movementobject.getMileage() < 2040 && rungame == 0 && win == 0)    
            {
                ///////////////////////////////         PLAY GAME OPTIONS       ///////////////////////////////
                ///////////////////////////////         CALLS MOVEMENT CLASS       ///////////////////////////////
                int miles = movementobject.getmilestonemiles(milestone_index)- movementobject.getMileage();
                cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                cout << "You Have Traveled: " << movementobject.getMileage() << " miles." << endl;
                cout << "Next Milestone is: " << movementobject.getmilestonename(milestone_index) << ". It is " << miles << " miles away." << endl;
                cout << "Oxen In Your Party: " << statsobject.getinventory(1) << endl;
                cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                cout << "Number of Spare Wagon Wheels: " << statsobject.getinventory(4) << endl;
                cout << "Number of Spare Wagon Axles: " << statsobject.getinventory(5) << endl;
                cout << "Number of Spare Wagon Tongues: " << statsobject.getinventory(6) << endl;
                cout << "Number of Medkits available: " << statsobject.getinventory(7) << endl;
                cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                int select = movementobject.playgame();
                if (select == 4)
                {
                    rungame++;
                }
                else
                {
                    if (select == 1)
                    {
                        int min = 1;
                        int max = 3;
                        int days_passed = rand()%(max-min+1)+min;
                        //cout << days_passed << endl;
                        time_index = time_index + days_passed;
                        int food_eaten = days_passed * 3 * 5;
                        //cout << food_eaten << endl;
                        int amount = statsobject.getinventory(2) - food_eaten;
                        statsobject.setinventory(2, amount);
                        //cout << statsobject.getinventory(2) << endl;
                    }
                    if (select == 2)
                    {
                        int min = 70;
                        int max = 140;
                        int random_miles = rand()%(max-min+1)+min;
                        int miles_traveled = movementobject.getMileage() + random_miles;
                        movementobject.setMileage(miles_traveled); 
                        time_index = time_index + 14;
                        int food_eaten = 14 * 3 * 5;
                        int amount = statsobject.getinventory(2) - food_eaten;
                        statsobject.setinventory(2, amount);
                        ///////////////////////     Landmark Checks         //////////////////////
                        if(movementobject.getMileage() >= 102 && milestone_checkpoint == 0)
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            int cross = 0;
                            while (choice != "2" && cross == 0)
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Cross the River. If you dare :)" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                            int amount = statsobject.getinventory(2) - 15;
                                            statsobject.setinventory(2, amount);
                                            //cout << statsobject.getinventory(2) << endl;
                                            time_index++;
                                            if(statsobject.getinventory(2) <= 0)
                                            {
                                                rungame++;
                                                cross++;        //technically they didn't cross, but I need to break the loop
                                            }
                                            cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                            cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                            cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                            cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                            cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                            cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                    {
                                        if(movementobject.getmilestonedepth(0) > 3)
                                        {
                                            cout << "The river is " << movementobject.getmilestonedepth(0) << "ft deep!" << endl;
                                            cout << "You will need to take a ferry in order to cross the river." << endl;
                                            cout << "Ferry ride costs $10." << endl;
                                            cout << "Do you want to pay the ferry driver?" << endl;
                                            cout << "Type y or Y for Yes. Type n or N for No" << endl;            
                                            cin >> choice;
                                            if(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                                            {
                                                while(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                                                {
                                                    cout << "Invalid input. Please stop trying to break my game!"  << endl;
                                                    cin >> choice;      
                                                }
                }
                                            if(choice == "n" || choice == "N")
                                            {
                                                cout << "Well you can't cross the river otherwise, so looks like you're stuck here until otherwise." << endl;
                                            }
                                            if(choice == "y" || choice == "Y")
                                            {
                                                if(statsobject.getinventory(0) <= 0)
                                                {
                                                    cout << "Sorry, you don't have enough money and are stuck here. Your Journey Ends Here!" << endl;
                                                    rungame++;
                                                }
                                                else
                                                {
                                                    cout << "You crossed the river safely and can continue your journey!" << endl;
                                                    int paid = statsobject.getinventory(0) - 10;
                                                    statsobject.setinventory(0, paid);
                                                    cross++;
                                                }
                                            }
                                            milestone_index++;
                                            milestone_checkpoint++;
                        }
                                        else
                                        {
                                            cout << "You were safe to cross the river and move onwards!" << endl;
                                        }
                                    }
                                    break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                                        }
                            }
                            movementobject.setMileage(102);
                        }
                        if(movementobject.getMileage() > 185 && milestone_checkpoint == 1)
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            int cross = 0;
                            while (choice != "2" && cross == 0)
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Cross the River. If you dare :)" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                            int amount = statsobject.getinventory(2) - 15;
                                            statsobject.setinventory(2, amount);
                                            //cout << statsobject.getinventory(2) << endl;
                                            time_index++;
                                            if(statsobject.getinventory(2) <= 0)
                                            {
                                                rungame++;
                                                cross++;        //technically they didn't cross, but I need to break the loop
                                            }
                                            cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                            cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                            cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                            cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                            cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                            cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                    {
                                        if(movementobject.getmilestonedepth(1) > 3)
                                        {
                                            cout << "The river is " << movementobject.getmilestonedepth(1) << "ft deep!" << endl;
                                            cout << "You will need to take a ferry in order to cross the river." << endl;
                                            cout << "Ferry ride costs $10." << endl;
                                            cout << "Do you want to pay the ferry driver?" << endl;
                                            cout << "Type y or Y for Yes. Type n or N for No" << endl;            
                                            cin >> choice;
                                            if(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                                            {
                                                while(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                                                {
                                                    cout << "Invalid input. Please stop trying to break my game!"  << endl;
                                                    cin >> choice;      
                                                }
                                            }
                                            if(choice == "n" || choice == "N")
                                            {
                                                cout << "Well you can't cross the river otherwise, so looks like you're stuck here until otherwise." << endl;
                                            }
                                            if(choice == "y" || choice == "Y")
                                            {
                                                if(statsobject.getinventory(0) <= 0)
                                                {
                                                    cout << "Sorry, you don't have enough money and are stuck here. Your Journey Ends Here!" << endl;
                                                    rungame++;
                                                }
                                                else
                                                {
                                                    cout << "You crossed the river safely and can continue your journey!" << endl;
                                                    int paid = statsobject.getinventory(0) - 10;
                                                    statsobject.setinventory(0, paid);
                                                    cross++;
                                                }
                                            }
                                            
                                        }
                                        else
                                        {
                                            cout << "You were safe to cross the river and move onwards!" << endl;
                                            cross++;
                                        }
                                        milestone_index++;
                                        milestone_checkpoint++;
                                    }
                                    break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                                        }
                            }
                            movementobject.setMileage(185);
                        }
                        if(movementobject.getMileage() >= 304 && milestone_checkpoint == 2)     //store 1
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            while (choice != "3")
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Visit the store" << endl;
                                cout << "3. Ready To Leave" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                        int amount = statsobject.getinventory(2) - 15;
                                        statsobject.setinventory(2, amount);
                                        //cout << statsobject.getinventory(2) << endl;
                                        time_index++;
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                        statsobject.main_buyfromstore();
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        break;
                                    case 3:
                                        statsobject.setprices(0, 2);
                                        milestone_index++;
                                        milestone_checkpoint++;
                                        break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                }
                            }
                            movementobject.setMileage(304);
                        }
                        if(movementobject.getMileage() >= 640 && milestone_checkpoint == 3)     //store 2
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            while (choice != "3")
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Visit the store" << endl;
                                cout << "3. Ready To Leave" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                        int amount = statsobject.getinventory(2) - 15;
                                        statsobject.setinventory(2, amount);
                                        //cout << statsobject.getinventory(2) << endl;
                                        time_index++;
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                        statsobject.main_buyfromstore();
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        break;
                                    case 3:
                                        statsobject.setprices(0, 3);
                                        milestone_index++;
                                        milestone_checkpoint++;
                                        break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                }
                            }
                            movementobject.setMileage(604);                        
                        }
                        if(movementobject.getMileage() >= 989 && milestone_checkpoint == 4)     //store 3
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            while (choice != "3")
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Visit the store" << endl;
                                cout << "3. Ready To Leave" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                        int amount = statsobject.getinventory(2) - 15;
                                        statsobject.setinventory(2, amount);
                                        //cout << statsobject.getinventory(2) << endl;
                                        time_index++;
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                        statsobject.main_buyfromstore();
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        break;
                                    case 3:
                                        statsobject.setprices(0, 4);
                                        milestone_index++;
                                        milestone_checkpoint++;
                                        break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                }
                            }
                            movementobject.setMileage(989);                        
                        }
                        if(movementobject.getMileage() >= 1151 && milestone_checkpoint == 5)
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            int cross = 0;
                            while (choice != "2" && cross == 0)
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Cross the River. If you dare :)" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                            int amount = statsobject.getinventory(2) - 15;
                                            statsobject.setinventory(2, amount);
                                            //cout << statsobject.getinventory(2) << endl;
                                            time_index++;
                                            if(statsobject.getinventory(2) <= 0)
                                            {
                                                rungame++;
                                                cross++;        //technically they didn't cross, but I need to break the loop
                                            }
                                            cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                            cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                            cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                            cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                            cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                            cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                    {
                                        if(movementobject.getmilestonedepth(5) > 3)
                                        {
                                            cout << "The river is " << movementobject.getmilestonedepth(5) << "ft deep!" << endl;
                                            cout << "You will need to take a ferry in order to cross the river." << endl;
                                            cout << "Ferry ride costs $10." << endl;
                                            cout << "Do you want to pay the ferry driver?" << endl;
                                            cout << "Type y or Y for Yes. Type n or N for No" << endl;            
                                            cin >> choice;
                                            if(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                                            {
                                                while(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                                                {
                                                    cout << "Invalid input. Please stop trying to break my game!"  << endl;
                                                    cin >> choice;      
                                                }
                }
                                            if(choice == "n" || choice == "N")
                                            {
                                                cout << "Well you can't cross the river otherwise, so looks like you're stuck here until otherwise." << endl;
                                            }
                                            if(choice == "y" || choice == "Y")
                                            {
                                                if(statsobject.getinventory(0) <= 0)
                                                {
                                                    cout << "Sorry, you don't have enough money and are stuck here. Your Journey Ends Here!" << endl;
                                                    rungame++;
                                                }
                                                else
                                                {
                                                    cout << "You crossed the river safely and can continue your journey!" << endl;
                                                    int paid = statsobject.getinventory(0) - 10;
                                                    statsobject.setinventory(0, paid);
                                                    cross++;
                                                }
                                            }
                                            milestone_index++;
                                            milestone_checkpoint++;
                        }
                                        else
                                        {
                                            cout << "You were safe to cross the river and move onwards!" << endl;
                                        }
                                    }
                                    break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                                        }
                            }
                            movementobject.setMileage(1151);                        
                        }
                        if(movementobject.getMileage() >= 1395 && milestone_checkpoint == 6)     //store 4
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            while (choice != "3")
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Visit the store" << endl;
                                cout << "3. Ready To Leave" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                        int amount = statsobject.getinventory(2) - 15;
                                        statsobject.setinventory(2, amount);
                                        //cout << statsobject.getinventory(2) << endl;
                                        time_index++;
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                        statsobject.main_buyfromstore();
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        break;
                                    case 3:
                                        statsobject.setprices(0, 5);
                                        milestone_index++;
                                        milestone_checkpoint++;
                                        break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                }
                            }
                            movementobject.setMileage(1395);                        
                        }
                        if(movementobject.getMileage() >= 1534 && milestone_checkpoint == 7)
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            int cross = 0;
                            while (choice != "2" && cross == 0)
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Cross the River. If you dare :)" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                            int amount = statsobject.getinventory(2) - 15;
                                            statsobject.setinventory(2, amount);
                                            //cout << statsobject.getinventory(2) << endl;
                                            time_index++;
                                            if(statsobject.getinventory(2) <= 0)
                                            {
                                                rungame++;
                                                cross++;        //technically they didn't cross, but I need to break the loop
                                            }
                                            cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                            cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                            cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                            cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                            cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                            cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                    {
                                        if(movementobject.getmilestonedepth(7) > 3)
                                        {
                                            cout << "The river is " << movementobject.getmilestonedepth(7) << "ft deep!" << endl;
                                            cout << "You will need to take a ferry in order to cross the river." << endl;
                                            cout << "Ferry ride costs $10." << endl;
                                            cout << "Do you want to pay the ferry driver?" << endl;
                                            cout << "Type y or Y for Yes. Type n or N for No" << endl;            
                                            cin >> choice;
                                            if(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                                            {
                                                while(choice != "y" && choice != "Y" && choice != "n" && choice != "N")
                                                {
                                                    cout << "Invalid input. Please stop trying to break my game!"  << endl;
                                                    cin >> choice;      
                                                }
                }
                                            if(choice == "n" || choice == "N")
                                            {
                                                cout << "Well you can't cross the river otherwise, so looks like you're stuck here until otherwise." << endl;
                                            }
                                            if(choice == "y" || choice == "Y")
                                            {
                                                if(statsobject.getinventory(0) <= 0)
                                                {
                                                    cout << "Sorry, you don't have enough money and are stuck here. Your Journey Ends Here!" << endl;
                                                    rungame++;
                                                }
                                                else
                                                {
                                                    cout << "You crossed the river safely and can continue your journey!" << endl;
                                                    int paid = statsobject.getinventory(0) - 10;
                                                    statsobject.setinventory(0, paid);
                                                    cross++;
                                                }
                                            }
                                            milestone_index++;
                                            milestone_checkpoint++;
                        }
                                        else
                                        {
                                            cout << "You were safe to cross the river and move onwards!" << endl;
                                        }
                                    }
                                    break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                                        }
                            }
                            movementobject.setMileage(1534);
                        }
                        if(movementobject.getMileage() >= 1648 && milestone_checkpoint == 8)    //store 5
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            while (choice != "3")
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Visit the store" << endl;
                                cout << "3. Ready To Leave" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                        int amount = statsobject.getinventory(2) - 15;
                                        statsobject.setinventory(2, amount);
                                        //cout << statsobject.getinventory(2) << endl;
                                        time_index++;
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                        statsobject.main_buyfromstore();
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        break;
                                    case 3:
                                        statsobject.setprices(0, 6);                                
                                        milestone_index++;
                                        milestone_checkpoint++;
                                        break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                }
                            }
                            movementobject.setMileage(1648);
                        }
                        if(movementobject.getMileage() >= 1863 && milestone_checkpoint == 9)    //store 6
                        {
                            cout << endl << "Congrats on making it to " << movementobject.getmilestonename(milestone_index) << "!" << endl;
                            string choice;
                            while (choice != "3")
                            {
                                cout << "Select a numerical option:" << endl;
                                cout << "======Main Menu=====" << endl;
                                cout << "What would you like to do?" << endl;
                                cout << "1. Rest" << endl;
                                cout << "2. Visit the store" << endl;
                                cout << "3. Ready To Leave" << endl;
                                int integer_check = false;
                                while (integer_check == false)
                                {
                                    cin >> choice;
                                    integer_check = movementobject.helper_function_stoicheck(choice);
                                    if (integer_check == true)
                                    {
                                        integer_check =  true;
                                    }
                                }
                                switch (stoi(choice)) {
                                    case 1:
                                        {
                                        int amount = statsobject.getinventory(2) - 15;
                                        statsobject.setinventory(2, amount);
                                        //cout << statsobject.getinventory(2) << endl;
                                        time_index++;
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        }
                                        break;
                                    case 2:
                                        statsobject.main_buyfromstore();
                                        cout << endl << "//////////////////////                      STATUS UPDATE                      //////////////////////" << endl;
                                        cout << "Today's Date: " << timeobject.getCurrentdate(time_index) << endl;
                                        cout << "Food Available (in lbs.): " << statsobject.getinventory(2) << endl;
                                        cout << "Number of Bullets available: " << statsobject.getinventory(3) << endl;
                                        cout << "Cash Remaining: $" << statsobject.getinventory(0) << endl;
                                        cout << "/////////////////////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
                                        break;
                                    case 3:
                                        milestone_index++;
                                        milestone_checkpoint++;
                                        break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                }
                            }
                            movementobject.setMileage(1395);
                        }
                    }
                    if (select == 3)
                    {
                        bool hunting = statsobject.hunting_game();
                        if(hunting == true)
                        {
                            cout << "Congrats on a successful hunt today." << endl;
                        }
                        int eat_check = 0;
                        while(eat_check == 0){
                            cout << "How well do you want eat tonight?" << endl;
                            cout << "1. Poorly (Small Rations)" << endl;
                            cout << "2. Moderately (Average Size Rations)" << endl;
                            cout << "3. Well (Large Rations)" << endl;
                            int integer_check = false;
                            int food_eaten = 0;
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
                                        food_eaten = statsobject.getinventory(2) - 10;
                                        statsobject.setinventory(2, food_eaten);
                                        eat_check++;
                                        break;   
                                    case 2:
                                        food_eaten = statsobject.getinventory(2) - 15;
                                        statsobject.setinventory(2, food_eaten);                                
                                        eat_check++;
                                        break;
                                    case 3:
                                        food_eaten = statsobject.getinventory(2) - 25;
                                        statsobject.setinventory(2, food_eaten);                                
                                        eat_check++;
                                        break;
                                    default:
                                        cout << "invalid input" << endl;
                                        cout << endl;
                                            }
                        }
                        time_index++;
                    }
                    ///////////////////////////////         CALLS MISFORUNATE CLASS       ///////////////////////////////
                    int how_misfortunate = misfortunesobject.MisfortunesHappened(statsobject.getPlayerName(0), statsobject.getPlayerName(1), statsobject.getPlayerName(2), statsobject.getPlayerName(3), statsobject.getPlayerName(4), statsobject.getHealthStatus(0), statsobject.getHealthStatus(1), statsobject.getHealthStatus(2), statsobject.getHealthStatus(3), statsobject.getHealthStatus(4), statsobject.getinventory(1), statsobject.getinventory(4), statsobject.getinventory(5), statsobject.getinventory(6), statsobject.getinventory(7));
                    //cout << "how_misfortunate: " << how_misfortunate << endl;
                    ///////////////////////////////         IF MEDKIT IS AVAILABLE       ///////////////////////////////
                    if(how_misfortunate == 1)   //party leader died
                    {
                        int medkit_used = statsobject.getinventory(7) - 1;
                        statsobject.setinventory(7, medkit_used);
                        //cout << statsobject.getinventory(7) << endl;
                        statsobject.setHealthStatus(0, 2);
                    }
                    else if(how_misfortunate == 2)   //party member 2 died
                    {
                        int medkit_used = statsobject.getinventory(7) - 1;
                        statsobject.setinventory(7, medkit_used);                        
                        statsobject.setHealthStatus(1, 2);
                    }
                    else if(how_misfortunate == 3)   //party member 3 died
                    {
                        int medkit_used = statsobject.getinventory(7) - 1;
                        statsobject.setinventory(7, medkit_used);                        
                        statsobject.setHealthStatus(2, 2);
                    }
                    else if(how_misfortunate == 4)   //party member 4 died
                    {
                        int medkit_used = statsobject.getinventory(7) - 1;
                        statsobject.setinventory(7, medkit_used);                        
                        statsobject.setHealthStatus(3, 2);
                    }
                    else if(how_misfortunate == 5)   //party member 5 died
                    {
                        int medkit_used = statsobject.getinventory(7) - 1;
                        statsobject.setinventory(7, medkit_used);                        
                        statsobject.setHealthStatus(4, 2);
                    }
                    else if(how_misfortunate == 6)   //no one died
                    {
                        int medkit_used = statsobject.getinventory(7) - 1;
                        statsobject.setinventory(7, medkit_used);                        
                    }
                    ///////////////////////////////         REST       ///////////////////////////////
                    else if(how_misfortunate == 7)   //party leader died
                    {
                        statsobject.setHealthStatus(0, 2);
                        time_index = time_index + 3;
                    }
                    else if(how_misfortunate == 8)   //party member 2 died
                    {
                        statsobject.setHealthStatus(1, 2);
                        time_index = time_index + 3;
                    }
                    else if(how_misfortunate == 9)   //party member 3 died
                    {
                        statsobject.setHealthStatus(2, 2);
                        time_index = time_index + 3;
                    }
                    else if(how_misfortunate == 10)   //party member 4 died
                    {
                        statsobject.setHealthStatus(3, 2);
                        time_index = time_index + 3;
                    }
                    else if(how_misfortunate == 11)   //party member 5 died
                    {
                        statsobject.setHealthStatus(4, 2);
                        time_index = time_index + 3;
                    }
                    else if(how_misfortunate == 12)   //no one died
                    {
                        time_index = time_index + 3;
                    }
                    ///////////////////////////////         PRESS ON       ///////////////////////////////
                    else if(how_misfortunate == 13)   //party leader died
                    {
                        statsobject.setHealthStatus(0, 2);
                    }
                    else if(how_misfortunate == 14)   //party member 2 died
                    {
                        statsobject.setHealthStatus(1, 2);
                    }
                    else if(how_misfortunate == 15)   //party member 3 died
                    {
                        statsobject.setHealthStatus(2, 2);
                    }
                    else if(how_misfortunate == 16)   //party member 4 died
                    {
                        statsobject.setHealthStatus(3, 2);
                    }
                    else if(how_misfortunate == 17)   //party member 5 died
                    {
                        statsobject.setHealthStatus(4, 2);
                    }
                    ///////////////////////////////         OXEN DIED       ///////////////////////////////
                    else if(how_misfortunate == 18)
                    {
                        int ox_lost = statsobject.getinventory(1) - 1;
                        statsobject.setinventory(1, ox_lost);
                    }
                    ///////////////////////////////         WAGON PART BROKE           ///////////////////////////////
                    else if(how_misfortunate == 19)  //have no spare wagon wheels
                    {
                        statsobject.setinventory(8, 1);
                    }
                    else if(how_misfortunate == 20)  //have spare wagon wheels
                    {
                        int wheel_used = statsobject.getinventory(4) - 1;
                        statsobject.setinventory(4, wheel_used);                        
                    }
                    else if(how_misfortunate == 21)  //have no spare axle 
                    {
                        statsobject.setinventory(8, 1);
                    }
                    else if(how_misfortunate == 22)  //have spare axle 
                    {
                        int axle_used = statsobject.getinventory(5) - 1;
                        statsobject.setinventory(5, axle_used);
                    }
                    else if(how_misfortunate == 23)  //have no spare tongues 
                    {
                        statsobject.setinventory(8, 1);
                    }
                    else if(how_misfortunate == 24)  //have spare tongues 
                    {
                        int tongues_used = statsobject.getinventory(6) - 1;
                        statsobject.setinventory(6, tongues_used);
                    }
                    ///////////////////////////////         CALLS RAIDER CLASS       ///////////////////////////////
                    bool its_a_raid = raidersobject.getRaidersProbability(movementobject.getMileage());
                    //cout << its_a_raid << endl;
                    if(its_a_raid == true)
                    {
                        int what_do_we_do = raidersobject.raiderchoice();
                        if(what_do_we_do == 1)  //run
                        {
                            cout << "You Managed To Get Away, But You Lost 1 Ox, 10 lbs of food, & 1 Wagon Part." << endl;
                            //cout << statsobject.getinventory(1) << endl;
                            //cout << statsobject.getinventory(2) << endl;
                            int ox_lost = statsobject.getinventory(1) - 1;
                            statsobject.setinventory(1, ox_lost);
                            int food_lost = statsobject.getinventory(2) - 10;
                            statsobject.setinventory(2, food_lost);
                            //cout << statsobject.getinventory(1) << endl;
                            //cout << statsobject.getinventory(2) << endl;
                            int min = 4;
                            int max = 6;
                            int select = rand()%(max-min+1)+min;
                            int part_lost = statsobject.getinventory(select) - 1;
                            statsobject.setinventory(select, part_lost);
                        }
                        if(what_do_we_do == 2)  //won the minigame
                        {
                            //cout << statsobject.getinventory(2) << endl;
                            //cout << statsobject.getinventory(3) << endl;                            
                            int food_gained = statsobject.getinventory(2) + 50;
                            statsobject.setinventory(2, food_gained);
                            int bullets_gained = statsobject.getinventory(3) + 50;
                            statsobject.setinventory(3, bullets_gained);
                            //cout << statsobject.getinventory(2) << endl;
                            //cout << statsobject.getinventory(3) << endl;                            
                        }
                        if(what_do_we_do == 3)  //lost the minigame
                        {
                            //cout << statsobject.getinventory(0) << endl;
                            //cout << statsobject.getinventory(3) << endl;
                            int money_lost = statsobject.getinventory(0) - (statsobject.getinventory(0)/4);
                            statsobject.setinventory(0, money_lost);
                            int bullets_lost = statsobject.getinventory(3) - 50;
                            if(bullets_lost < 0)
                            {
                                statsobject.setinventory(3, 0);
                            }
                            else
                            {
                                statsobject.setinventory(3, bullets_lost);
                            }
                            //cout << statsobject.getinventory(0) << endl;
                            //cout << statsobject.getinventory(3) << endl;                            
                        }
                        if(what_do_we_do == 4)  //surrender
                        {
                            //cout << statsobject.getinventory(0) << endl;
                            cout << "The Raiders decided to have mercy on you!" << endl;
                            cout << "You lost a quarter of their cash reserves." << endl;
                            int money_lost = statsobject.getinventory(0) - (statsobject.getinventory(0)/4);
                            statsobject.setinventory(0, money_lost);
                            //cout << statsobject.getinventory(0) << endl;
                        }
                    }
                    /////////////////           CHECK               /////////////////
                    if(statsobject.getinventory(2) < 0)
                    {
                        food_check++;
                    }
                    if(statsobject.getinventory(0) < 0)
                    {
                        statsobject.setinventory(0, 0);
                    }
                    if(statsobject.getHealthStatus(0) != 2 && movementobject.getMileage() >= 2040 && time_index <= 274)
                    {
                        win++;
                    }
                }
            }
            //////////////////////                      FINAL RESULTS.TXT                      //////////////////////
            ofstream result;
            result.open("results.txt");
            result << "//////////////////////                      FINAL RESULTS                      //////////////////////" << endl;
            //////////          How Did The Game End          //////////
            if(rungame == 1)
            {
                result << "So, you quit?! Well, hope you had a good time playing." << endl;
            }
            else
            {
                if(statsobject.getinventory(1) <= 0)
                {
                    result << "All your oxen died or were killed. You can not continue traveling. Your Journey Ends Here!" << endl;
                }
                if(statsobject.getHealthStatus(0) == 2)
                {
                    result << "I'm sorry to say: " << statsobject.getPlayerName(0) << " has died of disease!" << endl;
                }
                if(statsobject.getinventory(8) != 0)
                {
                    result << "Your wagon broke down and you didn't have the part to fix it. Your Journey Ends Here!" << endl;
                }
                if(food_check == 0)
                {
                    result << "Your party ran out of food and eventually starved to death." << endl;
                }            
                if(time_index > 274)
                {
                    result << "You did not make to your destination before 11/30/1847. Winter has come and your party froze to death." << endl;
                }
                if(win == 1)
                {
                    result << "Congrats on beating the game!" << endl;
                }
            }
            //////////          Results          //////////
            result << "Final Date: " << timeobject.getCurrentdate(time_index) << endl;
            result << "Party Leader: " << statsobject.getPlayerName(0) << endl;
            result << "Miles You Traveled: " << movementobject.getMileage() << endl;
            result << "Food Remaining (in lbs.): " << statsobject.getinventory(2) << endl;
            result << "Final Cash Remaining: $" << statsobject.getinventory(0) << endl;
            result << "/////////////////////////////////////////////////////////////////////////////////////////////////////";
            result.close();
            std::cin.get();
            cout << "Your game has ended. Your results have been saved in the results.txt file" << endl;
            rungame++;      //CURRENT SOLUTION TO STOP THE GAME FROM RUNNING
        }
    }
}
int main()
{
	// start the game! 
	OregonTrail();
	return 0;
}