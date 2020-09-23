#include<windows.h>
#include <vector>
#include <algorithm>
#include<string>
/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
#include <map>
#include <queue>
#include <functional>
#include <unordered_map>
#include <unordered_set>
namespace std
{
	using std::tr1::unordered_map;
	using std::tr1::unordered_set;
}


using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};

int dfsLeftNode(TreeNode* root,int curLength)
{
	int nLeftNodeLength = curLength;
	int nRightNodeLength = curLength;
	if (root == NULL)
		return curLength;
	if (root->left)
	{
		nLeftNodeLength = dfsLeftNode(root->left, curLength + 1);
	}
	if (root->right)
	{
		nRightNodeLength = dfsLeftNode(root->right, curLength + 1);
	}
	if (nLeftNodeLength > nRightNodeLength)
	{
		return nRightNodeLength;
	}
	else
	{
		return nLeftNodeLength;
	}
}

int minDepth(TreeNode* root) {
	return dfsLeftNode(root,1);
}

bool repeatedSubstringPattern(string s) {
	string subString = "";
	string subS1 = "";
	int nsub = 0;
	for (int i = 1; i <= s.length() / 2; ++i)
	{
		subString = s.substr(0, i);
		subS1 = s.substr(i , subString.length());
		while (subS1.compare(subString) == 0 && nsub != s.length())
		{
			subS1 = s.substr(nsub, subString.length());
			nsub = nsub + subString.length();
		}
		if (nsub == s.length() && subS1.compare(subString) == 0)
		{
			return true;
		}
		nsub = 0;
	}
	return false;

}

vector<vector<int>> findSubsequences(vector<int>& nums) {
	vector<vector<int>> vecRet;
	if (nums.size() == 2)
	{
		if (nums[0] < nums[1])
		{
			vecRet.push_back(nums);
			return vecRet;
		}
	}
	for (int i = 0; i < nums.size(); ++i)//循环次数
	{
		for (int j = 1; j < nums.size(); ++j)//间隔数
		{
			vector<int> apendVec = { nums[i] };
			int nIndex = i + j;
			while (nIndex < nums.size())
			{
				int nSize = apendVec.size();
				if (nums[nIndex] < apendVec[nSize - 1])
				{
					break;
				}
				apendVec.push_back(nums[nIndex]);
				vector<vector<int>>::iterator result = find(vecRet.begin(), vecRet.end(), apendVec);
				if (result == vecRet.end())
				{ 
					vecRet.push_back(apendVec);
				}
				nIndex += j;
				if (nIndex == nums.size() && j != 1)
				{
					if (nums[nIndex -1] >= apendVec[nSize - 1])
					{
						apendVec.push_back(nums[nIndex -1]);
						vector<vector<int>>::iterator result = find(vecRet.begin(), vecRet.end(), apendVec);
						if (result == vecRet.end())
						{
							vecRet.push_back(apendVec);
						}
					}
				}
			}
			apendVec.clear();
		}
	}
	return vecRet;
}

void Dfs(int nIndex,vector<string>& ret,char* szPre,string digits)
{
	char numPool[8][4] = {
		{ 'a','b','c' },{ 'd','e','f' },{ 'g','h','i' },{ 'j','k','l' },{ 'm','n','o' },{ 'p','q','r','s' },{ 't','u','v' },{ 'w','x','y','z' }
	};
	if (nIndex == digits.length())
	{
		if (strlen(szPre) == digits.length())
		{
			ret.push_back(szPre);
		}
		return;
	}
	int a = digits[nIndex] - '0' - 2;
	int next = nIndex + 1;
	for (int i = 0; i < 4; i++)
	{
		char buf[9] = { 0 };
		memset(buf, 0, 9);
		int n = strlen(szPre);
		if (n)
		{
			strcpy_s(buf, n + 1, szPre);
		}
		buf[nIndex] = numPool[a][i];
		Dfs(next, ret, buf, digits);
	}
}

vector<string> letterCombinations(string digits) {
	char sz[9] = {0};
	vector<string> ret;
	Dfs(0, ret, sz, digits);
	return ret;
}

