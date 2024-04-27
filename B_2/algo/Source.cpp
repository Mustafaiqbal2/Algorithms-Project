#include <iostream>
#include <algorithm>

using namespace std;

int maxTeamPower(int M, int N, int** grid) {

    // if only single row, return max element
    if (M == 1)
    {
        int maxPower = 0;
        for (int i = 0; i < N; ++i)
        {
            if (grid[0][i] > maxPower)
                maxPower = grid[0][i];
        }

        return maxPower;
    }

    int** dp = new int* [M];
    for (int i = 0; i < M; ++i)
        dp[i] = new int[N];

    // Initialize first column

    for (int i = 0; i < M; ++i) 
    {
        dp[i][0] = grid[i][0];

    }

    // keep track of maximum and second maximum power in the previous column
    int mmax = 0;
    int prevmax = 0;
    for (int i = 0; i < M; ++i) {
        if (dp[i][0] > mmax)
        {
            prevmax = mmax;
            mmax = dp[i][0];
        }
        else if (dp[i][0] > prevmax)
        {
            prevmax = dp[i][0];
        }
    }
    // Iterate over each cell
    int maxPower = 0;
    int prevmaxPower = 0;

    int lastcolmax = 0;
    int lastcolprevmax = 0;
    for (int j = 1; j < N; ++j) 
    {

        for (int i = 0; i < M; ++i) 
        {
            if (dp[i][j - 1] == mmax)
            {
                if (lastcolmax!=dp[i][j - 1] && lastcolmax + grid[i][j] > prevmax + grid[i][j])
                    dp[i][j] = lastcolmax + grid[i][j];
                else if (lastcolmax == dp[i][j - 1] && lastcolprevmax + grid[i][j] > prevmax + grid[i][j])
                    dp[i][j] = lastcolprevmax + grid[i][j];
                else
                    dp[i][j] = prevmax + grid[i][j];
            }
            else
            {
                if (lastcolmax != dp[i][j - 1] && lastcolmax + grid[i][j] > mmax + grid[i][j])
                    dp[i][j] = lastcolmax + grid[i][j];
                else
                dp[i][j] = mmax + grid[i][j];
            }
        }

        // update max and second max
        maxPower = 0;
        prevmaxPower = 0;
        for (int i = 0; i < M; ++i) 
        {
            if (dp[i][j] > maxPower)
            {
                prevmaxPower = maxPower;
                maxPower = dp[i][j];
            }
            else if (dp[i][j] > prevmaxPower)
            {
                prevmaxPower = dp[i][j];
            }
        }

        //cout << "maxPower: " << maxPower << endl;
        //cout << "prevmaxPower: " << prevmaxPower << endl;

        if (maxPower > mmax)
        {
            lastcolmax = mmax;
            mmax = maxPower;
        }
        if (prevmaxPower > prevmax)
        {
            lastcolprevmax = prevmax;
            prevmax = prevmaxPower;
        }
    }

    // Find the maximum power achievable from the last column
    int maxPpower = 0;
    for (int i = 0; i < M; ++i) {
        maxPpower = max(maxPpower, dp[i][N - 1]);
    }

    
    for (int j = 0; j < M; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            cout << dp[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Free allocated memory
    for (int i = 0; i < M; ++i)
        delete[] dp[i];
    delete[] dp;

    return maxPower;
}

int main() {
    cout << endl;
cout << "Enter input:" << endl;

    int M, N;
    cin >> M >> N;

    // Dynamically allocate memory for grid
    int** grid = new int* [M];
    for (int i = 0; i < M; ++i) {
        grid[i] = new int[N];
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    cout << endl;

    // Calculate and output the maximum team power
    cout << "max Power: "<< maxTeamPower(M, N, grid) << endl;

    // Free allocated memory for grid
    for (int i = 0; i < M; ++i)
        delete[] grid[i];
    delete[] grid;


    return 0;
}

