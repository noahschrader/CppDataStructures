#include "SmallVector.h"

#include <iostream>

struct A
{
    A()
    {
        std::cout << "A()" << std::endl;
    }

    A(const std::string& str) : str(str)
    {
        std::cout << "A(str)" << std::endl;
    }

    ~A()
    {
        std::cout << "~A()" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const A& a)
    {
        os << "A: " << a.str;
        return os;
    }

    std::string str;
};

int main()
{
    SmallVector<A, 1> svoAVector;
    svoAVector.push_back({"abcd"});
    std::cout << svoAVector[0] << std::endl;
    std::cout << "##########" << std::endl;
    svoAVector.push_back({"efgh"});
    std::cout << svoAVector[0] << std::endl;
    std::cout << svoAVector[1] << std::endl;
    std::cout << "##########" << std::endl;
    svoAVector.push_back({"ijkl"});
    svoAVector.push_back({"mnop"});
    std::cout << svoAVector[0] << std::endl;
    std::cout << svoAVector[1] << std::endl;
    std::cout << svoAVector[2] << std::endl;
    std::cout << svoAVector[3] << std::endl;
    std::cout << "##########" << std::endl;

    std::cout << "main finished" << std::endl;
    return 0;
}