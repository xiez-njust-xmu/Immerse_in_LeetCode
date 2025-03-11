// Immerse_in_LeetCode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "Immerse_in_LeetCode.hpp"

/*
86. 分隔链表

给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。

你应当 保留 两个分区中每个节点的初始相对位置。*/
class Solution89 {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* small = new ListNode(0);
        ListNode* smallHead = small;
        ListNode* large = new ListNode(0);
        ListNode* largeHead = large;

		while(head!=nullptr)
		{
			if(head->val<x)
			{
				small->next = head;
				small = small->next;
			}
			else
			{
				large->next = head;
				large = large->next;
			}
			head = head->next;
		}
		large->next = nullptr;
		small->next = largeHead->next;
		return smallHead->next;
    }
};

/*
90. 子集 II
给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的 子集（幂集）。
解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。*/
class Solution90 {
public:
    vector<vector<int>> ans;
    vector<int> temp;
    set <vector<int>> mySet;
    //myVector.assign(mySet.begin(), mySet.end());
    void backtracking(vector<int>& nums,int num_index)
    {
        if(num_index >= nums.size())
            return;
        for(int i=num_index;i<nums.size();i++)
        {
            temp.push_back(nums[i]);
            mySet.insert(temp);
            backtracking(nums,i+1);
            temp.pop_back();
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        backtracking(nums,0);
        ans.assign(mySet.begin(), mySet.end());
        ans.push_back(temp);
        return ans;
    }
};

/*
92. 反转链表 II
给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。
 */
class Solution92{
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode * dummynode = new ListNode(0);
		dummynode->next = head;
		ListNode* pre = dummynode;
		for(int i=0;i<left-1;i++)
			pre = pre->next;
		ListNode* cur = pre->next;
		ListNode* next_node;
		for(int i = 0;i<right-left;i++)
		{
			next_node = cur->next;
			cur->next = next_node->next;
			next_node->next = pre->next;
			pre->next = next_node;
		}
		return dummynode->next;
    }
};

/*
102. 二叉树的层序遍历

给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）*/
class Solution102 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> ans;
        if(!root)
			return ans;
		queue<TreeNode*> q;
		q.push(root);
		while(!q.empty())
		{
			int currentLevelSize = q.size();
			ans.push_back(vector <int> ());
			for(int i=1;i<=currentLevelSize;i++)
			{
				auto now_node = q.front();
				q.pop();
				ans.back().push_back(now_node->val);
				if(now_node->left)
					q.push(now_node->left);
				if(now_node->right)
					q.push(now_node->right);
			}
		}
		return ans;
    }
};
/*
103. 二叉树的锯齿形层序遍历
给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。*/
class Solution103 {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root)
			return ans;
		queue<TreeNode*> q;
		q.push(root);
		bool ordernow = false;
		while(!q.empty())
		{
			int currentLevelSize = q.size();
			ans.push_back(vector <int> ());
			for(int i=1;i<=currentLevelSize;i++)
			{
				auto now_node = q.front();
				q.pop();
				if(ordernow)
					ans.back().push_back(now_node->val);
				else
					ans.back().insert(ans.back().begin(),now_node->val);
				if(now_node->left)
					q.push(now_node->left);
				if(now_node->right)
					q.push(now_node->right);
			}
			ordernow =!ordernow;
		}
		return ans;
    }
};

/*107. 二叉树的层序遍历 II
给你二叉树的根节点 root ，返回其节点值 自底向上的层序遍历 。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）*/
class Solution107 {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> ans;
		if (!root)
			return ans;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			int currentLevelSize = q.size();
			ans.push_back(vector<int>());
			for (int i = 1; i <= currentLevelSize; i++) {
				auto now_node = q.front();
				q.pop();
				ans.back().push_back(now_node->val);
				if (now_node->left)
					q.push(now_node->left);
				if (now_node->right)
					q.push(now_node->right);
			}
		}
		reverse(ans.begin(), ans.end());
		return ans;
	}
};

