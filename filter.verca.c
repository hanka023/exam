#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

int ft_strlen(char *str)
{
	int len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		++str;
		++len;
	}
	return (len);
}
void ft_filter(char *line, char *str)
{
	int len;
	int i;
	int h;
	int l;

	len = ft_strlen(str);
	i = 0;
	h = 0;
	l = 0;
	
	while(line[i])
	{
		h = 0;
		while (str[h] && line[i + h] == str [h])
			h++;
		if (h == len)
		{
			l = 0;
			while (l < len)
			{
				write (1, "*", 1);
				l++;
			}
			i = i + h;
		}
		else
		{
			write (1, &line[i], 1);
			i++;
		}
	}
}

int main(int argc, char *argv[])
{
	char line[10000];
	int ret = 1;
	int i = 0;

	if (argc != 2 || !argv[1][0])
		return (1);
	while (ret > 0)
	{
		ret = read(0, &line[i], BUFFER_SIZE);
		if (ret < 0)
		{
			perror ("Error: ");
			return (1);
		}
		i = i + ret;
	}
	line [i] = '\0';
	ft_filter(line, argv[1]);
	return (0);
}