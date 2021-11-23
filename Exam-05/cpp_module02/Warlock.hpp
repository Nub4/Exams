#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <string>
# include <vector>
# include "ASpell.hpp"
# include "ATarget.hpp"
# include "SpellBook.hpp"

class Warlock
{
    public:
        Warlock(const std::string &name, const std::string &title);
        ~Warlock();

        const std::string   &getName() const;
        const std::string   &getTitle() const;

        void    introduce() const;

        void    setTitle(const std::string &title);

        void    learnSpell(ASpell *ptr);
        void    forgetSpell(std::string name);
        void    launchSpell(std::string name, const ATarget &ref);

    private:
        std::string name;
        std::string title;

        SpellBook   book;

        Warlock();
        Warlock(const Warlock &src);
        Warlock &operator=(const Warlock &rhs);
};

#endif