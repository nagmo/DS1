//
// Created by Nevo Agmon on 27/11/2017.
//

#include "Gladiator.h"
Gladiator::Gladiator(GladiatorID gladiatorID, Trainer* trainer,  Level level) :
        id(gladiatorID), level(level), trainer(trainer) {}

Gladiator::~Gladiator() = default;

Gladiator::Gladiator(const Gladiator& gladiator) : id(gladiator.id),
                                                   trainer(gladiator.trainer), level(gladiator.level){
}

Level Gladiator::GetLevel(){
    return level;
}

Trainer* Gladiator::GetTrainer(){
    return trainer;
}

void Gladiator::IncreaseLevel(LevelIncrease levelIncrease){
    level += levelIncrease;
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