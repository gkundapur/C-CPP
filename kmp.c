#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fills lps[] for given pattern pat
void computeLPSArray(const char* pat, int M, int* lps)
{
    // Length of the previous longest prefix suffix
    int j = 0;

    // lps[0] is always 0
    lps[0] = 0;

    // Loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[j]) {
            lps[i] = j + 1;
            i++;
            j++;
        }
        else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of pat in txt and returns an array of
// occurrences
int* KMPSearch(const char* pat, const char* txt, int* count)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // Create lps[] that will hold the longest prefix suffix
    // values for pattern
    //int* lps = (int*)malloc(M * sizeof(int));
	int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int* result = (int*)malloc(N * sizeof(int));

    // Number of occurrences found
    *count = 0;

    int i = 0; // index for txt
    int j = 0; // index for pat
  
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {

			// to return first occurance only
			// return i - j;

            // Record the all occurrence (1-based index)
            //result[*count] = i - j + 1;
            result[*count] = i - j;
            (*count)++;
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
    //free(lps);
    return result;
}

// Driver code
int main()
{
    //const char txt[] = "geeksforgeeks";
    //const char pat[] = "geeks";
    const char txt[] = "qabcgabcabcd";
	const char pat[] = "abcd";
    int count;

    // Call KMPSearch and get the array of occurrences
    int* result = KMPSearch(pat, txt, &count);

    // Print all the occurrences (1-based indices)
    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(result);

    return 0;
}

/***************************************************************************
Given an array of string words, return all strings in words that is a substring of another word. You can return the answer in any order.

A substring is a contiguous sequence of characters within a string

 

Example 1:

Input: words = ["mass","as","hero","superhero"]
Output: ["as","hero"]
Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
["hero","as"] is also a valid answer.
Example 2:

Input: words = ["leetcode","et","code"]
Output: ["et","code"]
Explanation: "et", "code" are substring of "leetcode".
Example 3:

Input: words = ["blue","green","bu"]
Output: []
Explanation: No string of words is substring of another string.
 

Constraints:

1 <= words.length <= 100
1 <= words[i].length <= 30
words[i] contains only lowercase English letters.
All the strings of words are unique.

class Solution {
public:
     void computeLPS(string pattern, int lps[]) {
        int M = pattern.length();
        int j = 0;

        lps[0] = 0;

        int i = 1;
        while (i < M) {
            if (pattern[i] == pattern[j]) {
                lps[i] = j + 1;
                i++;
                j++;
            } else {
                if (j != 0) {
                    j = lps[j-1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

     bool KMPsearch(string pat, string txt) {
        int N = txt.length();
        int M = pat.length();

        int lps[M];
        computeLPS(pat, lps);

        int i = 0; // Index for text
        int j = 0; // Index for pattern

        while (i < N) {
            if (pat[j] == txt[i]) {
                i++;
                j++;
            }

            if (j == M) {
                //result.push_back(i-j+1);
                //j = lps[j - 1];
                return true;
            } else if (i < N && pat[j] != txt[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return false;
    }

    vector<string> stringMatching(vector<string>& words) {
        int n = words.size();
        vector<string> result;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if (KMPsearch(words[i], words[j])) {
                        result.push_back(words[i]);
                        break;
                    }
                }
            }
        }
        return result;
    }
};
************************************************************************************/
