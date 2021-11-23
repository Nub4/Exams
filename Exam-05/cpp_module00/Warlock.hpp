#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <string>

class Warlock
{
    public:
        Warlock(const std::string &name, const std::string &title);
        ~Warlock();

        const std::string   &getName() const;
        const std::string   &getTitle() const;

        void    introduce() const;

        void    setTitle(const std::string &title);

    private:
        std::string name;
        std::string title;

        Warlock();
        Warlock(const Warlock &src);
        Warlock &operator=(const Warlock &rhs);
};

#endif