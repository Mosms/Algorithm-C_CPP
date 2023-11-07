/*  This is the file about the algorithms that solves the string pattern matching problem 
 *  Version 1.00 . 2023-10
 *  Written by B. Fu, from NJU. Email me at feaka@foxmail.com */

#include <cstdio>
#include <cstring>
#include <vector>

// int xxxxx_SPM(char *T, char *S) is the function that solves the string pattern matching problem
// T is the text string, S is the pattern string
// return all the positions that S appears in T
// Learned from https://oi-wiki.org/string/match/ 

// BruteForce_SPM is the function that solves the string pattern matching problem using Brute Force
std::vector<int> BruteForce_SPM(char *s, char *t) {
  int n = strlen(s), m = strlen(t);
  std::vector<int> ans;
  int i, j;
  for (i = 0; i < n - m + 1; i++) {
    for (j = 0; j < m; j++) {
      if (s[i + j] != t[j]) break;
    }
    if (j == m) ans.push_back(i);
  }
  return ans;
}

// KMP_SPM is the function that solves the string pattern matching problem using KMP Algorithm
// This prefix_function is the function that solves the prefix function of a string, which is the core of KMP Algorithm
// can be adapted to an online version.
std::vector<int> prefix_function(char *s) {
  int n = strlen(s);
  std::vector<int> pi(n); pi[0] = 0;
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}
std::vector<int> KMP_SPM(char *text, char *pattern) {
  int sz1 = strlen(text), sz2 = strlen(pattern);
  std::vector<int> v;
  std::vector<int> lps = prefix_function(strcat(strcat(pattern, "$"), text));
  for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
    if (lps[i] == sz2) v.push_back(i - 2 * sz2);
  }
  return v;
}

int main(void)
{
    char T[20] = "ababababcabcbbabc";
    char S[20] = "abc";
    std::vector<int> ans1 = BruteForce_SPM(T, S);
    std::vector<int> ans2 = KMP_SPM(T, S);
    for (int i = 0; i < ans1.size(); i++) printf("%d ", ans1[i]);
    printf("\n");
    for (int i = 0; i < ans2.size(); i++) printf("%d ", ans2[i]);
    printf("\n");

    return 0;
}