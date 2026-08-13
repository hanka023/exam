
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

// 1. Klasický strlen
int	ft_strlen(char *s)
{
	int	i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

// 2. Strjoin, který ROVNOU uvolňuje starý buffer (šetří řádky kódu)
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i = 0;
	int		j = 0;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1); // DŮLEŽITÉ: automaticky uvolní starý buffer!
	return (str);
}

// 3. Hlavní get_next_line
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			i;
	int			j;
	ssize_t 	n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		// 1. Pokud je buffer prázdný, načteme ze souboru
		if (buffer[0] == '\0')
		{
			n = read(fd, buffer, BUFFER_SIZE);
			if (n <= 0)
			break;
		}
		// 2. Spojíme line + buffer
		line = ft_strjoin(line, buffer);
		if (!line)
			return (NULL);
		// 3. Najdeme '\n' v bufferu
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		if (buffer[i] == '\n')
		{
			// Ořízneme vytvořenou 'line' přesně za '\n'
			line[ft_strlen(line) - ft_strlen(buffer) + i + 1] = '\0';
			// Posuneme zbytek bufferu na začátek (úklid)
			j = 0;
			i++;
			while (buffer[i])
				buffer[j++] = buffer[i++];
			buffer[j] = '\0';
			return (line);
		}
		// Pokud v bufferu '\n' nebylo, vyprázdníme ho pro další read()
		buffer[0] = '\0';
	}
	return (line);
}




int main ()
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf ("%s", line);
		free (line);
	}
	close (fd);
	return (0);
}