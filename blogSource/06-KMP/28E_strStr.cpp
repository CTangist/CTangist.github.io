#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isMatch(string P, string S, int start) {
        int len = P.size();
        bool flag = true;

        for (int i=0; i<len; ++i) {
            if (P[i] != S[start+i]) {
                flag = false;
                break;
            }
        }

        return flag;
    }

    int bruteForce(string P, string S) {
        int lengthP = P.size(), lengthS = S.size(), index = -1;

        for (int i=0; i<=lengthS-lengthP; ++i) {
            if (isMatch(P, S, i)) {
                index = i;
                break;
            }
        }

        return index;
    }

    int getNextI(string P, int i) {
        // 由于需要寻找子串"P[0]P[1]···P[i]"中令前 k 个字符等于后 k 个字符的最大的 k 值
        // 这里根据 k 的取值范围 (0 <= k < i+1) 倒着枚举：k : i -> 0
        int k = i, count = 0;
        while(k >= 0) {
            count = 0;          // count 用于累计相等字符个数
            for (int j=0; j<=k-1; ++j) {
                if (P[j] != P[i-k+j+1]) {
                    break;      // 出现不匹配字符，k 值过大
                } else {
                    count++;    // 增加相同字符个数
                }
            }
            if (count == k) return k;
            k--;
        }
        return 0;
    }

    vector<int> getNext(string P) {
        int lengthP = P.size(), k = 0;
        vector<int> next;

        // 遍历模式串P，依次计算next[i]
        for (int i=0; i<lengthP; ++i) next.push_back(getNextI(P, i));

        return next;
    }

    vector<int> getNextPro(string P) {
        int lengthP = P.size(), curK = 0, i = 1;
        vector<int> next;
        next.push_back(0);              // next[0] == 0 显然成立

        while (i < lengthP) {           // 从 next[1] 开始计算，方便回溯
            if (P[i] == P[curK]) {      // 符合第一种情况
                curK++;                 // 基于 next[i-1] 往后扩展一位
                next.push_back(curK);
                i++;
            } else {
                if (curK > 0) {         // 仍有回溯的空间
                    curK = next[curK-1];
                } else {                // curK 等于 0，不会再出现匹配成功的可能
                    next.push_back(0);
                    i++;
                }
            }
        }

        return next;
    }

    int KMP(string P, string S) {
        vector<int> next = getNextPro(P);
        /*
        curS:    存储主串（S）当前待匹配字符的索引；
        curP:    存储模式串（P）当前待匹配字符的索引；
        lengthS: 存储主串（S）的长度
        lengthP: 存储模式串（P）的长度
        */
        int curS = 0, curP = 0, lengthS = S.size(), lengthP = P.size();
        while (curS < lengthS) {
            if (P[curP] == S[curS]) {
                // 当前字符匹配成功
                curP++;
                curS++;
            } else {    // 匹配失败
                // 若第一个字符就不匹配，则将窗口向右滑动一位
                if (curP == 0) curS++;
                // 否则利用next[curP-1]设置窗口滑动步长
                else curP = next[curP-1];
            }
            // 如果一直到模式串最后都匹配成功，则返回S当前子串的起始位置索引
            if (curP == lengthP) return curS-lengthP;
        }

        return -1;
    }

};

int main() {
    string haystack = "a", needle = "a";
    Solution *so = new Solution();
    // cout << so->bruteForce(needle, haystack) << endl;
    // string P = "aaaab";
    // vector<int> next = so->getNextPro(P);
    // for (int i=0; i<next.size(); ++i) cout << next[i] << " ";
    // cout << endl;
    cout << so->KMP(needle, haystack) << endl;

    return 0;
}