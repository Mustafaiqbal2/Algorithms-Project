#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Function to calculate MNPN for a segment of the array
int calculateMNPN(const vector<int>& arr, int i, int j) {
    unordered_set<int> present;

    // Mark numbers present in the segment
    for (int k = i; k <= j; k++) {
        present.insert(arr[k]);
	}

    // Find the smallest non-present number
    int MNPN = 0;
    while (present.count(MNPN) != 0) {
        MNPN++;
    }

    return MNPN;
}
// Function to divide the array into segments with consistent MNPN
pair<int, vector<pair<int, int>>> divideArray(const vector<int>& arr) {
    int n = arr.size();
    int **dp = new int*[n];
    for (int i = 0; i < n; i++) {
        dp[i] = new int[n] {0};
	}

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
               dp[i][j]= calculateMNPN(arr, i, j);
        }
    }
    //print dp array
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
			cout<<dp[i][j]<<" ";
		}
		cout<<endl;
	}
    
    vector<pair<int, int>> segmentRanges;
    int ind = 0;
    int count = 0;
    
    for (int j = 0; j < n-1 && ind != n; j++) {
        bool flag = 1;
        for (int k = j + 1; k < n; k++)
        {
            if (dp[j][k] != dp[ind][j])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            if (dp[j + 1][j + 2] != dp[ind][j] && j + 2 < n)
            {
				continue;
			}
            segmentRanges.push_back({ ind + 1, j + 1 });
            ind = j + 1;
            count++;
        }
    }
    
    segmentRanges.push_back({ ind + 1, n });
    count++;
    

    cout<<count<<endl;
   
    
   
	//free memory
    for (int i = 0; i < n; i++) {
		delete[] dp[i];
	}
	delete[] dp;

    if (count <= 1)
    {
        return { -1,segmentRanges };
    }

    return {count, segmentRanges};
}

int main()
{
    vector<int> arr = {0,1,7,1,0,1,0,3};

    // Divide the array into segments with consistent MNPN
    pair<int, vector<pair<int, int>>> result = divideArray(arr);

    // Output the result
    if (result.first == -1) {
        cout << "No such division possible." << endl;
    }
    else {
        cout << "Number of segments: " << result.first << endl;
        cout << "Segment ranges:" << endl;
        for (auto segment : result.second) {
            cout << "[" << segment.first << ", " << segment.second << "]" << endl;
        }
    }

    return 0;
}
