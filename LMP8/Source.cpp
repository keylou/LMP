#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point {
    int coord_x;
    int coord_y;
    int id;
};

vector<Point> best_selection;
vector<Point> current_selection;
int n;
int bsx=INT_MAX, bsy= INT_MAX;
int sumx=0, simy=0;

void backtrack(vector<Point>& Points, double& minCG, vector<bool>& used, int j)
{
    if (current_selection.size() == n)
    {
        double CG;
        CG = sqrt((sumx * sumx) + (sumy * sumy)) / current_selection.size();
        if (CG < minCG)
        {
            minCG = CG;
            best_selection = current_selection;
            bsx = sumx;
            bsy = sumy;
        }
    }
    for (j; j < Points.size(); j++)
    {
        if (current_selection.size()==n)
            return;
        if (!used[j])
        {
            used[j] = true;
            current_selection.push_back(Points[j]);
            sumx += current_selection[k].coord_x;
            sumy += current_selection[k].coord_y;
            if (abs(sumx) < abs(bsx) || abs(sumy) < abs(bsy) )
                backtrack(Points, minCG, used, j,sumx,sumy);
            sumx -= current_selection[k].coord_x;
            sumy -= current_selection[k].coord_y;
            current_selection.pop_back();
            used[j] = false;
        }
    }
}

void init(vector<Point>& Points) {
    ifstream input("input.txt");
    int n;
    input >> n;

    for (int i = 0; i < n; i++) {
        Point Point;
        input >> Point.coord_x >> Point.coord_y;
        Point.id = i + 1;
        Points.push_back(Point);
    }

    input.close();
}

int main() {
    vector<Point> Points;
    init(Points);
    std::cout << "Input required number of points \n";
    std::cin >> n;

    vector<bool> used(Points.size(), false);
    double minCG = INT_MAX;

    for (int i = 0; i < Points.size(); i++)
    {
        cout << Points[i].coord_x << " " << Points[i].coord_y << '\n';
    }

    backtrack(Points, minCG, used, 0);

    cout << "Best selection: ";
    for (int i = 0; i < best_selection.size(); i++)
    {
        cout << best_selection[i].id << " ";
    }
    cout << endl << "MIN C.G.: " << minCG << endl;
}
