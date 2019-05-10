// 串.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"


//串结构体
typedef struct newstr
{
	char str[MAX_LEN];
	int str_len=0;
}Sstring;

//串赋值
void assign(Sstring &s, char *t)
{
	int len = strlen(t);
	for (int i = 0; i < len; i++)
	{
		s.str[i] = t[i];
		s.str_len++;
	}
	s.str[len] = '\0';
}

//获取串长度
int strLenth(Sstring s)
{
	return s.str_len;
}

//合并两个串为一个新串
Sstring concat(Sstring s, Sstring t)
{
	if (s.str_len + t.str_len<1||s.str_len + t.str_len >= MAX_LEN)
	{
		cout << "错误" << endl;
		exit(0);
	}
	else
	{
		Sstring new_str;
		for (int i = 0; i < s.str_len; i++)
		{
			new_str.str[i] = s.str[i];
		}
		for (int j = 0; j < t.str_len; j++)
		{
			new_str.str[j + s.str_len] = t.str[j];
		}
		new_str.str_len = s.str_len + t.str_len;
		new_str.str[s.str_len + t.str_len] = '\0';
		return new_str;
	}
}

//获取子串
Sstring subStr(Sstring s, int k=0, int len=0)
{
	if (s.str_len - k < len)
	{
		cout << "错误！" << endl;
		exit(0);
	}
	else
	{
		if (len == 0)
			len = s.str_len + 1;
		if(k!=0)
			k = k - 1;
		Sstring sub_str;
		for (int i = 0; i < len; i++)
		{
			sub_str.str[i] = s.str[k + i];
		}
		sub_str.str_len = len;
		sub_str.str[len] = '\0';
		return sub_str;
	}
}

//串插入
void insert(Sstring &s, int i, char *t)
{
	int len = strlen(t);
	if (i<0||i>=s.str_len)
	{
		cout << "错误！" << endl;
		exit(0);
	}
	else
	{
		i = i - 1;
		for (int j = 0; j < len; j++)
		{
			for (int k = s.str_len; k > i; k--)
				s.str[k] = s.str[k - 1];
			s.str[i] = t[j];
			s.str_len++;
			i++;
		}
		s.str[s.str_len] = '\0';
	}
}

//从串中删除子串
Sstring delstr(Sstring s, int i=0, int j=0)
{
	if (i < 0 || i >= s.str_len)
	{
		cout << "错误！" << endl;
		exit(0);
	}
	else
	{
		if (j == 0)
			j = s.str_len+1;
		Sstring new_str;
		if (i == 0)
		{
			new_str.str[0] = '\0';
			new_str.str_len = 0;
			return new_str;
		}
		int k;
		for (k = 0; k < i-1; k++)
		{
			new_str.str[k] = s.str[k];
			new_str.str_len++;
		}
		for (int x = i + j-1; x < s.str_len; x++)
		{
			new_str.str[k++] = s.str[x];
			new_str.str_len++;
		}
		new_str.str[k] = '\0';
		return new_str;
	}
}

//串输出
void dispstr(Sstring s)
{
	int j = 0;
	for (int i = 0; i < s.str_len; i++)
	{
		cout << s.str[i];
		j++;
	}
	cout << " 长度：" << j;
	cout << endl;
}

//串匹配1.0,使用BF算法
//int searchstr(Sstring s, Sstring t)
//{
//	if (t.str_len > s.str_len)
//	{
//		cout << "错误！" << endl;
//		exit(0);
//	}
//	else
//	{
//		int i = 0, j = 0,k=i;
//		while (i < s.str_len&&j < t.str_len)
//		{
//			if (s.str[k] == t.str[j]) { k++; j++; }
//			else
//			{
//				i++;
//				k = i; j = 0;
//			}
//		}
//		if (j >= t.str_len)
//			return i;
//		else
//			return -1;
//	}
//}

//=======================
//串匹配2.0，使用KMP算法
//获取next数组
void GetNext(Sstring p, int *next)
{
	next[0] = -1;
	int k = -1, j = 0;
	while (j<p.str_len)
	{
		if (k == -1 || p.str[j] == p.str[k])
		{
			++j;
			++k;
			if (p.str[j] != p.str[k])
				next[j] = k;
			else
				next[j] = next[k];
		}
		else
		{
			k = next[k];
		}
	}
}

//字符串匹配，KMP算法
int KMPsearch(Sstring s, Sstring p,int *next)
{
	int i = 0, j = 0;
	while (i<s.str_len&&j<p.str_len)
	{
		if (j == -1 || s.str[i] == p.str[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j == p.str_len)
		return i - j;
	else
		return -1;
}
//===========================================

//子串替换
void Replace(Sstring &s, char *t,int index)
{
	int len = strlen(t);
	int i, j;
	for (i = index, j = 0; j < len; j++, i++)
		s.str[i] = t[j];
}

int main()
{
	Sstring string1, string2;
	char s1[20], s2[20];
	cout << "请输入s1:";
	gets_s(s1);
	cout << "输入s2:";
	gets_s(s2);
	assign(string1, s1);
	assign(string2, s2);
	cout << "string1+string2=";
	Sstring string3;
	string3 = concat(string1, string2);
	dispstr(string3);
	Sstring sub_str3_1,sub_str3_2;
	sub_str3_1 = subStr(string3,7,5);
	sub_str3_2 = subStr(string3,19,4);
	cout << "string3第7个字符开始的连续5个字符:" << sub_str3_1.str << endl;
	cout << "string3第19个字符后的连续4个字符:" << sub_str3_2.str << endl; 
	string3 = delstr(string3,7,8);
	cout << "string3:";
	dispstr(string3);
	char t[] = "Data Structure";
	insert(string3, 7,t );
	cout << "string3:";
	dispstr(string3);
	char temp[] = "love";
	Sstring st;
	assign(st, temp);
	//int index = searchstr(string3, st);
	int *next;
	next = new int[st.str_len];
	GetNext(st, next);
	int index = KMPsearch(string3, st, next);
	char temp1[] = "hate";
	Replace(string3, temp1, index);
	cout << "string3:";
	dispstr(string3);
	return 0;
}