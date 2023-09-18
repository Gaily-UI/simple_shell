#include <stdio.h>
#include "shell.h"

/**
 * main - entry point
 * Return: num1, num2, num3
 */

int main(void)
{
	int num1, num2, num3, sum;

	printf("Enter three numbers: ");
	scanf("%d %d %d", &num1, &num2, &num3);
	sum = num1 + num2 + num3;

	printf("Sum: %d\n", sum);

	return (0);
}
