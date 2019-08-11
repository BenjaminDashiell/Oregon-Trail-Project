#ifndef MISFORTUNES_H
#define MISFORTUNES_H
#include <string>
using namespace std;

class Misfortunes
{
private:
    int misforunate_probability;
public:
////    "NO GAME BREAKING" FUNCTION     ////
    bool helper_function_stoicheck(string input);
////    MISFORUNATION FUNCTIONS   ////    
    int getMisfortunesChance(void);
    string getDisease(int index);
    int MisfortunesHappened(string partymember_one, string partymember_two, string partymember_three, string partymember_four, string partymember_five, int partymember_one_health, int partymember_two_health, int partymember_three_health, int partymember_four_health, int partymember_five_health, int oxen, int wagon_wheel, int wagon_axle, int wagon_tongue, int medkit);
};
#endif