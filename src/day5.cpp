#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("input.txt");

vector<string> passes;
int n;
const char FRONT = 'F',
           BACK = 'B',
           LEFT = 'L',
           RIGHT = 'R';

void read() {
    string s;
    while (f >> s) {
        passes.push_back(s);
    }
    n = passes.size();
}

void part1() {
    cout << "Answer for part 1: ";
    int low, high, j, max_id = 0, m, row, col, id, s_size;
    string s;
    for (int i = 0; i < n; i++) {
        low = j = 0, high = 127, s = passes[i], s_size = s.size();

        while(j < s_size && (s[j] == FRONT || s[j] == BACK)) {
            m = (low + high) / 2;
            if (s[j] == BACK) low = m+1;
            else high = m;
            j++;
        }
        row = low;

        low = 0, high = 7;
        while(j < s_size && (s[j] == LEFT || s[j] == RIGHT)) {
            m = (low + high) / 2;
            if (s[j] == RIGHT) low = m+1;
            else high = m;
            j++;
        }
        col = low;
        
        id = row * 8 + col;
        if (id > max_id) max_id = id;
    }
    cout << max_id << "\n";
}

void part2() {
    cout << "Answer for part 2: ";
    int low, high, j, max_id = 0, m, row, col, id, s_size;
    string s;
    vector<int> ids;
    for (int i = 0; i < n; i++) {
        low = j = 0, high = 127, s = passes[i], s_size = s.size();

        while(j < s_size && (s[j] == FRONT || s[j] == BACK)) {
            m = (low + high) / 2;
            if (s[j] == BACK) low = m+1;
            else high = m;
            j++;
        }
        row = low;

        low = 0, high = 7;
        while(j < s_size && (s[j] == LEFT || s[j] == RIGHT)) {
            m = (low + high) / 2;
            if (s[j] == RIGHT) low = m+1;
            else high = m;
            j++;
        }
        col = low;
        
        id = row * 8 + col;
        ids.push_back(id);
    }
    sort(ids.begin(), ids.end());
    for (int i = 1; i < n; i++) 
        if (ids[i]-ids[i-1] == 2) {
            cout << ids[i] - 1; 
            break;
        }
}

int main() {
    
    read();  
    part1();
    part2();
    return 0;
}
