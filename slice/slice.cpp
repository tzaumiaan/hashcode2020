#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> slice(vector<int>& pizza, int num_slices) {
        // greedy solution
        vector<int> order;
        int sum = 0;
        for (int i = (int)pizza.size()-1; i >= 0; --i){
            if (pizza[i] + sum <= num_slices) {
                sum += pizza[i];
                order.insert(order.begin(), i);
            }
            if (sum + pizza[0] >= num_slices) break;
        }
        return order;
    }
};

vector<int> parse_line(const string& s, char delimiter=' ') {
   vector<int> array;
   string token;
   stringstream ss(s);
   while (std::getline(ss, token, delimiter))
      array.push_back(stoi(token));
   return array;
}

int main() {
    string line;
    getline(cin, line);
    vector<int> line1 = parse_line(line);
    getline(cin, line);
    vector<int> line2 = parse_line(line);
    vector<int> result = Solution().slice(line2, line1[0]);
    string out = to_string(result.size()) + '\n';
    for (int i : result) out += to_string(i) + ' ';
    out = out.substr(0, out.size()-1) + '\n';
    cout << out;
}
