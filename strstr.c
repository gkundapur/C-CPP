#include <stdio.h>

char *
my_strstr(const char *heystack, const char *needle)
{
	if (*needle == '\0')
		return (char *)heystack;

	while (*heystack) {
		const char *h = heystack;
		const char *n = needle;

		while (*h && *n && *h == *n) {
			h++;
			n++;
		}

		if (*n == '\0')
			return (char *)heystack;

		heystack++;
	}

	return NULL;
}

int
my_strstr1(char txt[], char pat[])
{
	int i, j, k;
	int N = strlen(txt);
	int M = strlen(pat);

	i = j = k = 0;
	while ( i < N && j << M) {
		if (txt[i] == pat[i]) {
			i++;
			j++
		} else {
			j = 0;
			k++;
			i = k;
		}
	}

	if (j == M)
		return true; // return i - j
	
	return 0; // not found
}


int
main(void)
{
	const char *heystack = "Hello world worla";
	const char *needle = "worla";

	char *result = my_strstr(heystack, needle);
	if (result) 
		printf("sub string found: %s\n", result);
	else
		printf("\"%s\" not found in \"%s\"\n", needle, heystack);

	return 0;
}

