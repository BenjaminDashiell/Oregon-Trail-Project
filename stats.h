#ifndef STATS_H
#define STATS_H
#include <string>
using namespace std;

class Stats
{
private:
    int index;
    string player_name;
    string party_member_names[5];
    int player_health;
    int party_member_health[5];
    double money_count;
    int oxen_count;
    int food_count;
    int bullets_count;
    int wheel_count;
    int axle_count;
    int tongues_count;
    int medkit_count;
    int inventory_array[9];
    double store_prices[8];
    int bullets[6];
    string highscores[5];
public:
    bool helper_function_stoicheck(string input);
////    HUNTING FUNCTIONS       ////
    int setBulletsLost(void);
    int getBulletsLost(int animal_index);
    bool getAnimalSpawn(int animal);
    int hunting_game(void);
    int checkfoodfull(int hunt);
    int hunt_menu(int animal);
    bool puzzle(int animal_index);
 ////    STATS FUNCTIONS       ////
    string getPlayerName(int index);
    void setPlayerName(int index, string input_name);
    int getHealthStatus(int index);
    void setHealthStatus(int index, int health);
    double beginninginventory(void);
    int getinventory(int index);
    int setinventory(int index, int amount);
////    STORE FUNCTIONS       ////    
    double prices(void);
    int setprices(int index, int store);
    void displaystoremenu(double money);
    int main_buyfromstore(void);
    double purchasing_items(int input, double starting_price, int index);
};
#endif