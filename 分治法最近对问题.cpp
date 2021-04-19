#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
const int Count = 100;  //�ظ�����Ĵ��������С��ģʱʱ��̫���޷��ó�ʱ�������
using namespace std;

class myPoint {
	public:
		int x;   //x����
		int y;   //y����
};
bool compare(myPoint a,myPoint b,int type) { //��type=1���Ƚ�x���ꣻ���򣬾ͱȽ�y����
	if(type==1) {
		return a.x>b.x;
	} else {
		return a.y>b.y;
	}
}
void Initial(int N,myPoint* X,myPoint* Y) {
	srand(N);   //����Ϊ���ݵĹ�ģ
	int i;
	for(i=0; i<N; i++) { //�����������X����Y���е��������һ���ģ�ֻ������ķ�����ͬ
		X[i].x=rand();
		X[i].y=rand();
		Y[i].x=X[i].x;
		Y[i].y=X[i].y;
	}
}
double Distance(myPoint p1,myPoint p2) {
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

void quickSort(myPoint* P,int start,int end,int type) {  //��type=1���ͱȽ�x���ꣻ���򣬾ͱȽ�y����

	if(start==end) { //ֻ��һ����ʱ��ֱ�ӷ���
		return;
	}
	int primary_start = start;  //�����ʼ�ĵ�һ����λ�ú�βλ��
	int primary_end = end;
	myPoint pivotKey = P[start];  //������Ĭ��Ϊ��һ����

	while(start<end) {
		while(start<end && compare(P[end],pivotKey,type)) {  //�Ӻ���ǰ�ҵ�һ����pivotKeyС����
			end--;
		}
		if(start<end) { // �start��ָʾ�Ŀ�λ��start+1������һλ
			P[start++]= P[end];
		}
		while(start<end && compare(pivotKey,P[start],type)) { //��ǰ�����ҵ�һ����pivotKey�����
			start++;
		}
		if(start<end) { //�end��ָʾ�Ŀ�λ��end-1��ǰ��һλ
			P[end--]=P[start];
		}
	}
	P[start]=pivotKey;   //��ʱend=start,��pivotKey��м��λ��
	if(start-1>primary_start)  //�ݹ����
		quickSort(P,primary_start,start-1,type);
	if(start +1<primary_end)
		quickSort(P,start+1,primary_end,type);
}

int force(int start,int end,myPoint* P,myPoint &P1,myPoint& P2){
	int i,j;
	if(end-start<1){
		return 0.0;
	}
	double minDis = Distance(P[start],P[start+1]);
	P1=P[start];
	P2=P[start+1];
	for(i=start;i<=end;i++){
	for(j=start;j<=end;j++){
		if(i!=j&& Distance(P[i],P[j])<minDis)
		minDis = Distance(P[i],P[j]);
		P1 = P[i];
		P2 = P[j];
	}
}
return minDis;
}


double divide_conquer(int start, int end, myPoint* X, myPoint* Y, myPoint& P1, myPoint& P2) {

    if (end - start < 3)    //���������С�ڵ���3ʱ���ñ������������ǰ���x�������������򣬹�X����ĵ��������λ�þ�δ�����ı䣬����X���鲻��Y����
        return force(start, end, X,P1,P2);
    int mid = (start + end) / 2; //����x��������򣬴��м��п�

    int leftLen = 0, rightLen = 0, i, j; //leftLen����rightLen�ֱ�ָʾ�������ߵ㼯�ĸ���
    myPoint* YL = new myPoint[(end - start + 1) ]; //����������ߵĵ㼯������Y��������
    myPoint* YR = new myPoint[(end - start + 1) ]; //���������ұߵĵ㼯������Y��������

    for (i = 0; i <= end - start; i++) {    //����������ÿһ���㣬���Ƕ��ǰ���y��˳���������ģ������x����С�ڵ������ߣ���ָ���Ӽ�������ָ���Ӽ�
                                            //ͨ���˲���YL��YR�еĵ�����������ǰ���y��������õ�
        if (Y[i].x <= X[mid].x) {
            YL[leftLen++] = Y[i];
        }
        else {
            YR[rightLen++] = Y[i];
        }
    }

    double left = divide_conquer(start, mid, X, YL,P1,P2);      //�ݹ�����߲��ֵ���̾���
    myPoint leftP1 = P1;  //������֧������С�������������
    myPoint leftP2 = P2;
    double right = divide_conquer(mid + 1, end, X, YR,P1,P2);  //�ݹ����ұ߲��ֵ���̾���
    double minDis;   //ȡС��һ��
    if (left < right) {
        minDis = left;
        P1 = leftP1;
        P2 = leftP2;
    }
    else {  //��ʱ������Ҫ����P1��P2��ֵ����Ϊ��ʱP1��P2��ֵ������֧����С��һ�Ե������
        minDis = right;
    }


    myPoint* newY = new myPoint[(end - start + 1)];  //�½�һ�����飬���ڱ������н���Ϊ���ģ����Ϊ 2*minDis �Ĵ�ֱ���������ڵĵ�

    int newYLen = 0;
    double leftBorder = X[mid].x - minDis;   //�������߽�
    double rightBorder = X[mid].x + minDis;  //������ұ߽�

    for (i = 0; i <= end - start; i++) {     //����Y�������е㣬��������������¼��ϣ��¼��ϵĵ����Ȼ����y���������

        if (Y[i].x >= leftBorder && Y[i].x <= rightBorder)
            newY[newYLen++] = Y[i];
    }

    for (i = 0; i<newYLen; i++) {       //���¼����У��ж�ÿ������������7����ľ������Ƚϣ���С���������С����
        for (j = 1; j <= 7; j++) {
            if ((i + j)<newYLen) {  //������������ֹԽ��
                double dis = Distance(newY[i], newY[i + j]);

                if (dis < minDis) {
                    minDis = dis;
                    P1 = newY[i];
                    P2 = newY[i + j];
                }
            }

        }
    }

    delete YL;
    delete YR;
    delete newY;

    return minDis;
}
int main()
{
    int N;
    cout << "����������Ĺ�ģ��";
    cin >> N;
    myPoint* X = new myPoint[N];   //X,Y�����㼯��������ͬ����������X�㼯�ǰ���x����˳�����򣬶�Y�㼯�а�װy����˳������
    myPoint* Y = new myPoint[N];
    int i;

    clock_t start, end;
    double ave = 0.0;
    double minDis = 0.0;
    myPoint P1, P2; //������С�������������
    Initial(N, X, Y);   //��ʼ������


    for (i = 0; i < Count; i++) {   //�ظ�count�� 
        start = clock();
        minDis += force(0, N - 1, X,P1,P2);
        end = clock();
        ave += (double)(end - start);
    }
    ave /= Count;
    minDis /= Count;
    cout << "�����㷨: ��̾���Ϊ��" << minDis << "  ʱ��Ϊ��" <<ave<<" ms"<< endl;
    cout << "��С����������������Ϊ��(" << P1.x << "," << P1.y << "),(" << P2.x << "," << P2.y << ")"<<endl;

    ave = 0.0;
    minDis = 0.0;
    for (i = 0; i < Count; i++) {   //�ظ�count�� 
        start = clock();
        quickSort(X, 0, N - 1, 1);  //���㼯����x������������򣬲����浽X������
        quickSort(Y, 0, N - 1, 2);  //���㼯����y������������򣬲����浽Y������
        minDis+= divide_conquer(0, N - 1, X, Y,P1, P2);
        end = clock();
        Initial(N, X, Y);  //���³�ʼ��������һ��ʹ��
        ave += (double)(end - start);
    }
    ave /= Count;
    minDis /= Count;
    cout << "�����㷨: ��̾���Ϊ��" <<minDis<< "  ʱ��Ϊ��" << ave << " ms" << endl;
    cout << "��С����������������Ϊ��(" << P1.x << "," << P1.y << "),(" << P2.x << "," << P2.y << ")" << endl;


    delete[]X;
    delete[]Y;
    return 0;
}



