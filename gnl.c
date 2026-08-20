#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

int ft_strlen(char *str)
{
	int len = 0;

	while (str && str[len]) 
		++len;

	return(len);
}


char *ft_strjoin (char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *str;

	int len = ft_strlen(s1) + ft_strlen(s2);
;
	str = malloc (sizeof (char) * (len + 1));
	if (!str)
		return (NULL);
	
	while (s1 && s1[i])  
	{
		str[i]  = s1[i];
		++i;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		++j;
	}
	str[i + j] = '\0';
	free(s1); 
	return (str);
}



char *get_next_line(int fd)
{
	int i = 0;
	int j = 0;
	int len = 0;
	static char buffer[BUFFER_SIZE + 1];
	char *line = NULL;
	ssize_t n = 1;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0) 
		return (NULL);

	while (1)
	{
		i = 0;
		if (!buffer[0])
		{
			n = read(fd, buffer, BUFFER_SIZE);
			if (n < 0)
				return (NULL);
			if (n == 0)
				break;
			buffer[n] = '\0';
		}
		line = ft_strjoin (line, buffer);
		if (!line)
			return (NULL);
		while (buffer[i] && buffer[i] != '\n')
			++i;
		if (buffer[i] == '\n')
		{
			len = ft_strlen (line) - ft_strlen (buffer) + i + 1; 
			line[len] = '\0';
			i++;
			j = 0;
			while (buffer[i] && buffer[i] != '\0')
				buffer[j++] = buffer[i++];
			buffer[j] = '\0';	
		++len;
			return (line);
		}
		buffer[0] = '\0';
	}
	return (line); 
}

int main ()
{
	int fd = open ("text.txt", O_RDONLY);
	char *line; 

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (0);
	
	while ((line = get_next_line (fd)) != NULL)
	{
		printf ("%s", line);
		free (line);
	}
	close (fd);
	return (0);
}