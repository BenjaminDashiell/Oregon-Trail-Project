#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "stats.h"
#include "sstream"
using namespace std;
////////////////////////////            THE "NO GAME BREAKING" FUNCTIONS          ////////////////////////////
bool Stats::helper_function_stoicheck(string input)
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
/////////////////////////                   HUNTING FUNCTIONS                   /////////////////////////
int Stats::setBulletsLost(void)
{
    bullets[1] = 10;       //rabbit
    bullets[2] = 8;        //fox
    bullets[3] = 5;        //deer
    bullets[4] = 10;       //bear
    bullets[5] = 12;       //moose
};
int Stats::getBulletsLost(int animal_index)
{
    return bullets[animal_index];
};
bool Stats::getAnimalSpawn(int animal)
{
    int min = 0;
    int max = 100;
    int probability = rand()%(max-min+1)+min;
    if(animal == 1 && probability <= 50)
    {
        return true;
    }
    if(animal == 2 && probability <= 25)
    {
        return true;
    }
    if(animal == 3 && probability <= 15)
    {
        return true;
    }
    if(animal == 4 && probability <= 7)
    {
        return true;
    }
    if(animal == 5 && probability <= 5)
    {
        return true;
    }
    return false;   //if no animal spawns
};
int Stats::hunting_game(void)
{
    int food_gained = 0;
    bool rabbit = getAnimalSpawn(1);
    bool fox = getAnimalSpawn(2);
    bool deer = getAnimalSpawn(3);
    bool bear = getAnimalSpawn(4);
    bool moose = getAnimalSpawn(5);
    bool successful = false;
    if(rabbit == true)
    {
        successful = hunt_menu(1);
    }
    if(fox == true)
    {
        successful = hunt_menu(2);
    }
    if(deer == true)
    {
        successful = hunt_menu(3);
    }
    if(bear == true)
    {
        successful = hunt_menu(4);
    }
    if(moose == true)
    {
        successful = hunt_menu(5);
    }
    if(rabbit == false && fox == false && deer == false && bear == false && moose == false)     //if no animals are found
    {
        cout << "No Animals Were Found! There's always tomorrow." << endl;
        return false;
    }
    return successful;
};
int Stats::checkfoodfull(int hunt)
{
    int amount = getinventory(2) + hunt;
    if(amount <= 1000)
    {
        setinventory(2, amount);
    }
    else
    {
        cout << "Sorry. Max capacity on the wagon is 1000. You stored what you could and had to leave behind some of the food from your hunt." << endl;
        amount = 1000;
        setinventory(2, amount);
    }
};
int Stats::hunt_menu(int animal)
{
    //OUTCOME: RETURN FOOD GAINED IF PLAYER ENCOUNTERED AN ANIMAL AND WINS THE PUZZLE
    cout << "YOU GOT LUCKY! YOU ENCOUNTERED A ";
    if(animal == 1)
    {
        cout << "RABBIT!" << endl;
    }
    if(animal == 2)
    {
        cout << "FOX!" << endl;
    }
    if(animal == 3)
    {
        cout << "DEER!" << endl;
    }
    if(animal == 4)
    {
        cout << "BEAR!" << endl;
    }
    if(animal == 5)
    {
        cout << "MOOSE!" << endl;
    }
    cout << "DO YOU WANT TO HUNT: 1. YES, 2. NO" << endl;
    string choice;
    bool hunt = false;
    while (choice != "2" && hunt == false){
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
            {
                setBulletsLost();
                bool hunt_successful = puzzle(animal);
                if(hunt_successful == true)
                {
                    if(animal == 1)
                    {
                        //cout << getBulletsLost(animal) << endl;
                        int bullets_lost = getinventory(3) - getBulletsLost(animal);
                        //cout << bullets_lost << endl;
                        setinventory(3, bullets_lost);
                        //cout << getinventory(3) << endl;
                        checkfoodfull(2);
                        //cout << getinventory(2) << endl;
                        hunt = true;
                    }
                    if(animal == 2)
                    {
                        //cout << getBulletsLost(animal) << endl;
                        int bullets_lost = getinventory(3) - getBulletsLost(animal);
                        //cout << bullets_lost << endl;
                        setinventory(3, bullets_lost);
                        //cout << getinventory(3) << endl;
                        checkfoodfull(5);
                        //cout << getinventory(2) << endl;
                        hunt = true;
                    }
                    if(animal == 3)
                    {
                        int min = 30;
                        int max = 55;
                        int random_food = rand()%(max-min+1)+min;
                        //cout << getBulletsLost(animal) << endl;
                        int bullets_lost = getinventory(3) - getBulletsLost(animal);
                        //cout << bullets_lost << endl;
                        setinventory(3, bullets_lost);
                        //cout << getinventory(3) << endl;
                        checkfoodfull(random_food);
                        //cout << getinventory(2) << endl;
                        hunt = true;
                    }
                    if(animal == 4)
                    {
                        int min = 100;
                        int max = 350;
                        int random_food = rand()%(max-min+1)+min;
                        //cout << getBulletsLost(animal) << endl;
                        int bullets_lost = getinventory(3) - getBulletsLost(animal);
                        //cout << bullets_lost << endl;
                        setinventory(3, bullets_lost);
                        //cout << getinventory(3) << endl;
                        checkfoodfull(random_food);
                        //cout << getinventory(2) << endl;
                        hunt = true;
                    }
                    if(animal == 5)
                    {
                        int min = 300;
                        int max = 600;
                        int random_food = rand()%(max-min+1)+min;
                        //cout << getBulletsLost(animal) << endl;
                        int bullets_lost = getinventory(3) - getBulletsLost(animal);
                        //cout << bullets_lost << endl;
                        setinventory(3, bullets_lost);
                        //cout << getinventory(3) << endl;
                        checkfoodfull(random_food);
                        //cout << getinventory(2) << endl;
                        hunt = true;
                    }
                    return true;
                }
                if (hunt_successful == false)
                {
                    return 0;
                }
            }
                break;
            case 2:
                return false;
                break;
            default:
                cout << "invalid input" << endl;
                              }
        }
};
bool Stats::puzzle(int animal_index)     //no change
{
    int min = 1;
    int max = 10;
    int random = rand()%(max-min+1)+min;
    //cout << random << endl;
    cout << "----welcome to the puzzle!-----" << endl;
    if(getinventory(3) <= getBulletsLost(animal_index))
    {   
        cout << "You do not have enough bullets for hunting this animal." << endl;
        return false;
    }
    cout << "In order to successfully hunt, you must correctly guess a number between 1 to 10. You will be given at most 3 tries. Good luck!." << endl;
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
                    cout << "Input is not between 1 to 10. It counts as a guess. Please try again" << endl;
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
            cout << "You have passed the puzzle! Your Hunt Was Successful!" << endl;
            return true;
        }
    }
    cout << "You failed passed the puzzle! The Animal Got Away!" << endl;
    return false;
};
/////////////////////////                   STATS FUNCTIONS                   /////////////////////////
string Stats::getPlayerName(int index)
{
    return party_member_names[index];  
};
void Stats::setPlayerName(int index, string input_name)
{
    party_member_names[index] = input_name;
};
int Stats::getHealthStatus(int index)
{
    return party_member_health[index];
};
void Stats::setHealthStatus(int index, int health)
{
    party_member_health[index] = health;
};
double Stats::beginninginventory(void)
{
    inventory_array[0] = 1000.00;
    cout << "Money: " <<  inventory_array[0] << endl;
    inventory_array[1] = 0;
    cout << "Oxen: " <<  inventory_array[1] << endl;
    inventory_array[2] = 0;
    cout << "Food (in lbs): " <<  inventory_array[2] << endl;
    inventory_array[3] = 0;
    cout << "Bullets: " <<  inventory_array[3] << endl;
    inventory_array[4] = 0;
    cout << "Wheel Parts: " <<  inventory_array[4] << endl;
    inventory_array[5] = 0;
    cout << "Axle Parts: " <<  inventory_array[5] << endl;
    inventory_array[6] = 0;
    cout << "Tongue Parts: " <<  inventory_array[6] << endl;
    inventory_array[7] = 0;
    cout << "Medkits: " <<  inventory_array[7] << endl << endl;
    inventory_array[8] = 0;
    //cout << "Wagon Status: " << inventory_array[8] << endl;
    //cout << "0 Means it is not broken or fixed. 1 Means it needs repairs" << endl  << endl;
};
int Stats::getinventory(int index)
{
    return inventory_array[index];
};
int Stats::setinventory(int index, int amount)
{
    inventory_array[index] = amount;
};
/////////////////////////                   STORE FUNCTIONS                   /////////////////////////
double Stats::prices(void)
{
    store_prices[0] = 0;        //stores visited
    store_prices[1] = 40;
    store_prices[2] = 0.5;
    store_prices[3] = 2;
    store_prices[4] = 20;
    store_prices[5] = 20;
    store_prices[6] = 20;
    store_prices[7] = 25;
};
int Stats::setprices(int index, int stores)
{
    store_prices[index] = stores;
};
void Stats::displaystoremenu(double money)
{
    cout << "Select a numerical option:" << endl;
    cout << "======Main Menu=====" << endl;
    cout << "1. Oxen" << endl;
    cout << "2. Food" << endl;
    cout << "3. Bullets" << endl;
    cout << "4. Wagon Parts" << endl;
    cout << "5. Med Kits" << endl;
    cout << "6. Leave Store" << endl << endl;
    cout << "Amount you have: $" << money << endl;
    cout << "What would you like to do?" << endl;
};
int Stats::main_buyfromstore(void)
{
    string choice;
    string buy;
    int input = 0;
    double starting_price = 0;
    int index;
    while (choice != "6"){
        double money = inventory_array[0];
        displaystoremenu(money);
        int integer_check = false;
        while (integer_check == false)
        {
            cin >> choice;
            integer_check = helper_function_stoicheck(choice);
            //cout << "integer_check " << integer_check << endl;
            if (integer_check == true)
            {
                integer_check =  true;
            }
        }
        switch (stoi(choice)) {
            case 1:
                {
                    starting_price = store_prices[1];
                    index = 1;
                    double current_price = starting_price + (starting_price * (0.25 * store_prices[0]));
                    cout << "There are 2 oxen in a yoke and the price of each yoke is $" << current_price << ". How many yokes would you like to buy?" << endl;
                    int input_check = false;
                    while (input_check == false)
                    {
                        cin >> buy;
                        input_check = helper_function_stoicheck(buy);
                        if (input_check == true)
                        {
                            input_check =  true;
                        }
                    }
                    input = stoi(buy);
                    //cout << "Starting at " << starting_price << endl;
                    purchasing_items(input, starting_price, index);
                }
                break;
            case 2:
                {
                    starting_price = store_prices[2];
                    index = 2;
                    double current_price = starting_price + (starting_price * (0.25 * store_prices[0]));
                    cout << "Each bag contains a pound of food that costs $" << current_price << ". How many bags would you like to buy?" << endl;
                    cout << "Reminder: The wagon cannot hold more than 1000 lbs. of food." << endl;
                                        int input_check = false;
                    while (input_check == false)
                    {
                        cin >> buy;
                        input_check = helper_function_stoicheck(buy);
                        if (input_check == true)
                        {
                            input_check =  true;
                        }
                    }
                    input = stoi(buy);
                    purchasing_items(input, starting_price, index);
                }
                break;
            case 3:
                {
                    starting_price = store_prices[3];
                    index = 3;
                    double current_price = starting_price + (starting_price * (0.25 * store_prices[0]));
                    cout << "Each box comes with 20 bullets for $" << current_price << ". How many boxes would you like to buy?" << endl;
                    int input_check = false;
                    while (input_check == false)
                    {
                        cin >> buy;
                        input_check = helper_function_stoicheck(buy);
                        if (input_check == true)
                        {
                            input_check =  true;
                        }
                    }
                    input = stoi(buy);
                    purchasing_items(input, starting_price, index);
                }
                break;
            case 4:
                {
                    starting_price = store_prices[4];
                    index = 4;
                    double current_price = starting_price + (starting_price * (0.25 * store_prices[0]));
                    cout << "Each wagon part costs $" << current_price << "." << endl;
                    cout << "How many wheel parts would you like to buy?" << endl;
                    int input_check = false;
                    while (input_check == false)
                    {
                        cin >> buy;
                        input_check = helper_function_stoicheck(buy);
                        if (input_check == true)
                        {
                            input_check =  true;
                        }
                    }
                    input = stoi(buy);
                    purchasing_items(input, starting_price, index);
                    input_check = false;
                    cout << "How many axle parts would you like to buy?" << endl;
                    while (input_check == false)
                    {
                        cin >> buy;
                        input_check = helper_function_stoicheck(buy);
                        if (input_check == true)
                        {
                            input_check =  true;
                        }
                    }
                    input = stoi(buy);
                    index = 5;
                    purchasing_items(input, starting_price, index);
                    input_check = false;
                    cout << "How many tongue parts would you like to buy?" << endl;
                    while (input_check == false)
                    {
                        cin >> buy;
                        input_check = helper_function_stoicheck(buy);
                        if (input_check == true)
                        {
                            input_check =  true;
                        }
                    }
                    input = stoi(buy);
                    index = 6;
                    purchasing_items(input, starting_price, index);
                }
                break;
            case 5:
                {
                    starting_price = store_prices[7];
                    index = 7;
                    double current_price = starting_price + (starting_price * (0.25 * store_prices[0]));
                    cout << "Each medkit costs $" << current_price << ". How many medkits would you like to buy?" << endl;
                    int input_check = false;
                    while (input_check == false)
                    {
                        cin >> buy;
                        input_check = helper_function_stoicheck(buy);
                        if (input_check == true)
                        {
                            input_check =  true;
                        }
                    }
                    input = stoi(buy);
                    purchasing_items(input, starting_price, index);
                }
                break;
            case 6:
                break;
            default:
                cout << "invalid input" << endl;
                cout << endl;
                               }
    }
};
double Stats::purchasing_items(int input, double starting_price, int index)
{
    int purchased = input;
    double current_price = starting_price + (starting_price * (0.25 * store_prices[0]));
    double total = purchased * current_price;
    if(total > inventory_array[0])
    {
        cout << "You do not have sufficient funds. Please come back when you have enough money or purchase less" << endl;
    }
    else
    {
        if(index == 1)
        {
            int amount = inventory_array[index] + (2 * purchased);
            setinventory(1, amount);
            double money_spent = inventory_array[0] - total;
            setinventory(0, money_spent);
        }
        else if(index == 2)
        {
            int amount = inventory_array[index] + purchased;
            if(amount <= 1000)
            {
                setinventory(2, amount);
                double money_spent = inventory_array[0] - total;
                setinventory(0, money_spent);
            }
            else
            {
                cout << "Sorry. Max capacity on the wagon is 1000. Here's your money back and try again." << endl;
            }
        }
        else if(index == 3)
        {
            int amount = inventory_array[index] + (20 * purchased);
            setinventory(3, amount);
            double money_spent = inventory_array[0] - total;    
            setinventory(0, money_spent);
        }
        else if (index == 4 || index == 5 || index == 6 || index == 7)
        {
            int amount = inventory_array[index] + purchased;
            setinventory(index, amount);
            double money_spent = inventory_array[0] - total;
            setinventory(0, money_spent);
        }
    }
};