#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

enum states { TEXT, 
                SAW_SLASH, 
                SAW_STAR, 
                SINGLE_COMMENT, 
                MULTI_COMMENT 
} state = TEXT;

int main(int argc, char **argv)
{
  
  FILE *fp;
  int c;
  unsigned int chars  = 0;
  unsigned int total  = 0;
  unsigned int multi  = 0;
  unsigned int single = 0;

  vector<string> args(argv, argv+argc);

  for(size_t i = 0; i < args.size(); ++i) {

    fp = fopen( argv[i], "r");

    while ( (c = fgetc( fp )) != EOF )
      {
    chars++;
    switch( state )
    {
      case TEXT :
        switch( c )
        {
          case '/'  : state = SAW_SLASH; break;
          case '\n' : total++; // fall-through
          default   : break;
        }
        break;

      case SAW_SLASH :
        switch( c )
        {
          case '/'  : state = SINGLE_COMMENT; break;
          case '*'  : state = MULTI_COMMENT; break;
          case '\n' : total++; // fall through
          default   : state = TEXT; break;
        }
        break;

      case SAW_STAR :
        switch( c )
        {
          case '/'  : state = TEXT; multi++; break;
          case '*'  : break;
          case '\n' : total++; multi++; // fall through
          default   : state = MULTI_COMMENT; break;
        }
        break;

      case SINGLE_COMMENT :
        switch( c )
        {
          case '\n' : state = TEXT; total++; single++; // fall through
          default   : break;
        }
        break;

      case MULTI_COMMENT :
        switch( c )
        {
          case '*'  : state = SAW_STAR; break;
          case '\n' : total++; multi++; // fall through
          default   : break;
        }
        break;

      default: // NOT REACHABLE
        break;
    }
  }

  fclose(fp);
  }

  

  printf( "File                 : %s\n", argv[1] );
  printf( "Total lines          : %8u\n", total );
  printf( "Single-comment lines : %8u\n", single );
  printf( "Multi-comment lines  : %8u\n", multi );
  return 0;
}