/*111. 二叉树的最小深度
给定一个二叉树，找出其最小深度。

最小深度是从根节点到最近叶子节点的最短路径上的节点数量。

说明：叶子节点是指没有子节点的节点。*/
class Solution111 {
public:
	/*dfs*/
	int minDepth(TreeNode* root) {
		if (root == nullptr)
			return 0;
		if (root->left == nullptr && root->right == nullptr) {
			return 1;
		}

		int min_depth = INT_MAX;
		if (root->left != nullptr) {
			min_depth = min(minDepth(root->left), min_depth);
		}
		if (root->right != nullptr) {
			min_depth = min(minDepth(root->right), min_depth);
		}

		return min_depth + 1;
	}
	/*bfs*/
	int minDepth2(TreeNode* root) {
		if (root == nullptr)
			return 0;
		queue< pair<TreeNode*, int> >que;
		que.push({ root,1 });
		while (!que.empty())
		{
			TreeNode* now_node = que.front().first;
			int now_depth = que.front().second;
			que.pop();
			if (now_node->left == nullptr && now_node->right == nullptr)
			{
				return now_depth;
			}
			if (now_node->left != nullptr)
				que.push({ now_node->left,now_depth + 1 });
			if (now_node->right != nullptr)
				que.push({ now_node->right,now_depth + 1 });
		}
		return 0;
	}
};

/*112. 路径总和
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。

叶子节点 是指没有子节点的节点*/
class Solution112 {
public:
	/*bfs*/
    bool hasPathSum1(TreeNode* root, int targetSum) {
        if(root==nullptr)
			return false;
		queue< pair<TreeNode*,int> > qt;
		qt.push({root,root->val});
		while(!qt.empty())
		{
			TreeNode* now_node = qt.front().first;
			int now_sum = qt.front().second;
			qt.pop();
			if(now_node->left==nullptr&&now_node->right==nullptr)
			{
				if(now_sum == targetSum)
					return true;
				continue;
			}
			if(now_node->left!=nullptr)
			{
				qt.push({now_node->left,now_sum+now_node->left->val});
			}
			if(now_node->right!=nullptr)
			{
				qt.push({now_node->right,now_sum+now_node->right->val});
			}
		}
		return false;
    }
	/*递归*/
	bool hasPathSum2(TreeNode* root, int targetSum) {
        if(root==nullptr)
			return false;
		if(root->left==nullptr&&root->right==nullptr)
			return targetSum == root->val;
		return hasPathSum2(root->left,targetSum-root->val)||hasPathSum2(root->right,targetSum-root->val);
    }
};
/*113. 路径总和 II
给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。

叶子节点 是指没有子节点的节点。*/

class Solution113 {
public:
	vector<vector<int> > ans;
	unordered_map<TreeNode*,TreeNode* > parent_node;
	void add_path(TreeNode* node)
	{
		vector<int>temp;
		while(node!=nullptr)
		{
			temp.push_back(node->val);
			node = parent_node[node];
		}
		reverse(temp.begin(),temp.end());
		ans.push_back(temp);
	}
	vector<int> onepath;
	void dfs(TreeNode* root, int targetSum)
	{
		if(root==nullptr)
			return;
		onepath.push_back(root->val);
		targetSum -= root->val;
		if(root->left==nullptr&&root->right==nullptr)
		{
			if(0 == targetSum)
				ans.push_back(onepath);
		}
		dfs(root->left,targetSum);
		dfs(root->right,targetSum);
		onepath.pop_back();
	}
    vector<vector<int> > pathSum(TreeNode* root, int targetSum) {
		if(root==nullptr)
			return ans;
		/* dfs(root,targetSum);
			return ans; */
		queue< pair<TreeNode*,int> > qt;
		qt.push({root,root->val});
		while(!qt.empty())
		{
			TreeNode* now_node = qt.front().first;
			int now_sum = qt.front().second;
			qt.pop();
			if(now_node->left==nullptr&&now_node->right==nullptr)
			{
				if(now_sum == targetSum)
					add_path(now_node);
			}
			if(now_node->left!=nullptr)
            {
                parent_node[now_node->left] = now_node;
                qt.push({now_node->left,now_sum+now_node->left->val});
            }	
			if(now_node->right!=nullptr)
            {
                 parent_node[now_node->right] = now_node;
                 qt.push({now_node->right,now_sum+now_node->right->val});
            }
		}
		return ans;
    }
};

/*
114. 二叉树展开为链表

给你二叉树的根结点 root ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
展开后的单链表应该与二叉树 先序遍历 顺序相同。*/
class Solution114 {
public:
	void preorderTraversal(TreeNode* root,vector<TreeNode*>& l)
	{
		if(root!=nullptr)
		{
			l.push_back(root);
			preorderTraversal(root->left,l);
			preorderTraversal(root->right,l);
		}
	}
    void flatten(TreeNode* root) {
        vector<TreeNode* > l;
		preorderTraversal(root,l);
		for(int i=1;i<l.size();i++)
		{
			TreeNode* pre = l.at(i-1);
			TreeNode* cur = l.at(i);
			pre->left = nullptr;
			pre->right = cur;
		}
    }
};

/*
116. 填充每个节点的下一个右侧节点指针

给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。*/

