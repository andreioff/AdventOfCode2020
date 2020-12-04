#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("input.txt");

vector<vector<bool>> input(500);
int n, m;

void read() {
    string s;

    while (f >> s) {
        m = s.size();
        for (int i = 0; i < m; i++) {
            input[n].push_back(s[i] == '.' ? 0 : 1);
        }
        n++;
    }
    /*for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << input[i][j] << " ";
        }
        cout << "\n";
    }*/
}

void part1() {
    cout << "Answer part 1: ";

    int x = 0, trees = 0;
    for (int i = 0; i < n; i++) {
        if (input[i][x]) trees++;
        x += 3;
        if (x >= m) x -= m;
    }
    cout << trees << "\n";
}

void part2() {
     cout << "Answer part 2: ";

    vector<pair<int, int>> slopes = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
    int slopes_size = slopes.size();
    long long result = 1;

    for (int i = 0; i < slopes_size; i++) {
        int x = 0, trees = 0;
        for (int j = 0; j < n; j += slopes[i].second) {
            if (input[j][x]) trees++;
            x += slopes[i].first;
            if (x >= m) x -= m;
        }
        if (trees > 0) result *= trees;
    }
    cout << result;
}

int main() {
    
    read();  
    part1();
    part2();
    return 0;
}
