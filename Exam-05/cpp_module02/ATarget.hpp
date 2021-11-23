#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <iostream>
# include <string>
# include "ASpell.hpp"

class ASpell;

class ATarget
{
    public:
        ATarget();
        ATarget(const std::string &type);
        ATarget(const ATarget &src);
        virtual ~ATarget();

        ATarget &operator=(const ATarget &rhs);

        const std::string   &getType() const;

        void    getHitBySpell(const ASpell &ref) const;

        virtual ATarget *clone() const = 0;

    private:
        std::string type;

};

#endif