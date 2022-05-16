#include <stdio.h>
#include <string.h>

unsigned int pidx;

void find_matching_close_brace( char *prog )
{
   int depth = 0;

   while ( 1 )
   {
      if ( prog[ pidx ] == '[' )
      {
         depth++;
      }
      if ( prog[ pidx ] == ']' )
      {
         depth--;
         if ( depth == 0 )
         {
            pidx++;
            return;
         }
      }
      pidx++;
   }
}

void find_matching_open_brace( char *prog )
{
   int depth = 0;

   while ( 1 )
   {
//printf("fmob : %c (%d) depth %d\n", prog[ pidx ], pidx, depth);
      if ( prog[ pidx ] == ']' )
      {
         depth++;
      }
      if ( prog[ pidx ] == '[' )
      {
         depth--;
         if ( depth == 0 )
         {
            return;
         }
      }
      pidx--;
   }

}

void interpret( char *prog )
{
   int running = 1;
   char array[1000] = {0};
   unsigned int tidx = 0;

   while( running )
   {
//printf("pidx = %d (%c), tidx = %d\n", pidx, prog[pidx], tidx);
      switch( prog[ pidx ] )
      {
         case '+':
            array[ tidx ]++;
            pidx++;
            break;
         case '-':
            array[ tidx ]--;
            pidx++;
            break;
         case '[':
            if ( array[ tidx ] != 0 )
            {
               pidx++;
            }
            else
            {
               find_matching_close_brace(prog);
            }
            break;
         case ']':
            find_matching_open_brace(prog);
            break;
         case '>':
            tidx++;
            pidx++;
            break;
         case '<':
            tidx--;
            pidx++;
            break;
         case '.':
            printf("%c", array[ tidx ]);
            pidx++;
            break;
         case ',':
            getchar();
         default:
            // Unknown symbol, skip it.
            pidx++;
      }
   }

   return;
}


void main( void )
{
   unsigned char prog[256];
   pidx = 0;
//   strcpy( prog, "++>+++++ [<+>-] ++++ ++++ [ < +++ +++ > - ] < ." );
//   strcpy( prog, "++++++++ [ >++++ [ >++ >+++ >+++ >+ <<<<- ] >+ >+ >- >>+ [<] <- ]" );
    strcpy( prog, "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.," );

   interpret( prog );

   return;
}

