//100 0 # 100
//6 16 # 3
//8 20 # 3
//15964 89498 # 4781
//3 43 # 6
//4 27 # 5
//5 35 # 5
//6 43 # 5
//7 43 # 6
//100 1 # 99
//10 19 # 2
//5 19 # 3
//1 20 # 5
//100000 100000 # 0
//0 100000 # 22
//100000 0 # 100000
//0 1 # 1
//3482 45592 # 637
//2 4 # 1
//9 5 # 4
//5 5 # 0
//5 17 # 4

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

#define MAX 100001
vector<int> v;

void bfs(int start, int target)
{
    queue<pair<int, int>> q;
    q.push({ start,0 });

    while (!q.empty())
    {
        int first = q.front().first;
        int second = q.front().second;
        if (first == target)
        {
            cout << second << "\n";
            break;
        }
        q.pop();
        
        //if (v[first] == 0) v[first] = second;
        //else if (first > target)
        //{
        //    int tmp = first - target + second;
        //    v[first] = min(tmp, v[first]);
        //    continue;
        //}
        //else if (v[first] > second) v[first] = second;
        //else continue;

        if (first - 1 >= 0 && v[first - 1] == 0)
        {
            v[first - 1] = second + 1;
            q.push({ first - 1,second + 1 });
        }
        if(first + 1 < MAX && v[first + 1] == 0)
        {
            v[first + 1] = second + 1;
            q.push({ first + 1,second + 1 });
        }
        if(first * 2 > 0 && first * 2 < MAX && v[first * 2] == 0)
        {
            int tmp = 0;
            if (first * 2 > target)
            {
                tmp = first * 2 - target + second;
            }
            else tmp = second + 1;
            v[first * 2] = tmp;
            q.push({ first * 2,second + 1 });
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL); cout.tie(NULL);

    int n, k;

    cin >> n >> k;
    if (n >= k)
    {
        cout << n - k << "\n";
        return 0;
    }
    v = move(vector<int>(MAX, 0));
    bfs(n, k);

    return 0;
}