#include "test.h"

int ft_strlen(char *str)
{
    int i = 0;
    if(!str)
        return(0);
    while(str[i])
        i++;
    return (i);
}
char    *get_line(char *str)
{
    int i = 0;
    char *line;

    if(!str[0])
        return (NULL);
    while(str[i] && str[i] != '\n')
        i++;
    if(str[i] == '\n')
        line = malloc(sizeof(char) * i + 2);
    else
        line = malloc(sizeof(char) * i + 1);
    if(!line)
        return (NULL);
    i = 0;
    while(str[i] && str[i] != '\n')
    {
        line[i] = str[i];
        i++;
    }
    if(str[i] != '\n')
        line[i] = '\0';
    else
    {
        line[i] = '\n';
        line[i + 1] = '\0';
    }
    return (line);
}

char    *get_rest(char *str)
{
    int i = 0;
    int j = 0;
    char *rest;

    while(str[i] && str[i] != '\n')
        i++;
    if(!str[i])
    {
        free(str);
        return (NULL);
    }
    rest = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
    if(!rest)
        return (NULL);
    i++;
    while(str[i] != '\0')
    {
        rest[j] = str[i];
        j++;
        i++;
    }
    rest[j] = '\0';
    free(str);
    return (rest);
}
int ft_strchr(char *str, char c)
{
    int i = 0;

    if(!c || !str)
        return (0);
    while(str[i])
    {
        if(str[i] == (char)c)
            return (1);
        i++;
    }
    return (0);
}
char    *ft_strjoin(char *str, char *buff)
{
    char *dest;
    int i = 0;
    int j = 0;

    if(!str)
    {
        str = malloc(sizeof(char) * 1);
        if(!str)
            return (NULL);
        str[0] = '\0';
    }
    if(!str || !buff)
        return (NULL);
    dest = malloc((ft_strlen(str) + ft_strlen(buff)) + 1);
    if(!dest)
        return (NULL);
    while(str[i])
    {
        dest[i] = str[i];
        i++;
    }
    while(buff[j] != '\0')
    {
        dest[i + j] = buff[j];
        j++;
    }
    dest[i + j] = '\0';
    free(str);
    return (dest);
}

char    *get_all_lines(int fd, char *str)
{
    int byte = 1;
    char *buff;

    buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if(!buff)
        return (NULL);
    while(byte != 0)
    {
        byte = read(fd, buff, BUFFER_SIZE);
        if(byte == -1)
        {
            free(str);
            free(buff);
            return (NULL);
        }
        buff[byte] = '\0';
        str = ft_strjoin(str, buff);
        if(ft_strchr(str, '\n') == 1)
            break ;
    }
    free(buff);
    return (str);
}

char    *get_next_line(int fd)
{
    static char *str;
    char        *dest;

    if(fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
    str = get_all_lines(fd, str);
    if(!str)
        return (NULL);
    dest = get_line(str);
    str = get_rest(str);
    return (dest);
}

int main(void)
{
	char *str;
	int fd = open("text", O_RDONLY);
	str = get_next_line(fd);
	while(str)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
    return (0);
}