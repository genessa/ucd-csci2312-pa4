//
// Created by Genessa Moodie on 3/31/16.
//
#include "Agent.h"
#include "Advantage.h"

namespace Gaming
{

//    double Agent::__energy;

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g,p), __energy(energy)
    { }

    Agent::~Agent()
    { }

//    double Agent::getEnergy() const
//    { return __energy; }
//
//    void addEnergy(double e)
//    { __energy += e; } //call when Interact-ing with resource

    void Agent::age() // call at end of takeTurn or whatever that's called?
    {
        __energy = __energy - AGENT_FATIGUE_RATE;
    }
//    bool Agent::isViable()
//    {
//          Shouldn't need this, it's already implemented in Piece
//    }

//    const override Agent::final{return !isFinished() && __energy > 0.0;}

    Piece &Agent::operator*(Piece &p1)
    {
        if (p1.isViable())
        { // conditions go by casting tests
            Piece *p = &p1;
            Resource *res = dynamic_cast<Resource*>(p);
            if (res)
            { interact(res); }

            Agent *agent = dynamic_cast<Agent*>(p);
            if (agent)
            { interact(agent); }

            if (!isFinished())
            {
                Position newPos;
                newPos = p1.getPosition();
                Position oldPos;
                oldPos = getPosition();
                setPosition(newPos);
                p1.setPosition(oldPos);
            }

        }//if isViable
        return *this;
    }//operator*


    Piece &Agent::interact(Agent *a1)
    {
        {
            if (__energy == a1->__energy)
            {
                finish(); // for calling agent
                a1->finish(); // for parameter agent
                //return 0?
            }

            if (__energy > a1->__energy) //calling agent wins
            {
                addEnergy(a1->__energy);
                a1->finish(); // rip a1
                return *this;
            }
            else // a1 wins
            {
                a1->__energy = a1->__energy - __energy;
                finish();
                return *this;
            }

        }



    }

    Piece &Agent::interact(Resource *res)
    {
        __energy = __energy + res->getCapacity();
        return *this;
    }

}//namespace