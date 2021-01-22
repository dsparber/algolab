///8
#include <iostream>
#include <vector>
#include <cmath>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt KSqrt;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2_traits_2<KSqrt> TraitsSqrt;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef CGAL::Min_circle_2<TraitsSqrt> MinCircleSqrt;
typedef K::Point_2 P;
typedef KSqrt::Point_2 PSqrt;
typedef KSqrt::FT FTSqrt;

using namespace std;

void print_sqrt(const FTSqrt &x2)
{
    FTSqrt x = CGAL::sqrt(x2);
    long a = CGAL::to_double(x);
    while (a > 0 && a - 1 > x) a -= 1;
    while (a < x) a += 1;
    cout << setprecision(0) << fixed << a << endl;
}

void solve(int n) {
    vector<P> points;

    if (n == 1) {
        print_sqrt(0);
        return;
    }

    points.reserve(n);
    for (int i = 0; i < n; ++i) {
        long x, y;
        cin >> x;
        cin >> y;
        points.push_back(P(x, y));
    }

    Min_circle minCircle(points.begin(), points.end(), true);

    vector<PSqrt> pointsSqrt;
    for (auto p = minCircle.support_points_begin(); p != minCircle.support_points_end(); ++p) {
        long x = CGAL::to_double(p->x());
        long y = CGAL::to_double(p->y());
        pointsSqrt.push_back(PSqrt(x, y));
    }
    MinCircleSqrt minCircleSqrt(pointsSqrt.begin(), pointsSqrt.end(), true);
    
    FTSqrt squared_radius = minCircleSqrt.circle().squared_radius();
    print_sqrt(squared_radius);
}

int main()
{
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n > 0) {
        solve(n);
        cin >> n;
    }
}