/*117. 填充每个节点的下一个右侧节点指针 II

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。

初始状态下，所有 next 指针都被设置为 NULL 。*/
class Solution116_117 {
public:
    Node* connect(Node* root) {
        if(root == nullptr)
			return nullptr;
		queue<Node* > q;
		q.push(root);
		while(!q.empty())
		{
			int current_level_size = q.size();
			for(int i = 0;i<current_level_size;i++)
			{
				Node* now_node = q.front();
				q.pop();
				 
				if(i<current_level_size-1)
					now_node->next = q.front();
				else
					now_node->next = nullptr;
				
				if(now_node->left!=nullptr)
					q.push(now_node->left);
				if(now_node->right!=nullptr)
					q.push(now_node->right);
			}
		}
		return root;
    }
};
/*118. 杨辉三角
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。*/
class Solution118 {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
		for(int i=1;i<=numRows;i++)
		{
			vector<int> temp;
			for(int j=0;j<i;j++)
			{
				if(j==0)
				{
					temp.push_back(1);
					continue;
				}
				if(j==i-1)
				{
					temp.push_back(1);
					continue;
				}
				if(j>0&&j<i-1)
					temp.push_back(ans.back()[j]+ans.back()[j-1]);
			}
			ans.push_back(temp);
		}
		return ans;	
    }
};
/*119. 杨辉三角 II
给定一个非负索引 rowIndex，返回「杨辉三角」的第 rowIndex 行。

在「杨辉三角」中，每个数是它左上方和右上方的数的和。*/
class Solution119 {
public:
	vector<int> getRow(int rowIndex) {
		vector<int> temp;
		vector<int> Upper;
		for (int i = 1; i <= rowIndex+1; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (j == 0)
				{
					temp.push_back(1);
					continue;
				}
				if (j == i - 1)
				{
					temp.push_back(1);
					continue;
				}
				if (j > 0 && j < i - 1)
					temp.push_back(Upper[j] + Upper[j - 1]);
			}
			Upper = temp;
			temp.clear();
		}
		return Upper;
	}
};
/*122. 买卖股票的最佳时机 II
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。

在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。

返回 你能获得的 最大 利润 。
*/
class Solution122 {
public:
    int maxProfit(vector<int>& prices) {
		int ans = 0;
        for(int i =1;i<prices.size();i++)
		{
			if(prices[i]>prices[i-1])
				ans+=(prices[i]-prices[i-1]);
		}
		return ans;
    }
};

/*128. 最长连续序列
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。*/
class Solution128 {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set <int> st;
		for(int i=0;i<nums.size();i++)
			st.insert(nums[i]);
		int ans = 0;
		int currentnum = 0;
		for(auto & onenum:st)
		{
			int nowcount = 0;
			if(!st.count(onenum-1))
			{
				currentnum = onenum;
				nowcount = 1;
			}
			while(st.count(currentnum + 1))
			{	
				currentnum++;
				nowcount++;
			}
			ans = max(ans,nowcount);
		}
		return ans;
    }
};

/*129. 求根节点到叶节点数字之和
给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
每条从根节点到叶节点的路径都代表一个数字：

例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。

叶节点 是指没有子节点的节点。*/
class Solution129 {
public:
	vector<int> onepath;
	int ans = 0;
	void dfs(TreeNode* root)
	{
		if(root==nullptr)
			return;
		onepath.push_back(root->val);
		if(root->left==nullptr&&root->right==nullptr)
		{
			for(int i=0;i<onepath.size();i++)
			{
				ans += (pow(10,onepath.size()-i-1)*onepath[i]);
			}
		}
		dfs(root->left);
		dfs(root->right);
		onepath.pop_back();
	}
	
    int sumNumbers(TreeNode* root) {
        dfs(root);
		return ans;
    }
};

/*134. 加油站
在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

给定两个整数数组 gas 和 cost ，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1 。如果存在解，则 保证 它是 唯一 的。*/
class Solution134 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        size_t n = gas.size();
		int i = 0;
		while (i<n)
		{
			int sum_gas = 0;
			int sum_cost = 0;
			int cnt = 0;
			while(cnt < n)
			{
				int now = (i+cnt)%n;
				sum_cost += cost[now];
				sum_gas += gas[now];
				if(sum_cost>sum_gas)
					break;
				++cnt;
			}
			if(cnt == n)
				return i;
			else
				i = i+cnt+1;
		}
		return -1;
    }
};

