#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> depot; // Global variable to store depot values
vector<vector<vector<int>>> memo; // Global variable to store memoization values
// Function to calculate strategic value
int strategicValue(int i, int j)
{
    // Calculate cumulative sums of the depot array
    vector<int> cumulativeSum(j + 1, 0);
    for (int k = j; k >= i; --k) {
        cumulativeSum[k] = depot[k] + (k + 1 <= j ? cumulativeSum[k + 1] : 0);
    }

    // Calculate strategic value using precomputed cumulative sums
    int sum = 0;
    for (int k = i + 1; k <= j; ++k) {
        sum += depot[k-1] * cumulativeSum[k];
    }

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
    std::vector<std::vector<std::vector<int>>> dp(n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(n + 1, INT16_MAX)));
    std::vector<std::vector<int>> dp2(n + 1, std::vector<int>(n + 1));

    // Base case for no remaining attacks
    for (int curr = 0; curr <= n; ++curr) {
        for (int start = 0; start < n; ++start) {
            dp[curr][0][start] = strategicValue(curr, end);
        }
    }
    
    // Base case when curr == n
    for (int attack = 0; attack <= m; ++attack) {
        for (int start = 0; start < n; ++start) {
            dp[n][attack][n] = 0;
        }
    }
    /*
    //calculate all possible commulative sums
    vector<vector<int>> cumulativeSum(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++)
    {
        for (int k = n; k > i; --k)
        {
            cumulativeSum[i][k] = depot[k] + (k + 1 <= n ? cumulativeSum[i][k + 1] : 0);
        }
    }
    //
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k <= n; k++)
        {
            cout << cumulativeSum[i][k] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //Preprocessing for Start to curr
    for (int start = 0; start < n; start++)
    {
        int sum = 0;
        for (int curr = start + 1; curr < n; curr++)
        {
            dp2[curr][start] = dp2[curr - 1][start] + depot[curr] * cumulativeSum[start][n - curr];
        }
    }
    cout << '\n' << "DP2" << endl;
    //Print dp2
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << dp2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
	//Preprocessing for Start to curr
    for (int start = 0; start < n; start++)
	{
	    for (int curr = start+1; curr < n; curr++)
		{
			dp2[curr][start] = strategicValue(start, curr);
		}
	}

    //Print dp2
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << dp2[i][j] << " ";
		}
		cout << endl;
	}
    

    // Fill the DP table
    for (int curr = n - 1; curr >= 0; --curr) {
        for (int remainingAttacks = 1; remainingAttacks <= m; ++remainingAttacks) {
            for (int start = 0; start <= curr; ++start) {
                int attack_here = dp2[curr][start] + dp[curr + 1][remainingAttacks - 1][curr + 1];
                int skip_attack = dp[curr + 1][remainingAttacks][start];
                dp[curr][remainingAttacks][start] = std::min(attack_here, skip_attack);
            }
        }
    }
    //print
    for (int rema = 0; rema <= m; rema++)
    {
        for (int curr = 0; curr < n; curr++)
        {
            for (int start = 0; start < n; start++)
            {
				cout << dp[curr][rema][start] << " ";
            }
			cout << endl;
        }
        cout << endl;
    }

    // The answer is the minimal strategic value starting from depot 0 with m attacks remaining
    return dp[0][m][0];
}
int main() {
    do
    {
        int n,m;
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        for (int i = 0; i < n; i++)
        {
            int num;
            cin >> num;
            depot.push_back(num);
        }
        memo.assign(m + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, -1)));
        int result = minStrategicValueBU(n - 1, m , n - 1);//, 0, 0, n);
        cout << result << endl;
        depot.clear();
    } 
    while (1);

    return 0;
}