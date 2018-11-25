#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NotFound -1

void BuildMatch(char *pattern, int *match);
int KMP(char *string, char *pattern);


int main()
{


	return 0;
}


int KMP(char *string, char *pattern)
{
	
	int n = strlen(string);
	int m = strlen(pattern);
	int s, p, *match;
	s = p = 0;

	if (n < m) return NotFound;

	// 建立起记录前后子串匹配位置的数组match
	// ****xxxxxxxxx**** 例如 **** 是匹配的子串 match[m] = 3
	match = malloc(sizeof(int) * m);
	BuildMatch(pattern, match);

	while (s < n && p < m) {
		if (string[s] == pattern[p]) { s++; p++; } // 当两个字符相等的时候 s 和 p 一起先前推进
		else if (p > 0) p = match[p-1] + 1;        // 遇到不想等的时候把 p 回溯至 match 的字串末尾
		else s++;								   // p <= 0 的时候说明两段字符串从第一个字母开始就不匹配 所以要将 s 向前推进	 p不动即可 											   
	}

	// 当 p 已经到了结尾 而 s 还没有到达结尾说明匹配成功 返回 s - m 否则匹配失败
	return (p == m)? (s - m) : NotFound;
}


void BuildMatch(char *pattern, int *match)
{
    int i, j;
    int m = strlen(pattern);
    match[0] = -1;
     
    for (j = 1; j < m; j++) {
        i = match[j-1];
        while ((i >= 0) && (pattern[i+1] != pattern[j])) i = match[i];
        if (pattern[i+1] == pattern[j]) match[j] = i + 1;
        else match[j] = -1;
    }
}