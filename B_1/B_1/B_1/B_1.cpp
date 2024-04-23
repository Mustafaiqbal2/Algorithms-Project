#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> depot; // Global variable to store depot values
vector<vector<vector<int>>> memo; // Global variable to store memoization values
// Function to calculate strategic value
int strategicValue(int i, int j) {
    int sum = 0;
    for (int k = i; k <= j; k++)
    {
        int val = 0;
        for (int l = k + 1; l <= j; l++)
            val += depot[l];
        val *= depot[k];
        sum += val;
    }
    //cout << "i: " << i << " j: " << j << " sum: " << sum << endl;
    return sum;
}


int minStrategicValue(int n, int m, int curr, int start, int end) {
    if (m == 0) {
        return strategicValue(curr, end);
    }
    else if (curr == n) {
        return INT16_MAX; // Return a large value for invalid cases
    }
    else {
        int attack_here = strategicValue(start, curr) + minStrategicValue(n, m - 1, curr + 1, curr + 1, end);
        int skip_attack = minStrategicValue(n, m, curr + 1, start, end);
        if (attack_here == INT_MIN)
            attack_here = INT_MAX;
        return min(attack_here, skip_attack);
    }
}
int minStrategicValueTD(int n, int m, int curr, int start, int end) {
    // Base case: No attacks remaining
    if (m == 0) {
        return strategicValue(curr, end);
    }
    // Base case: Reached end of depots
    else if (curr == n) {
        return INT16_MAX; // Return a large value for invalid cases
    }
    // Check if the value is already computed
    else if (memo[curr][m][start] != -1) {
        return memo[curr][m][start];
    }
    else {
        // Calculate strategic value if attack is made at the current position
        int attack_here = strategicValue(start, curr) + minStrategicValueTD(n, m - 1, curr + 1, curr + 1, end);
        // Calculate strategic value if attack is skipped at the current position
        int skip_attack = minStrategicValueTD(n, m, curr + 1, start, end);
        // Update memoization array
        if (attack_here == INT_MIN) {
            attack_here = INT_MAX;
        }
        memo[curr][m][start] = min(attack_here, skip_attack);
        return memo[curr][m][start];
    }
}


int minStrategicValueBU(int n, int m) {
    vector<vector<vector<int>>> memo(n + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));

    // Base case: No attacks remaining
    for (int curr = 0; curr < n; ++curr) {
        for (int start = 0; start < n; ++start) {
            memo[curr][0][start] = strategicValue(curr, n);
        }
    }

    //print memo
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
            {
                cout << memo[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Iterate over all possible states
    for (int curr = n - 1; curr >= 0; --curr) {
        for (int attacks = 1; attacks <= m; ++attacks) {
            for (int start = curr; start >= 0; --start) {
                int& memo_value = memo[curr][attacks][start];
                int& attack_here = memo_value;
                int& skip_attack = memo[curr + 1][attacks][start];

                if (attack_here == -1) {
                    attack_here = strategicValue(start, curr) + memo[curr + 1][attacks - 1][curr + 1];
                    if (attack_here == INT_MIN) {
                        attack_here = INT16_MAX;
                    }
                }

                if (attacks < m) {
                    if (skip_attack == -1) {
                        skip_attack = memo[curr + 1][attacks][start];
                    }
                    if (attack_here == -1)
                        attack_here = INT16_MAX;
                    memo_value = min(attack_here, skip_attack);
                }
                else {
                    memo_value = attack_here;
                }
            }
        }
    }
    cout << endl << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < n; k++)
            {
                cout << memo[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return memo[0][m][0];
}

int main() {
    depot = { 8,5,4,8,7,3,6 }; // Initializing depot with given values

    int n = depot.size() - 1; // Number of depots
    int m = 3; // Number of attacks (assuming 2 as given in the example)
    memo.assign(n, vector<vector<int>>(m + 1, vector<int>(n, -1)));

    int result = minStrategicValueBU(n, m);
    cout << result << endl;
    return 0;
}