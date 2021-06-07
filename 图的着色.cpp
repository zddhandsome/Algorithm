#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e2 + 6;
int n, k, m;//n:�����;k:����;m:ͼȾɫ����ɫ��;
int mp[MAXN][MAXN];//����ͼ
int color[MAXN];//���Ⱦ������ɫ
bool OK;//�Ƿ����Ⱦɫ����
bool judge(int x){ //�ж�x���Ⱦɫ�����Ƿ���ȷ
	for (int i = 1; i < x; i++)
		if (mp[i][x] && color[x] == color[i])//���������,����ɫһ��,�򷽰�������
			return false;
	return true;
}
void DFS(int i) 
{
	if (i > n) {
		OK = true;
		for (int j = 1; j <= n; j++)//�������Ⱦɫ����
			printf("%d%c", color[j], " \n"[j == n]);
		return;
	}
	for (int j = 1; j <= m; j++){
		color[i] = j;//i���Ⱦjɫ
		if (judge(i))//���оͽ�����һ�����
			DFS(i + 1);
		color[i] = 0;//i�����ݵ�����ɫ״̬
	}
}
int main(){
	OK = false;
	memset(mp, 0, sizeof(mp));
	memset(color, false, sizeof(color));
	scanf("%d%d%d", &n, &k, &m);
	for (int i = 0; i < m; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		mp[u][v] = mp[v][u] = 1;
	}
	printf("Ⱦɫ����\n");
	DFS(1);
	return 0;
}
