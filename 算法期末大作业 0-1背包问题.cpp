#include<bits/stdc++.h>
using namespace std;

int main() {
	int n = 0;//��������
	cin>>n;
	int *t = new int[n]; //n��������Եļӹ�ʱ��ti
	int total  = 0; // �ӹ���ʱ��
	for(int i = 0; i < n; i++) {
		cin>>t[i];
		total += t[i];
	}
	//���ּӹ�ʱ��
	int half = total/2;
	int **dp = new int*[n];//dp[i][j]Ϊǰi�������ڼӹ�ʱ�䲻����jʱʵ����Ҫ��ʱ��
	for(int i = 0; i<n; i++) {
		dp[i] = new int[half+1];
	}
	int **path = new int*[n];//·����¼��path[i][j] = 1 ��ʾ����i�ļӹ�ʱ�䲻����j���ҽ��ɱ�����ִ��
	for(int i = 0; i<n; i++) {
		path[i] = new int[half+1];
	}
	//��ʼ����һ��dp
	for(int i = 0; i<=half; ++i) {
		dp[0][i] = i;
		if(i>=t[0]) {
			dp[0][i] = t[0];
		} else dp[0][i] = 0;
	}

	//���Ĵ���
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
	cout<<"���ټӹ�ʱ�䣺"<<total-dp[n-1][half]<<endl;

	//·�����
	int i = n - 1, j = half;
	int *flag = new int[n];
	cout<<"����1�ӹ�����";
	while (i > 0 && j > 0) {
		if (path[i][j] == 1) {
			cout<<i+1<<" ";
			flag[i] = 1;
			j -= t[i];
		}
		--i;
	}
	cout<<"����2�ӹ�����";
	for (int k = 0; k < n; k++) {
		if (flag[k] == 0) {
			cout<<k+1<<" ";
		}
	}
	return 0;
}
