// Immerse_in_LeetCode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "Immerse_in_LeetCode.hpp"

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
		memset(ageCnt, 0, sizeof(int)*200);
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
				if (!((j <= i/2 + 7) || j > i || (j > 100 && i < 100))) {
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
        vector<vector<int>> sum(m+1, vector<int>(n+1, 0));
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
class Solution {
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
				for(int i=0;i<n;i++)
					cout<<dis[i]<<" ";
				cout<<endl;
			}
			cout<<"---------------"<<endl;
			ans.emplace_back(dis[n-1]);
		}
		return ans;
    }
};

int main()
{
	Solution3243 s;
	string str = "[[0,3],[0,2]]";
	auto temp1 = s2vv(str);
	auto temp2 = s.shortestDistanceAfterQueries(4,temp1);
	Printv(temp2);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
