maxTeamPower(M, N, grid) :
    if M == 1 :
        // If only a single row, return the maximum element
        maxPower = 0
        for i from 0 to N - 1 :
            if grid[0][i] > maxPower:
maxPower = grid[0][i]
return maxPower

// Dynamic programming array to store the maximum power achievable
dp = allocate memory for 2D array of size M x N

// Initialize the first column of dp with the first column of grid
for i from 0 to M - 1:
dp[i][0] = grid[i][0]

// Initialize variables to keep track of maximum and second maximum power in the previous column
mmax = 0
prevmax = 0

// Update mmax and prevmax based on the first column of grid
for i from 0 to M - 1:
    if dp[i][0] > mmax:
        prevmax = mmax
        mmax = dp[i][0]
    else if dp[i][0] > prevmax:
        prevmax = dp[i][0]

// Iterate over each cell starting from the second column
// Initialize variables to keep track of maximum and second maximum power in the current column
int maxPower = 0;
int prevmaxPower = 0;
int lastcolmax = 0;
int lastcolprevmax = 0;

for j from 1 to N - 1:
    for i from 0 to M - 1 :
        if dp[i][j - 1] == mmax :
            if lastcolmax != dp[i][j - 1] and lastcolmax + grid[i][j] > prevmax + grid[i][j]:
                dp[i][j] = lastcolmax + grid[i][j]
            else if lastcolmax == dp[i][j - 1] and lastcolprevmax + grid[i][j] > prevmax + grid[i][j]:
                dp[i][j] = lastcolprevmax + grid[i][j]
            else :
                dp[i][j] = prevmax + grid[i][j]
         else:
            if lastcolmax != dp[i][j - 1] and lastcolmax + grid[i][j] > mmax + grid[i][j]:
                dp[i][j] = lastcolmax + grid[i][j]
            else :
                dp[i][j] = mmax + grid[i][j]

    // Update max and second max
    maxPower = 0
    prevmaxPower = 0
    for i from 0 to M - 1:
        if dp[i][j] > maxPower:
            prevmaxPower = maxPower
            maxPower = dp[i][j]
        else if dp[i][j] > prevmaxPower:
            prevmaxPower = dp[i][j]

    if maxPower > mmax:
        lastcolmax = mmax
        mmax = maxPower
    if prevmaxPower > prevmax:
        lastcolprevmax = prevmax
        prevmax = prevmaxPower

 
// Find the maximum power achievable from the last column
maxPpower = 0
for i from 0 to M - 1:
    maxPpower = max(maxPpower, dp[i][N - 1]);

    // Deallocate memory for dp
    deallocate memory for dp

        // Return the maximum power achievable
return maxPpower

END


