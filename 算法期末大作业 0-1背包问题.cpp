#include<bits/stdc++.h>
using namespace std;

int main() {
	int n = 0;//任务数量
	cin>>n;
	int *t = new int[n]; //n项任务各自的加工时间ti
	int total  = 0; // 加工总时间
	for(int i = 0; i < n; i++) {
		cin>>t[i];
		total += t[i];
	}
	//二分加工时间
	int half = total/2;
	int **dp = new int*[n];//dp[i][j]为前i件任务在加工时间不超过j时实际需要的时间
	for(int i = 0; i<n; i++) {
		dp[i] = new int[half+1];
	}
	int **path = new int*[n];//路径记录，path[i][j] = 1 表示任务i的加工时间不大于j并且交由本机器执行
	for(int i = 0; i<n; i++) {
		path[i] = new int[half+1];
	}
	//初始化第一行dp
	for(int i = 0; i<=half; ++i) {
		dp[0][i] = i;
		if(i>=t[0]) {
			dp[0][i] = t[0];
		} else dp[0][i] = 0;
	}

	//核心代码
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= half; j++) {
			if (j < t[i]) {
				dp[i][j] = dp[i - 1][j];
			} else {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - t[i]] + t[i]);
				path[i][j] = 1;
			}
		}
	}
	cout<<"最少加工时间："<<total-dp[n-1][half]<<endl;

	//路径求解
	int i = n - 1, j = half;
	int *flag = new int[n];
	cout<<"机器1加工任务：";
	while (i > 0 && j > 0) {
		if (path[i][j] == 1) {
			cout<<i+1<<" ";
			flag[i] = 1;
			j -= t[i];
		}
		--i;
	}
	cout<<"机器2加工任务：";
	for (int k = 0; k < n; k++) {
		if (flag[k] == 0) {
			cout<<k+1<<" ";
		}
	}
	return 0;
}
