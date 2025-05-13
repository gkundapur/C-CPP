#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool
valid_segment(char s[])
{
        int len = strlen(s);
        if (len == 0 || len > 3)
                return false;

        for (int i = 0; i < len; i++) {
                if (!isdigit(s[i]))
                        return false;
        }

        int num = 0;
        for (int i = 0; i < len; i++)
                num = num * 10 + (s[i] - '0');

        return (num >= 0 && num <= 255) && !(s[0] == '0' && len > 1);
}

bool
is_valid_ip4(char ip[])
{
    int len = strlen(ip);
    if (len == 0)
        return false;

    char segment[4];
    int segIdx = 0;
    int segCnt = 0;

    for (int i = 0; i <= len; i++) {
        if (ip[i] == '.' || ip[i] == '\0') {
            if (segIdx == 0)
                return false;

            segment[segIdx] = '\0';
            if (!valid_segment(segment))
                return false;
            segIdx = 0;
            segCnt++;
        } else if (isdigit(ip[i])) {
            if (segIdx >= 3)
                return false;
            segment[segIdx++] = ip[i];
        } else
            return false;
    }
    return segCnt == 4;
}

int
check_for_digits(char *ip_str)
{
    while (*ip_str) {
        if (*ip_str >= '0' && *ip_str <= '9')
            *ip_str++;
        else {
            printf("%c not a digit\n", *ip_str);
            return 0;
        }
    }
    return 1;
}

int
main(void)
{
    const char *test_ips[] = {
        "128.0.0.1",
        "255.255.255.255",
        "0.0.0.0",
        "256.100.50.25",
        "192.168.1",
        "192.168.1.1.1",
        "abc.def.ghi.jkl",
        "01.02.03.004",
        NULL
    };

    for (int i = 0; test_ips[i]; i++)
        printf("%s\t\t\t%s\n", test_ips[i], is_valid_ip4(test_ips[i]) ? "---> Valid" : "--->INVALID");

    printf("Tokenizing-------------------------------------\n");
    int seg = 0;
    char *ptr, ip[] = "127.0.0.1";
    ptr = strtok(ip, ".");
    while (ptr) {
        printf("token = %s\n", ptr);
        if (!check_for_digits(ptr)) {
            printf("Invalid ip\n");
            return 0;
        }

        int num = atoi(ptr);
        if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, ".");
            if (ptr != NULL)
                seg++;
        } else
            return 0;
    }

    printf("seg = %d\n", seg);
    if (seg != 3) {
        printf("invalid ip\n");
        return 0;
    }

    return 0;
}