//void ticketsDfs(vector<vector<string>>& tickets,vector<string>& ret,string szNext,bool bFrist)
//{
//	//第一步先筛选出from时jfk的机票
//	vector<vector<string>>::iterator it;
//	vector<vector<string>> fromTickets;
//	string mszNext;
//	bool loopfalg = true;
//	bool localFisrt = false;
//	bool bfalg = false;//标志是否找到了该开头的机票，false则没有机票了，到最后
//	for (it = tickets.begin(); it != tickets.end(); it++)
//	{
//		if ((*it)[0] == szNext)
//		{
//			fromTickets.push_back(*it);
//		}
//	}
//	if (fromTickets.size() == 0)
//	{
//		if (tickets.size() != 0)
//		{
//			localFisrt = true;
//			mszNext = "JFK";
//			goto NextDfs;
//		}
//		return;
//	}
//	int minIndex;
//checkNext:
//	//第二步，排序to ，找到最小，作为下一个出发地
//	if (fromTickets.size() == 0)
//	{
//		loopfalg = false;
//		for (it = tickets.begin(); it != tickets.end(); it++)
//		{
//			if ((*it)[0] == szNext)
//			{
//				fromTickets.push_back(*it);
//			}
//		}
//	}
//	minIndex = 0;
//	for (int i = 1; i < fromTickets.size(); ++i)
//	{
//		if (fromTickets[minIndex][1] > fromTickets[i][1])
//		{
//			minIndex = i;
//		}
//	}
//	//特殊情况，不连贯的情况下，就不能按照大小来了
//	mszNext = fromTickets[minIndex][1];
//	for (it = tickets.begin(); it != tickets.end(); it++)
//	{
//		if (mszNext.compare((*it)[0]) == 0)
//		{
//			bfalg = true;
//			break;
//		}
//	}
//	if (!bfalg && loopfalg)
//	{
//		fromTickets.erase(fromTickets.begin() + minIndex);
//		goto checkNext;
//	}
//	if (!bFrist)
//	{
//		ret.pop_back();
//	}
//	ret.push_back(fromTickets[minIndex][0]);
//	ret.push_back(fromTickets[minIndex][1]);
//	for (it = tickets.begin(); it != tickets.end(); it++)
//	{
//		if ((*it)[0] == fromTickets[minIndex][0] && (*it)[1] == fromTickets[minIndex][1])
//		{
//			break;
//		}
//	}
//	if (it != tickets.end())
//	{
//		tickets.erase(it);
//	}
//NextDfs:
//	ticketsDfs(tickets, ret, mszNext, localFisrt);
//}
//
//vector<string> findItinerary(vector<vector<string>>& tickets) {
//	vector<string> ret;
//	ticketsDfs(tickets, ret, "JFK",true);
//	return ret;
//}

unordered_map<string, priority_queue<string, vector<string>, std::greater<string>>> vec;

vector<string> stk;

void dfs(const string& curr) {
	while (vec.count(curr) && vec[curr].size() > 0) {
		string tmp = vec[curr].top();
		vec[curr].pop();
		dfs(move(tmp));
	}
	stk.emplace_back(curr);
}

vector<string> findItinerary(vector<vector<string>>& tickets) {
	for (auto& it : tickets) {
		vec[it[0]].emplace(it[1]);
	}
	dfs("JFK");

	reverse(stk.begin(), stk.end());
	return stk;
}

