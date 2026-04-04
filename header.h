#ifndef LAB_2_HEADER_H
#define LAB_2_HEADER_H

struct Point
{
    double x, y;
};

struct Triangle
{
    Point A, B, C;

    double area() const;
    bool contains(const Point &P) const;
    bool containsArea(const Point &P) const;
    bool onEdge(const Point &P) const;
};

void run();

#endif
