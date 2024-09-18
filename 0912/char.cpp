#include <stdio.h>

int main()
{
	char string[20] = "abcd";
	int i;

	printf("%d\n", sizeof(string));
	i = printf("%s\n", string);
	printf("%d\n", i);

	/*char c;

	scanf("%s", string);
	scanf("%c", &c);

	printf("%s\n", string);
	printf("!!%c!!\n", c);*/

	return 0;
}
