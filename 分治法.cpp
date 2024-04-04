#include <iostream>;
using namespace std;
#define QUEUESIZE 10000

typedef struct Queue
{
	int front;
	int rear;
	int data[QUEUESIZE];
}Queue;

static int hannicount = -1;
int Translate(char str);//数字字符转化为数字
int Multi(char* a, char* b);//三位数乘三位数
void Hanni(int n, char one, char two, char three);//汉诺塔 递归
void move(char a, char b);//汉诺塔移动
int binary_search(int* array, int len, int elem);//二分查找
void InitQueue(Queue* Q);
bool IsEmptyQueue(Queue* Q);
void EnQueue(Queue* Q, int a);
void DeQueue(Queue* Q, int* b);
void MaxArr(int* arr, int& front, int& rear, int& sum);//穷举法求最大子数组和
int MaxSubArray(int* x, int low, int high);//分治法求最大子数组和
int CrossingSubArray(int* x, int low, int high);//过中心的最大子数组和
int Max(int a, int b, int c);//三个数中最大值
int CountInver(int* x, int left, int right);//求最大逆序对
int MergeCount(int* x, int left, int right);//跨中心逆序对

int main()
{
	int a[8] = { 8,7,6,5,4,3,2,1 };
	cout << CountInver(a, 0, 7) << endl;
	system("pause");
	return 0;
}

int Translate(char str)
{
	return str - 48;
}

int Multi(char* a, char* b)
{
	int temp[3][6] = { 0 };
	int flag = -1;
	int temp_x = 0;
	int temp_y;
	int index_a, index_b;
	for (index_a = 2; index_a >= 0; index_a--)
	{
		temp_y = 5 - temp_x;
		for (index_b = 2; index_b >= 0; index_b--,temp_y--)
		{
			temp[temp_x][temp_y] =
				Translate(a[index_a]) * Translate(b[index_b]);
			if (flag != -1)
			{
				temp[temp_x][temp_y] += flag;
				flag = -1;
			}
			if (temp[temp_x][temp_y] >= 10)
			{
				flag = temp[temp_x][temp_y] / 10;
				temp[temp_x][temp_y] %= 10;
			}
		}
		if (flag != -1)
		{
			temp[temp_x][temp_y] += flag;
			flag = -1;
		}
		temp_x++;
	}

	int temp_sum[6] = { 0 };
	flag = -1;

	for (int i = 5; i >= 0; i--)
	{
		for (int j = 2; j >= 0; j--)
		{
			temp_sum[i] += temp[j][i];
		}
		if (flag != -1)
		{
			temp_sum[i] += flag;
			flag = -1;
		}
		if (temp_sum[i] >= 10)
		{
			flag = temp_sum[i] / 10;
			temp_sum[i] %= 10;
		}
	}
	int sum = 0;
	int jie = 1;
	for (int i = 5; i >= 0; i--)
	{
		sum += jie * temp_sum[i];
		jie *= 10;
	}
	return sum;
}

void Hanni(int n, char one, char two, char three)
{
	if (n == 1)
	{
		move(one, three);
	}
	else
	{
		Hanni(n - 1, one, three, two);
		Hanni(1, one, two, three);
		Hanni(n - 1, two, one, three);
	}
}

void move(char a, char b)
{
	hannicount++;
	if (!( hannicount% 5))
	{
		cout << endl;
	}
	cout << a << "-->" << b << " ";
}

int binary_search(int* array, int len, int elem)
{
	int low = 0;
	int high = len - 1;
	int middle;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (array[middle] == elem)
		{
			return middle;
		}
		else if (elem < array[middle])
		{
			high = middle;
		}
		else
		{
			low = middle;
		}
	}
	return -1;
}

void InitQueue(Queue* Q)
{
	Q = new Queue;
	if (!Q)
	{
		return;
	}
	Q->front = 0;
	Q->rear = 0;
}

bool IsEmptyQueue(Queue* Q)
{
	if (Q->front == Q->rear)
	{
		return true;                                                                          
	}
	else
	{
		return false;
	}
}

void EnQueue(Queue* Q, int a)
{
	if (Q->rear == QUEUESIZE - 1)
	{
		return;
	}
	Q->data[Q->rear] = a;
	Q->rear++;
}

void DeQueue(Queue* Q, int* b)
{
	if (IsEmptyQueue(Q))
	{
		return;
	}
	*b= Q->data[Q->front];
	Q->front++;
}

void MaxArr(int* arr, int& front, int& rear, int& sum)
{
	Queue* Q=NULL;
	InitQueue(Q);
	int lens = 10;
	int tempsum = 0;
	sum = arr[0];
	front = 0;
	rear = 0;
	for (int x = 0; x <= lens - 1; x++)
	{
		tempsum = arr[x];
		for (int y = x; y <= lens - 1; y++)
		{
			if (x != y)
			{
				tempsum += arr[y];
			}
			if (tempsum > sum)
			{
				front = x;
				rear = y;
				sum = tempsum;
			}
		}
	}
}

int MaxSubArray(int* x, int low, int high)
{
	if (low == high)
	{
		return x[low];
	}
	else
	{
		int mid = (low + high) / 2;
		int s1 = MaxSubArray(x, low, mid);
		int s2 = MaxSubArray(x, mid + 1, high);
		int s3 = CrossingSubArray(x, low, high);
		return Max(s1, s2, s3);
	}
}

int CrossingSubArray(int* x, int low, int high)
{
	int mid = (low + high) / 2;
	int sumleft = -1000;
	int sum = 0;
	int sumright = -1000;
	for (int i = mid; i >= low; i--)
	{
		sum += x[i];
		if (sum > sumleft)
		{
			sumleft = sum;
		}
	}
	sum = 0;
	for (int i = mid + 1; i <= high; i++)
	{
		sum += x[i];
		if (sum > sumright)
		{
			sumright = sum;
		}
	}
	sum = sumright + sumleft;
	return sum;
}

int Max(int a, int b, int c)
{
	int max = a > b ? a : b;
	max = max > c ? max : c;
	return max;
}

int CountInver(int* x, int left, int right)
{
	if (left >=right )
	{
		return 0;
	}
	int mid = (left + right) / 2;
	int s1 = CountInver(x, 0, mid);
	int s2 = CountInver(x, mid + 1, right);
	int s3 = MergeCount(x, left, right);
	return s1 + s2 + s3;
}

int MergeCount(int* x, int left, int right)
{
	int count = 0;
	int* temp = new int[right - left + 1];
	int k = 0;
	int mid = (left + right) / 2;
	int a = left;
	int b = mid + 1;
	while (a <= mid&&b <= right)
	{
		if (x[a] > x[b])
		{
			temp[k++] = x[b++];
			count += mid - a + 1;
		}
		else
		{
			temp[k++] = x[a++];
		}
	}
	if (a > mid)
	{
		for (int i = b; i <= right; i++)
		{
			temp[k++] = x[i];
		}
	}
	if (b > right)
	{
		for (int i = a; i <= mid; i++)
		{
			temp[k++] = x[i];
		}
	}
	for (int i = left; i <= right; i++)
	{
		x[i] = temp[i - left];
	}
	delete [] temp;
	return count;
}