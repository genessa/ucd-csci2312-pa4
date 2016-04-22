//
// Created by Genessa Moodie on 3/31/16.
//
#include "Piece.h"

namespace Gaming {

//    class Piece {
//
//    private:
        unsigned int Piece::__idGen = 1000;
//
//        bool __finished;
//        bool __turned;
//
//        Position __position;
//
//    protected:
//        const Game &__game; // note: a reference to the Game object

//
//        virtual void print(std::ostream &os) const = 0;
//
//        void finish() { __finished = true; }
//        bool isFinished() const { return __finished; }

        Piece::Piece(const Game &g, const Position &p) : __game(g), __position(p)
        {
            __id = __idGen;
            __idGen++;
            __finished = false;
            __turned = false;
        }

        Piece::~Piece() {} // this doesn't get implemented riiiight?
//
//        const Position getPosition() const { return __position; }
//        void setPosition(const Position &p) { __position = p; }
//
//        bool getTurned() const { return __turned; }
//        void setTurned(bool turned) { __turned = turned; }
//
//        virtual void age() = 0;
//        virtual bool isViable() const = 0;
//        virtual PieceType getType() const = 0;
//
//        virtual ActionType takeTurn(const Surroundings &surr) const = 0; // note: doesn't actually change the object
//
//        virtual Piece &operator*(Piece &other) = 0;
//        virtual Piece &interact(Agent *) = 0;
//        virtual Piece &interact(Resource *) = 0;

        std::ostream &operator<<(std::ostream &os, const Piece &piece)
        {
            piece.print(os);
            return os;
        }

}