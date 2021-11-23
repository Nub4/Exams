#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <iostream>
# include <string>
# include "ATarget.hpp"

class ATarget;

class ASpell
{
    public:
        ASpell();
        ASpell(const std::string &name, const std::string &effects);
        ASpell(const ASpell &src);
        virtual ~ASpell();

        ASpell  &operator=(const ASpell &rhs);

        const std::string   &getName() const;
        const std::string   &getEffects() const;

        void    launch(const ATarget &ref);

        virtual ASpell  *clone() const = 0;

    private:
        std::string name;
        std::string effects;

};

#endif