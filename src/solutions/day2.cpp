#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream f("../input/input_day2.txt");

vector<string> input;
vector<pair<char, pair<int, int>>> rules;
int n;

void read() {
    string s;
    int mini, maxi;
    char c;

    while(f >> mini) {
        f >> c >> maxi >> c;
        rules.push_back(make_pair(c, make_pair(mini, maxi)));

        f >> c >> s;
        input.push_back(s);
    }
    n = input.size();
}

void part1() {
    cout << "Answer part 1: ";

    int mini, maxi, c, count, result = 0;
    string s;
    for (int i = 0; i < n; i++) {
       mini = rules[i].second.first; 
       maxi = rules[i].second.second;
       c = rules[i].first;
       count = 0;
       s = input[i];

       for (int j = 0; j < s.size() && count <= maxi; j++) {
            if (s[j] == c) count ++; 
       }
       if (count >= mini && count <= maxi) result++;
    }
    cout << result << "\n";
}

void part2() {
    cout << "Answer part 2: ";
 
    int mini, maxi, c, result = 0;
    string s;
    bool found1, found2;
    for (int i = 0; i < n; i++) {
        mini = rules[i].second.first;
        maxi = rules[i].second.second;
        c = rules[i].first;
        s = input[i];
        found1 = found2 = false;

        if (mini > 0 && mini <= s.size() && s[mini-1] == c) found1 = true; 
        if (maxi > 0 && maxi <= s.size() && s[maxi-1] == c) found2 = true; 
        if ((found1 && !found2) || (!found1 && found2)) result++;
    }

    cout << result << "\n";
}

int main() {
    
    read();  
    part1();
    part2();
    return 0;
}
