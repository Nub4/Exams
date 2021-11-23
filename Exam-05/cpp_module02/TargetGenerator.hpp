#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

# include <iostream>
# include <string>
# include <vector>
# include "ATarget.hpp"

class ATarget;

class TargetGenerator
{
    public:
        TargetGenerator();
        ~TargetGenerator();

        void    learnTargetType(ATarget *ptr);
        void    forgetTargetType(std::string const &type);
        ATarget *createTarget(std::string const &type);

    private:
        std::vector<ATarget *> arr_target;

        TargetGenerator(const TargetGenerator &src);
        TargetGenerator &operator=(const TargetGenerator &rhs);
};

#endif