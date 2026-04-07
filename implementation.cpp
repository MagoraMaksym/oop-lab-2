#include "header.h"
#include <iostream>
#include <cmath>

using namespace std;

double cross(Point A, Point B, Point P) {
    return (B.x - A.x)*(P.y - A.y) - (B.y - A.y)*(P.x - A.x);
}

double Triangle::area() const {
    return fabs((A.x*(B.y-C.y) + B.x*(C.y-A.y) + C.x*(A.y-B.y))/2.0);
}

bool Triangle::contains(const Point &P) const {
    if (area() < 1e-9) return false;

    double d1 = cross(A,B,P);
    double d2 = cross(B,C,P);
    double d3 = cross(C,A,P);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

bool Triangle::containsArea(const Point &P) const {
    double S = area();
    if (S < 1e-9) return false;

    double S1 = fabs((P.x*(B.y-C.y) + B.x*(C.y-P.y) + C.x*(P.y-B.y))/2.0);
    double S2 = fabs((A.x*(P.y-C.y) + P.x*(C.y-A.y) + C.x*(A.y-P.y))/2.0);
    double S3 = fabs((A.x*(B.y-P.y) + B.x*(P.y-A.y) + P.x*(A.y-B.y))/2.0);

    return fabs(S - (S1 + S2 + S3)) < 1e-9;
}

bool Triangle::onEdge(const Point &P) const {
    double d1 = cross(A,B,P);
    double d2 = cross(B,C,P);
    double d3 = cross(C,A,P);

    return (fabs(d1) < 1e-9 || fabs(d2) < 1e-9 || fabs(d3) < 1e-9);
}

void run() {
    Triangle t;
    cout << "Enter triangle coordinates: ";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;

    bool deg = (t.area() < 1e-9);

    if (deg) {
        cout << "Degenerate triangle\n";
    }

    int n;
    cout << "Enter number of points: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;

        if (!deg) {
            if (t.contains(p)) {
                cout << "Vector method: Inside";
                if (t.onEdge(p)) cout << " (on edge)";
            } else {
                cout << "Vector method: Outside";
            }
            cout << "\n";

            if (t.containsArea(p)) {
                cout << "Area method: Inside";
                if (t.onEdge(p)) cout << " (on edge)";
            } else {
                cout << "Area method: Outside";
            }
            cout << "\n";
        } else {
            if (t.onEdge(p)) {
                cout << "Point is on line\n";
            } else {
                cout << "Point is outside line\n";
            }
        }
    }
}
