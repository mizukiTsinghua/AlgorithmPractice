#include <iostream>
#include <vector>
#include <assert.h>
#include <stack>
#include <string>
#include <queue>
#include <deque>
#include <list>

//////////////////////////////////////////////////////////////////////////
// 旋转数组的最小数字
int MinInOrder(std::vector<int>& Vec, int index1, int index2)
{
	int min = Vec[index1];
	for (std::vector<int>::iterator it = Vec.begin() + 1; it != Vec.end(); ++it)
	{
		if (min > *it)
			min = *it;
	}
	return min;
}

int minNumberInRotateArray(std::vector<int> rotateArray)
{
	int length = rotateArray.size();

	int index1 = 0;
	int index2 = length - 1;
	int index = index1;
	while (rotateArray[index1] >= rotateArray[index2])
	{
		index = index2;
		if (index2 - index1 == 1)
			break;
		index = (index2 + index1) / 2;

		if (rotateArray[index1] == rotateArray[index2] &&
			rotateArray[index] == rotateArray[index1])
			return MinInOrder(rotateArray, index1, index2);

		if (rotateArray[index] >= rotateArray[index1])
			index1 = index;
		else if (rotateArray[index] <= rotateArray[index2])
			index2 = index;
	}
	return rotateArray[index];
}


//////////////////////////////////////////////////////////////////////////
// 矩阵中的路径
bool hasPathCore(const char* matrix, int rows, int cols, int row, int col, const char* str, int pathLength, bool* visited)
{
	if (str[pathLength] == '\0')
		return true;
	bool isHas = false;
	if (row >= 0 && col >= 0 && row < rows && col < cols
		&& matrix[row*cols + col] == str[pathLength]
		&& !visited[row*cols + col])
	{
		++pathLength;
		visited[row*cols + col] = true;
		isHas = hasPathCore(matrix, rows, cols, row, col - 1, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row - 1, col, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row, col + 1, str, pathLength, visited)
			|| hasPathCore(matrix, rows, cols, row + 1, col, str, pathLength, visited);
		if (!isHas)
		{
			--pathLength;
			visited[row*cols + col] = false;
		}
	}
	return isHas;
}


bool hasPath(char* matrix, int rows, int cols, char* str)
{
	if (nullptr == matrix || rows < 1 || cols < 1 || nullptr == str)
		return false;
	bool* visited = new bool[rows*cols];
	::memset(visited, false, rows*cols);
	int pathLength=0;
	for (int i=0;i<rows;++i)
	{
		for (int j=0;j<cols;++j)
		{
			if (hasPathCore(matrix, rows, cols, i, j, str, pathLength, visited))
				return true;
		}
	}
	delete[] visited;
	visited = nullptr;

	return false;
}

//////////////////////////////////////////////////////////////////////////
// 机器人的运动范围
int GetDigitSum(int number)
{
	int sum = 0;
	while (number > 0)
	{
		sum += number % 10;
		number /= 10;
	}
	return sum;
}

bool Check(int threshold, int rows, int cols, int row, int col, bool* visited)
{
	if (row >= 0 && row < rows && col >= 0 && col < cols
		&& GetDigitSum(col) + GetDigitSum(row) <= threshold
		&& !visited[cols*row + col])
		return true;

	return false;
}

int MovingCountCore(int threshold, int rows, int cols, int row, int col, bool* visited)
{
	int count = 0;
	if (Check(threshold, rows, cols, row, col, visited))
	{
		visited[row*cols + col] = true;
		count = 1 + MovingCountCore(threshold, rows, cols, row, col - 1, visited)
			+ MovingCountCore(threshold, rows, cols, row - 1, col, visited)
			+ MovingCountCore(threshold, rows, cols, row, col + 1, visited)
			+ MovingCountCore(threshold, rows, cols, row + 1, col, visited);
	}
	return count;
}

int movingCount(int threshold, int rows, int cols)
{
	if (threshold < 0 || rows <= 0 || cols <= 0)
		return 0;

	bool* visited = new bool[rows*cols];
	::memset(visited, false, rows*cols);
	int count = MovingCountCore(threshold, rows, cols, 0, 0, visited);

	delete[] visited;
	visited = nullptr;

	return count;
}

