#include <stdio.h>
#include <string.h>

int isuniqchars(char s[])
{
    int n = strlen(s);
    int freqcount = 0;
    for (int i = 0; i < n; i++) {
        int val = s[i] - 'a';
        if ((freqcount & (1 << val)) > 0)
            return 0; // false
        freqcount |= (1 << val);
    }
    return 1; // true
}

int
main()
{
    char s1[] = "abc";
    printf("\"%s\" has unique chars : %s\n", s1, isuniqchars(s1) ? "true" : "false");
    char s2[] = "abca";
    printf("\"%s\" has unique chars : %s\n", s2, isuniqchars(s2) ? "true" : "false");

    return 0;
}
