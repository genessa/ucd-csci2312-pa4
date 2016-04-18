//
// Created by Genessa Moodie on 4/7/16.
//

#include "Resource.h"

namespace Gaming {
    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g,p), __capacity(capacity)
    { }

    Resource::~Resource()
    { }

    void Resource::age()
    {
        if (__capacity == 0)
        { finish(); }

        __capacity = __capacity / RESOURCE_SPOIL_FACTOR;
    }

    double Resource::consume()
    {
        double temp = __capacity;
        __capacity = 0;
        finish();
        return temp;
    }

    ActionType Resource::takeTurn(const Surroundings &s) const
    { return STAY; }

    // note: these won't be called while resources don't move
    Piece &Resource::operator*(Piece &other) { return *this; } //just to shut up compiler

    Piece &Resource::interact(Agent *)
    { return *this; }

    Piece &Resource::interact(Resource *)  // note: no interaction between resources
    { return *this; }
} //namespace