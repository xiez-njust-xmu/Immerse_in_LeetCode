// Immerse_in_LeetCode.h : 此文件包含部分结构体定义。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>
using namespace std;
struct ListNode {
    int val;    
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//Definition for a binary tree node.
struct TreeNode {
    int val;  
    TreeNode *left;
    TreeNode *right;  
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
// range-based loop
void Printv(vector<vector<int> >& res) {
  cout << endl;
  for (auto& rowV : res) {
	cout << "[ ";
    for (auto& el : rowV) {
      cout << el << " ";
    }
    cout << "] ";
  }
  cout << endl;
}

void Printv(vector<int> & res) {
  cout << endl;
  cout << "[ ";
  for (auto& rowV : res) {
    cout << rowV << " ";
  }
  cout << "] ";
}


template<typename T = int>
vector<T> s2v(const string& s) {
  vector<T> res;

  int idx = 0;
  while (idx < s.size()) {
    while (idx < s.size() && !isdigit(s[idx])) idx++;
    int begin = idx;

    if (begin >= s.size()) {
      break;
    }

    while (idx < s.size() && isdigit(s[idx])) idx++;
    auto subs = s.substr(begin, idx - begin);
    res.push_back(stoll(subs));
  }

  return res;
}

template<typename T = int>
vector<vector<T>> s2vv(const string& s) {
  vector<vector<T>> res;

  // assume string should start with "["
  size_t pos = 1;
  while (pos < s.size()) {
    auto next_pos = s.find(']', pos);
    if (next_pos == string::npos) {
      break;
    }

    string s_sub_vec = s.substr(pos, next_pos - pos + 1);
    if (s_sub_vec.size() >= 2) {
      res.push_back(s2v<T>(s_sub_vec));
    }

    pos = next_pos + 1;
  }

  return res;
}