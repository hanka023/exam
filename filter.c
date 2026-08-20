#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>

#define BUFFER_SIZE 25

void filter(char *str, char *s)
{
	int i = 0;
	int j = 0;
	int len = 0;

	while (str[i] != '\0')
	{
		j = 0;
		len = 0;
		while (s[j] == str[i + j])
			++j;
		if (s[j] == '\0')
		{
			len = j;
			while (len > 0)
			{
				write (1, "*", 1);
				--len;
			}
			i = i + j;
		}
		else 
		{
			write (1, &str[i], 1);
			++i;
		}
	
	}
}

int main (int argc, char *argv[])
{
	int fd = 0;
	int i = 0;
	ssize_t n = 1;
	char line [100000];

	if (argc != 2 || !argv[1][0])
		return (0);

	char *s = argv[1];

	while ((n = read(fd, &line[i], BUFFER_SIZE)) > 0)
	{
		i = i + n;
	}
	if (n < 0)
	{ 
		perror ("Error");
		return (1);
	}
	line [i] = '\0';
	filter(line, s);
	return (0);
}