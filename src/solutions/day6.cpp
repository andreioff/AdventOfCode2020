#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

ifstream f("../input/input_day6.txt");

vector<string> groups;
vector<int> groups_sizes;
int n;

void read() {
    string s;
    int i = 0;
    groups.push_back("");
    groups_sizes.push_back(0);

    while(getline(f, s)) {
        if (s.empty()) {
            i++;
            groups.push_back("");
            groups_sizes.push_back(0);
        } else {
            groups[i].append(s);
            groups_sizes[i]++;
        }
    }
    n = groups.size();
}

void part1() {
    cout << "Answer for part 1: ";
    
    int result = 0, ch_code;
    for (int i = 0; i < n; i++) {
        bitset<26> questions;
        for (int j = 0; j < groups[i].size(); j++) {
            ch_code = groups[i][j] - 'a';
            if(questions[ch_code] == 0) {
                result += 1;
                questions[ch_code] = 1;
            }
        }
    }
    cout << result << "\n";
}

void part2() {
    cout << "Answer for part 2: ";

    int result = 0, ch_code;
    for (int i = 0; i < n; i++) {
        vector<int> questions(26);
        for (int j = 0; j < groups[i].size(); j++) {
            ch_code = groups[i][j] - 'a';
            questions[ch_code]++;
        }
        for (int j = 0; j < 26; j++) {
            if (questions[j] == groups_sizes[i]) result++;
        }
    }
    cout << result << "\n";
}

int main() {
    
    read();  
    part1();
    part2();
    return 0;
}
