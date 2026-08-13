#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFER_SIZE 42

int ft_strlen(char *str)
{
	int len = 0;

	if (!str)
		return (0);

	while (str [len])
	{
		++len;
	
	}

	return(len);
}


char *ft_strjoin (char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *str;
	int len1 = ft_strlen (s1);
	int len2 = ft_strlen (s2);
	int len = len1 + len2;
;
	if (!s1 && !s2)
		return (NULL);

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
	free(s1);  //   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return (str);
}



char *get_next_line(int fd)
{
	int i = 0;
	int j = 0;
	static char buffer [BUFFER_SIZE + 1];
	char *line = NULL;

	ssize_t n;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE < 0)
		return (0);

	while (1)
	{
	
		i = 0;
		j = 0;

		if (!buffre[0])
			if (read ())

	}
	return (line);
	

}


int main ()
{
	int fd = open ("text.txt", O_RDONLY);

	char *line; 

	if (fd < 0 || fd > 10240 || BUFFER_SIZE < 0)
		return (0);
	
	while ((line = get_next_line (fd)) != NULL)
	{
		printf ("%s", line);
		free (line);
	}
	close (fd);
	return (0);
}