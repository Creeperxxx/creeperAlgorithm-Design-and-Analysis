#include  <iostream>
#include <stdlib.h>
#include <time.h>
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
void MergeSort(int* x, int low, int high);//归并排序
void Merge(int* x, int low, int high);//归并
int Randomized_Partition(int* x, int low, int high);//数组划分_随机主元
void QuickSort(int* x, int low, int high);//快速排序
void Exchange(int* x, int a, int b);//交换两数
int partition(int* x, int low, int high);//数组划分
int QuickMin(int* x, int k, int low, int high);//次序排序
void Max_Continuous_Subarray_DP(int* x, int n, int& max, int& low, int& high);//动态规划最大子数组和
void Longest_Common_Subsequence(int* x, int* y, int** c, char** rec);//最大子数组
void Print_LCS(int* x, char** rec, int m,int n);//求最大公共子数组
void GetLCSxy(int** c, int& x, int& y);
void Longest_Common_Substring(int* x, int* y, int& max, int& end);//最大公共子串
void Minimum_Edit_Distance(char* s, char* t, int** c, char** rec);//编辑距离问题
int mymin(int a, int b, int c);//找最小
void Print_MED(char** rec, char* s, char* t, int i, int j);//索引

int main()
{
	int x[2] = { 0 };
	int y[5] = { 0 };
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

void MergeSort(int* x, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		MergeSort(x, low, mid);
		MergeSort(x, mid+1,high);
		Merge(x, low, high);
		return;
	}
}

void Merge(int* x, int low, int high)
{
	if (low >= high)
	{
		return;
	}
	int mid = (low + high) / 2;
	
	int* temp = new int[high - low + 1];
	int k = 0;
	int left = low;
	int right = mid + 1;
	while (left <= mid && right <= high)
	{
		if (x[left] >= x[right])
		{
			temp[k++] = x[right++];
		}
		else
		{
			temp[k++] = x[left++];
		}
	}
	while (left <= mid)
	{
		temp[k++] = x[left++];
	}
	while (right <= high)
	{
		temp[k++] = x[right];
	}
	k = 0;
	for (int i = low; i <= high; i++)
	{
		x[i] = temp[k++];
	}
	delete[]temp;
}

int Randomized_Partition(int* x, int low, int high)
{
	srand((unsigned int)time(NULL));
	int p = rand() % (high - low + 1) + low;
	Exchange(x, p, high);
	return partition(x, low, high);
}

void Exchange(int* x, int a, int b)
{
	int temp = x[a];
	x[a] = x[b];
	x[b] = temp;
}

int partition(int* x, int low, int high)
{
	int i = low - 1;
	int j = low;
	for (j; j <= high - 1; j++)
	{
		if (x[j] <= x[high])
		{
			Exchange(x, ++i, j);
		}
	}
	Exchange(x, ++i, high);
	return i;
}

void QuickSort(int* x, int low, int high)
{
	if (low < high)
	{
		int p = Randomized_Partition(x, low, high);
		QuickSort(x, low, p - 1);
		QuickSort(x, p + 1, high);
	}
	return;
}

int QuickMin(int* x, int k, int low, int high)
{
	if (low >= high)
	{
		return x[low];
	}
	else
	{
		int temp = Randomized_Partition(x, low, high);
		if (k == temp - low + 1)
		{
			return x[temp];
		}
		else if (k < temp - low + 1)
		{
			return QuickMin(x, k, low, temp - 1);
		}
		else
		{
			return QuickMin(x, k - (temp - low + 1), temp + 1, high);
		}
	}
}

void Max_Continuous_Subarray_DP(int* x, int n, int& max, int& low, int& high)
{
	int* d = new int[n];
	int* rec = new int[n];
	d[n - 1] = x[n - 1];
	rec[n - 1] = n - 1;
	for (int i = n - 2; i >= 0; i--)
	{
		if (d[i + 1] > 0)
		{
			d[i] = d[i + 1] + x[i];
			rec[i] = rec[i + 1];
		}
		else
		{
			d[i] = x[i];
			rec[i] = i;
		}
	}
	int templow = 0;
	int temphigh = rec[0];
	int tempmax = d[0];
	for (int i = 1; i <= n - 1; i++)
	{
		if (d[i] > max)
		{
			max = d[i];
			low = i;
			high = rec[i];
		}
	}
	max = tempmax;
	low = templow;
	high = temphigh;
}

