#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

ifstream f("../input/input_day4.txt");

vector<vector<string>> passports(10000);
int n;

void split_passport(string s, int index) {
    int n = s.size();
    string word = "";
    for (int i = 0; i < n; i++) {
        if (s[i] == ' ') {
            passports[index].push_back(word);
            word = "";
        } else {
            word += s[i];
        }
    }
    if (word != "") {
        passports[index].push_back(word);
    }
}

void read() {
    string s;
    int i = 0;
    while(getline(f, s)) {
        if (s.empty()) {
            i++;
        } else {
            split_passport(s, i);
        }
    }
    n = i+1;
}

bool has_valid_fields(int index) {
    unordered_map<string, int> fields = {{"byr", 0}, {"iyr", 0}, {"eyr", 0},
                                         {"hgt", 0}, {"hcl", 0}, {"ecl", 0},
                                         {"pid", 0}};

    int found, fields_size= fields.size();
    string s;

    found = 0;
    for (int j = 0; j < passports[index].size(); j++) {
        s = passports[index][j].substr(0, 3);
        if (fields.find(s) != fields.end()) fields[s]++; 
    }
    
    for (auto field : fields) {
        if (field.second != 1) return false;
    }
    return true;
}

bool is_valid_field(string field) {
    string field_name = field.substr(0, 3),
           value = field.substr(field.find(":") + 1, field.size()), m;

    unordered_map<string, bool> eye_color = {{"amb", 1}, {"blu", 1},
                                             {"brn", 1}, {"gry", 1},
                                             {"grn", 1}, {"hzl", 1},
                                             {"oth", 1}};

    unordered_map<string, int> fields = {{"byr", 0}, {"iyr", 1}, {"eyr", 2},
                                         {"hgt", 3}, {"hcl", 4}, {"ecl", 5},
                                         {"pid", 6}, {"cid", 7}};
    
    int nr, v_size, index;

    //cout << "\n" << field_name << " " << value << "\n";

    switch(fields[field_name]) {

        case 0: 
            nr = stoi(value);
            if (nr < 1920 || nr > 2002) return false; 
            break;

        case 1:
            nr = stoi(value);
            if (nr < 2010 || nr > 2020) return false;
            break;

        case 2:
            nr = stoi(value);
            if (nr < 2020 || nr > 2030) return false; 
            break;

        case 3:
            index = 0;
            nr = stoi(value);
            while (index < value.size() && value[index] >= '0' && value[index] <= '9') index++;
            if (index >= value.size()) return false;
            m = value.substr(index);
            if (m != "in" && m != "cm") return false;
            if (m == "in" && (nr < 59 || nr > 76)) return false;
            if (m == "cm" && (nr < 150 || nr > 193)) return false;
            break;

        case 4:
            v_size = value.size();
            if (value[0] != '#') return false;
            for (int i = 1; i < v_size; i++)
                if ((value[i] < '0' || value[i] > '9') && (value[i] < 'a' && value[i] > 'f')) return 0;
            break;

        case 5:
            if (eye_color.find(value) == eye_color.end()) return false;
            break;

        case 6:
            v_size = value.size();
            if (v_size != 9) return false;
            for (int i = 0; i < v_size; i++)
                if (value[i] < '0' || value[i] > '9') return 0;
            break;
        
        case 7: break;

        default: break;
    }

    return true;
}

void part1() {
    cout << "Answer part 1: ";

    int result = 0;

    for (int i = 0; i < n; i++) {
        if (has_valid_fields(i)) result++;
    }
    cout << result << "\n";
}

void part2() {
    cout << "Answer part 2: ";

    int result = 0, p_size;
    bool found;
    string s;

    for (int i = 0; i < n; i++) {
        if (has_valid_fields(i)) {
            p_size = passports[i].size();
            found = 1;
            for (int j = 0; j < p_size && found; j++) {
                s = passports[i][j];
                if (!is_valid_field(s)) found = 0;
            }
            if (found) result++;
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