/*
137. 只出现一次的数字 II
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。

你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。*/
class Solution137 {
public:
    int singleNumber(vector<int>& nums) {
		int ans = 0;
        for(int i= 0;i < 32;i++)
		{
			int total = 0;
			for(int num :nums)
			{
				total += (num>>i)&1;
			}
			if(total%3)
				ans |= (1<<i);
		}
		return ans;
    }
};

/*142. 环形链表 II
给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

不允许修改 链表。*/
class Solution142 {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> visited;
		while(head!=nullptr)
		{
			if(visited.count(head)!=0)
				return head;
			visited.insert(head);
			head = head->next;
		}
		return nullptr;
    }
};

/*143. 重排链表
给定一个单链表 L 的头节点 head ，单链表 L 表示为：

L0 → L1 → … → Ln - 1 → Ln
请将其重新排列后变为：

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。*/
class Solution143{
public:
	ListNode* findmiddle(ListNode* head)
	{
		ListNode* fast = head;
		ListNode* slow = head;
		/*快慢指针的顺序必须是这样！*/
		while (fast->next != nullptr &&fast->next->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		return slow;
	}
	ListNode* ReverseList(ListNode* head)/*迭代反转*/
	{
		ListNode* pre = nullptr;
		ListNode* cur = head;
		ListNode* nex = nullptr;
		while (cur != nullptr)
		{
			nex = cur->next;
			cur->next = pre;
			pre = cur;
			cur = nex;
		}
		return pre;
	}
	void MergeList(ListNode* l1, ListNode* l2)
	{
		ListNode* temp1;
		ListNode* temp2;
		while (l1 != nullptr && l2 != nullptr) {
			temp1 = l1->next;
			temp2 = l2->next;

			l1->next = l2;
			l1 = temp1;

			l2->next = l1;
			l2 = temp2;
		}
	}
	void reorderList(ListNode* head) {
		if (head == nullptr || head->next == nullptr)
			return;
		ListNode* middle = findmiddle(head);
		ListNode* l1 = head;
		ListNode* l2 = middle->next;
		middle->next = nullptr;
		l2 = ReverseList(l2);
		MergeList(l1, l2);
	}
};

/*144. 二叉树的前序遍历
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。*/
class Solution144 {
public:
	void preorder(TreeNode* root, vector<int>& res) {
		if (root == nullptr) {
			return;
		}
		res.push_back(root->val);
		preorder(root->left, res);
		preorder(root->right, res);
	}
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> ans;
		preorder(root, ans);
		return ans;
	}
};

/*145. 二叉树的后序遍历
给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。*/
class Solution145 {
public:
	void backorder(TreeNode* root, vector<int>& res) {
		if (root == nullptr) {
			return;
		}
		backorder(root->left, res);
		backorder(root->right, res);
		res.push_back(root->val);
	}
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ans;
		backorder(root, ans);
		return ans;
	}
};
/*151. 反转字符串中的单词
给你一个字符串 s ，请你反转字符串中 单词 的顺序。

单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。

返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。

注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。*/
class Solution151 {
public:
    string reverseWords(string s) {
        int left = 0;
		int right = s.size()-1;
		while(left <= right&&s[left]==' ')
			left++;
		while(left <= right&&s[right]==' ')
			right--;
		deque<string> d;
		string now_word;
		while(left<=right)
		{
			char c = s[left];
			if(now_word.size()&&c==' ')
			{
				d.push_front(std::move(now_word));
				now_word="";
			}
			else if(c!=' ')
				now_word+=c;
			++left;
		}
		d.push_front(std::move(now_word));
		string ans;
		while(!d.empty())
		{
			ans+=d.front();
			d.pop_front();
			if(!d.empty())
				ans+=' ';
		}
		return ans;
    }
};

/*152. 乘积最大子数组
给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续 
子数组
（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

测试用例的答案是一个 32-位 整数。*/
class Solution152 {
public:
    int maxProduct(vector<int>& nums) {
        long minf = nums[0];
		long maxf = nums[0];
		long ans = nums[0];
		for(int i=1;i<nums.size();i++)
		{
			long mx = maxf;
			long mn = minf;
			maxf = max(mx*nums[i],max((long)nums[i],mn*nums[i]));
			minf = min(mn*nums[i],min((long)nums[i],nums[i]*mx));
			if(minf<INT_MIN)
				minf = nums[i];
			ans = max(ans,maxf);
		}
		return ans;
    }
};

/*153. 寻找旋转排序数组中的最小值

已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]
注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。

给你一个元素值 互不相同 的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。

你必须设计一个时间复杂度为 O(log n) 的算法解决此问题*/
class Solution153 {
public:
    int findMin(vector<int>& nums) {
        int left= 0;
		int right = nums.size()-1;
		while(left<right)
		{
			int mid = (left+right)/2;
			if(nums[mid]>nums[right])
				left = mid+1;
			else
				right = mid;
		}
		return nums[right];
    }
};

