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
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
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
/*
661. 图片平滑器
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
int main()
{
	Solution118 s;
	auto temp2 = s.generate(5);
	Printv(temp2);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
