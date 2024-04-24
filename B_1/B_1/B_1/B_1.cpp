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
    else if (memo[m][curr][start] != -1) {
        return memo[m][curr][start];
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
        memo[m][curr][start] = min(attack_here, skip_attack);
        return memo[m][curr][start];
    }
}


int minStrategicValueBU(int n, int m, int end) {
    // Initialize the DP array
    std::vector<std::vector<std::vector<int>>> dp(n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(n+1, INT16_MAX)));

    // Base case for no remaining attacks
    for (int curr = 0; curr <= n; ++curr) {
        for (int start = 0; start < n; ++start) {
            dp[curr][0][start] = strategicValue(curr, end);
        }
    }

    // Base case when curr == n
    for (int attack = 0; attack <= m; ++attack) {
        for (int start = 0; start < n; ++start) {
            dp[n][attack][start] = INT16_MAX;
        }
    }

    // Fill the DP table
    for (int curr = n - 1; curr >= 0; --curr) {
        for (int remainingAttacks = 1; remainingAttacks <= m; ++remainingAttacks) {
            for (int start = 0; start <= curr; ++start) {
                int attack_here = strategicValue(start, curr) + dp[curr + 1][remainingAttacks - 1][curr + 1];
                int skip_attack = dp[curr + 1][remainingAttacks][start];
                dp[curr][remainingAttacks][start] = std::min(attack_here, skip_attack);
            }
        }
    }

    // The answer is the minimal strategic value starting from depot 0 with m attacks remaining
    return dp[0][m][0];
}
int main() {
    depot = {8,5,4,8,7,3,6 }; // Initializing depot with given values

    int n = depot.size() - 1; // Number of depots
    int m = 1; // Number of attacks (assuming 2 as given in the example)
    memo.assign(m + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, -1)));

    int result = minStrategicValueBU(n, m, n);//, 0, 0, n);
    cout << result << endl;
    return 0;
}