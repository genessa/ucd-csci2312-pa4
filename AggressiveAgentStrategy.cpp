//
// Created by Genessa Moodie on 4/7/16.
//

#include <random>
#include <chrono>
#include "AggressiveAgentStrategy.h"
#include "Game.h"

namespace Gaming {

//    class AggressiveAgentStrategy : public Strategy {
//        double __agentEnergy;
//
    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy)
    { __agentEnergy = agentEnergy; }

    AggressiveAgentStrategy::~AggressiveAgentStrategy()
    { }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const // notes about aggressive agent interaction..
    {
        std::vector<int> positions;

        // this randomizer is from http://www.cplusplus.com/reference/algorithm/shuffle/
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rnd(seed);

        if (__agentEnergy > DEFAULT_AGGRESSION_THRESHOLD)
        {
            for (int i = 0; i < 9; ++i) //this is going to fail the added big test, gah
            {
                if (s.array[i] == PieceType::SIMPLE || s.array[i] == PieceType::STRATEGIC)
                { positions.push_back(i); }
            }//for
        }//if

        //  advantage
        if (positions.size() == 0)
        {
            for (int i = 0; i < 9; ++i)
            {
                if (s.array[i] == PieceType::ADVANTAGE)
                { positions.push_back(i); }
            }
        }

        //  if no advantage, food
        if (positions.size() == 0)
        {
            for (int i = 0; i < 9; ++i)
            {
                if (s.array[i] == PieceType::FOOD)
                { positions.push_back(i); }
            }
        }

        //
        if (positions.size() == 0) {
            for (int i = 0; i < 9; ++i)
            {
                if (s.array[i] == PieceType::EMPTY)
                { positions.push_back(i); }
            }
        }

        if (positions.size() > 0)
        {
            int posIndex = positions[rnd() % positions.size()];

            if (positions.size() == 1)
                posIndex = positions[0];

            ActionType action;
            switch (posIndex) //so much easier than doing this with ifs
            {
                case 0: action = NW;
                    break;
                case 1: action = N;
                    break;
                case 2: action = NE;
                    break;
                case 3: action = W;
                    break;
                case 4: action = STAY;
                    break;
                case 5: action = E;
                    break;
                case 6: action = SW;
                    break;
                case 7: action = S;
                    break;
                case 8: action = SE;
                    break;
                default: action = STAY;
            }
            return (action);
        }

        return ActionType::STAY;
    }


}