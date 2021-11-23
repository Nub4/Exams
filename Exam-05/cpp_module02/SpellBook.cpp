#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook(){
    for (std::vector<ASpell *>::iterator it = this->arr_spell.begin(); it != this->arr_spell.end(); it++)
        delete *it;
    this->arr_spell.clear();
}

void    SpellBook::learnSpell(ASpell *ptr){
    if (ptr == NULL)
        return ;
    for (std::vector<ASpell *>::iterator it = this->arr_spell.begin(); it != this->arr_spell.end(); it++)
        if ((*it)->getName() == ptr->getName())
            return ;
    this->arr_spell.push_back(ptr->clone());
}

void    SpellBook::forgetSpell(std::string const &name){
    for (std::vector<ASpell *>::iterator it = this->arr_spell.begin(); it != this->arr_spell.end(); it++){
        if ((*it)->getName() == name){
            delete *it;
            this->arr_spell.erase(it);
            return ;
        }
    }
}

ASpell  *SpellBook::createSpell(std::string const &name){
    for (std::vector<ASpell *>::iterator it = this->arr_spell.begin(); it != this->arr_spell.end(); it++)
        if ((*it)->getName() == name)
            return *it;
    return NULL;
}