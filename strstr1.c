#include <stdio.h>
#include <string.h>

/************************************************
pat:    a   a  b \0
        j      lastp

txt:    a     b      a    b     b    a    a    b    a    a       \0
        start        endmatch                            lastt

lastt = 9
lastp = 2
endmatch = lastp = 2

txt[2] != pat[2]
endmatch++ = 3
start++ = 1
txt:    a     b      a     b          b    a    a    b    a    a       \0
              start        endmatch                            lastt

txt[3] == pat[2]
  cmp txt[start...endmatch] with pat[0..lastp] ie "bab" with "aab"
  not matched, increment endmatch and start

endmatch = 4
start =  2
txt:    a     b      a        b       b               a    a    b    a    a       \0
                     start            endmatch                            lastt
txt[4] == pat[2]
compare txt[start...endmatch] = "abb" with pat[j..lastp]= "aab"
not matched, increment endmatch and start

endmatch = 5
start = 3
txt:    a     b      a        b       b        a    a    b    a    a       \0
                              start            endmatch            lastt
compare txt[start...endmatch] = "bba" with pat[j...lastp] = "aab"
not matched, increment endmatch and start

endmatch = 6
start = 4
txt:    a     b      a        b       b        a    a    b    a    a       \0
                                      start         endmatch       lastt
compare "baa" with "aab"
not matched, increment start and endmatch

endmatch = 7
start = 5
txt:    a     b      a        b       b        a    a    b         a    a       \0
                                               start     endmatch       lastt
compare "aab" with "aab" 
matched, return start
*/ 
int 
nfind(const char *txt, const char *pat)
{
	int i, j, start = 0;
	int lastt = strlen(txt) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	printf("lastt = %d, lastp = %d\n", lastt, lastp);
	for (i = 0; endmatch <= lastt; endmatch++, start++) {
		if (txt[endmatch] == pat[lastp])
			for (j = 0, i = start; j < lastp && txt[i] == pat[j]; i++, j++)
				;

		if (j == lastp)
			return start;
	}
	return -1;
}
	
int
main(void)
{
	const char *txt = "ababbaabaa";
	const char *pat = "aabc";

	printf("txt: %s\n", txt);
	printf("pat: %s\n", pat);
	int result = nfind(txt, pat);
	if (result > 0) 
		printf("sub string found at: %d\n", result);
	else
		printf("not found\n");

	return 0;
}

