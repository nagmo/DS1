//
// Created by Nevo Agmon on 27/11/2017.
//

#include "Gladiator.h"

Gladiator::Gladiator(GladiatorID gladiatorID, Level level = 0, TrainerID trainerID = 0) :
        id(gladiatorID), level(level), trainer(trainerID) {}
Gladiator::~Gladiator() = default;
Gladiator::Gladiator(const Gladiator& gladiator){
    id =gladiator.id;
    level = gladiator.level;
    trainer = gladiator.trainer;
}

Level Gladiator::GetLevel(){
    return level;
}

TrainerID Gladiator::GetTrainerID(){
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