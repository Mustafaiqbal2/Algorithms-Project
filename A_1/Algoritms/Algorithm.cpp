#include <iostream>

using namespace std;
int memo[201][201];

int helperRecurse(int n, int prevStage);
void printMemo(int n)
{
    cout << "\t";
    for (int i = 0; i <= n; i++)
    {
		cout << i << "\t";
	}
    cout << endl;
    cout<<"\t";
    for (int i = 0; i <= n; i++)
    {
        cout << "_\t";
    }
    cout << endl;

    for (int i = 0; i <= n; ++i)
    {
        cout<< i<<"|\t";
        for (int j = 0; j <= n; ++j)
        {
            cout << memo[i][j] << "\t";
        }
        cout << endl<<endl;
    }
}

int countStructuresRecursive(int n) {
    
    int sum = 0;
    int i = 0;
    while (sum < n)
    {
		i++;
		sum += i;
	}
    int totalStructures = 0;
    // Iterate over possible heights for the first stage
    for (; i < n; ++i) {
        // Calculate the number of structures for the remaining blocks after considering the first stage of height i
        totalStructures += helperRecurse(n - i,i);
    }

    return totalStructures;
}
int helperRecurse(int n, int prevStage)
{
    if (n == 2)
    {
        if (n >= prevStage)
        {
		    return 0;
	    }
    }
    if (n == 3 && n < prevStage)
    {
		return 2;
	}
    if (n < 3) {
        // Base case: if n is 0 or 1, there's only one possible structure
        return 1;
    }

    int totalStructures = 0;
    // Iterate over possible heights for the first stage
    //minimum number of blocks in a stage is n/2-1
    for (int i = min(prevStage-1,n); i >= 2 ; --i) {
        totalStructures += helperRecurse(n - i, i);
    }
    return totalStructures;
}
//TOP DOWN
//ROWS = number of blocks left COLUMN = height of Previous stage

int helperRecurseTD(int n, int prevStage) {
    if (n == 2) {
        if (n >= prevStage) {
            return 0;
        }
    }
    if (n == 3 && n < prevStage) {
        return 2;
    }
    if (n < 3) {
        return 1;
    }

    if (memo[n][prevStage] != -1) {
        return memo[n][prevStage];
    }

    int totalStructures = 0;
    // Iterate over possible heights for the first stage
    for (int i = min(prevStage - 1, n); i >= 2; --i) {
        totalStructures += helperRecurseTD(n - i, i);
    }

    return memo[n][prevStage] = totalStructures;
}

int countStructuresTD(int n) 
{
    memset(memo, -1, sizeof(memo));

    //memo[remaining blocks][height of previous stage]
    int totalStructures = 0;
    for (int i = 2; i < n; ++i) {
        totalStructures += helperRecurseTD(n - i, i);
    }

    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (memo[i][j] == -1)
                cout << "X" << " ";
            else 
                cout << memo[i][j] << " ";
        }
        cout << endl;
    }
    return totalStructures;
}
//BOTTOM UP
int countStructuresBU(int n) 
{
    // Initialize the memoization table
    for (int i = 0; i <= n; ++i) {
        if (i > 0)
        {
            memo[0][i] = 1;
            if (i > 1)
            {
                memo[1][i] = 1;
                if (i > 2)
                {
                    memo[2][i] = 1;
                    if (i > 3)
                        memo[3][i] = 2;
                    else
                        memo[3][i] = 1;
                }
            }
        }
    }
    //printMemo(n);
    // Populate the memoization table iteratively
    for (int i = 4; i <= n; ++i) 
    {
        for (int j = 4; j <= n; ++j) 
        {
            for (int k = 3; k <= min(j - 1, i); ++k) 
            {
                memo[i][j] += memo[i - k][k];
            }
        }
    }
    //printMemo(n);
    // Calculate the total structure
    return memo[n][n];
}

int main()
{
    //cout<< countStructuresTD(10) << endl;
    cout<< countStructuresBU(200) << endl;
}