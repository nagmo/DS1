
#ifndef EX1_GLADIATOR_H
#define EX1_GLADIATOR_H

#include "utility.h"
class Trainer;

class Gladiator {

public:

    Gladiator(GladiatorID, Trainer* = nullptr, Level = 0);
    ~Gladiator();
    Gladiator(const Gladiator&);

    Gladiator();

    Level GetLevel();
    GladiatorID GetGladiatorID();
    Trainer* GetTrainer();
    /**
     * increase the level by levelIncrease
     */
    void IncreaseLevel(LevelIncrease);

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

private:

    GladiatorID id;
    Level level;
    Trainer* trainer;
};


#endif //EX1_GLADIATOR_H
