#include "ATarget.hpp"

ATarget::ATarget() {}

ATarget::ATarget(const std::string &type) { this->type = type; }

ATarget::ATarget(const ATarget &src) { this->type = src.type; }

ATarget::~ATarget() {}

ATarget &ATarget::operator=(const ATarget &rhs){
    this->type = rhs.type;
    return *this;
}

const std::string   &ATarget::getType() const { return this->type; }

void    ATarget::getHitBySpell(const ASpell &ref) const{
    std::cout << this->type << " has been " << ref.getEffects() << "!\n";
}