//////////////////////////////////////////////////////////////////////////
// 剪绳子
int MaxCutting(int length)
{
	if (length < 2)
		return 0;
	if (length == 2)
		return 1;
	if (length == 3)
		return 2;

	int* Sum = new int[length + 1];
	Sum[0] = 0;
	Sum[1] = 1;
	Sum[2] = 2;
	Sum[3] = 3;
	int max = 0;
	
	for (int i = 4; i < length; ++i)
	{
		max = 0;
		for (int j = 1; j <= length / 2; ++j)
		{
			int temp = Sum[i] * Sum[i - j];
			if (temp > max)
				max = temp;

			Sum[i] = max;
		}
	}
	max = Sum[length];
	delete[] Sum;

	return max;
}

//////////////////////////////////////////////////////////////////////////
// 数组中重复的数字
bool duplicate(int numbers[], int length, int* duplication) 
{
	if (nullptr == numbers || length <= 0)
		return false;

	for (int i = 0; i < length; ++i)
	{
		if (numbers[i]<0 || numbers[i]>length - 1)
			return false;
	}

	for (int i = 0; i < length; ++i)
	{
		while (numbers[i] != i)
		{
			if (numbers[i] == numbers[numbers[i]])
			{
				*duplication = numbers[i];
				return true;
			}
			int temp = numbers[numbers[i]];
			numbers[numbers[i]] = numbers[i];
			numbers[i] = temp;
		}
	}

	return false;
}

