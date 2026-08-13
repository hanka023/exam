#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define MAX_SIZE 100000

int main(int argc, char *argv[])
{
    char    *str;
    char    *s;
    int     i = 0;
    int     j;
    int     len;
    int     line_len = 0;
    ssize_t n;

    if (argc != 2 || argv[1][0] == '\0')
        return (1);

    str = malloc(sizeof(char) * (MAX_SIZE + 1));
    if (!str)
    {
        printf("Error: Malloc failed\n");
        return (1);
    }
    s = argv[1];

    // Načítání s kontrolou nepřetečení MAX_SIZE
    while (line_len < MAX_SIZE && (n = read(0, &str[line_len], BUFFER_SIZE)) > 0)
    {
        line_len = line_len + n;
    }

    if (n < 0)
    {
        perror("Error: Read failed\n");
        free(str);
        return (1);
    }
    str[line_len] = '\0';

    /* * * * * * * L O G I K A * * * * * * */
    while (str[i] != '\0')
    {   
        j = 0;
        while (s[j] != '\0' && str[i + j] == s[j])
            ++j;
			
        if (s[j] == '\0') // Našli jsme celou shodu
        {
            len = j;
            i += j;
            while (len > 0)
            {
                write(1, "*", 1);
                --len;
            }
        }
        else // Není shoda, zapíšeme 1 znak
        {
            write(1, &str[i], 1);
            ++i;
        }
    }

    free(str);  
    return (0);
}