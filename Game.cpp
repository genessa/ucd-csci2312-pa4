//
// Created by Genessa Moodie on 3/31/16.
//

#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <sstream>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {


//    enum Status { NOT_STARTED, PLAYING, OVER };

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;

    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;

    PositionRandomizer Game::__posRandomizer; // should put each initial resource or agent in a randomizer selected pos

    void Game::populate() // populate the grid (used in automatic random initialization of a Game)
    {
        // construct grid, then put agents and resources into a set

        std::default_random_engine rand;
        std::uniform_int_distribution<int> dist(0, __width * __height);
        // std::unordered_set<Piece> gamePieces;

        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;
        // some kinda for loop, i < agents + resources
        while (numStrategic > 0)
        {
            int i = dist(rand);

            if (i != (__width * __height) && __grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        while (numSimple > 0)
        {
            int i = dist(rand);
            if (i != (__width * __height) && __grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        while (numFoods > 0)
        {
            int i = dist(rand);
            if (i != (__width * __height) && __grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }

        while (numAdvantages > 0)
        {
            int i = dist(rand);
            if (i != (__width * __height) && __grid[i] == nullptr)
            {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }
    }//populate
//
//    unsigned Game::__numInitAgents, Game::__numInitResources;
//    unsigned Game::__width, Game::__height;
//    std::vector<Piece *> __grid; // if a position is empty, nullptr
//    unsigned int Game::__round;
//    Game::Status Game::__status; // pretty sure this is already initialised further up??
//    bool Game::__verbose;

    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    Game::Game() : __width(3), __height(3)
    {
        for (unsigned i = 0; i < 9; ++i)
        { __grid.push_back(nullptr); }
        __status = NOT_STARTED;
        __verbose = false;
        __round = 0;
    }

    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height)  // note: manual population by default
    {    if (width < MIN_WIDTH || height < MIN_HEIGHT)
        { throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height); }

        __status = NOT_STARTED;
        __verbose = false;
        __round = 0;

        for (unsigned i = 0; i < (__width * __height); ++i)
        { __grid.push_back(nullptr); }

        if (!manual)
        { populate(); }
    }

    Game::~Game() // not much dynamically allocated, should be pretty short
    {
        for (auto curr = __grid.begin(); curr != __grid.end(); ++curr) //pointer arith. nerve racking.
        {
            if (*curr != nullptr)
            { delete *curr; }
        }
    }
    // getters
//    unsigned int getWidth() const { return __width; }
//    unsigned int getHeight() const { return __height; }
    unsigned int Game::getNumPieces() const
    { //iterate through game grid and count
        unsigned int temp = 0;
        for (auto curr = __grid.begin(); curr != __grid.end(); ++curr)
        {
            if (*curr != nullptr)
                temp++;
        }
        return temp;
    }

    unsigned int Game::getNumAgents() const //same method as getNumPieces but with casting
    {
        unsigned int temp = 0;
        for (auto curr = __grid.begin(); curr != __grid.end(); ++curr)
        {
            Agent *simple = dynamic_cast<Agent*>(*curr);
            if (simple)
            temp++;
        }
        return temp;
    }

    unsigned int Game::getNumSimple() const
    {
        unsigned int temp = 0;
        for (auto curr = __grid.begin(); curr != __grid.end(); ++curr)
        {
            Simple *simple = dynamic_cast<Simple*>(*curr);
            if (simple)
                temp++;
        }
        return temp;
    }

    unsigned int Game::getNumStrategic() const // could do same way, or run of above and subtract simple
    { return ( getNumAgents() - getNumSimple() ); }

    unsigned int Game::getNumResources() const // see prev.
    { return ( getNumPieces() - getNumAgents() ); }

//    Status Game::getStatus() const { return __status; }
//    unsigned int Game::getRound() const { return __round; }
    const Piece *Game::getPiece(unsigned int x, unsigned int y) const
    {
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[y + (x * __width)] == nullptr)
            throw PositionEmptyEx(x, y);

        return __grid[y + (x * __width)];
    }

    // grid population methods
    void Game::addSimple(const Position &position)
    {
        int index = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[index])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy) // used for testing only
    {
        int index = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[index])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Simple(*this, position, energy);
    }

    void Game::addSimple(unsigned x, unsigned y) // position in xy, default energy level
    {
        int index = y + (x * __width);

        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[index])
            throw PositionNonemptyEx(x, y);

        __grid[index] = new Simple(*this, Position(x, y), STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy)
    {
        int index = y + (x * __width);
        if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[index]) throw PositionNonemptyEx(x, y);

        __grid[index] = new Simple(*this, Position(x, y), energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s)
    {
        int index = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[index])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s)
    {
        int index = y + (x * __width);
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[index])
            throw PositionNonemptyEx(x, y);

        __grid[index] = new Strategic(*this, Position(x,y), STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position &position)
    {
        int index = position.y + (position.x * __width);

        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[index])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    void Game::addFood(unsigned x, unsigned y)
    {
        int index = y + (x * __width);
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[index])
            throw PositionNonemptyEx(x, y);

        __grid[index] = new Food(*this, Position(x,y), STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(const Position &position)
    {
        int index = position.y + (position.x * __width);
        if (position.y >= __width || position.x >= __height)
            throw OutOfBoundsEx(__width, __height, position.x, position.y);

        if (__grid[index])
            throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y)
    {
        int index = y + (x * __width);
        if (y >= __width || x >= __height)
            throw OutOfBoundsEx(__width, __height, x, y);

        if (__grid[index])
            throw PositionNonemptyEx(x, y);

        __grid[index] = new Advantage(*this, Position(x,y), STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const
    {
        Surroundings surr;
        for (int i = 0; i < 9; ++i)
        { surr.array[i] = EMPTY; }

        for (int row = -1; row <= 1; ++row)
        {
            for (int col = -1; col <= 1; ++col)
            {
                if ( (pos.x + row >= 0) && (pos.x + row < __height) && (pos.y + col >= 0) && (pos.y + col < __width) )
                {
                    // In bounds
                    unsigned int index = pos.y + col + ((pos.x + row) * __width);

                    if (__grid[index])
                        surr.array[col + 1 + ((row + 1) * 3)] = __grid[index]->getType();
                }

                else // outside
                { surr.array[col + 1 + ((row + 1) * 3)] = INACCESSIBLE; }
            }
        }
        surr.array[4] = SELF;
        return surr;
    }

    // gameplay methods
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) // note: STAY by default
    {
        int x, y;
        x = to.x - from.x;
        y = to.y - from.y;
        x++;
        y++;

        int index = (y + (x * 3));

        switch (index)
        {
            case 0: return NW;
            case 1: return N;
            case 2: return NE;
            case 3: return W;
            case 4: return STAY;
            case 5: return E;
            case 6: return SW;
            case 7: return S;
            case 8: return SE;
            default: return STAY;
        }
    }

//    const Position Game::randomPosition(const std::vector<int> &positions)  // note: from Surroundings as an array
//    { return __posRandomizer(positions); }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const
    {
        int x, y;
        x = pos.x;
        y = pos.y;
        switch (ac)
        {
            case E: y++; break;
            case NE: y++; x--; break;
            case N: x--; break;
            case NW: y--; x--; break;
            case W: y--; break;
            case SW: y--; x++; break;
            case S: x++; break;
            case SE: x++; y++; break;
            default: break;
        }
        Position p((unsigned )x, (unsigned)y);
        if (p.x < __height && p.y < __width)
            return true;
        return false;
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const  // note: assumes legal, use with isLegal()
    {    if (isLegal(ac, pos))
        {
            int x, y;
            x = pos.x;
            y = pos.y;
            switch (ac)
            {
                case E: y++; break;
                case NE: y++; x--; break;
                case N: x--; break;
                case NW: y--; x--; break;
                case W: y--; break;
                case SW: y--; x++; break;
                case S: x++; break;
                case SE: x++; y++; break;
                default: break;
            }
            Position p((unsigned )x, (unsigned)y);
            return p;
        }
        return pos;
    }

    void Game::round()    // play a single round
        {
        std::unordered_set<Piece*> pieces;
        for (auto it = __grid.begin(); it != __grid.end(); ++it)
        {
            if (*it)
            {
                pieces.insert(pieces.end(), *it);
                (*it)->setTurned(false);
            }
        }

        // Take turns
        for (auto it = pieces.begin(); it != pieces.end(); ++it)
        {
            if (!(*it)->getTurned())
            {
                (*it)->setTurned(true);
                (*it)->age();
                ActionType ac = (*it)->takeTurn(getSurroundings((*it)->getPosition()));
              Position pos0 = (*it)->getPosition();
                Position pos1 = move(pos0, ac);
                if (pos0.x != pos1.x || pos0.y != pos1.y)
                {
                    Piece *p = __grid[pos1.y + (pos1.x * __width)];
                    if (p) {
                        (*(*it)) * (*p);
                        if ((*it)->getPosition().x != pos0.x || (*it)->getPosition().y != pos0.y)
                        {
                            // piece moved
                            __grid[pos1.y + (pos1.x * __width)] = (*it);
                            __grid[pos0.y + (pos0.x * __width)] = p;
                        }
                    } else
                    {
                        // empty move
                        (*it)->setPosition(pos1);
                        __grid[pos1.y + (pos1.x * __width)] = (*it);
                        __grid[pos0.y + (pos0.x * __width)] = nullptr;
                    }
                }
            }
        }

        // Update positions and delete
        // Delete invalid first
        for (unsigned int i = 0; i < __grid.size(); ++i)
        {
            if (__grid[i] && !(__grid[i]->isViable()))
            {
                delete __grid[i];
                __grid[i] = nullptr;
            }
        }

        // Check game over
        if (getNumResources() <= 0) {
            __status = Status::OVER;
        }
        __round++;
    }

    void Game::play(bool verbose)
    {
        __status = PLAYING; // when to change it to over? just after while loop?
        while (__status != OVER)
        { round();
            if (verbose) std::cout << *this;
        }

        if (!verbose) std::cout << *this;
    }

    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        os << "Round " << game.__round << std::endl;
        int column = 0;
        for (auto it = game.__grid.begin(); it != game.__grid.end(); ++it)
        {
            if (*it == nullptr) {
                os << "[" << std::setw(6) << "]";
            }
            else
            {
                std::stringstream ss;
                ss << "[" << **it;
                std::string str;
                std::getline(ss, str);
                //os << str << std::setw(3) << "]";
                os << str << "]";
                //os << std::setw(4) << "[" << **it;
                //os << "]";
                //os ;
            }

            if (++column == game.__width)
            {
                column = 0;
                os << std::endl;
            }
        }
        os << "Status: ";
        switch (game.getStatus())
        {
            case Game::Status::NOT_STARTED:
                std::cout << "Not Started..." << std::endl;
                break;
            case Game::Status::PLAYING:
                std::cout << "Playing..." << std::endl;
                break;
            default:
                std::cout << "Over!" << std::endl;
                break;
        }
        return os;
    }

}