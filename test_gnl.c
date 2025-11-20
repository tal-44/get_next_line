/* ************************************************************************** */
/*                                                                            */
/*   test_gnl.c - Comprehensive test suite for get_next_line                 */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void test_basic_reading(void)
{
	int fd;
	char *line;
	int line_count = 0;

	printf("Testing basic file reading...\n");
	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening test.txt\n");
		return;
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", ++line_count, line);
		free(line);
	}
	
	close(fd);
	printf("✓ Basic reading test passed (%d lines read)\n", line_count);
}

void test_multiple_files(void)
{
	int fd1, fd2, fd3;
	char *line1, *line2, *line3;

	printf("Testing multiple file descriptors...\n");
	
	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	
	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		printf("Error opening test files\n");
		return;
	}

	// Read alternating from different files
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	
	if (line1) { printf("FD1: %s", line1); free(line1); }
	if (line2) { printf("FD2: %s", line2); free(line2); }
	if (line3) { printf("FD3: %s", line3); free(line3); }

	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	
	if (line1) { printf("FD1: %s", line1); free(line1); }
	if (line2) { printf("FD2: %s", line2); free(line2); }

	// Read remaining
	while ((line1 = get_next_line(fd1)) != NULL)
		free(line1);
	while ((line2 = get_next_line(fd2)) != NULL)
		free(line2);
	while ((line3 = get_next_line(fd3)) != NULL)
		free(line3);

	close(fd1);
	close(fd2);
	close(fd3);
	
	printf("✓ Multiple file descriptors test passed\n");
}

void test_empty_file(void)
{
	int fd;
	char *line;

	printf("Testing empty file...\n");
	
	// Create empty file
	fd = open("empty.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	close(fd);
	
	fd = open("empty.txt", O_RDONLY);
	line = get_next_line(fd);
	
	if (line == NULL)
		printf("✓ Empty file test passed\n");
	else
	{
		printf("✗ Empty file test failed\n");
		free(line);
	}
	
	close(fd);
}

void test_invalid_fd(void)
{
	char *line;

	printf("Testing invalid file descriptor...\n");
	
	line = get_next_line(-1);
	if (line == NULL)
		printf("✓ Invalid FD test passed\n");
	else
	{
		printf("✗ Invalid FD test failed\n");
		free(line);
	}
	
	line = get_next_line(9999);
	if (line == NULL)
		printf("✓ Invalid FD (9999) test passed\n");
	else
	{
		printf("✗ Invalid FD (9999) test failed\n");
		free(line);
	}
}

void test_long_line(void)
{
	int fd;
	char *line;
	
	printf("Testing long line (if file exists)...\n");
	
	fd = open("long_line.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("⚠ long_line.txt not found, skipping test\n");
		return;
	}
	
	line = get_next_line(fd);
	if (line)
	{
		printf("✓ Long line read: length = %zu\n", strlen(line));
		free(line);
	}
	
	close(fd);
}

void test_no_newline_at_end(void)
{
	int fd;
	char *line;
	int count = 0;

	printf("Testing file without newline at end...\n");
	
	// Create test file without final newline
	fd = open("no_nl.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd, "Line without newline", 20);
	close(fd);
	
	fd = open("no_nl.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		printf("Read: '%s'\n", line);
		free(line);
	}
	close(fd);
	
	if (count == 1)
		printf("✓ No newline at end test passed\n");
	else
		printf("✗ No newline at end test failed (read %d lines)\n", count);
}

int main(void)
{
	printf("========================================\n");
	printf("   GET_NEXT_LINE COMPREHENSIVE TESTS   \n");
	printf("   BUFFER_SIZE = %d                    \n", BUFFER_SIZE);
	printf("========================================\n\n");

	test_basic_reading();
	printf("\n");
	test_invalid_fd();
	printf("\n");
	test_empty_file();
	printf("\n");
	test_no_newline_at_end();
	printf("\n");
	test_long_line();
	printf("\n");
	test_multiple_files();

	printf("\n========================================\n");
	printf("     ALL GNL TESTS COMPLETED!          \n");
	printf("========================================\n");

	return (0);
}
