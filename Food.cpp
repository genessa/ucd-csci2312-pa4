//
// Created by Genessa Moodie on 4/7/16.
//
#include <iomanip>
#include <sstream>
#include "Food.h"

namespace Gaming
{

    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity)
    { }

    Food::~Food()
    { }

    void Food::print(std::ostream &os) const
    {
        std::string idString, idNum, temp;
        idString = Food::FOOD_ID;
        idNum = std::to_string(__id);

        temp = idString + idNum;
        os << temp;
    }
}