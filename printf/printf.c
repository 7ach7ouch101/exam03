#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

int ft_putstr(char *str)
{
    int i = 0;
    if(!str)
        str = "(null)";
    while(str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (i);
}

int ft_printhex(unsigned int i, int base)
{
    char *arr = "0123456789abcdef";
    int len = 0;
    int n = i % base;

    if(i / base != 0)
        len += ft_printhex(i / base , base);
    write(1, &arr[n], 1);
    len++;
    return (len);
}

int ft_putnbr(int i)
{
    int len = 0;
    if(i == -2147483648)
    {
        write(1, "-2147483648", 11);
        return (11);
    }
    if(i < 0)
    {
        write(1 , "-", 1);
        i *= -1;
        len++;
    }
    len += ft_printhex(i, 10);
    return (len);
}

int   printf(char *str, ...)
{
    int len = 0;
    int i = 0;
    va_list args;
    va_start(args, str);
    while(str[i])
    {
        if(str[i] == '%')
        {
            i++;
            if(str[i] == 'd')
                len += ft_putnbr(va_arg(args, int));
            if(str[i] == 's')
                len += ft_putstr(va_arg(args, char));
            if(str[i] == 'x')
                len += ft_puthex(va_arg(args, unsigned int), 16);
        }
        else
        {
            write(1, &str[i], 1);
            len++;
        }
        i++;
    }
    va_end(args);
    return (len);
}

int main(void)
{
    printf("%d\n", INT_MIN);
}