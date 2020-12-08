#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

ifstream f("../input/input_day8.txt");

vector<pair<int, int>> code;
unordered_map<string, int> instr = {{"nop", 0}, {"acc", 1}, {"jmp", 2}};

int n;

void read() {
    string instruction, nr;
    while (f >> instruction) {
        f >> nr;
        code.push_back(make_pair(instr[instruction], stoi(nr)));
    }
    n = code.size();
}

void apply_instruction(int &i, int &result) {
    int ins = code[i].first, nr = code[i].second;

    switch(ins) {
        
        case 0:
            i++;
            break;

        case 1:
            result += nr;
            i++;
            break;

        case 2:
            i += nr;
            break;

        default:
            break;
    }
}

bool execute(int &result, vector<bool> v) {
    int i = 0;

     while(i < n && !v[i]) {
        v[i] = 1;
        apply_instruction(i, result);
    }

    return (i == n) ? 1 : 0;
}

void part1() {
    cout << "Answer for part 1: ";
    vector<bool> v(n);
    int result = 0;

    execute(result, v);

    cout << result << "\n";
    
}

void part2() {
    cout << "Answer for part 2: ";
    int result, switch_instr;
    vector<bool> v(n);

    for (int i = 0; i < n; i++) {
        if (code[i].first == 0 || code[i].first == 2) {
            switch_instr = (code[i].first == 0) ? 2 : -2;
            code[i].first += switch_instr;
            result = 0;
            if (execute(result, v)) {
                cout << result << "\n";
                break;
            }
            code[i].first -= switch_instr;
        }
    }
}

int main() {
    
    read(); 
    part1();
    part2();
    return 0;
}

