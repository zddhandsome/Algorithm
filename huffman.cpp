#include <bits/stdc++.h>
using namespace std;

#define n 6                      //Ҷ����Ŀ
#define m 2 * n - 1              //���н������
typedef struct {                 //�������
    double weight;               //����Ȩֵ
    int parent, lchild, rchild;  //˫��ָ�뼰���Һ���
} HTNode;
typedef HTNode HuffmanTree[m];  // HuffmanTree����������

typedef struct {    //����SelectMin����������Ľ������
    int id;         //���������������е����
    double weight;  //���������Ȩֵ
} temp;

typedef struct {       //������
    char ch;           //�洢�ַ�
    char bits[n + 1];  //��ű���λ��
} CodeNode;
typedef CodeNode HuffmanCode[n];

void InitHuffmanTree(HuffmanTree T) {
    //��ʼ����������
    //��2n-1������������ָ�����Ϊ��(����Ϊ-1)��Ȩֵ��Ϊ0
    for (int i = 0; i < m; i++) {
        T[i].lchild = -1;
        T[i].rchild = -1;
        T[i].parent = -1;
        T[i].weight = 0;
    }
}

void InputWeight(HuffmanTree T) {
    //����Ҷ��Ȩֵ
    //����n��Ҷ�ӵ�Ȩֵ����������ǰn��������
    for (int i = 0; i < n; i++) {
        double x;
        scanf("%lf", &x);
        T[i].weight = x;
    }
}

bool cmp(temp a, temp b) {
    //��������ıȽϺ���
    return a.weight < b.weight;
}

void SelectMin(HuffmanTree T, int k, int* p1, int* p2) {
    //��ǰk�������ѡ��Ȩֵ��С�ʹ�С�ĸ���㣬����ŷֱ�Ϊp1��p2
    temp x[m];  // x����Ϊtemp���͵�����
    int i, j;
    for (i = 0, j = 0; i <= k; i++) {  //Ѱ����С�ʹ�С���ڵ�Ĺ���
        if (T[i].parent == -1) {  //����Ǹ��ڵ�,��������²���
            x[j].id = i;          //���ø��ڵ����Ÿ�ֵ��x
            x[j].weight = T[i].weight;  //���ø��ڵ��Ȩֵ��ֵ��x
            j++;                        // x������ָ�����һλ
        }
    }
    sort(x, x + j, cmp);  //��x����Ȩֵ��С��������
    //������x�����ĵ�һ�͵ڶ���λ���д洢��id�����ҵĸ��ڵ�����ֵ
    *p1 = x[0].id;
    *p2 = x[1].id;
}

void CreateHuffmanTree(HuffmanTree T) {//�������������T[m-1]Ϊ������
    int i, p1, p2;
    InitHuffmanTree(T);
    InputWeight(T);
    for (i = n; i < m; i++) {
        SelectMin(T, i - 1, &p1, &p2);
        T[p1].parent = T[p2].parent = i;
        T[i].lchild = p1;
        T[i].rchild = p2;
        T[i].weight = T[p1].weight + T[p2].weight;
    }
}

void CharSetHuffmanEncoding(HuffmanTree T, HuffmanCode H) { //���ݹ�������T������������H
    int c, p;
    char cd[n + 1];
    int start;
    cd[n] = '\0';
    getchar();
    for (int i = 0; i < n; i++) { 
        H[i].ch = getchar(); 
        start = n; 
        c = i; 
        while ((p = T[c].parent) >= 0) {
            if (T[p].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            c = p; 
        }
        strcpy(H[i].bits, &cd[start]);
    }
}

int main() {
    HuffmanTree T;
    HuffmanCode H;
    printf("������%d��Ҷ�ӽ���Ȩֵ����������������\n", n);
    CreateHuffmanTree(T);
    printf("������%d��Ҷ�ӽ����������ַ���\n", n);
    CharSetHuffmanEncoding(T, H);
    printf("���������Ѿ����ã������������Ѿ���ɣ�������£�\n");
    printf("����������\n");
    for (int i = 0; i < m; i++) {
        printf("id:%d  weight:%.1lf   parent:%d", i, T[i].weight, T[i].parent);
        printf("  lchild:%d rchild:%d\n", T[i].lchild, T[i].rchild);
    }
    printf("���������룺\n");
    double wpl = 0.0;
    for (int i = 0; i < n; i++) {
        printf("id:%d   ch:%c  code:%s\n", i, H[i].ch, H[i].bits);
        wpl += strlen(H[i].bits) * T[i].weight;
    }
    printf("ƽ���볤Ϊ��%.2lf\n", wpl);
    return 0;
}