/*661. 图片平滑器
图像平滑器 是大小为 3 x 3 的过滤器，用于对图像的每个单元格平滑处理，平滑处理后单元格的值为该单元格的平均灰度。

每个单元格的  平均灰度 定义为：该单元格自身及其周围的 8 个单元格的平均值，结果需向下取整。（即，需要计算蓝色平滑器中 9 个单元格的平均值）。

如果一个单元格周围存在单元格缺失的情况，则计算平均灰度时不考虑缺失的单元格（即，需要计算红色平滑器中 4 个单元格的平均值）。*/
class Solution661 {
public:
	vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
		int m = img.size();
		int n = img[0].size();
		vector<vector<int>> sum(m + 1, vector<int>(n + 1, 0));
		vector<vector<int>> ans(m, vector<int>(n, 0));
		//前缀和
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + img[i - 1][j - 1];
			}
		}

		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				//四个边界
				int a = max(0, i - 1);
				int b = max(0, j - 1);
				int c = min(m - 1, i + 1);
				int d = min(n - 1, j + 1);
				//格子数量
				int cnt = (c - a + 1) * (d - b + 1);

				int tot = sum[c + 1][d + 1] - sum[a][d + 1] - sum[c + 1][b] + sum[a][b];
				ans[i][j] = tot / cnt;
			}
		}
		return ans;
	}
};

/*155. 最小栈
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

实现 MinStack 类:

MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。*/
class MinStack {
public:
	vector <int > ans;
    MinStack() {
        
    }
    void push(int val) {
	   ans.push_back(val);
    }
    
    void pop() {
		ans.pop_back();
    }
    
    int top() {
		return ans[ans.size()-1];
    }
    
    int getMin() {
        return *min_element(ans.begin(),ans.end());
    }
};
/*743. 网络延迟时间
有 n 个网络节点，标记为 1 到 n。

给你一个列表 times，表示信号经过 有向 边的传递时间。 times[i] = (ui, vi, wi)，其中 ui 是源节点，vi 是目标节点， wi 是一个信号从源节点传递到目标节点的时间。

现在，从某个节点 K 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 -1 。*/
class Solution743 {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;
        vector<vector<pair<int, int>>> grid(n);
        for (auto &t : times) {
            int x = t[0] - 1, y = t[1] - 1;
            grid[x].emplace_back(y, t[2]);
        }
		vector<int> dist(n, inf);
        dist[k - 1] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
		q.emplace(k-1,0);
		while(!q.empty())
		{
			auto now_node = q.top();
			q.pop();
			int to = now_node.first;
			int use_time = now_node.second;
			if(dist[to]<use_time)
				continue;
			for(auto & e: grid[to])
			{
				int y = e.first;
				int d = dist[to]+e.second;
				if(d<dist[y])
				{
					dist[y] = d;
					q.emplace(y,d);
				}
			}
		}
		auto ans = *max_element(dist.begin(),dist.end());
		return ans == inf ? -1: ans;
    }
};
/*
825. 适龄的朋友
在社交媒体网站上有 n 个用户。给你一个整数数组 ages ，其中 ages[i] 是第 i 个用户的年龄。

如果下述任意一个条件为真，那么用户 x 将不会向用户 y（x != y）发送好友请求：

ages[y] <= 0.5 * ages[x] + 7
ages[y] > ages[x]
ages[y] > 100 && ages[x] < 100
否则，x 将会向 y 发送一条好友请求。

注意，如果 x 向 y 发送一条好友请求，y 不必也向 x 发送一条好友请求。另外，用户不会向自己发送好友请求。

返回在该社交媒体网站上产生的好友请求总数。*/
class Solution825 {
public:
	int numFriendRequests(vector<int>& ages) {
		int* ageCnt = new int[200];
		memset(ageCnt, 0, sizeof(int) * 200);
		int ans = 0;

		for (int i = 0; i < ages.size(); i++)
		{
			ageCnt[ages[i]]++;
		}

		for (int i = 1; i < 121; i++)
		{
			for (int j = 1; j < 121; j++)
			{
				if (ageCnt[i] == 0 || j > i) {
					continue;
				}
				if (!((j <= i / 2 + 7) || j > i || (j > 100 && i < 100))) {
					if (i == j)
						ans += ageCnt[i] * (ageCnt[i] - 1);
					else
						ans += ageCnt[i] * (ageCnt[j]);
				}
			}
		}
		delete[] ageCnt;
		return ans;
	}
};
/*2012. 数组美丽值求和
中等

给你一个下标从 0 开始的整数数组 nums 。对于每个下标 i（1 <= i <= nums.length - 2），nums[i] 的 美丽值 等于：

2，对于所有 0 <= j < i 且 i < k <= nums.length - 1 ，满足 nums[j] < nums[i] < nums[k]
1，如果满足 nums[i - 1] < nums[i] < nums[i + 1] ，且不满足前面的条件
0，如果上述条件全部不满足
返回符合 1 <= i <= nums.length - 2 的所有 nums[i] 的 美丽值的总和 。
*/
class Solution2012 {
public:
	int sumOfBeauties(vector<int>& nums) {
		int n = nums.size();
		vector <int> state(n);
		int premax = nums[0];
		for(int i=1;i<n-1;i++)
		{
			if(nums[i]>premax)
			{
				state[i] = 1;
				premax = nums[i];
			}
		}
		int premin = nums[n-1];
		int ans = 0;
		for(int i=n-2;i>=1;i--)
		{
			if(state[i]&&nums[i]<premin)
				ans+=2;
			else if(nums[i-1]<nums[i]&&nums[i]<nums[i+1])
				ans++;
			
			premin = min(premin,nums[i]);
		}
		return ans;
	}
};

