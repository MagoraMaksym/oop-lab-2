#include "header.h"
#include <iostream>
#include <cmath>

using namespace std;

double cross(Point A, Point B, Point P) {
    return (B.x - A.x)*(P.y - A.y) - (B.y - A.y)*(P.x - A.x);
}

double dist2(Point a, Point b) {
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
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
            // 🔥 знайти найдовший відрізок
            Point p1 = t.A, p2 = t.B;

            if (dist2(t.A, t.C) > dist2(p1, p2)) {
                p1 = t.A; p2 = t.C;
            }
            if (dist2(t.B, t.C) > dist2(p1, p2)) {
                p1 = t.B; p2 = t.C;
            }

            double d = cross(p1, p2, p);

            bool onLine = fabs(d) < 1e-9;
            bool onSeg =
                p.x >= min(p1.x, p2.x) &&
                p.x <= max(p1.x, p2.x) &&
                p.y >= min(p1.y, p2.y) &&
                p.y <= max(p1.y, p2.y);

            if (onLine && onSeg)
                cout << "Vector method: On segment\n";
            else
                cout << "Vector method: Outside\n";

            double S1 = fabs((p.x*(p2.y-p1.y) + p2.x*(p1.y-p.y) + p1.x*(p.y-p2.y))/2.0);

            if (S1 < 1e-9 && onSeg)
                cout << "Area method: On segment\n";
            else
                cout << "Area method: Outside\n";
        }
    }
}        Point p;
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
            double d = cross(t.A, t.B, p);

            bool onLine = fabs(d) < 1e-9;

            bool onSeg =
                p.x >= min(min(t.A.x, t.B.x), t.C.x) &&
                p.x <= max(max(t.A.x, t.B.x), t.C.x) &&
                p.y >= min(min(t.A.y, t.B.y), t.C.y) &&
                p.y <= max(max(t.A.y, t.B.y), t.C.y);

            if (onLine && onSeg)
                cout << "Vector method: On segment\n";
            else
                cout << "Vector method: Outside\n";

            double S1 = fabs((p.x*(t.B.y-t.C.y) + t.B.x*(t.C.y-p.y) + t.C.x*(p.y-t.B.y))/2.0);

            if (S1 < 1e-9 && onSeg)
                cout << "Area method: On segment\n";
            else
                cout << "Area method: Outside\n";
        }
    }
}

