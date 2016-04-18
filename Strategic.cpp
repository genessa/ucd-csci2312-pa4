//
// Created by Genessa Moodie on 4/7/16.
//
#include <sstream>
#include <iomanip>
#include "Strategic.h"

namespace Gaming {

    const char Strategic::STRATEGIC_ID = 'T';
    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s)
            : Agent(g, p, energy)
    { __strategy = s; }

    Strategic::~Strategic()
    {
        delete __strategy;
    }

    void Strategic::print(std::ostream &os) const
    {
        std::string idString, idNum, temp;
        idString = Strategic::STRATEGIC_ID;
        idNum = std::to_string(__id);

        temp = idString + idNum;
        os << temp;
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const
    {
        return (*__strategy)(s);
    }
}//namespace