bool judgeCircle(string moves) {
	//R = 1 L = -1 U = 1 D = -1
std:map<char, int> mp;
	mp['R'] = 1;
	mp['L'] = -1;
	mp['U'] = 1;
	mp['D'] = -1;
	int end = 0;
	for (char i : moves)
	{
		end += mp[i];
	}
	if (end == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool palindrome(const char *s,int& nRet)
{
	int n;
	n = strlen(s) - 1;
	int i = 0;
	for (i = 0; i <= n; i++)
	{
		if (s[i] == s[n])
		{
			n--;
		}
		else
		{
			nRet = i;
			return false;
		}	
	}
	return true;
}
//1.给的字符串就是回文字符串
//2.不是回文字符串，就要找回文字符第一个出现的子串
string shortestPalindrome(string s) {
	if (s.empty()) //  || palindrome(s.c_str())
	{
		return s;
	}
	int nIndex = 0;
	size_t nsize = s.length();
	string temp = "";
	while (nIndex <= nsize)
	{
		int nTemp = 0;
		temp = s.substr(0, nsize - nIndex);
		bool bret = palindrome(temp.c_str(), nTemp);
		if (bret)
		{
			break;
		}
		else
		{
			if(nTemp && nTemp != 1)
			{
				nIndex = nIndex + nTemp - 1;
			}
			else
			{
				nIndex++;
			}
		}
	}
	temp = s.substr(nsize - nIndex, nIndex);
	reverse(temp.begin(), temp.end());
	temp = temp + s;
	return temp;
}

void OpenDoorDfs(map<int, bool>& mprooms, vector<vector<int>>& rooms,int roomsID)
{
	vector<int> roomKey = rooms[roomsID];
	for (size_t i = 0; i < roomKey.size(); i++)
	{
		if (!mprooms[roomKey[i]])
		{
			mprooms[roomKey[i]] = true;
			OpenDoorDfs(mprooms, rooms, roomKey[i]);
		}
	}
}

bool canVisitAllRooms(vector<vector<int>>& rooms) {
	map<int, bool> mprooms;
	mprooms[0] = true;
	for (int i = 1; i < rooms.size(); ++i)
	{
		mprooms[i] = false;
	}
	OpenDoorDfs(mprooms, rooms, 0);
	map<int, bool>::iterator it;
	for (it = mprooms.begin(); it != mprooms.end(); it++) {
		if (!it->second)
		{
			return false;
		}
	}
	return true;
}

void trim(string &s)
{

	if (!s.empty())
	{
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}

}

bool isNumber(string s) {
	int forwardSingle = 0;//1：数字 2： 数字或者E 3:正负号且之后只能为数字 4:数字或者小数点或者E 5:数字或者E，E不能紧跟. 6:纯数字，
	bool bDotnet = false;
	bool bLastDot = false;
	trim(s);
	if (s.empty())
	{
		return false;
	}
	int cont = 0;
	if (!s.empty())
	{
		for (int x = 0; x < s.length(); ++x)
		{
			if (s[x] == '.')
			{
				cont++;
			}
		}
	}
	if (cont >= 2)
	{
		return false;
	}
	if (s.length() == 1)
	{
		if (0 <= s[0] - '0' && s[0] - '0' <= 9)
		{
			;
		}
		else
		{
			return false;
		}
	}
	if (!s.empty())
	{
		if (s[0] == '+' || s[0] == '-')
		{
			bDotnet = true;
			s.erase(0, 1);
		}
		if (s[0] == '.')
		{
			bDotnet = true;
			s.erase(0, 1);
		}
		if (s.empty())
		{
			return false;
		}
		if (s[s.length() - 1] == '.')
		{
			bLastDot = true;
			s.erase(s.length()-1);
		}
	}
	if (s.empty())
	{
		return false;
	}
	char chFirsh = s[0];
	if (0 <= chFirsh - '0' && chFirsh - '0' <= 9)
	{//当前是数字 下一期望是保持上一期望不变
		if (bLastDot)
		{
			forwardSingle = 6;
		}
		else
		{
			forwardSingle = 4;
		}
	}
	else if ((chFirsh == '+' || chFirsh == '-') && !bDotnet)
	{
		forwardSingle = 2;
	}
	else
	{
		return false;
	}
	for (int i = 1; i < s.length(); ++i)
	{
		chFirsh = s[i];
		//期望值
		if (0 <= chFirsh - '0' && chFirsh - '0' <= 9)
		{//当前是数字 下一期望是保持上一期望不变
			if (forwardSingle == 5)
			{
				forwardSingle = 2;
			}
			continue;
		}
		//else if (chFirsh == '+')
		//{/*
		//	if (forwardSingle == 1 || forwardSingle == 2)
		//	{
		//		return false;
		//	}
		//	else
		//	{
		//		continue;
		//	}*/
		//	return false;
		//}
		else if (chFirsh == '-' || chFirsh == '+')
		{
			if(forwardSingle == 3)
			{
				forwardSingle = 1;
				continue;
			}
			else
			{
				return false;
			}
		}
		else if (chFirsh == 'e' || chFirsh == 'E')
		{
			if (forwardSingle == 2 || forwardSingle == 4)
			{
				forwardSingle = 3;
				continue;
			}
			else
			{
				return false;
			}
		}
		else if (chFirsh == '.')
		{
			if (forwardSingle == 4)
			{
				forwardSingle = 2;
				continue;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	}
	if (0 <= chFirsh - '0' && chFirsh - '0' <= 9)
	{
		return true;
	}
	return false;
}
vector<vector<vector<int>>> vecCheckerBoard;

void DfsHang(vector<vector<int>> vcheckerBoard,int nx,int n)
{
	vector<vector<int>> pre = vcheckerBoard;
	if (nx == n)
	{
		vecCheckerBoard.push_back(vcheckerBoard);
		return;
	}
	for (int j = 0; j < n; j++)
	{
		//假设当前被占用
		if (vcheckerBoard[nx][j] == 0)
		{
			vcheckerBoard[nx][j] = 1;
			int delta = 0;
			for (int k = nx + 1; k < n; k++)
			{
				vcheckerBoard[k][j] = 2;
				//使左右斜着的不能用
				delta = k - nx;
				if ((j - delta) >= 0)
				{
					vcheckerBoard[k][j - delta] = 2;
				}
				if ((j + delta) < n)
				{
					vcheckerBoard[k][j + delta] = 2;
				}
			}
			DfsHang(vcheckerBoard, nx + 1, n);
			vcheckerBoard = pre;
		}
	}
}

vector<vector<string>> solveNQueens(int n) {
	vector<vector<int>> checkerBoard(n);
	//vector<vector<vector<int>>> vecCheckerBoard;
	vector<vector<string>> vecRet;
	vector<string> vecS;
	string s = "";
	for (size_t i = 0; i < n; i++)
	{
		checkerBoard[i].resize(n);
	}
	//0空白 1棋子 2不可用
	for (size_t i = 0; i < n; i++)
	{
		//checkerBoard[i].resize(n);
		for (size_t j = 0; j < n; j++)
		{
			checkerBoard[i][j] = 0;
		}
	}
	DfsHang(checkerBoard, 0, n);
	for (vector<vector<vector<int>>>::iterator its = vecCheckerBoard.begin(); its != vecCheckerBoard.end(); ++its)
	{
		vector<vector<int>> vecbuf = *its;
		vecS.resize(vecbuf.size());
		for (size_t i = 0; i < vecbuf.size(); i++)
		{
			s = string(n,'.');
			for (size_t j = 0; j < vecbuf[i].size(); j++)
			{
				if (vecbuf[i][j] == 1)
				{
					s[j] = 'Q';
				}
			}
			vecS[i] = s;
		}
		vecRet.push_back(vecS);
	}
	return vecRet;
}

void treeDfs(vector<string>&vecRet, string szRet, TreeNode* root)
{
	if (root->left == NULL && root->right == NULL)
	{
		szRet += to_string(root->val);
		vecRet.push_back(szRet);
	}
	else
	{
		szRet = szRet + to_string(root->val) + "->";
		if (root->left)
		{
			treeDfs(vecRet, szRet, root->left);
		}
		if (root->right)
		{
			treeDfs(vecRet, szRet, root->right);
		}
	}
}
vector<string> binaryTreePaths(TreeNode* root) {
	vector<string> vecRet;
	string s = "";
	treeDfs(vecRet, s, root);
	return vecRet;
}

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second < b.second;
}

vector<int> topKFrequent(vector<int>& nums, int k) {
	map<int, int> mpConut;
	vector<int> ret;
	for (size_t i = 0; i < nums.size(); i++)
	{
		mpConut[nums[i]] = 0;
	}
	for (size_t i = 0; i < nums.size(); i++)
	{
		mpConut[nums[i]] += 1;
	}
	map<int, int>::iterator it = mpConut.begin();
	vector< pair<int, int> > vec;
	for (; it != mpConut.end(); it++)
	{
		vec.push_back(pair<int, int>(it->first, it->second));
	}
	sort(vec.begin(), vec.end(), cmp);
	size_t s = vec.size();
	for (int j = 1; j <= k; j++)
	{
		pair<int, int> pi = vec[s - j];
		ret.push_back(pi.first);
	}
	return ret;
}

void pushDfs(vector<int> vec, vector<vector<int>> &vecRet,int n, int startNum,int k,int numFlag)
{
	int thisNum = startNum + 1;
	if (numFlag == k)
	{
		vecRet.push_back(vec);
	}
	if (thisNum > n)
	{
		return;
	}
	for (int i = thisNum; i <= n; i++)
	{
		vec.push_back(i);
		pushDfs(vec, vecRet, n, i, k , numFlag + 1);
		vec.pop_back();
	}
}

vector<vector<int>> combine(int n, int k) {
	vector<vector<int>> vecRet;
	if (n < k)
	{
		return vecRet;
	}
	vector<int> vec;
	pushDfs(vec, vecRet, n, 0, k, 0);
	return vecRet;
}

void sumDfs(vector<vector<int>> &vecRet, vector<int> candidates, vector<int> temp, int target)
{
	for (vector<int>::iterator it = candidates.begin(); it != candidates.end(); )
	{
		temp.push_back(*it);
		int subNum = target - *it;
		if (subNum == 0)
		{
			vecRet.push_back(temp);
		}
		else if (subNum > 0)
		{
			sumDfs(vecRet, candidates, temp, subNum);
		}
		it = candidates.erase(it);
		temp.pop_back();
	}
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<int> temp;
	vector<vector<int>> vecRet;
	sumDfs(vecRet, candidates, temp, target);
	return vecRet;
}


void sumDfs2(vector<vector<int>> &vecRet, vector<int> candidates, vector<int> temp, int target)
{
	for (vector<int>::iterator it = candidates.begin(); it != candidates.end(); )
	{
		temp.push_back(*it);
		int subNum = target - *it;
		it = candidates.erase(it);
		if (subNum == 0)
		{
			vector<vector<int>>::iterator result = find(vecRet.begin(), vecRet.end(), temp);
			if (result == vecRet.end())
			{
				vecRet.push_back(temp);
			}
		}
		else if (subNum > 0)
		{
			sumDfs2(vecRet, candidates, temp, subNum);
		}
		temp.pop_back();
	}
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
	vector<int> temp;
	vector<vector<int>> vecRet;
	sort(candidates.begin(), candidates.end());
	sumDfs2(vecRet, candidates, temp, target);
	return vecRet;
}

#include<numeric>
vector<int> temp;
vector<vector<int>> ans;
void dfs(int cur, int n, int k, int sum) {
	if (temp.size() + (n - cur + 1) < k || temp.size() > k) {
		return;
	}
	if (temp.size() == k && accumulate(temp.begin(), temp.end(), 0) == sum) {
		ans.push_back(temp);
		return;
	}
	temp.push_back(cur);
	dfs(cur + 1, n, k, sum);
	temp.pop_back();
	dfs(cur + 1, n, k, sum);
}

vector<vector<int>> combinationSum3(int k, int n) {
	dfs(1, 9, k, n);
	return ans;
}

void sumTreeDfs(TreeNode* root, map<int, pair<double, double>>& mp,int level)
{
	if (root == NULL)
	{
		return;
	}
	pair<double, double> pr = mp[level];
	pr.first += root->val;
	pr.second++;
	mp[level] = pr;
	sumTreeDfs(root->left, mp, level + 1);
	sumTreeDfs(root->right, mp, level + 1);
}

vector<double> averageOfLevels(TreeNode* root) {
	map<int, pair<double, double>> mp;
	vector<double> ans;
	sumTreeDfs(root, mp, 0);
	map<int, pair<double, double>>::iterator it = mp.begin();
	for (; it != mp.end(); it++)
	{
		ans.emplace_back(it->second.first / it->second.second);
	}
	return ans;
}

void inorderTraversalDfs(TreeNode* root,vector<int> &vecRet)
{
	if (root == NULL)
	{
		return;
	}
	inorderTraversalDfs(root->left, vecRet);
	vecRet.emplace_back(root->val);
	inorderTraversalDfs(root->right, vecRet);
}

vector<int> inorderTraversal(TreeNode* root) {
	vector<int> vecRet;
	inorderTraversalDfs(root, vecRet);
	return vecRet;
}

void checkSmallNineBox(vector<vector<char>>& board, bool* numpool, int ax, int ay)
{
	int bx = -1, by = -1;
	int cx = -2, cy = -2;
	//第一排九宫格
	if (0 <= ax && ax <= 2 && ay >= 0 && ay <= 2)
	{
		bx = 0;
		by = 0;
		cx = 2;
		cy = 2;
	}
	else if (0 <= ax && ax <= 2 && ay >= 3 && ay <= 5)
	{
		bx = 0;
		by = 3;
		cx = 2;
		cy = 5;
	}
	else if (0 <= ax && ax <= 2 && ay >= 6 && ay <= 8)
	{
		bx = 0;
		by = 6;
		cx = 2;
		cy = 8;
	}
	else if (3 <= ax && ax <= 5 && ay >= 0 && ay <= 2) //第二排九宫格
	{
		bx = 3;
		by = 0;
		cx = 5;
		cy = 2;
	}
	else if (3 <= ax && ax <= 5 && ay >= 3 && ay <= 5)
	{
		bx = 3;
		by = 3;
		cx = 5;
		cy = 5;
	}
	else if (3 <= ax && ax <= 5 && ay >= 6 && ay <= 8)
	{
		bx = 3;
		by = 6;
		cx = 5;
		cy = 8;
	}
	else if (6 <= ax && ax <= 8 && ay >= 0 && ay <= 2) //第三排九宫格
	{
		bx = 6;
		by = 0;
		cx = 8;
		cy = 2;
	}
	else if (6 <= ax && ax <= 8 && ay >= 3 && ay <= 5)
	{
		bx = 6;
		by = 3;
		cx = 8;
		cy = 5;
	}
	else if (6 <= ax && ax <= 8 && ay >= 6 && ay <= 8)
	{
		bx = 6;
		by = 6;
		cx = 8;
		cy = 8;
	}
	for (int i = bx; i <= cx; i++)
	{
		for (int j = by; j <= cy; j++)
		{
			if (board[i][j] != '.')
			{
				numpool[board[i][j] - '0'] = false;
			}
		}
	}
}

void checkHorizontal(vector<vector<char>>& board, bool* numpool, int ax)
{
	for (size_t i = 0; i < 9; i++)
	{
		if (board[ax][i] != '.')
		{
			numpool[board[ax][i] - '0'] = false;
		}
	}
}

void checkVertical(vector<vector<char>>& board, bool* numpool, int ay)
{
	for (size_t i = 0; i < 9; i++)
	{
		if (board[i][ay] != '.')
		{
			numpool[board[i][ay] - '0'] = false;
		}
	}
}

bool checkIsHasNull(vector<vector<char>>& board, int &x, int&y)
{
	for (int i = x; i < 9; i++)
	{
		for (int j = y; j < 9; j++)
		{
			if (board[i][j] == '.')
			{
				x = i;
				y = j;
				return true;
			}
		}
		x++;
		y = 0;
	}
	return false;
}


void solveDfs(vector<vector<vector<char>>> &ans, vector<vector<char>> board, int x, int y)
{
	//给定资源数组
	bool numpool[10] = { true };
	numpool[0] = false;
	int conut = 0;
	int tempnum = 0;
	for (int i = 1; i < 10; i++)
	{
		numpool[i] = true;
	}
	int nextx = x, nexty = y + 1;
	//检查小九宫格,排除当前格子不能填的数字
	checkSmallNineBox(board, numpool, x, y);
	//检查横排,排除当前格子不能填的数字
	checkHorizontal(board, numpool, x);
	//检查竖排,排除当前格子不能填的数字
	checkVertical(board, numpool, y);
	//递归
	for (int i = 0; i < 10; i++)
	{
		if (numpool[i])
		{
			board[x][y] = i + '0';
			//检查是否还有空位，如果没有
			if (!checkIsHasNull(board, nextx, nexty))
			{
				ans.emplace_back(board);
				return;
			}
			solveDfs(ans, board, nextx, nexty);
		}
	}
}

void solveSudoku(vector<vector<char>>& board) {
	int x = 0;
	int y = 0;
	vector<vector<vector<char>>> ans;
	checkIsHasNull(board, x, y);
	solveDfs(ans, board, x, y);
	if (ans.size() == 1)
	{
		board = ans[0];
	}
}

void invertTreeDfs(TreeNode* root)
{
	if (!root)
	{
		return;
	}
	TreeNode* buff = NULL;
	buff = root->left;
	root->left = root->right;
	root->right = root->left;
	invertTreeDfs(root->left);
	invertTreeDfs(root->right);
}

TreeNode* invertTree(TreeNode* root) {
	invertTreeDfs(root);
	return root;
}

static const int N = 1010; // 如题：二维数组大小的在3到1000范围内
int father[N];
int n; // 边的数量
		// 并查集初始化
void init() {
	for (int i = 1; i <= n; ++i) {
		father[i] = i;
	}
}
// 并查集里寻根的过程
int findx(int u) {
	return u == father[u] ? u : father[u] = findx(father[u]);
}
// 将v->u 这条边加入并查集
void join(int u, int v) {
	u = findx(u);
	v = findx(v);
	if (u == v) return;
	father[v] = u;
}
// 判断 u 和 v是否找到同一个根
bool same(int u, int v) {
	u = findx(u);
	v = findx(v);
	return u == v;
}
// 在有向图里找到删除的那条边，使其变成树
vector<int> getRemoveEdge(const vector<vector<int>>& edges) {
	init(); // 初始化并查集
	for (int i = 0; i < n; i++) { // 遍历所有的边
		if (same(edges[i][0], edges[i][1])) { // 构成有向环了，就是要删除的边
			return edges[i];
		}
		join(edges[i][0], edges[i][1]);
	}
	return{};
}

// 删一条边之后判断是不是树
bool isTreeAfterRemoveEdge(const vector<vector<int>>& edges, int deleteEdge) {
	init(); // 初始化并查集
	for (int i = 0; i < n; i++) {
		if (i == deleteEdge) continue;
		if (same(edges[i][0], edges[i][1])) { // 构成有向环了，一定不是树
			return false;
		}
		join(edges[i][0], edges[i][1]);
	}
	return true;
}

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
	int inDegree[N] = { 0 }; // 记录节点入度
	n = edges.size(); // 边的数量
	for (int i = 0; i < n; i++) {
		inDegree[edges[i][1]]++; // 统计入度
	}
	vector<int> vec; // 记录入度为2的边（如果有的话就两条边）
						// 找入度为2的节点所对应的边，注意要倒叙，因为优先返回最后出现在二维数组中的答案
	for (int i = n - 1; i >= 0; i--) {
		if (inDegree[edges[i][1]] == 2) {
			vec.push_back(i);
		}
	}
	// 处理图中情况1 和 情况2
	// 如果有入度为2的节点，那么一定是两条边里删一个，看删哪个可以构成树
	if (vec.size() > 0) {
		if (isTreeAfterRemoveEdge(edges, vec[0])) {
			return edges[vec[0]];
		}
		else {
			return edges[vec[1]];
		}
	}
	// 处理图中情况3
	// 明确没有入度为2的情况，那么一定有有向环，找到构成环的边返回就可以了
	return getRemoveEdge(edges);

}
//超出时间限制
//void UniqueDfs(vector<vector<int>>& ans,vector<int> nums, vector<int> ret)
//{
//	if (nums.empty())
//	{
//		vector<vector<int>>::iterator it = find(ans.begin(), ans.end(), ret);
//		if (it == ans.end())
//		{
//			ans.emplace_back(ret);
//		}
//		return;
//	}
//	vector<int> next;
//	for (size_t i = 0; i < nums.size(); i++)
//	{
//		next = nums;
//		ret.push_back(nums[i]);
//		next.erase(next.begin() + i);
//		UniqueDfs(ans, next, ret);
//		ret.pop_back();
//	}
//}
//官方题解
/*class Solution {
	vector<int> vis;

public:
	void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
		if (idx == nums.size()) {
			ans.emplace_back(perm);
			return;
		}
		for (int i = 0; i < (int)nums.size(); ++i) {
			if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
				continue;
			}
			perm.emplace_back(nums[i]);
			vis[i] = 1;
			backtrack(nums, ans, idx + 1, perm);
			vis[i] = 0;
			perm.pop_back();
		}
	}

	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> ans;
		vector<int> perm;
		vis.permize(nums.size());
		sort(nums.begin(), nums.end());
		backtrack(nums, ans, 0, perm);
		return ans;
	}
};*/

void UniqueDfs(vector<vector<int>>& ans, map<int,int> nums, vector<int> ret,int endSize)
{
	if (ret.size() == endSize || nums.empty())
	{
		ans.emplace_back(ret);
		return;
	}
	for (map<int, int>::iterator it = nums.begin(); it != nums.end();)
	{
		if (it->second == 0)
		{
			it = nums.erase(it);
		}
		else
		{
			ret.emplace_back(it->first);
			(it->second)--;
			//if (ret.size() == endSize)
			//{
			//	ans.emplace_back(ret);
			//}
			UniqueDfs(ans, nums, ret, endSize);
			(it->second)++;
			ret.pop_back();
			it++;
		}
	}
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
	vector<vector<int>> ans;
	vector<int> ret;
	map<int, int> mpNums;
	int endSize = nums.size();
	for (auto i : nums)
	{
		mpNums[i]++;
	}
	UniqueDfs(ans, mpNums, ret, endSize);
	return ans;
}

void sumOfLeftLeaves(TreeNode* root, int& ret,int isLeft)
{
	if (!root)
	{
		return;
	}
	if (root->left == NULL && root->right == NULL && isLeft == 1)
	{
		ret += root->val;
	}
	sumOfLeftLeaves(root->left, ret, 1);
	sumOfLeftLeaves(root->right, ret, 0);
}
int sumOfLeftLeaves(TreeNode* root) {
	int ret = 0;
	sumOfLeftLeaves(root, ret,0);
	return ret;
}

int sum = 0;

TreeNode* convertBST(TreeNode* root) {
	if (root != nullptr) {
		convertBST(root->right);
		sum += root->val;
		root->val = sum;
		convertBST(root->left);
	}
	return root;
}

struct Status {
	int a, b, c;
};

//Status dfs(TreeNode* root) {
//	if (!root) {
//		return{ INT_MAX / 2, 0, 0 };
//	}
//	auto[la, lb, lc] = dfs(root->left);
//	auto[ra, rb, rc] = dfs(root->right);
//	int a = lc + rc + 1;
//	int b = min(a, min(la + rb, ra + lb));
//	int c = min(a, lb + rb);
//	return{ a, b, c };
//}
//
//int minCameraCover(TreeNode* root) {
//	auto[a, b, c] = dfs(root);
//	return b;
//}


void mergeTreesFun(TreeNode** t1, TreeNode** t2)
{
	if (*t2 == nullptr)
	{
		return;
	}
	if (*t1 == nullptr && *t2)
	{
		*t1 = *t2;
	}
	else
	{
		(*t1)->val += (*t2)->val;
	}
	mergeTreesFun(&((*t1)->left), &((*t2)->left));
	mergeTreesFun(&((*t1)->right), &((*t2)->right));
}

TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
	mergeTreesFun(&t1, &t2);
	return t1;
}


int main(void)
{
	TreeNode root(1);
	TreeNode l1(3);
	TreeNode r1(2);
	TreeNode l2(5);
	root.left = &l1;
	root.right = &r1;
	l1.left = &l2;

	TreeNode root2(2);
	TreeNode l11(1);
	TreeNode r11(3);
	TreeNode l22(4);
	TreeNode r22(7);

	root2.left = &l11;
	root2.right = &r11;
	l11.right = &l22;
	r11.right = &r22;
	//printf("%d", minDepth(&root));
	//unsigned a = -1;
	//if (a == 0xffffffff)
	//{
	//	printf("if");
	//}
	//else
	//{
	//	printf("else");
	//}
	//if (repeatedSubstringPattern("ababba"))
	//{
	//	printf("true");
	//}
	//else
	//{
	//	printf("false");
	//}
	//vector<int> num = { 4,6,7,7,5};
	//vector<vector<int>> ret;
	//ret = findSubsequences(num);
	//vector<string> s = letterCombinations("3");
	/*vector<vector<string>> tickets =
		{{"JFK", "KUL"}, {"JFK", "NRT"}, {"NRT", "JFK"}};
	vector<string>s = findItinerary(tickets);*/
	//bool a = judgeCircle("UDU");
	//string s = shortestPalindrome("aabba");
	//vector<vector<int>> rooms = {{1, 3}, {3, 0, 1}, {2}, {0}};
	//bool a = canVisitAllRooms(rooms);
	//bool bret = isNumber("4e3.");
	//vector<vector<string>> s = solveNQueens(4);
	//vector<int> num = { 2, 3, 6, 7 };
	//vector<int> vec = topKFrequent(num,1);
	//vector<vector<int>> ret = combinationSum(num, 7);
	vector<vector<char>> b = { 
		{ '1', '.', '.', '3', '.', '7', '.', '9', '.' },
		{ '.', '.', '4', '.', '1', '.', '5', '.', '.' },
		{ '5', '.', '.', '.', '9', '.', '.', '.', '.' },
		{ '.', '.', '.', '2', '.', '9', '.', '7', '6' },
		{ '.', '.', '7', '.', '8', '.', '.', '.', '.' },
		{ '.', '9', '.', '.', '.', '.', '.', '.', '.' },
		{ '.', '.', '.', '.', '.', '8', '7', '.', '2' },
		{ '.', '.', '.', '5', '.', '.', '.', '1', '.' },
		{ '.', '1', '6', '.', '.', '.', '3', '.', '.' }
	};
	//solveSudoku(b);
	//vector<vector<int>> a =
		//{{1, 2}, {2, 3}, {3, 1}, {4, 1}};
		//{{2, 1}, {3, 1}, {4, 2}, {1, 4}};
	//vector<int> c = findRedundantDirectedConnection(a);
	//vector<int> a = { 1,1,2 };
	//vector<vector<int>> c = permuteUnique(a);
	//int ret = minCameraCover(&root);
	TreeNode* ret = mergeTrees(&root, &root2);
	getchar();
	return 0;
}
