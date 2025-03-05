#include <stdio.h>

int
main(void)
{
	int num = 5;

	for (int i = 1; i <= num; i <<= 1)
		num ^= i;

	printf("num %d\n", num);

	return 0;
}
