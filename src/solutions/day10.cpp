#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("../input/input_day10.txt");

vector<int> input;
int n;

void read() {
    int x;
    input.push_back(0);
    while (f >> x) {
        input.push_back(x);
    }
    n = input.size();

    sort(input.begin(), input.end());
    input.push_back(input[n-1] + 3);
    n++;
}

void part1() {
    cout << "Answer for part 1: ";
    
    int diff1 = 0, diff3 = 0, diff;
    
    for (int i = 1; i < n; i++) {
       diff = input[i] - input[i-1];
       if (diff == 1) diff1++;
       else if (diff == 3) diff3++;
    }
    cout << diff1 * diff3 << "\n";
}

long long ways(int offset, vector<int> arr, vector<long long> &memo) {
    int arr_size = arr.size();
    if (arr[arr_size - 1] == input[n - 1]) return 1;
    long long result = 0;
    for (int i = offset; i < n && input[i] - arr[arr_size - 1] <= 3; i++) {
        if (memo[i] == 0) {
            arr.push_back(input[i]);
            memo[i] = ways(i+1, arr, memo);
            arr.pop_back();
        }
        result += memo[i];
    }
    return result;
}

void part2() {
    cout << "Answer for part 2: ";
    
    vector<int> arr(n);
    vector<long long> memo(n);

    arr.push_back(0);
    cout << ways(1, arr, memo);
}

int main() {
    
    read();  
    part1();
    part2();
    return 0;
}