/*
3001. 捕获黑皇后需要的最少移动次数
	现有一个下标从 1 开始的 8 x 8 棋盘，上面有 3 枚棋子。
	给你 6 个整数 a 、b 、c 、d 、e 和 f ，其中：
	(a, b) 表示白色车的位置。
	(c, d) 表示白色象的位置。
	(e, f) 表示黑皇后的位置。
假定你只能移动白色棋子，返回捕获黑皇后所需的最少移动次数。
请注意：
	车可以向垂直或水平方向移动任意数量的格子，但不能跳过其他棋子。
	象可以沿对角线方向移动任意数量的格子，但不能跳过其他棋子。
	如果车或象能移向皇后所在的格子，则认为它们可以捕获皇后。
	皇后不能移动。*/

class Solution3001 {
public:
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) {
		 if(a == e &&(c!=a || d<min(b,f) || d>max(b,f)))
			return 1;
		if(b==f&&(b!=d||c<min(a,e)||c>max(a,e)))
			return 1;
        if(abs(e-c)==abs(f-d)&&((c-e)*(b-f)!=(a-e)*(d-f)||a<min(c,e)||a>max(c,e)))
			return 1;
		else
			return 2;
    }
};

/*3159. 查询数组中元素的出现位置

给你一个整数数组 nums ，一个整数数组 queries 和一个整数 x 。

对于每个查询 queries[i] ，你需要找到 nums 中第 queries[i] 个 x 的位置，并返回它的下标。如果数组中 x 的出现次数少于 queries[i] ，该查询的答案为 -1 。

请你返回一个整数数组 answer ，包含所有查询的答案。*/
class Solution3159 {
public:
    vector<int> occurrencesOfElement(vector<int>& nums, vector<int>& queries, int x) {
		vector<int> ans;
		vector<int> arr;
		for(int i=0;i<nums.size();i++)
		{
			if(nums[i] == x)
				arr.push_back(i);
		}
		for(int i=0;i<queries.size();i++)
		{
			if(arr.size()<queries[i])
				ans.push_back(-1);
			else
				ans.push_back(arr[queries[i]-1]);
		}
		return ans;
    }
};
/*3206. 交替组 I
给你一个整数数组 colors ，它表示一个由红色和蓝色瓷砖组成的环，第 i 块瓷砖的颜色为 colors[i] ：

colors[i] == 0 表示第 i 块瓷砖的颜色是 红色 。
colors[i] == 1 表示第 i 块瓷砖的颜色是 蓝色 。
环中连续 3 块瓷砖的颜色如果是 交替 颜色（也就是说中间瓷砖的颜色与它 左边 和 右边 的颜色都不同），那么它被称为一个 交替 组。

请你返回 交替 组的数目。

注意 ，由于 colors 表示一个 环 ，第一块 瓷砖和 最后一块 瓷砖是相邻的。*/
class Solution3206 {
public:
	int numberOfAlternatingGroups(vector<int>& colors) {
		int ans = 0;
		int n = colors.size();
		for (int i = 0; i < n; i++)
		{
			if (colors[i] != colors[(i + 1) % n] && colors[(i + 2) % n] != colors[(i + 1) % n])
				ans++;
		}
		return ans;
	}
};