bool Test(int* arr,int length,int* value)
{
	int* temp = new int[length];
	::memset(temp, 0, length);

	for (int i = 0; i < length; ++i)
	{
		if (temp[arr[i]] == 0)
			temp[arr[i]] = 1;
		else
		{
			*value = arr[i];
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 不修改数组找出重复的数字（以空间换时间）
int CalCount(const int* numbers,int length,int start,int end)
{
	if (nullptr == numbers)
		return -1;
	int count = 0;
	for (int i=0;i<length;++i)
	{
		if (numbers[i] >= start && numbers[i] <= end)
			++count;
	}
	return count;
}

int GetDup(const int* numbers,int length)
{
	if (nullptr == numbers || length < 0)
		return -1;
	int start = 1;
	int end = length - 1;
	while (end>=start)
	{
		int middle = ((end - start) >> 1) + start;

		int count = CalCount(numbers, length, start, middle);

		if (start == end)
		{
			if (count > 1)
				return start;
			else 
				break;
		}

		if (count > middle-start+1)
			end = middle;
		else
			start = middle + 1;
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////
// 二维数组中的查找
//bool Find(int target, std::vector<std::vector<int> > array)
//{
//
//}

int TestStrcmp(const char* str1,const char* str2)
{
	assert((nullptr!=str1) && (nullptr!=str2));
	while (*str1==*str2)
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

void TestStrcpy(char* dest,const char* str)
{
	assert((nullptr!=dest) && (nullptr!=str));
	while (*str != '\0')
		*dest++ = *str++;
	*dest = '\0';
}

char* TestStrncat(char* dest,const char* src,int n)
{
	assert((nullptr != dest) && (nullptr != src));

	if (n <= 0)
		return dest;
	else
	{
		while (*dest != '\0')
			dest++;
		while (n>0)
		{
			*dest++ = *src++;
			n--;
		}
		*dest = '\0';

		return dest;
	}
}

//////////////////////////////////////////////////////////////////////////
// 替换空格
void replaceSpace(char* str, int length)
{
	if (nullptr == str || length <= 0)
		return;
	int length1 = 0;
	int ii = 0;
	for (int i = 0; i < length; ++i)
	{
		++ii;
		if (' ' == str[i])
			++length1;
	}
	int length2 = length + length1 * 2;
	if (length2 < length)
		return;
	int index1 = length2;

	while (ii >= 0 && index1 > ii)
	{
		if (str[ii] == ' ')
		{
			str[index1--] = '0';
			str[index1--] = '2';
			str[index1--] = '%';
		}
		else
			str[index1--] = str[ii];
		--ii;
	}
}

//////////////////////////////////////////////////////////////////////////
// 从头到尾打印链表
struct ListNode
{
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {

	}
};

//std::vector<int> printListFromTailToHead(ListNode* head) 
//{
//	std::stack<ListNode*>nodes;
//	ListNode* temp = head;
//	while (temp)
//	{
//		nodes.push(temp);
//		temp = temp->next;
//	}
//	while (!nodes.empty())
//	{
//		::printf_s("%d", nodes.top()->val);
//		nodes.pop();
//	}
//}

//////////////////////////////////////////////////////////////////////////
// 重建二叉树
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* ConstructBinaryTree(int* preStart, int* preEnd, int* inStart, int* inEnd)
{
	int rootValue = preStart[0];
	TreeNode* root = new TreeNode(0);
	root->val = rootValue;
	root->left = root->right = nullptr;

	if (preStart == preEnd)
	{
		if ((inStart == inEnd) && (*preStart = *inStart))
			return root;
	}

	int* rootInorder = inStart;
	while (rootInorder != inEnd && *rootInorder != rootValue)
		++rootInorder;
	int leftLength = rootInorder - inStart;
	int* preleftEnd = preStart + leftLength;

	if (leftLength > 0)
		root->left = ConstructBinaryTree(preStart - 1, preleftEnd, inStart, rootInorder - 1);
	if (leftLength < preEnd - preStart)
		root->right = ConstructBinaryTree(preleftEnd + 1, preEnd, rootInorder + 1, inEnd);

	return root;
}

TreeNode* reConstructBinaryTree(std::vector<int> pre, std::vector<int> vin)
{
	if (pre.empty() || vin.empty() || pre.size() != vin.size())
		return nullptr;

	return ConstructBinaryTree(&(pre.front()),&(pre.back()),&(vin.front()),&(vin.back()));
}

//////////////////////////////////////////////////////////////////////////
// 二叉树的下一个结点
struct TreeLinkNode
{
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(nullptr), right(nullptr), next(nullptr) 
	{

	}
};

TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
	if (nullptr == pNode)
		return nullptr;
	TreeLinkNode* pNext = nullptr;

	if (pNode->right)
	{
		TreeLinkNode* pRight = pNode->right;
		while (pRight->left)
			pRight = pRight->left;

		pNext = pRight;
	}
	else if (pNode->next)
	{
		TreeLinkNode* current = pNode;
		TreeLinkNode* parent = pNode->next;

		while (parent && (current == parent->right))
		{
			current = parent;
			parent = parent->next;
		}
		pNext = parent;
	}

	return pNext;
}

//////////////////////////////////////////////////////////////////////////
// 两个栈实现队列
std::stack<int> stack1;
std::stack<int> stack2;

void push(int node) 
{
	stack1.push(node);
}

int pop() 
{
	if (stack2.size() <= 0)
	{
		while(!stack1.empty())
		{
			int data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}
	int head = stack2.top();
	stack2.pop();

	return head;
}

//////////////////////////////////////////////////////////////////////////
// 调整数组顺序使奇数位于偶数前面
void reOrderArray(std::vector<int>& array)
{
	if (array.empty())
		return;
	int head = 0;
	int tail = array.size() - 1;
	
	while (head<tail)
	{
		while (head < tail && (array[head] % 2 != 0))
			++head;
		while (head < tail && (array[tail] % 2 == 0))
			--tail;

		if (head < tail)
		{
			int temp = array[head];
			array[head] = array[tail];
			array[tail] = temp;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 树的子结构
bool Equal(double num1, double num2)
{
	if (num1 == num2)
		return true;
	return false;
}

bool DoesTreeHaveTree(TreeNode* root1, TreeNode* root2)
{
	if (!root1 || !root2)
		return false;
	if (!Equal(root1->val, root2->val))
		return false;

	return DoesTreeHaveTree(root1->left, root2->left) && DoesTreeHaveTree(root1->right, root2->right);
}

bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
	bool result = false;

	if (pRoot1 && pRoot2)
	{
		if (Equal(pRoot1->val, pRoot2->val))
			result = DoesTreeHaveTree(pRoot1, pRoot2);
		if (!result)
			result=HasSubtree(pRoot1->left, pRoot2);
		if (!result)
			result=HasSubtree(pRoot1->right, pRoot2);
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////
// 二叉树的镜像
void Mirror(TreeNode *pRoot) 
{
	if (!pRoot)
		return;
	if (!pRoot->left && !pRoot->right)
		return;
	TreeNode* temp = pRoot->left;
	pRoot->left = pRoot->right;
	pRoot->right = temp;

	if (pRoot->left)
		Mirror(pRoot->left);
	if (pRoot->right)
		Mirror(pRoot->right);
}
//////////////////////////////////////////////////////////////////////////
// 顺时针打印矩阵
void PrintMatrixInCircle(std::vector<std::vector<int>> matrix, int start, std::vector<int>& tmp)
{
	int row = matrix.size() - start - 1;  //行
	int col = matrix[start].size() - start - 1;  //列

	// 左到右
	for (int i = start; i <= col; ++i)
		tmp.push_back(matrix[start][i]);
	//::printf_s("%d", matrix[start][i]);

// 上到下
	if (start < row)
	{
		for (int i = start + 1; i <= row ; ++i)
			tmp.push_back(matrix[i][col]);
		//::printf_s("%d", matrix[i][col]);
	}

	// 右到左
	if (start < row && start < col)
	{
		for (int i = col - 1; i >= start; --i)
			tmp.push_back(matrix[row][i]);
		//::printf_s("%d", matrix[row][i]);
	}

	// 下到上
	if (start < col && start < row - 1)
	{
		for (int i = row - 1; i >= start + 1; --i)
			tmp.push_back(matrix[i][start]);
		//::printf_s("%d", matrix[i][start]);
	}
}

std::vector<int> printMatrix(std::vector<std::vector<int>> matrix)
{
	std::vector<int>tmp;
	if (matrix.empty() || matrix[0].empty())
		return tmp;

	int start = 0;
	int row = matrix.size();
	int col = matrix[0].size();
	while (col > start * 2 && row > start * 2)
	{
		PrintMatrixInCircle(matrix, start, tmp);
		++start;
	}

	return  tmp;
}

//////////////////////////////////////////////////////////////////////////
// 二叉树的深度
int TreeDepth(TreeNode* pRoot)
{
	if (nullptr == pRoot)
		return 0;
	int left = TreeDepth(pRoot->left);
	int right = TreeDepth(pRoot->right);

	return left > right ? left + 1 : right + 1;
}

//////////////////////////////////////////////////////////////////////////
// 平衡二叉树
bool IsBalanced_Solution(TreeNode* pRoot) 
{
	if (nullptr == pRoot)
		return true;
	int left = TreeDepth(pRoot->left);
	int right = TreeDepth(pRoot->right);

	if (::abs(left - right) > 1)
		return false;

	return IsBalanced_Solution(pRoot->left) && IsBalanced_Solution(pRoot->right);
}

bool Isbalanced(TreeNode* root,int* depth)
{
	if (!root)
	{
		*depth = 0;
		return 0;
	}

	int left, right;
	if (Isbalanced(root->left,&left) && Isbalanced(root->right,&right))
	{
		if (::abs(right - left) <= 1)
		{
			*depth = left > right ? left + 1 : right + 1;
			return true;
		}
	}

	return false;
}

bool IsBalancedSolution(TreeNode* root)
{
	int depth = 0;

	return Isbalanced(root, &depth);
}

//////////////////////////////////////////////////////////////////////////
// 二叉搜索树的第K大结点
TreeNode* KthNode(TreeNode* pRoot, int k)
{
	TreeNode* target = nullptr;

	if (!target && pRoot->left)
		target = KthNode(pRoot->left, k);

	if (!target)
	{
		if (k == 1)
			target = pRoot;
		--k;
	}
	if (!target && pRoot->right)
		target = KthNode(pRoot->right, k);

	return target;
}

//////////////////////////////////////////////////////////////////////////
// 字符串排列
void Permuta(std::string str,int k)
{
	//if(k==str.size())

	for (int i = k; i, str.length(); ++i)
	{
		char temp = str[k];
		str[k] = str[i];
		str[i] = temp;

		Permuta(str, k + 1);

		temp = str[k];
		str[k] = str[i];
		str[i] = temp;
	}
}

//std::vector<std::string> permutation(std::string str) 
//{
//
//}

class AA
{
public:
	std::string str1 = "456";
	int a;
	AA()
	{
		a = 100;
		Test();
	}

	virtual void Test()
	{
		std::cout << a << " " << str1 << std::endl;
	}
};

class BB : public AA
{
public:
	std::string str1 = "789";

	virtual void Test()
	{
		std::cout << str1 << std::endl;
	}
};

//////////////////////////////////////////////////////////////////////////
/** 包含min函数的栈 */
class Solution
{
public:
	void push(int value)
	{
		m_data.push(value);

		if (m_min.empty() || value < m_min.top())
			m_min.push(value);
		else
			m_min.push(m_min.top());
	}

	void pop()
	{
		if (m_min.empty() && m_data.empty())
			return;

		m_min.pop();
		m_data.pop();
	}

	int top()
	{
		return m_min.top();
	}
	int min()
	{
		return m_min.top();
	}

private:
	std::stack<int>m_min;
	std::stack<int>m_data;
};

//////////////////////////////////////////////////////////////////////////
/* 从上到下打印二叉树（层序遍历） */
std::vector<int> PrintFromTopToBottom(TreeNode* root) 
{
	std::vector<int>data;
	if (!root)
		return data;
	std::queue<TreeNode*>queueTree;
	queueTree.push(root);
	while (!queueTree.empty())
	{
		TreeNode* temp = queueTree.front();
		queueTree.pop();
		data.push_back(temp->val);
		if (temp->left)
			queueTree.push(temp->left);
		if (temp->right)
			queueTree.push(temp->right);
	}

	return data;
}

//////////////////////////////////////////////////////////////////////////
/** 二叉搜索树的后序遍历序列 */
bool SquenceOfBST(const std::vector<int>& sequence,int begin,int end)
{
	if (sequence.empty() || begin>end)
		return false;

	int root = sequence[end];
	int i = begin;
	for (; i < end; ++i)
	{
		if (sequence[i] > root)
			break;
	}
	for (int j = i; j < end; ++j)
	{
		if (sequence[j] < root)
			return false;
	}

	// 因为只有一个结点或结点没有左/右子树，所以将bool值置为true，满足特殊测试用例
	bool left = true;
	if (i > begin)
		left = SquenceOfBST(sequence, begin, i - 1);

	bool right = true;
	if (i < end - 1)
		right = SquenceOfBST(sequence, i, end - 1);

	return (left && right);
}

bool VerifySquenceOfBST(std::vector<int> sequence) 
{
	return SquenceOfBST(sequence, 0, sequence.size() - 1);
}

int jumpFloorII(int number)
{
	if (number == 0)
		return 0;
	int total = 1;
	for (int i = 1; i < number; ++i)
		total *= 2;

	return total;
}

struct NUM
{
	int a;
	int b;
	bool c:1;
};

//////////////////////////////////////////////////////////////////////////
/* 二叉树中和为某一值的路径 */
void FIndPath(TreeNode* root,std::vector<int>& path,int expectNumber,int currentNumber)
{
	currentNumber += root->val;
	path.push_back(root->val);
	bool isLeaf = !root->left && !root->right;
	if (currentNumber == expectNumber && isLeaf)
	{
		for (std::vector<int>::iterator it = path.begin(); it != path.end(); ++it)
		{
			::printf_s("%d", *it);
		}
		::printf_s("\n");
	}

	if (root->left)
		FIndPath(root->left, path, expectNumber, currentNumber);
	if (root->right)
		FIndPath(root->right, path, expectNumber, currentNumber);

	path.pop_back();
}

std::vector<int> FindPath(TreeNode* root, int expectNumber) 
{
	if (!root)
		return;

	std::vector<int>path;
	int currentNumber = 0;
	FIndPath(root, path, expectNumber, currentNumber);

	return path;
}

int main()
{
	std::string tr = "123";
	::printf_s("%d\n", tr.size());

	double s;
	::printf_s("%d\n", sizeof(s));
	::printf_s("%d\n",sizeof(NUM));

	int t1 = 4;
	int t2 = 4;
	//初始化方法1
	std::vector<std::vector<int>> TwoVec(t1, std::vector<int>(t2));  //4行4列
	int m = TwoVec.size();   //size()表示实际行元素个数
	int n = TwoVec[0].size();   //实际列元素个数
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
		//	TwoVec[i][j] = i * j;
			::scanf_s("%d", &TwoVec[i][j]);
		}
	}

	std::vector<int>TwoTmp = printMatrix(TwoVec);
	for (std::vector<int>::iterator it = TwoTmp.begin(); it != TwoTmp.end(); ++it)
		::printf_s("%d", *it);

	std::vector<int>vec = { 1,2,3,4,5 };
	reOrderArray(vec);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		::printf_s("%d ", *it);
	::printf_s("\n");

	::printf_s("%d\n", jumpFloorII(3));

	AA* a11 = new BB();
	//a11->Test();

	std::string str1 = "456";
	std::cout << str1 << std::endl;
	//::printf_s("%s\n",str1);

	 char str[] = "We Are Happy";
	replaceSpace(str,12);
	::printf_s("%s\n", str);

	char* a=new char[5];
	const char* b = "123";
	TestStrcpy(a, b);
	::printf_s("%s\n", a);

	int a1[8] = { 1,7,5,4,3,2,6,7 };
	int* b1 = a1;
	Test(a1, 8, b1);
	::printf_s("%d", *b1);

	delete[] a;
	b = nullptr;
	b1 = nullptr;

	::getchar(); ::getchar();
	return 0;
}

