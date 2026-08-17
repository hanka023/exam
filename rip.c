// Assignment name: rip
// Expected files: *.c *.h
// Allowed functions: printf, write
// --------------------------------------------------------------------------------
// Write a program that will take as argument a string containing only parenthesis.
// If parenthesis are unbalanced (for example "())") your program shall remove the
// minimum number of parenthesis for the expression to be balanced.
// By removing we mean replacing by spaces.
// You will print all the solutions (can be more than one).
// The order of the solutions is not important.
// For example this should work:
// (For readability reasons the '_' means space and the spaces are for readability only.)
// $> ./rip '( ( )' | cat -e
// _ ( ) $
// ( _ ) $
// $> ./rip '( ( ( ) ( ) ( ) ) ( ) )' | cat -e
// ( ( ( ) ( ) ( ) ) ( ) ) $
// $> ./rip '( ) ( ) ) ( )' | cat -e
// ( ) ( ) _ ( ) $
// ( ) ( _ ) ( ) $
// ( _ ( ) ) ( ) $
// $> ./rip '( ( ) ( ( ) (' | cat -e
// ( ( ) _ _ ) _ $
// ( _ ) ( _ ) _ $
// ( _ ) _ ( ) _ $
// _ ( ) ( _ ) _ $
// _ ( ) _ ( ) _ $



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int open = 0;
int closee = 0;
int i = 0;
int casee = 0;

void rmv(char *str)
{
	if (*str == '(' || *str == ')')
		*str = '_';
}

void solve(char *str, int i)
{
	

	if ((!str[i + 1]) && open == 0 && closee == 0)
	{
		printf ("%s\n", str);
		return;
	}
	else if(!str[i + 1])
		return;
	
	//solve(str, i + 1);
	*str = '_';
	solve(str, i + 1);
	++i;
}

int main(int argc, char *argv[])
{
	if (argc != 2 || !argv[1][0])
		return (-1);
	
	char *str;

	str = argv[1];

	solve(str, i);
	return 0;
}