#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::~TargetGenerator(){
    for (std::vector<ATarget *>::iterator it = this->arr_target.begin(); it != this->arr_target.end(); it++)
        delete *it;
    this->arr_target.clear();
}

void    TargetGenerator::learnTargetType(ATarget *ptr){
    if (ptr == NULL)
        return ;
    for (std::vector<ATarget *>::iterator it = this->arr_target.begin(); it != this->arr_target.end(); it++)
        if ((*it)->getType() == ptr->getType())
            return ;
    this->arr_target.push_back(ptr->clone());
}

void    TargetGenerator::forgetTargetType(std::string const &type){
    for (std::vector<ATarget *>::iterator it = this->arr_target.begin(); it != this->arr_target.end(); it++){
        if ((*it)->getType() == type){
            delete *it;
            this->arr_target.erase(it);
            return ;
        }
    }
}

ATarget *TargetGenerator::createTarget(std::string const &type){
    for (std::vector<ATarget *>::iterator it = this->arr_target.begin(); it != this->arr_target.end(); it++)
        if ((*it)->getType() == type)
            return *it;
    return NULL;
}