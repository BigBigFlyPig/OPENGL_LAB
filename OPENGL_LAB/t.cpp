//
//#include<iostream>
//#include<vector>
//#include<string>
//using namespace std;
//#define third
//
//int getInt(string N)
//{
//	int n = 0;
//	for (int i = 0; i < N.length(); i++)
//	{
//		n = n * 10 + (int)(N[i] - '0');
//	}
//	return n;
//}
//
//
//#ifdef first
//
//int find(int i, int j, vector<vector<string>>& map)
//{
//	int x[8] = {-1,1,0,0,-1,1,-1,1};
//	int y[8] = {0,0,1,-1,-1,1,1,-1};
//	if ((i<0)||(i>=map.size())||(j<0)||(j>=map[0].size())|| (map[i][j] == "0"))
//	{
//		return 0;
//	}
//	else
//	{
//		map[i][j] = "0";
//		int res = 1;
//		for (int k = 0; k < 8; k++)
//		{
//			res += find(i + x[k], j + y[k], map);
//		}
//		return res;
//	}
//}
//int main()
//{
//	string input;
//	vector<string> num;
//	cin>>input;
//	string tem;
//	bool flag = false;
//	for (int i = 0; i < input.length(); i++)
//	{
//		if (flag == false)
//		{
//			if ((input[i] <= '9') && (input[i] >= '0'))
//			{
//				flag = true;
//				tem =  "";
//				tem += input[i];
//				if (i == input.length() - 1)
//				{
//					num.push_back(tem);
//				}
//			}
//		}
//		else
//		{
//			 if (!((input[i] <= '9') && (input[i] >= '0')))
//			{
//				flag = false;
//				num.push_back(tem);
//			}
//			else
//			{
//				tem += input[i];
//				if (i == input.length() - 1)
//				{
//					num.push_back(tem);
//				}
//			}
//		}
//	}
//	int M = getInt(num[0]);
//	int N = getInt(num[1]);
//	vector<vector<string>> map(M, vector<string>(N, "0"));
//	int count = 0;
//	for (int i = 0; i < M; i++)
//	{
//		count = 0;
//		tem = "";
//		cin >> input;
//		for (int j = 0; j < input.length(); j++)
//		{
//			if (flag == false)
//			{
//				if ((input[j] <= '9') && (input[j] >= '0'))
//				{
//					flag = true;
//					tem = "";
//					tem += input[j];
//					if (j == input.length() - 1)
//					{
//						map[i][count] = tem;
//					}
//				}
//			}
//			else
//			{
//
//				if (!((input[j] <= '9') && (input[j] >= '0')))
//				{
//					flag = false;
//					map[i][count] = tem;
//
//					count++;
//				}
//				else
//				{
//					tem += input[j];
//					if (j == input.length() - 1)
//					{
//						map[i][count] = tem;
//					}
//				}
//			}
//		}
//
//	}
//	int part_num = 0;
//	int max_num = 0;
//	for(int i=0;i<M;i++)
//		for (int j = 0; j < N; j++)
//		{
//			int p_n = find(i, j, map);
//			if (p_n == 0)
//			{
//				continue;
//			}
//			else
//			{
//				part_num++;
//				max_num = max_num > p_n ? max_num : p_n;
//			}
//		}
//	cout << part_num <<","<<max_num;
//	getchar();
//	getchar();
//	return 0;
//}
//#endif
//
//#ifdef second
//void quick_sort(vector<int>& num, int start, int end)
//{
//	if (start > end)
//	{
//		return;
//	}
//	int f_p = start;
//	int b_p = end;
//	int line_start = num[start];
//	int line_end = num[start + 1];
//	while (f_p < b_p)
//	{
//		while ((num[b_p] >= line_start) && (f_p < b_p))
//		{
//			b_p -= 2;
//		}
//		num[f_p] = num[b_p];
//		num[f_p+1] = num[b_p+1];
//		while ((num[f_p] <= line_start) && (f_p < b_p))
//		{
//			f_p += 2;
//		}
//		num[b_p] = num[f_p];
//		num[b_p + 1] = num[f_p + 1];
//	}
//	num[f_p] = line_start;
//	num[f_p+1] = line_end;
//	quick_sort(num, start, f_p - 2);
//	quick_sort(num, f_p + 2, end);
//}
//
//void getLinePart(vector<int>& line)
//{
//	for (int i = 0; i < line.size()/2; i++)
//	{
//		
//		if (i == line.size()/2 - 1)
//		{
//			break;
//		}
//		else
//		{
//			int ind = i * 2;
//			if (line[ind + 1] >= line[ind + 2])
//			{
//				line[ind + 1] = line[ind + 1] > line[ind + 3] ? line[ind + 1] : line[ind + 3];
//				line.erase(line.begin() + ind + 2);
//				line.erase(line.begin() + ind + 2);
//				i--;
//			}
//		}
//
//	}
//}
//
//int main()
//{
//
//	int edit_num;
//	cin >> edit_num;
//	string input;
//	vector<int> num;
//	string tem;
//	bool flag = false;
//	for (int j = 0; j < edit_num; j++)
//	{
//		cin >> input;
//		flag = false;
//		tem = "";
//		for (int i = 0; i < input.length(); i++)
//		{
//			if (flag == false)
//			{
//				if ((input[i] <= '9') && (input[i] >= '0'))
//				{
//					flag = true;
//					tem = "";
//					tem += input[i];
//					if (i == input.length() - 1)
//					{
//						num.push_back(getInt(tem));
//					}
//				}
//			}
//			else
//			{
//				if (!((input[i] <= '9') && (input[i] >= '0')))
//				{
//					flag = false;
//					num.push_back(getInt(tem));
//				}
//				else
//				{
//					tem += input[i];
//					if (i == input.length() - 1)
//					{
//						num.push_back(getInt(tem));
//					}
//				}
//			}
//		}
//	}
//	//for (int i = 0; i < num.size()/2; i++)
//	//{
//	//	cout << num[i*2] << " " << num[i*2 + 1] << endl;
//	//}
//	quick_sort(num, 0, num.size() - 2);
//	//for (int i = 0; i < num.size() / 2; i++)
//	//{
//	//	cout << num[i * 2] << " " << num[i * 2 + 1] << endl;
//	//}
//	getLinePart(num);
//	for (int i = 0; i < num.size() / 2; i++)
//	{
//		if (i != 0)
//			cout << ";";
//		cout << num[i * 2] << "," << num[i * 2 + 1];
//	}
//	getchar();
//	getchar();
//	return 0;
//}
//
//#endif
