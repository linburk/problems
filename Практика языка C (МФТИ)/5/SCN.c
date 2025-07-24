#include <stdio.h>

int main()
{
	int res = 0;
	char c;
	while (scanf("%c", &c) == 1)
		res += c;
	printf("%d\n", res);
}