/*3208. 交替组 II
给你一个整数数组 colors 和一个整数 k ，colors表示一个由红色和蓝色瓷砖组成的环，第 i 块瓷砖的颜色为 colors[i] ：

colors[i] == 0 表示第 i 块瓷砖的颜色是 红色 。
colors[i] == 1 表示第 i 块瓷砖的颜色是 蓝色 。
环中连续 k 块瓷砖的颜色如果是 交替 颜色（也就是说除了第一块和最后一块瓷砖以外，中间瓷砖的颜色与它 左边 和 右边 的颜色都不同），那么它被称为一个 交替 组。

请你返回 交替 组的数目。

注意 ，由于 colors 表示一个 环 ，第一块 瓷砖和 最后一块 瓷砖是相邻的。*/
class Solution3208 {
public:
	int numberOfAlternatingGroups(vector<int>& colors, int k) {
		int ans = 0;
		int n = colors.size();
		int cnt = 1;
		for (int i = 0; i < n + k - 2; i++)
		{
			if (colors[i % n] != colors[(i + 1) % n])
				cnt++;
			else
				cnt = 1;
			if (cnt >= k)
				ans++;
		}
		return ans;
	}
};
/*3232. 判断是否可以赢得数字游戏
给你一个 正整数 数组 nums。

Alice 和 Bob 正在玩游戏。在游戏中，Alice 可以从 nums 中选择所有个位数 或 所有两位数，剩余的数字归 Bob 所有。如果 Alice 所选数字之和 严格大于 Bob 的数字之和，则 Alice 获胜。

如果 Alice 能赢得这场游戏，返回 true；否则，返回 false。*/
class Solution3232 {
public:
	bool canAliceWin(vector<int>& nums) {
		int ans = 0;
		int ans10 = 0;
		for (int num : nums)
		{
			if (num < 10)
				ans += num;
			else
				ans10 += num;
		}
		return !(ans == ans10);
	}
};
/*3238. 求出胜利玩家的数目
给你一个整数 n ，表示在一个游戏中的玩家数目。同时给你一个二维整数数组 pick ，其中 pick[i] = [xi, yi] 表示玩家 xi 获得了一个颜色为 yi 的球。

如果玩家 i 获得的球中任何一种颜色球的数目 严格大于 i 个，那么我们说玩家 i 是胜利玩家。换句话说：

如果玩家 0 获得了任何的球，那么玩家 0 是胜利玩家。
如果玩家 1 获得了至少 2 个相同颜色的球，那么玩家 1 是胜利玩家。
...
如果玩家 i 获得了至少 i + 1 个相同颜色的球，那么玩家 i 是胜利玩家。
请你返回游戏中 胜利玩家 的数目。

注意，可能有多个玩家是胜利玩家。*/
class Solution3238 {
public:
	int winningPlayerCount(int n, vector<vector<int>>& pick) {
		int SUM[10][11];
		memset(SUM, 0, sizeof(SUM));
		for (auto& onepick : pick)
		{
			SUM[onepick[0]][onepick[1]]++;
		}
		int ans = 0;
		for (int i = 0; i < n; i++)
		{
			//bool temp = false;
			for (int j = 0; j <= 10; j++)
			{
				if (SUM[i][j] > i)
				{
					ans++;
					break;
				}
					
			}
		}
		return ans;
	}
};

/*
3243. 新增道路查询后的最短距离 I

给你一个整数 n 和一个二维整数数组 queries。

有 n 个城市，编号从 0 到 n - 1。初始时，每个城市 i 都有一条单向道路通往城市 i + 1（ 0 <= i < n - 1）。

queries[i] = [ui, vi] 表示新建一条从城市 ui 到城市 vi 的单向道路。每次查询后，你需要找到从城市 0 到城市 n - 1 的最短路径的长度。

返回一个数组 answer，对于范围 [0, queries.length - 1] 中的每个 i，answer[i] 是处理完前 i + 1 个查询后，从城市 0 到城市 n - 1 的最短路径的长度*/
class Solution3243 {
public:
	const int inf = 0x3f3f3f3f;
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int> >grid(n);
		for(int i=0;i<n-1;i++)
			grid[i].push_back(i+1);
		vector<int> ans;
		int *dis = new int[n];
		int *vis = new int[n];
		//onepath表示一条路径
		for(auto& onepath : queries)
		{
			grid[onepath[0]].push_back(onepath[1]);
			memset(dis,inf,sizeof(int)*n);
			memset(vis,0,sizeof(int)*n);
			dis[0] = 0;
			priority_queue<int> pq;
			pq.push(0);
			int now = 0;
			int new_dis = 0;
			while(!pq.empty())
			{
				now = pq.top();
				pq.pop();
				/* if (vis[now])
            		continue;
        		vis[now] = 1; */
				for(int i=0;i<grid[now].size();i++)
				{
					/* if(vis[grid[now][i]])
						continue; */
					new_dis = dis[now] + 1;
					if(new_dis < dis[grid[now][i]])
					{
						dis[grid[now][i]] = new_dis;
						pq.push(grid[now][i]);
					}
				}
			}
			ans.emplace_back(dis[n-1]);
		}
		return ans;
    }
};

