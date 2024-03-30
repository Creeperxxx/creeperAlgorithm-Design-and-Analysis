#include <iostream>;
using namespace std;

static int hannicount = -1;
int Translate(char str);//数字字符转化为数字
int Multi(char* a, char* b);//三位数乘三位数
void Hanni(int n, char one, char two, char three);//汉诺塔 递归
void move(char a, char b);//汉诺塔移动
int binary_search(int* array, int len, int elem);

int main()
{
	int a[8] = { 1,2,3,4,5,6,7,8 };
	cout << binary_search(a, 8, 6) << endl;
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