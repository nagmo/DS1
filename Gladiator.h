
#ifndef EX1_GLADIATOR_H
#define EX1_GLADIATOR_H

#include "utility.h"
class Trainer;

class Gladiator {

public:

    explicit Gladiator(GladiatorID, Trainer* = NULL, Level = 0, bool subOrderFlag = false);
    ~Gladiator(){}
    Gladiator(const Gladiator&);

    Level GetLevel();
    GladiatorID GetGladiatorID();
    Trainer* GetTrainer();
    /**
     * increase the level by levelIncrease
     */
    void IncreaseLevel(LevelIncrease);

    void MultiplyLevel(LevelIncrease);
    /**
     * two gladiators are equal if have the same id
     * @param gladiator
     * @return
     */
    bool operator==(Gladiator& gladiator);
    /**
     * compare by id
     * @param gladiator
     * @return
     */
    bool operator<(Gladiator& gladiator);
    /**
     * compare by id
     * @param gladiator
     * @return
     */
    bool operator>(Gladiator& gladiator);

    void SetFlag(bool);

private:

    bool subOrderFlag;
    GladiatorID id;
    Level level;
    Trainer* trainer;
};


class UpdateGladLevel{
public:
    UpdateGladLevel(StimulantCode stimulantCode, StimulantFactor stimulantFactor):
            stimulantCode(stimulantCode), stimulantFactor(stimulantFactor){};
    void operator()(Gladiator& glad){
        if(glad.GetGladiatorID() % stimulantCode == 0)
            glad.MultiplyLevel(stimulantFactor);
    }

private:
    StimulantFactor stimulantFactor;
    StimulantCode stimulantCode;
};


#endif //EX1_GLADIATOR_H
