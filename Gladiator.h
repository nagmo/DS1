
#ifndef EX1_GLADIATOR_H
#define EX1_GLADIATOR_H

#include "utility.h"

class Gladiator {

public:

    Gladiator(GladiatorID, Level = 0, TrainerID = 0);
    ~Gladiator();
    Gladiator(const Gladiator&);
    Level GetLevel();
    TrainerID GetTrainerID();
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
    TrainerID trainer;
};


#endif //EX1_GLADIATOR_H
