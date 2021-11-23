#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

# include <iostream>
# include <string>
# include <vector>
# include "ASpell.hpp"

class ASpell;

class SpellBook
{
    public:
        SpellBook();
        ~SpellBook();

        void    learnSpell(ASpell *ptr);
        void    forgetSpell(std::string const &name);
        ASpell  *createSpell(std::string const &name);

    private:
        std::vector<ASpell *> arr_spell;

        SpellBook(const SpellBook &src);
        SpellBook   &operator=(const SpellBook &rhs);
};

#endif