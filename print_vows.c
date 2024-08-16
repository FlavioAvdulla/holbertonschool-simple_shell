#include <stdio.h>

void print_vows(char str[])
{

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'u' || str[i] == 'o')
		{
			printf("The vows letters are: %c \n", str[i]);
		}
	}
}

int main()
{
	char str[] = {"qwertyuiopasdfghjklzxcvbnm"};
	print_vows(str);
	return(0);
}

