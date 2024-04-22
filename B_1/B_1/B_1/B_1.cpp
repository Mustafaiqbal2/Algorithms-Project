#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Function to divide the array into segments with consistent MNPN
pair<int, vector<pair<int, int>>> divideArray(const vector<int>& arr) {
    int n = arr.size();
    int* dp1 = new int[n];
    int* dp2 = new int[n];

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl <<endl ; 

    dp1[0] = (arr[0]) ? 0 : 1;
    for (int k = 1; k < n; k++)
    {
        int MNPN = 0;
        if (dp1[k - 1] < arr[k])
            MNPN = dp1[k - 1];
        else
            MNPN = max(arr[k] + 1, dp1[k - 1]);

        dp1[k] = MNPN;
    }
    dp2[n-1] = (arr[n-1]) ? 0 : 1;
    for (int k = n-2; k >= 0; k--)
    {
        int MNPN = 0;
        if (dp2[k + 1] < arr[k])
            MNPN = dp2[k + 1];
        else
            MNPN = max(arr[k] + 1,dp2[k + 1]);

        dp2[k] = MNPN;
    }


    //print dp array
    for (int i = 0; i < n; i++)
    {
        cout << dp1[i] << " ";
    }
    cout << endl <<endl;

    for (int i = 0; i < n; i++)
    {
        cout << dp2[i] << " ";
    }

    cout << endl << endl;
    vector<pair<int, int>> segmentRanges;
    int ind = 0;
    int count = 0;

    
    for (int j = 0; j < (n - 1)/2; j++) 
    {
        if (dp1[j] == dp2[j])
        {
			segmentRanges.push_back({ ind + 1,j+1 });
            segmentRanges.push_back({ j+2,n });
			ind = j + 1;
			count++;
            break;
		}
    }
    



    //cout << count << endl;



    //free memory

    if (count < 1)
    {
        return { -1,segmentRanges };
    }

    return { count, segmentRanges };
}

int main()
{
    vector<int> arr = { 1 ,2 ,3 ,4 ,5 };

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
