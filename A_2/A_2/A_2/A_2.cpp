#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> depot; // Global variable to store depot values
vector<vector<int>> memo; // Global variable to store memoization values
// Function to calculate strategic value
int strategicValue(int i, int j) {
	int sum = 0;
    for (int k = i; k <= (j+i)/2; k++) {
        for (int l = k + 1; l <= j; l++)
            sum += depot[k] * depot[l];
	}
	return sum;
}


int minStrategicValue(int n, int m,int curr, int start, int end)// number of depots = N, number of attacks = M
{
    if (m == 0)
    {
        return strategicValue(curr, end);
    }
    else if (curr == n)
    {
		return INT16_MAX;
	}
    else
    {
       return min(minStrategicValue(n,m,curr+1,start,end), strategicValue(start, curr) + (minStrategicValue(n, m - 1, curr + 1, curr+1, end)));
	}
}

int minStrategicValueTD(int n, int m, int curr, int start, int end) {
    if (m == 0) {
        return strategicValue(curr, end);
    }
    if (curr == n) {
        return INT16_MAX;
    }
    if (memo[curr][m] != -1) {
        return memo[curr][m];
    }

    int minVal = strategicValue(start, curr) + minStrategicValueTD(n, m - 1, curr + 1, curr + 1, end);
    minVal = min(minVal, minStrategicValueTD(n, m, curr + 1, start, end));

    memo[curr][m] = minVal;
    return minVal;
}

int minStrategicValueBU(int n, int m, int start, int end) {
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));

    // Base case when no attacks left
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = strategicValue(i, end);
    }

    // Initialize memoization for m = 1
    for (int i = 0; i <= n; ++i) {
        dp[i][1] = strategicValue(start, i);
    }
    //print(dp);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
			cout << dp[i][j] << " ";
		}
		cout << endl;
	}

    // Bottom-up DP filling
    for (int j = 1; j <= m; ++j) {
        for (int i = 0; i <= n; ++i) {
            for (int k = i + 1; k <= n; ++k) {
                dp[i][j] = min(dp[i][j], strategicValue(i, k) + dp[k][j - 1]);
            }
        }
    }

    cout << endl << endl;
    //print(dp);
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

    return dp[start][m];
}

int main() {
    depot = { 4,5, 1, 2 }; // Initializing depot with given values

    int n = depot.size() -1; // Number of depots
    int m = 2; // Number of attacks (assuming 2 as given in the example)
    memo.assign(n, vector<int>(m + 1, -1)); // Initializing memoization table with -1

    int result = minStrategicValueBU(n,m,0,n);
    cout << result << endl;
    return 0;
}
