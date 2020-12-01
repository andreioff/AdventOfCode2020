#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

ifstream f("input.txt");

vector<int> input;
int n; //size of input

void read() {
    int x;
    while(f >> x) input.push_back(x);
    n = input.size();
}

void part1() {
    cout << "Answer to part1: ";

    unordered_map<int, int> complement;
    int x;
    bool found = 0;

    for (int i = 0; i < n && !found; i++) {
        x = input[i];
        if (complement.find(x) != complement.end()) {
            cout << x*complement[x] << "\n";
            found = 1;
        }
        complement[2020 - x] = x;
    }
    
    if (!found) cout << "not found!\n";
}

void part2() {
    cout << "Answer to part 2: ";
    
    int new_sum, x;
    bool found = 0;

    for (int i = 0; i < n && !found; i++) {
        new_sum = 2020 - input[i];
        unordered_map<int, int> complement;
        for (int j = i+1; j < n && !found; j++) {
            x = input[j];
            if (complement.find(x) != complement.end()) {
                cout << input[i]*x*complement[x] << "\n";
                found = 1;
            }
            complement[new_sum - x] = x;
        }
    }

    if (!found) cout << "not found!\n";
}

int main() {
    read();
    part1();
    part2();
    return 0;
}
