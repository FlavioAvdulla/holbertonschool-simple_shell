#include <stdio.h>
void print_E()
{
	int i, j;

	// for (i = 0; i < 7; i++)
	// {
	// 	if(i == 0 || i == 3 || i == 6)
	// 	{
	// 		for (j = 0; j < 6; j++)
	// 		{
	// 			printf(" *");
	// 		}
	// 	}
	// 	printf(" *");
	// 	printf("\n");
	// }

	// for(i = 0; i < 7; i++)
	// {
	// 	if(i == 0 || i == 6) //ROWS
	// 	{
	// 		for (j = 0; j < 6; j++) //COLUMNS
	// 		{
	// 			printf(" *");
	// 		}
	// 	}
	// 	printf(" *");
	// 	printf("\n");
	// }

	for(i = 0; i < 7; i++)
	{
		if(i == 1) //ROWS
		{
			for (j = 0; j < 1; j++) //COLUMNS
			{
				printf(" *");
			}
		}

		if (i == 2) { // ROWS
            for (int j = 0; j < 2; j++) // COLUMNS
			{
                if (j == 0 || j == 2)  // Skip printing when j == 1
				{
                    printf(" *");
                }
				else
				{
					printf(" ");
				}
            }

		if (i == 3) { // ROWS
            for (int j = 0; j < 2; j++) // COLUMNS
			{
                if (j == 0 || j == 2)  // Skip printing when j == 1
				{
                    printf(" *");
                }
				else
				{
					printf(" ");
				}
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