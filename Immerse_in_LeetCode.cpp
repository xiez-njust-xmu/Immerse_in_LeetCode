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

int main()
{
	Solution90 leetcode90;
	vector<int> test{4,4,4,1,4};
	auto s = leetcode90.subsetsWithDup(test);
	PrintVecofVec(s);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
