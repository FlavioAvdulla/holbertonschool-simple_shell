#include <stdio.h>
void print_E()
{
	int i, j;

	for (i = 0; i < 7; i++)
	{
		if(i == 0 || i == 3 || i == 6)
		{
			for (j = 0; j < 6; j++)
			{
				printf(" *");
			}
		}
		printf(" *");
		printf("\n");
	}


}

int main()
{
	print_E();
	return(0);
}