void Longest_Common_Subsequence(int* x, int* y, int** c, char** rec)
{
	int len_x = 0;
	int len_y = 0;
	for (int i = 0; x[i]; i++)
	{
		len_x++;
	}
	for (int i = 0; y[i]; i++)
	{
		len_y++;
	}
	if (len_x == 0 || len_y == 0)
	{
		return;
	}
	c = new int* [len_x+1];

	for (int i = 0; i < len_x; i++)
	{
		c[i] = new int[len_y+1];
	}

	rec = new char* [len_x];

	for (int i = 0; i < len_x; i++)
	{
		rec[i] = new char[len_y];
	}

	for (int i = 0; i < len_x; i++)
	{
		c[i][0] = 0;
		c[0][i] = 0;
	}
	
	for (int i = 0; i < len_x; i++)
	{
		for (int j = 0; j < len_y; j++)
		{
			if (x[i] == y[j])
			{
				c[i + 1][j + 1] = c[i][j] + 1;
				rec[i][j] = 'LU';
			}
			else if (c[i][j+1] >= c[i+1][j])
			{
				c[i + 1][j + 1] = c[i][j + 1];
				rec[i][j] = 'U';
			}
			else
			{
				c[i + 1][j + 1] = c[i + 1][j];
				rec[i][j] = 'L';
			}
		}
	}
	return;
}

void Print_LCS(int* x, char** rec, int m, int n)
{
	if (m < 0 || n < 0)
	{
		return;
	}
	if (rec[m][n]=='LU')
	{
		Print_LCS(x, rec, m - 1, n - 1);
		cout << x[m] << " ";
	}
	else if (rec[m][n] == 'U')
	{
		Print_LCS(x, rec, m - 1, n);
	}
	else
	{
		Print_LCS(x, rec, m, n - 1);
	}
}

void GetLCSxy(int** c, int& x, int& y)
{
	if (!c[0])
	{
		return;
	}
	int max = c[1][1];
	x = 0;
	y = 0;
	int len_x = 0;
	int len_y = 0;
	for (int i = 0; c[i]; i++)
	{
		len_x++;
	}
	for (int i = 0; c[0][i]; i++)
	{
		len_y++;
	}
	for (int i = 1; i < len_x; i++)
	{
		for (int j = 1; j < len_y; j++)
		{
			if (c[i][j] > max)
			{
				max = c[i][j];
				x = i - 1;
				y = j - 1;
			}
		}
	}
}

void Longest_Common_Substring(int* x, int* y, int& max, int& end)
{
	int len_x = 0;
	int len_y = 0;
	for (int i = 0; x[i]; i++)
	{
		len_x++;
	}
	for (int i = 0; y[i]; i++)
	{
		len_y++;
	}
	int** c = new int* [len_x+1];
	for (int i = 0; i < len_x + 1; i++)
	{
		c[i] = new int[len_y + 1];
	}
	for (int i = 0; i < len_y + 1; i++)
	{
		c[0][i] = 0;
	}
	for (int i = 0; i < len_x + 1; i++)
	{
		c[i][0] = 0;
	}
	max = 0;
	end = 0;
	for (int i = 0; i < len_x; i++)
	{
		for (int j = 0; j < len_y; j++)
		{
			if (x[i] == y[j])
			{
				c[i + 1][j + 1] = c[i][j] + 1;
				if (c[i + 1][j + 1] > max)
				{
					max = c[i + 1][j + 1];
					end = i;
				}
			}
			else
			{
				c[i + 1][j + 1] = 0;
			}
		}
	}
	
}

void Minimum_Edit_Distance(char* s, char* t, int** c, char** rec)
{
	int len_s = strlen(s);
	int len_t = strlen(t);
	c = new int* [len_s + 1];
	for (int i = 0; i < len_t + 1; i++)
	{
		c[i] = new int[len_t + 1];
	}
	for (int i = 0; i < len_t + 1; i++)
	{
		c[0][i] = i;
	}
	for (int i = 0; i < len_s; i++)
	{
		c[i][0] = i;
	}
	int Replace = 0;
	int Delete = 0;
	int Insert = 0;
	for (int i = 0; i < len_s + 1; i++)
	{
		for (int j = 0; j < len_t+1; j++)
		{
			int flag = 0;
			if (s[i] == t[j])
			{
				flag = 1;
			}
			Replace = c[i][j] + flag;
			Delete = c[i][j + 1] + 1;
			Insert = c[i + 1][j] + 1;
			int min = mymin(Replace, Delete, Insert);
			if (Replace == min)
			{
				c[i + 1][j + 1] = Replace;
				rec[i + 1][i + 1] = 'LU';
			}
			else if (Insert == min)
			{
				c[i + 1][j + 1] = Insert;
				rec[i + 1][j + 1] = 'L';
			}
			else
			{
				c[i + 1][j + 1] = Delete;
				rec[i + 1][j + 1] = 'U';
			}
		}
	}
}

int mymin(int a, int b, int c)
{
	int min = a > b ? b : a;
	min = c > min ? min : c;
	return min;
}

void Print_MED(char** rec, char* s, char* t, int i, int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (rec[i][j] == 'LU')
	{
		Print_MED(rec, s, t, i - 1, j - 1);
		if (s[i] == t[j])
		{
			cout << "无需操作 ";
		}
		else
		{
			cout << "用t替换s ";
		}
	}
	else if (rec[i][j] == 'U')
	{
		Print_MED(rec, s, t, i - 1, j);
		cout << "删除s ";
	}
	else
	{
		Print_MED(rec, s, t, i, j + 1);
		cout << "插入t ";
	}
}