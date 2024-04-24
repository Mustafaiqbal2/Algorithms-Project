#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

void dividearrayMNPN(const vector<int>& arr) 
{
	// create a hashmap 
    unordered_set<int> hash;
    int n = arr.size();

    for (int i = 0; i < n; i++)
    {
		hash.insert(arr[i]);
	}
    // calculate mnpn from the hashmap
    int mnpn = 0;
    while (hash.find(mnpn) != hash.end()) 
    {
		mnpn++;
	}

    cout<<"mnpn: "<<mnpn<<endl;

    int count = 0;
    int index = -1;
    unordered_set<int> unique;
    for (int i = 0; i < n; i++)
    {
        if (arr[i]<mnpn && unique.find(arr[i]) == unique.end())
        {
            count++;
        }
        if (count == mnpn)
        {
			cout<<"index: "<<i<<endl;
            index = i+1;
            break;
		}
        unique.insert(arr[i]);
    }

     count = 0;
    
    unordered_set<int> unique1;

    for (int i = index; i < n; i++)
    {
        if (arr[i] < mnpn && unique1.find(arr[i]) == unique1.end())
        {
            count++;
        }
        unique1.insert(arr[i]);
	}
    
    if (count == mnpn)
    {
		// display the result
		cout<<"2"<<endl;
		cout<<"["<<1<<", "<<index<<"]"<<endl;
		cout<<"["<<index+1<<", "<<n<<"]"<<endl;
	}
    else
    {
		cout<<"-1"<<endl;
	}



    
}

int main()
{
    int size;
    cin>>size;
    vector<int> arr(size);
    for (int i = 0; i < size; i++)
    {
		cin >> arr[i];
	}

    dividearrayMNPN(arr);
    return 0;
}