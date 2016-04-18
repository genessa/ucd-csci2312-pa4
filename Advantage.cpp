//
// Created by Genessa Moodie on 4/7/16.
//

#include <sstream>
#include "Advantage.h"

namespace Gaming
{
    const char Advantage::ADVANTAGE_ID = 'D';

    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity)
    { }

    Advantage::~Advantage()
    { }


void Advantage::print(std::ostream &os) const
{
    std::string idString, idNum, temp;
    idString = Advantage::ADVANTAGE_ID;
    idNum = std::to_string(__id);

    temp = idString + idNum;
    os << temp;
}

double Advantage::getCapacity() const { return __capacity; }

double Advantage::consume() // add resource's energy to agent energy, delete resource
{
    double temp;
    temp = __capacity;
    finish(); // may need to use a more explicit deletion here
    __capacity = 0;
    return temp;
}

}// namespace