#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

ifstream f("../input/input_day9.txt");

int preamble = 25, n;
vector<long long> input;
long long invalid_nr;

void read() {
    long long x;
    while (f >> x) {
        input.push_back(x);
    }
    n = input.size();
}

void part1() {
    cout << "Answer for part 1: ";
    
    int start_i = 0;
    long long start = input[start_i], x;
    unordered_map<long long, bool> complement;
    bool found;

    for (int i = 0; i < preamble; i++) complement[input[i]] = 1;
    for (int i = preamble; i < n; i++) {
        x = input[i];
        found = 0;
        for (auto k : complement) {
            if (complement.find(x - k.first) != complement.end()) {
                found = 1;
                break;
            }
        }
        if (found) {
            complement.erase(complement.find(start));
            start_i++;
            start = input[start_i];
            complement[input[i]] = 1;
        } else {
            cout << x << "\n";
            invalid_nr = x;
            break;
        }
    }
}

long long mini(int start, int end) {
    int mini = input[start];
    for (int i = start+1; i <= end; i++) {
        if (input[i] < mini) mini = input[i];
    } 
    return mini;
}

long long maxi(int start, int end) {
    int maxi = input[start];
    for (int i = start+1; i <= end; i++) {
        if (input[i] > maxi) maxi = input[i];
    }
    return maxi;
}

void part2() {
    cout << "Answer for part 2: ";

    int start, end;
    long long sum;
    bool found = 0;
    for (int i = 0; i < n && !found; i++) {
        start = end = i, sum = input[i];
        while(end < n && sum < invalid_nr) {
            end++;
            sum += input[end];
            if (sum == invalid_nr) {
                cout << mini(start, end) + maxi(start, end) << "\n";
                found = 1;
            }
        }
    }
}

int main() {
    
    read();  
    part1();
    part2();
    return 0;
}
