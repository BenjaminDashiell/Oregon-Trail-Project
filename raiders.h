#ifndef RAIDERS_H
#define RAIDERS_H
#include <string>
using namespace std;

class Raiders
{
private:
    int raider_probability;
public:
////    "NO GAME BREAKING" FUNCTION     ////
    bool helper_function_stoicheck(string input);
////    RAIDER FUNCTIONS   ////
    bool getRaidersProbability(int miles_traveled);
    void displayraidersmenu(void);
    int raiderchoice(void);
    bool puzzle(void);
};
#endif