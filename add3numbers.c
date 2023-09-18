#include <stdio.h>
#include "shell.h"

/**
 * main - entry point
 * Return: num1, num2, num3
 */

int main(void)
{
double num1, num2, num3, sum;
/* This program adds three numbers from the user */

printf("Input three numbers: ");
scanf("%lf %lf %lf", &num1, &num2, &num3);
sum = add3num;
printf("Sum = %.2lf\n", sum);

return (0); }
