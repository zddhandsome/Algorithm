#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>
const int Count = 100;  //重复计算的次数，解决小规模时时间太短无法得出时间的问题
using namespace std;

class myPoint {
	public:
		int x;   //x坐标
		int y;   //y坐标
};
bool compare(myPoint a,myPoint b,int type) { //若type=1，比较x坐标；否则，就比较y坐标
	if(type==1) {
		return a.x>b.x;
	} else {
		return a.y>b.y;
	}
}
void Initial(int N,myPoint* X,myPoint* Y) {
	srand(N);   //种子为数据的规模
	int i;
	for(i=0; i<N; i++) { //产生随机数，X集和Y集中点的内容是一样的，只是排序的方法不同
		X[i].x=rand();
		X[i].y=rand();
		Y[i].x=X[i].x;
		Y[i].y=X[i].y;
	}
}
double Distance(myPoint p1,myPoint p2) {
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

void quickSort(myPoint* P,int start,int end,int type) {  //若type=1，就比较x坐标；否则，就比较y坐标

	if(start==end) { //只有一个点时，直接返回
		return;
	}
	int primary_start = start;  //保存初始的第一个首位置和尾位置
	int primary_end = end;
	myPoint pivotKey = P[start];  //枢轴量默认为第一个数

	while(start<end) {
		while(start<end && compare(P[end],pivotKey,type)) {  //从后往前找第一个比pivotKey小的数
			end--;
		}
		if(start<end) { // 填到start所指示的空位，start+1，后移一位
			P[start++]= P[end];
		}
		while(start<end && compare(pivotKey,P[start],type)) { //从前往后找第一个比pivotKey大的数
			start++;
		}
		if(start<end) { //填到end所指示的空位，end-1，前移一位
			P[end--]=P[start];
		}
	}
	P[start]=pivotKey;   //此时end=start,把pivotKey填到中间的位置
	if(start-1>primary_start)  //递归调用
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

    if (end - start < 3)    //当点的数量小于等于3时，用暴力法。由于是按照x坐标来划分区域，固X数组的点的数量和位置君未发生改变，故用X数组不用Y数组
        return force(start, end, X,P1,P2);
    int mid = (start + end) / 2; //按照x坐标的排序，从中间切开

    int leftLen = 0, rightLen = 0, i, j; //leftLen，和rightLen分别指示左右两边点集的个数
    myPoint* YL = new myPoint[(end - start + 1) ]; //保存中线左边的点集，按照Y坐标排序
    myPoint* YR = new myPoint[(end - start + 1) ]; //保存中线右边的点集，按照Y坐标排序

    for (i = 0; i <= end - start; i++) {    //遍历集合中每一个点，他们都是按照y的顺序进行排序的，若点的x坐标小于等于中线，则分割到左子集，否则分割到右子集
                                            //通过此操作YL和YR中的点的坐标依旧是按照y坐标排序好的
        if (Y[i].x <= X[mid].x) {
            YL[leftLen++] = Y[i];
        }
        else {
            YR[rightLen++] = Y[i];
        }
    }

    double left = divide_conquer(start, mid, X, YL,P1,P2);      //递归求左边部分的最短距离
    myPoint leftP1 = P1;  //保存左支距离最小的两个点的坐标
    myPoint leftP2 = P2;
    double right = divide_conquer(mid + 1, end, X, YR,P1,P2);  //递归求右边部分的最短距离
    double minDis;   //取小的一个
    if (left < right) {
        minDis = left;
        P1 = leftP1;
        P2 = leftP2;
    }
    else {  //此时并不需要更新P1，P2的值，因为此时P1和P2的值就是右支的最小的一对点的坐标
        minDis = right;
    }


    myPoint* newY = new myPoint[(end - start + 1)];  //新建一个数组，用于保存以中界线为中心，宽度为 2*minDis 的垂直带形区域内的点

    int newYLen = 0;
    double leftBorder = X[mid].x - minDis;   //区域的左边界
    double rightBorder = X[mid].x + minDis;  //区域的右边界

    for (i = 0; i <= end - start; i++) {     //遍历Y集中所有点，满足条件则加入新集合，新集合的点的依然按照y坐标排序好

        if (Y[i].x >= leftBorder && Y[i].x <= rightBorder)
            newY[newYLen++] = Y[i];
    }

    for (i = 0; i<newYLen; i++) {       //在新集合中，判断每个点跟它后面的7个点的距离作比较，若小于则更新最小距离
        for (j = 1; j <= 7; j++) {
            if ((i + j)<newYLen) {  //加入条件，防止越界
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
    cout << "请输入问题的规模：";
    cin >> N;
    myPoint* X = new myPoint[N];   //X,Y两个点集的内容相同，区别在于X点集是按照x坐标顺序排序，而Y点集市安装y坐标顺序排序
    myPoint* Y = new myPoint[N];
    int i;

    clock_t start, end;
    double ave = 0.0;
    double minDis = 0.0;
    myPoint P1, P2; //距离最小的两个点的坐标
    Initial(N, X, Y);   //初始化数组


    for (i = 0; i < Count; i++) {   //重复count次 
        start = clock();
        minDis += force(0, N - 1, X,P1,P2);
        end = clock();
        ave += (double)(end - start);
    }
    ave /= Count;
    minDis /= Count;
    cout << "暴力算法: 最短距离为：" << minDis << "  时间为：" <<ave<<" ms"<< endl;
    cout << "最小距离的两个点的坐标为：(" << P1.x << "," << P1.y << "),(" << P2.x << "," << P2.y << ")"<<endl;

    ave = 0.0;
    minDis = 0.0;
    for (i = 0; i < Count; i++) {   //重复count次 
        start = clock();
        quickSort(X, 0, N - 1, 1);  //将点集按照x坐标的升序排序，并保存到X数组中
        quickSort(Y, 0, N - 1, 2);  //将点集按照y坐标的升序排序，并保存到Y数组中
        minDis+= divide_conquer(0, N - 1, X, Y,P1, P2);
        end = clock();
        Initial(N, X, Y);  //重新初始化，供下一次使用
        ave += (double)(end - start);
    }
    ave /= Count;
    minDis /= Count;
    cout << "分治算法: 最短距离为：" <<minDis<< "  时间为：" << ave << " ms" << endl;
    cout << "最小距离的两个点的坐标为：(" << P1.x << "," << P1.y << "),(" << P2.x << "," << P2.y << ")" << endl;


    delete[]X;
    delete[]Y;
    return 0;
}



