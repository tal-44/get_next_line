/* ************************************************************************** */
/*                                                                            */
/*   stress_test_gnl.c - Stress test for get_next_line memory leaks          */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	char *line;
	int count = 0;
	int i;

	printf("========================================\n");
	printf("   GET_NEXT_LINE STRESS TEST           \n");
	printf("   Reading file 1000 times              \n");
	printf("========================================\n\n");

	for (i = 0; i < 1000; i++)
	{
		fd = open("test.txt", O_RDONLY);
		if (fd < 0)
		{
			printf("Error opening file\n");
			return (1);
		}

		count = 0;
		while ((line = get_next_line(fd)) != NULL)
		{
			count++;
			free(line);
		}
		close(fd);

		if (i % 100 == 0)
			printf("Iteration %d completed (%d lines read)\n", i, count);
	}

	printf("\n========================================\n");
	printf("   STRESS TEST COMPLETED!               \n");
	printf("   Total iterations: 1000                \n");
	printf("========================================\n");

	return (0);
}
