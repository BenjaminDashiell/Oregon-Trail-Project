#ifndef MOVEMENT_H
#define MOVEMENT_H
#include <string>
using namespace std;

class Movement
{
private:
    int start_turn;
    int current_mileage;
    int move_miles;
    int index_number;
    string milestone_name[11];
    int milestone_miles[11];
    int milestone_depth[11];
    bool milestone_checkpoint[11];
public:
////    CONSTRUCTORS   ////
    //default constructor
    Movement(void);
    //parameterized constructor
    Movement(int currentmiles, int index);
////    "NO GAME BREAKING" FUNCTION     ////
    bool helper_function_stoicheck(string input);
////    MOVEMENT DATABASE   ////
    int split(string str, char c, string array[], int size);
    int readmilestones(string readfilename);
    string getmilestonename(int index);
    int getmilestonemiles(int index);
    int getmilestonedepth(int index);
    bool getmilestonecheck(int index);
    bool setmilestonecheck(int index);
    int milestone_status(void);
    int setMileage(int traveled);
    int getMileage(void);
////    MOVEMENT FUNCTIONS   ////    
    int displaychoices(void);
    int playgame(void);
};
#endif