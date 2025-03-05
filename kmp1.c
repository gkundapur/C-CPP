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
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of pat in txt and returns an array of
// occurrences
int KMPSearch(const char* pat, const char* txt, int* count)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // Create lps[] that will hold the longest prefix suffix
    // values for pattern
    int* lps = (int*)malloc(M * sizeof(int));

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt
    int j = 0; // index for pat

	while (i < N && j < M) {
		if (txt[i] == pat[j]) {
			i++;
			j++;
		}

		// check for pattern has been found
		if (j == M) 
			return i - j; // return starting position of pat

		if (txt[i] != pat[j]) {
			if (j > 0) 
				j = lps[j - 1];
			else
				i++;
		}
	}

    free(lps);
    //return result;
	return -1;
}

// Driver code
int main()
{
    //const char txt[] = "geeksforgeeks";
    //const char pat[] = "geeks";
    const char txt[] = "qabcgabcabcdcga";
	//const char pat[] = "abcd";
	const char pat[] = "cga";
    int count;

    // Call KMPSearch and get the array of occurrences
    int result = KMPSearch(pat, txt, &count);
	printf("txt = %s, pat = %s\n", txt, pat);
	printf("\"%s\" found at index %d in \"%s\"\n", pat, result, txt);

	return 0;
}
