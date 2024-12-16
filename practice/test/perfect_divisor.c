#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

char ans[1000];

void isPerfect(unsigned long long num)
{
    if (num < 0)
    {
        printf("Invalid input.\n");
        return;
    }
    unsigned long long sum = 1;
    sprintf(ans, "1");
    for (unsigned long long i = 2; i *i <num; i++)
    {
        if (num % i == 0)
        {
            sum += i + num / i;
            sprintf(ans + strlen(ans), " + %llu", i);
            sprintf(ans + strlen(ans), " + %llu", num / i);
        }
    }
    if (sum == num && num != 1)
    {
        printf("%llu is a perfect number.\n", num);
        printf("Divisors of %llu : %s = %llu\n", num, ans, sum);
    }
    else
    {
        printf("%llu is NOT a perfect number.\n", num);
        if (num > 1)
            printf("Divisors of %llu : %s = %llu\n", num, ans, sum);
        else
            printf("Divisors of %llu : \n", num);
    }
}

void trim(char *str)
{
    int start = 0, end = strlen(str) - 1, idx = 0;

    while (str[start] == ' ')
    {
        start++;
    }

    while (end >= start && str[end] == ' ')
    {
        str[end] = '\0';
        end--;
    }

    while (str[start] != '\0')
    {
        str[idx++] = str[start++];
    }
    str[idx] = '\0';
}

int convert(char *str, unsigned long long *num)
{
    trim(str);
    if (strlen(str) == 0)
        return 0;
    int check = 0;
    char *st = strchr(str, '.');
    char *neg = strchr(str, '-');
    char *com = strchr(str, ',');

    if (isalpha(str[0]) && str[1] == '\0')
    {
        *num = (unsigned long long)str[0];
        return 1;
    }

    if ((isalpha(str[0]) && str[1] == '\0') || st != NULL || neg != NULL || com != NULL)
    {
        return 0;
    }
    if (isalpha(str[0]))
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            if (isalpha(str[i]))
            {
                return 0;
            }
        }
    }

    if (strncmp(str, "0x", 2) == 0 || strncmp(str, "0X", 2) == 0)
    {
        *num = strtoull(str, NULL, 16);
        check = 1;
    }
    else if (str[0] == '0' && str[1] != 'x' && str[1] != 'X')
    {
        *num = strtoull(str, NULL, 8);
        check = 1;
    }
    else
    {
        *num = strtoull(str, NULL, 10);
        check = 1;
    }

    // printf("num: %llu\n", *num);
    return check;
}

int main()
{
    unsigned long long i;
    char in[500];
    printf("Input: ");
    fgets(in, 500, stdin);
    in[strcspn(in, "\n")] = '\0';

    if (convert(in, &i))
        isPerfect(i);
    else
    {
        printf("Invalid input.\n");
    }

    // char *str = "1+2+4+8+16+32+64+128+256+512+1024+2048+4096+8192+16384+32768+65536+131072+262144+524288+1048576+2097152+4194304+8388608+16777216+33554432+67108864+134217728+268435456+536870912+1073741824";
    // printf("len: %d", strlen(str));
    return 0;
}
