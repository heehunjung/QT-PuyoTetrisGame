#ifndef ELEMENT_H
#define ELEMENT_H
#include <string>
#include <vector>

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
class Oshape:public Board
{
public:
    Oshape() : Board("Gray",6,-6) {}
};
class Tshape:public Board
{
public:
    Tshape() : Board("Gray",6,-6) {}
};
class Sshape:public Board
{
public:
    Sshape() : Board("Gray",6,-6) {}
};
class Zshape:public Board
{
public:
    Zshape() : Board("Gray",6,-6) {}
};
class Jshape:public Board
{
public:
    Jshape() : Board("Gray",6,-6) {}
};
class Lshape:public Board
{
public:
    Lshape() : Board("Gray",6,-6) {}
};
class Ishape:public Board
{
public:
    Ishape() : Board("Gray",6,-6) {}
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
class Points {
public:
    vector<Point*> points;

    void addPoint(Point* point) {
        points.push_back(point);
    }

    Point* getPoint(int index) {
        return points[index];
    }

    int size() const {
        return points.size();
    }

    ~Points() {
        for (Point* point : points) {
            delete point;
        }
    }
};

#endif // ELEMENT_H
