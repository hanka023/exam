#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) /* xCh v0.5 */
{
 int l, i = 0, zbytek, nalezeno = 0, schovej = 0;
 char *buffer;
 if(argc == 2 && (zbytek = l = strlen(argv[1])) && (buffer = (char *)malloc(l)))
 {
  while(read(0,&buffer[i%l],1) == 1)
  {
   if(buffer[i%l] == argv[1][nalezeno])
   {
    if(++nalezeno == l)
    {
     schovej = nalezeno;
     nalezeno = 0;
    }
   }
   else if (buffer[i%l] == argv[1][0])
   {
    nalezeno = 1; /* reset pattern match after partial match */
   }
   else nalezeno = 0;

   if(++i >= l)
   {
    if(schovej-- > 0) write(1,"*",1);  
    else write(1,&buffer[(i-l)%l],1);
   }
  }
  if(i < zbytek) zbytek = i+1;

  while(--zbytek > 0)
  {
   if(schovej-- > 0) write(1,"*",1);  
   else write(1,&buffer[(i-zbytek)%l],1);  
  }
  free(buffer);
  return(0);
 }
}