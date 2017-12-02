
#include "Gladiator.h"
Gladiator::Gladiator(GladiatorID gladiatorID, Trainer* trainer,  Level level, bool subOrderFlag) :
        id(gladiatorID), level(level), trainer(trainer), subOrderFlag(subOrderFlag) {}

Gladiator::Gladiator(const Gladiator& gladiator) :
        id(gladiator.id), trainer(gladiator.trainer),
        level(gladiator.level), subOrderFlag(gladiator.subOrderFlag) {}

Level Gladiator::GetLevel(){
    return level;
}

Trainer* Gladiator::GetTrainer(){
    return trainer;
}

void Gladiator::IncreaseLevel(LevelIncrease levelIncrease){
    level += levelIncrease;
}
void Gladiator::MultiplyLevel(LevelIncrease levelIncrease){
    level *= levelIncrease;
}
/**
 * two gladiators are equal if have the same id
 * @param gladiator
 * @return
 */
bool Gladiator::operator==(Gladiator& gladiator){
    return id == gladiator.id;
}
/**
 * compare by id
 * @param gladiator
 * @return
 */
bool Gladiator::operator<(Gladiator& gladiator){
    if(subOrderFlag){
        return level < gladiator.level ? id > gladiator.id : false;
    }
    return id < gladiator.id;
}
/**
 * compare by id
 * @param gladiator
 * @return
 */
bool Gladiator::operator>(Gladiator& gladiator){
    return !(*this < gladiator || *this == gladiator);
}

void Gladiator::SetFlag(bool flag) {
    subOrderFlag = flag;
}
GladiatorID Gladiator::GetGladiatorID(){
    return id;
}

