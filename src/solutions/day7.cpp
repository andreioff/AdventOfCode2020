#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <bitset>

using namespace std;

ifstream f("../input/input_day7.txt");

vector<vector<pair<int, int>>> g(1000);
int n;
unordered_map<string, int> color_map;

int add_node(string s, int start) {
    int code, end;
    string node;

    end = s.find(" bag", start);
    node = s.substr(start, end - start);
    if (color_map.find(node) == color_map.end()) {
        code = n;
        n++;
        color_map[node] = code;  
    } else {
        code = color_map[node];
    }
    return code;        
}

void read() {
    string s;
    int parent_code, start, child_code, comma, child_nr;

    while (getline(f, s)) {
        parent_code = add_node(s, 0);
        start = s.find(" bag") + 14;
        
        if (s.substr(start, s.size()) != "no other bags.") {
            do {
                child_nr = stoi(s.substr(start, s.find(" ", start) - start));
                start = s.find(" ", start) + 1;

                child_code = add_node(s, start);
                g[parent_code].push_back(make_pair(child_code, child_nr));

                comma = s.find(", ", start);
                start = comma + 2;
            } while(comma != -1);
        }
    }
}

void dfs_part1(int root, int target, unordered_map<int, int> &bags_target, vector<bool> &v) {
    v[root] = 1;
    for (auto node : g[root]) {
        if (node.first == target || (v[node.first] && bags_target.find(node.first) != bags_target.end())) {
            bags_target[root] = 1;
        } else if (!v[node.first]) {
            dfs_part1(node.first, target, bags_target, v);
            if (bags_target.find(node.first) != bags_target.end()) {
                bags_target[root] = 1;
            }
        }
    } 
}

void part1() {
    cout << "Answer for part 1: ";

    unordered_map<int, int> bags_target;
    vector<bool> v(n);
    int target = color_map["shiny gold"];
     

    for (int i = 0; i < n; i++) {
        if (!v[i] && i != target) {
            dfs_part1(i, target, bags_target, v);
        }
    }
    cout << bags_target.size() << "\n";
}

int dfs_part2(int root, vector<bool> &v) {
    int result = 0, node_bags;
    v[root] = 1;
    for (auto node : g[root]) {
        if (!v[node.first]) {
            node_bags = dfs_part2(node.first, v);
            result += node.second;
            result += node.second*node_bags;
        }
    }
    v[root] = 0;
    return result;
}

void part2() {
    cout << "Answer for part 2: ";
    int target = color_map["shiny gold"];
    vector<bool> v(n);
    
    cout << dfs_part2(target, v) << "\n";
}

int main() {
    
    read();  
    part1();
    part2();
    return 0;
}
