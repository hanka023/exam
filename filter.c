
// filter:
// Allowed functions: read, strlen, malloc, calloc, realloc, free, printf, perror
// ------------------------------------------------------------------------------

// Write a programm that will take one and only one argument s.

// Your programm will then read from stdin and write all the content read in stdout
// except that every occurence of s must be replaced by '*'.

// For example :

// ./filter bonjour
// will behave the same way as:
// sed 's/bonjour/*******/g'

// in case of error during read or a malloc you must write "Error: " followed by
// the error message in stderr and return 1.

// $> echo 'abcdefgaaaabcdefabc' | ./filter abc | cat -e
// ***defgaaa***def***

// If the program is called whitout argument or with an empty argument or with
// multiples arguments it must return 1.


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10000


int main (int argc, char *argv[])
{
	char	*str;
	char	*s;
	int		i;
	int		j;
	int		len;
	
	ssize_t n;

	if (argc != 2 || argv [1][0] == '\0')
		return (1);
	

	str = malloc (sizeof (char) * (	BUFFER_SIZE + 1));
	if (!str)
	{
		perror("Error: ");
		return (1);
	}

	n = read(0, str, BUFFER_SIZE);
	if (!n)
	{
		perror("Error: ");
		free(str);
		return(1);
	}
	str[n] = '\0';

	s = argv[1];
	i = 0;
	j = 0;
	len = 0;

	/* * * * * * * L O G I K A * * * * * * */

	while (str[i] != '\0')
	{	
		j = 0;
		if (str[i] == s[j])
		{
			while (str[i + j] == s[j])
				++j;
			if (s[j] == '\0')
			{
				len = j;
				i = i + j;
				while (len > 0)
				{
					write (1, "*", 1);
					--len;
				}
			}
			else
			{
				write (1, &str[i], 1);
				++i;
			}
		}
		else
		{
			write (1, &str[i], 1);
			++i;
		}
	}
	free(str);	
	return (0);
}

