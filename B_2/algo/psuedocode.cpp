//                  QUESTION 1
Function countStructuresRecursive(n)
    sum = 0
    i = 0
    while sum < n
        i++
        sum += i
        End while
        totalStructures = 0
        for i = i to n
            totalStructures += helperRecurse(n - i, i)
            End for
            Return totalStructures
End Function

Function helperRecurse(n, prevStage)
    if n == 2 and n >= prevStage
        Return 0
    End if
    if n == 3 and n < prevStage
        Return 2
        End if
        if n < 3
            Return 1
            End if
            totalStructures = 0
            for i = min(prevStage - 1, n) to 2
                totalStructures += helperRecurse(n - i, i)
                End for
                Return totalStructures
    End Function

Function countStructuresTD(n)
    Initialize memoization table with -1
    totalStructures = 0
    for i = 2 to n
        totalStructures += helperRecurseTD(n - i, i)
    End for
    Output memoization table
    Return totalStructures
End Function


Function helperRecurseTD(n, prevStage)
    if n == 2 and n >= prevStage
        Return 0
    End if
    if n == 3 and n < prevStage
        Return 2
    End if
    if n < 3
        Return 1
    End if
    if memo[n][prevStage] is not -1
        Return memo[n][prevStage]
    End if
    totalStructures = 0
    for i = min(prevStage - 1, n) to 2
        totalStructures += helperRecurseTD(n - i, i)
    End for
    memo[n][prevStage] = totalStructures
    Return totalStructures
End Function



//                  QUESTION 2


Function strategicValue(i, j)
    sum = 0
    for k = i to j
        val = 0
        for l = k + 1 to j
            val += depot[l]
        End for
        val *= depot[k]
        sum += val
    End for
    Return sum
End Function


Function minStrategicValue(n, m, curr, start, end)
    If m == 0
        Return strategicValue(curr, end)
    Else if curr == n
        Return INT16_MAX
    Else
        attack_here = strategicValue(start, curr) + minStrategicValue(n, m - 1, curr + 1, curr + 1, end)
        skip_attack = minStrategicValue(n, m, curr + 1, start, end)
        If attack_here == INT_MIN
            attack_here = INT_MAX
        End if
        Return min(attack_here, skip_attack)
    End if
End Function


Function minStrategicValueTD(n, m, curr, start, end)
    If m == 0
        Return strategicValue(curr, end)
    Else if curr == n
        Return INT16_MAX
    Else if memo[m][curr][start] != -1
        Return memo[m][curr][start]
    Else
        attack_here = strategicValue(start, curr) + minStrategicValueTD(n, m - 1, curr + 1, curr + 1, end)
        skip_attack = minStrategicValueTD(n, m, curr + 1, start, end)
        If attack_here == INT_MIN
            attack_here = INT_MAX
        End if
        memo[m][curr][start] = min(attack_here, skip_attack)
        Return memo[m][curr][start]
    End if
End Function


Function minStrategicValueBU(n, m, end)
    Initialize dp array with dimensions (n + 1) x (m + 1) x (n + 1) filled with INT16_MAX

    For curr = 0 to n
        For start = 0 to n - 1
            dp[curr][0][start] = strategicValue(curr, end)
        End for
    End for

    For attack = 0 to m
        For start = 0 to n - 1
            dp[n][attack][start] = INT16_MAX
        End for
    End for

    For curr = n - 1 down to 0
        For remainingAttacks = 1 to m
            For start = 0 to curr
                attack_here = strategicValue(start, curr) + dp[curr + 1][remainingAttacks - 1][curr + 1]
                skip_attack = dp[curr + 1][remainingAttacks][start]
                dp[curr][remainingAttacks][start] = min(attack_here, skip_attack)
            End for
        End for
    End for

    Return dp[0][m][0]
End Function


//                  QUESTION 3

dividearrayMNPN(arr) :
    // Create a hashmap to store unique elements from the array
            hash = create empty unordered set
            n = size of arr

            // Insert elements of arr into the hashmap
            for i from 0 to n - 1:
             hash.insert(arr[i])

        // Calculate mnpn (minimum non-positive number) from the hashmap
        mnpn = 0
        while mnpn is found in hash :
        mnpn++

        // Output mnpn
        output "mnpn: " + mnpn

        // Initialize variables for counting and finding index
        count = 0
        index = -1
        unique = create empty unordered set

        // Iterate through the array elements before the mnpn
        for i from 0 to n - 1:
         if arr[i] < mnpn and arr[i] is not in unique :
            increment count
         if count is equal to mnpn :
            set index to(i + 1)
            break
        insert arr[i] into unique

        // Reset count and initialize another unique set
        count = 0
        unique1 = create empty unordered set

        // Iterate through the array elements after the found index
        for i from index to n - 1:
            if arr[i] < mnpn and arr[i] is not in unique1 :
            increment count
        insert arr[i] into unique1

        // Check if count equals mnpn after the found index
        if count is equal to mnpn :
    // Display the result when both segments meet the conditions
        output "2"
        output "[" + 1 + ", " + index + "]"
        output "[" + (index + 1) + ", " + n + "]"
        else:
    // Display -1 when the conditions are not met
        output "-1"


//                  QUESTION 4
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


