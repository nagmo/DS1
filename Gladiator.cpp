
#include "Gladiator.h"
Gladiator::Gladiator(GladiatorID gladiatorID, Trainer* trainer,  Level level, bool subOrderFlag) :
        subOrderFlag(subOrderFlag), id(gladiatorID), level(level), trainer(trainer) {}

Gladiator::Gladiator(const Gladiator& gladiator) :
        subOrderFlag(gladiator.subOrderFlag) , id(gladiator.id), level(gladiator.level),
        trainer(gladiator.trainer){}

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
        return (level == gladiator.level) ? (id > gladiator.id) : (level < gladiator.level);
    }
    return id < gladiator.id;
}
/**
 * compare by id
 * @param gladiator
 * @return
 */
bool Gladiator::operator>(Gladiator& gladiator){
    return (!(*this < gladiator) && !(*this == gladiator));
}

void Gladiator::SetFlag(bool flag) {
    subOrderFlag = flag;
}
GladiatorID Gladiator::GetGladiatorID(){
    return id;
}

