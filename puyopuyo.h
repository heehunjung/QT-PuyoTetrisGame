#ifndef PUYOPUYO_H
#define PUYOPUYO_H
#include <string>

using namespace std;

class Board
{
public:
    std::string color;
    int value;
    int afterValue;
    Board(const std::string& c, int v, int a) : color(c), value(v), afterValue(a) {}
};
class Red:public Board
{
public:
    // Constructor for Red that initializes the Board base class
    Red() : Board("Red", 1, -1) {}
};
class Yellow:public Board
{
public:
    // Constructor for Red that initializes the Board base class
    Yellow() : Board("Yellow", 2, -2) {}
};
class Green:public Board
{
public:
    // Constructor for Red that initializes the Board base class
    Green() : Board("Green", 3, -3) {}
};
class Blue:public Board
{
public:
    // Constructor for Red that initializes the Board base class
    Blue() : Board("Blue", 4, -4) {}
};
class Purple:public Board
{
public:
    // Constructor for Red that initializes the Board base class
    Purple() : Board("Purple", 5, -5) {}
};
class Point{
public:
    int x;
    int y;

    Point(int x,int y)
    {
        this->x = x;
        this->y = y;
    }
};
class PointPuyopuyo:public Point {
public:
    PointPuyopuyo(): Point(0,0){};
    PointPuyopuyo(int x,int y): Point(x,y){};
};

#endif // PUYOPUYO_H
