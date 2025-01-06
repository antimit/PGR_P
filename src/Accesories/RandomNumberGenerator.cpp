#include "RandomNumberGenerator.hpp"
#include <random>
#include <stdexcept>

using namespace std;


us generateRandomNumber(us range1, us range2)
{
    if (range1 > range2) 
    {
        throw std::invalid_argument("range1 must be less than or equal to range2");
    }
    static std::random_device randomDevice;   
    static std::mt19937 mt(randomDevice());  
    std::uniform_int_distribution<unsigned short> distribution(range1, range2);
    return distribution(mt); 

}