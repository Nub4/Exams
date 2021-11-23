#include "Warlock.hpp"

Warlock::Warlock(const std::string &name, const std::string &title){
    this->name = name;
    this->title = title;
    std::cout << this->name << ": This looks like another boring day.\n";
}

Warlock::~Warlock(){
    for (std::vector<ASpell *>::iterator it = this->arr.begin(); it != this->arr.end(); it++)
        delete *it;
    this->arr.clear();
    std::cout << this->name << ": My job here is done!\n";
}

const std::string   &Warlock::getName() const { return this->name; }
const std::string   &Warlock::getTitle() const { return this->title; }

void    Warlock::introduce() const {
    std::cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";
}

void    Warlock::setTitle(const std::string &title) { this->title = title; }

void    Warlock::learnSpell(ASpell *ptr){
    if (ptr == NULL)
        return ;
    for (std::vector<ASpell *>::iterator it = this->arr.begin(); it != this->arr.end(); it++)
        if ((*it)->getName() == ptr->getName())
            return ;
    this->arr.push_back(ptr->clone());
}

void    Warlock::forgetSpell(std::string name){
    for (std::vector<ASpell *>::iterator it = this->arr.begin(); it != this->arr.end(); it++){
        if ((*it)->getName() == name){
            delete *it;
            this->arr.erase(it);
            return ;
        }
    }
}

void    Warlock::launchSpell(std::string name, const ATarget &ref){
    for (std::vector<ASpell *>::iterator it = this->arr.begin(); it != this->arr.end(); it++)
        if ((*it)->getName() == name)
            (*it)->launch(ref);
}