/*
3233. 统计不是特殊数字的数字数量
给你两个 正整数 l 和 r。对于任何数字 x，x 的所有正因数（除了 x 本身）被称为 x 的 真因数。

如果一个数字恰好仅有两个 真因数，则称该数字为 特殊数字。例如：

数字 4 是 特殊数字，因为它的真因数为 1 和 2。
数字 6 不是 特殊数字，因为它的真因数为 1、2 和 3。
返回区间 [l, r] 内 不是 特殊数字 的数字数量。*/
class Solution3233 {
public:
	bool *is_prime = nullptr;
	void sieve(int n)
	{
		is_prime = new bool[n+1];    // 标记范围内所有数
		int p = 0;
		for(int i=0;i<=n;i++)
			is_prime[i]=true;       // 所有数先标记为true
		is_prime[0] = is_prime[1] = false;   // 把数字0，1标记为质数
		for(int i=2;i<=n;i++)
		{
			if(is_prime[i])         // 如果这个数没有被标记为false
			{
				for(int j=i*i;j<=n;j+=i)   // 这里没有优化时的写法是for(int j=2*i; j<=n; j++)。
					is_prime[j]=false;
			}
		}
	}
    int nonSpecialCount(int l, int r) {
        int sum_num = r-l+1;
		sieve(sqrt(r+1));
		/*取上界函数*/
		for(int i = ceil(sqrt(l));i <= sqrt(r);i++)
		{
			if(is_prime[i])
				sum_num--;
		}
		return sum_num;
    }
};

/*3248. 矩阵中的蛇
大小为 n x n 的矩阵 grid 中有一条蛇。蛇可以朝 四个可能的方向 移动。矩阵中的每个单元格都使用位置进行标识： grid[i][j] = (i * n) + j。

蛇从单元格 0 开始，并遵循一系列命令移动。

给你一个整数 n 表示 grid 的大小，另给你一个字符串数组 commands，其中包括 "UP"、"RIGHT"、"DOWN" 和 "LEFT"。题目测评数据保证蛇在整个移动过程中将始终位于 grid 边界内。

返回执行 commands 后蛇所停留的最终单元格的位置。*/
class Solution3248 {
public:
    int finalPositionOfSnake(int n, vector<string>& commands) {
		int nowx = 0;
		int nowy = 0;
		for(auto& one_command:commands)
		{
			if(one_command[0] == 'U')
			{
				nowy--;
			}
			else if(one_command[0] == 'R')
			{
				nowx++;
			}
			else if(one_command[0] == 'L')
			{
				nowx--;
			}
			else{
				nowy++;
			}
		}
		return nowy*n+nowx;
    }
};

/*3274. 检查棋盘方格颜色是否相同
给你两个字符串 coordinate1 和 coordinate2，代表 8 x 8 国际象棋棋盘上的两个方格的坐标。*/
class Solution3274 {
public:
	bool checkTwoChessboards(string coordinate1, string coordinate2) {
		int c1 = coordinate1[0] - 'a' + coordinate1[1] - '1';
		int c2 = coordinate2[0] - 'a' + coordinate2[1] - '1';
		return (c1 % 2 == c2 % 2);
	}
};

/*3285. 找到稳定山的下标

有 n 座山排成一列，每座山都有一个高度。给你一个整数数组 height ，其中 height[i] 表示第 i 座山的高度，再给你一个整数 threshold 。

对于下标不为 0 的一座山，如果它左侧相邻的山的高度 严格大于 threshold ，那么我们称它是 稳定 的。我们定义下标为 0 的山 不是 稳定的。

请你返回一个数组，包含所有 稳定 山的下标，你可以以 任意 顺序返回下标数组。*/
class Solution3285 {
public:
    vector<int> stableMountains(vector<int>& height, int threshold) {
        vector<int> ans;
		for(int i=0;i<height.size()-1;i++)
		{
			if(height[i]>threshold)
				ans.push_back(i+1);
		}
		return ans;
    }
};
int main()
{
	
	Solution151 s;
	auto a = "the sky is blue";
	auto x = s.reverseWords(a);
	cout<<x;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
