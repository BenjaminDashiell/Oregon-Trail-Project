#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "misfortunes.h"
using namespace std;

////////////////////////////            THE "NO GAME BREAKING" FUNCTIONS          ////////////////////////////
bool Misfortunes::helper_function_stoicheck(string input)
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
////////////////////////////            MISFORUNATION FUNCTIONS          ////////////////////////////
int Misfortunes::getMisfortunesChance(void)
{
    int min = 0;
    int max = 100;
    int misforunate_chance = rand()%(max-min+1)+min;
    return misforunate_chance;
};
string Misfortunes::getDisease(int index)
{
    if(index == 1)
    {
        return "typhoid";
    }
    if(index == 2)
    {
        return "cholera";
    }
    if(index == 3)
    {
        return "diarrhea";
    }
    if(index == 4)
    {
        return "measles";
    }
    if(index == 5)
    {
        return "dysentery";
    }
    if(index == 6)
    {
        return "fever";
    }
};
int Misfortunes::MisfortunesHappened(string partymember_one, string partymember_two, string partymember_three, string partymember_four, string partymember_five, int partymember_one_health, int partymember_two_health, int partymember_three_health, int partymember_four_health, int partymember_five_health, int oxen, int wagon_wheel, int wagon_axle, int wagon_tongue, int medkit)
{
    int how_unfortunate = getMisfortunesChance();
    if(how_unfortunate <= 40)
    {
        int min = 1;
        int max = 3;
        int which_misfortune = rand()%(max-min+1)+min;
        if(which_misfortune == 1)
        {
            min = 1;
            max = 5;
            int who_is_sick = rand()%(max-min+1)+min;
            string sick_person;
            if(who_is_sick == 1)
            {
                sick_person = partymember_one;
                //int leader_sick = 1;
            }
            if(who_is_sick == 2)
            {
                sick_person = partymember_two;
            }
            if(who_is_sick == 3)
            {
                sick_person = partymember_three;
            }
            if(who_is_sick == 4)
            {
                sick_person = partymember_four;
            }
            if(who_is_sick == 5)
            {
                sick_person = partymember_five;
            }
            min = 1;
            max = 6;
            int disease = rand()%(max-min+1)+min;
            cout << "OH NO! " << sick_person << " HAS " << getDisease(disease) << "!" << endl;
            min = 1;
            max = 100;
            int still_sick = rand()%(max-min+1)+min;
            if(medkit > 0)
            {
                cout << "A Medkit was used to potentially save " << sick_person << "'s life." << endl;
                if(still_sick > 50)
                {
                    if(sick_person == partymember_one && partymember_one_health == 0)
                    {
                        cout << "Sorry, " << partymember_one << " died of " <<  getDisease(disease) << "!" << endl;
                        return 1;
                    }
                    if(sick_person == partymember_two && partymember_two_health == 0)
                    {
                        cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                        return 2;
                    }
                    if(sick_person == partymember_three && partymember_three_health == 0)
                    {
                        cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                        return 3;
                    }
                    if(sick_person == partymember_four && partymember_four_health == 0)
                    {
                        cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                        return 4;
                    }
                    if(sick_person == partymember_five && partymember_five_health == 0)
                    {
                        cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                        return 5;
                    }
                }
                cout << "No One Died... For Now :)" << endl;
                return 6;
            }
            else
            {
                string choice;
                bool integer_check = false;
                while (integer_check == false)
                {
                    cout << "Select a numerical option:" << endl;
                    cout << "======Main Menu=====" << endl;
                    cout << "1. Rest" << endl;
                    cout << "2. Press On" << endl;
                    cin >> choice;
                    integer_check = helper_function_stoicheck(choice);
                    if (integer_check == true)
                    {
                        if(stoi(choice) <= 2)
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
                        {
                            int min = 1;
                            int max = 100;
                            int still_sick = rand()%(max-min+1)+min;
                            if(still_sick <= 30)
                            {
                                if(sick_person == partymember_one && partymember_one_health == 0)
                                {
                                    cout << "Sorry, " << partymember_one << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 7;
                                }
                                if(sick_person == partymember_two && partymember_two_health == 0)
                                {
                                    cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 8;
                                }
                                if(sick_person == partymember_three && partymember_three_health == 0)
                                {
                                    cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 9;
                                }
                                if(sick_person == partymember_four && partymember_four_health == 0)
                                {
                                    cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 10;
                                }
                                if(sick_person == partymember_five && partymember_five_health == 0)
                                {
                                    cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 11;
                                }
                                cout << "No One Died... For Now :)" << endl;
                                return 12;  //no one dies, +3 days
                            }
                            else
                            {
                                cout << "No One Died... For Now :)" << endl;
                                return 0;
                            }
                        }
                    case 2:
                        {
                            if(still_sick <= 70)
                            {
                                if(sick_person == partymember_one && partymember_one_health == 0)
                                {
                                    cout << "Sorry, " << partymember_one << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 13;
                                }
                                if(sick_person == partymember_two && partymember_two_health == 0)
                                {
                                    cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 14;
                                }
                                if(sick_person == partymember_three && partymember_three_health == 0)
                                {
                                    cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 15;
                                }
                                if(sick_person == partymember_four && partymember_four_health == 0)
                                {
                                    cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 16;
                                }
                                if(sick_person == partymember_five && partymember_five_health == 0)
                                {
                                    cout << "Sorry, " << sick_person << " died of " <<  getDisease(disease) << "!" << endl;
                                    return 17;
                                }
                                cout << "No One Died... For Now :)" << endl;
                                return 0;  //no one dies
                            }
                            else
                            {
                                cout << "No One Died... For Now :)" << endl;
                                return 0;
                            }
                        }
                    default:
                        cout << "invalid input" << endl;
                                            }
            }
        }
        if(which_misfortune == 2)
        {
            int count = oxen - 1;
            cout << "OH NO! ONE OF THE OXEN HAS DIED! YOU HAVE " << count << " OXEN LEFT!" << endl << endl;
            return 18;
        }
        if(which_misfortune == 3)
        {
            int min = 1;
            int max = 3;
            int broken = rand()%(max-min+1)+min;
            string part;
            if(broken == 1)
            {
                cout << "OH NO! ONE OF YOUR WHEELS IS BROKEN!" << endl;
                if(wagon_wheel <= 0)
                {
                    cout << "OH NO! YOU DO NOT HAVE THE SPARE PART! YOUR WAGON BROKE DOWN!" << endl << endl;
                    return 19;
                }
                else
                {
                    cout << "YOU FIXED THE WHEEL! YOUR JOURNEY CONTINUES!" << endl;
                    return 20;
                }
            }
            if(broken == 2)
            {
                cout << "OH NO! ONE OF YOUR AXLES IS BROKEN!" << endl;
                if(wagon_axle <= 0)
                {
                    cout << "OH NO! YOU DO NOT HAVE THE SPARE PART! YOUR WAGON BROKE DOWN!" << endl << endl;
                    return 21;
                }
                else
                {
                    cout << "YOU FIXED THE AXLE! YOUR JOURNEY CONTINUES!" << endl;
                    return 22;
                }
            }
            if(broken == 3)
            {
                cout << "OH NO! ONE OF YOUR WAGON TONGUES IS BROKEN!" << endl;
                if(wagon_tongue <= 0)
                {
                    cout << "OH NO! YOU DO NOT HAVE THE SPARE PART! YOUR WAGON BROKE DOWN!" << endl << endl;
                    return 23;
                }
                else
                {
                    cout << "YOU FIXED THE WAGON TONGUES! YOUR JOURNEY CONTINUES!" << endl;
                    return 24;
                }
            }
        }
    }
    else
    {
        cout << "Nothing bad happened... for now >:)" << endl;
        return 0;
    }
};