#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_HEIGHT 1024
#define MAX_WIDTH 1024
#define MAX_PIXELS_PER_LINE 25
#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )

int theImageArray[1024][1024];

FILE* read_pgm_file_info(int* height, int* width,int* maxPixel, char* pgmFname){
    static FILE* fp = 0L ;
    char pgmFormatFlag[3] =  { '\0' } ;
    char trash[80] = { '\0' } ;
    memset ( ( void * ) trash, '\0', 80 ) ;
    fp = fopen ( pgmFname, "r" ) ;
    if ( fp ){
        fscanf ( fp, "%2c\n", pgmFormatFlag ) ;
        if ( ! strcmp ( pgmFormatFlag, "P2" ) ){
            fgets (  trash, 70, fp ) ;
            fscanf ( fp, "%i", width ) ;
            fscanf ( fp, "%i", height ) ;
            fscanf ( fp, "%i", maxPixel ) ;
        }
    }
    return fp ;
}

void read_pgm_file_into_array(int imageArray[][MAX_WIDTH], int* height, int* width, int* maxPixel, char* pgmInFileName){
    int row = 0 ;
    int col = 0 ;
    FILE* fp = read_pgm_file_info ( height, width, maxPixel, pgmInFileName ) ;
    char trash = ' ';
    char yesThreshold = ' ';
    if ( fp ){
        printf ( "reading height=%d, width=%d\n maxPixel=%d\n", *height, *width, *maxPixel ) ;
        for ( row = 0 ; row < MIN( MAX_HEIGHT - 1, *height ) ; row ++ ){
            for ( col = 0 ; col < MIN( MAX_WIDTH -1, *width ) ; col ++ ){
                fscanf ( fp, "%i", &imageArray[row][col]);
            }
        }
        fclose ( fp ) ;
    }

    return ;
}
void write_pgm_file_from_array (char* pgmOutFileName, int imageArray[][MAX_WIDTH], char* commentLine, int height, int width, int maxPixel){
    int row = 0 ;
    int col = 0 ;
    FILE* fp = fopen ( pgmOutFileName, "w" ) ;
    if ( fp ){
        fprintf ( fp, "P2\n" ) ;
        fprintf ( fp, "%s\n", commentLine ) ;
        fprintf ( fp, "%u %u\n", width, height ) ;
        fprintf ( fp, "%u\n", maxPixel ) ;
        for ( row = 0 ; row < height ; row ++ ){
            for ( col = 0 ; col < width ; col ++ ){
                fprintf (fp, "%u", imageArray[row][col]) ;
                if ( MAX_PIXELS_PER_LINE > 1 ){
                    fprintf ( fp, " " ) ;
                }
                if ( ( col % MAX_PIXELS_PER_LINE ) == 0 ){
                    fprintf ( fp, "\n" ) ;
                }
            }
            if ( col % MAX_PIXELS_PER_LINE ){
                fprintf ( fp, "\n" ) ;
            }
        }
        fclose ( fp ) ;
    }
    return ;
}

void binary(int theImageArray[1024][1024]){
  for (int i = 0; i < MAX_HEIGHT; ++i){
    for (int j = 0; j < MAX_WIDTH; ++j){
        if (theImageArray[i][j] > 122)
            theImageArray[i][j]= 245;
        else
            theImageArray[i][j] = 0;
    }
  }
}

int* binary1d(int theImageArray [1024]){
    int binary [1024];
    for(int i=0; i< 1024;i++){
      if (theImageArray[i]>= 122)
         theImageArray[i] = 245;
     else
        theImageArray[i] = 0;
    }
    return binary;
}

int* flatten(int theImageArray [1024][1024]){
    int res [1024*1024];
    for (int i = 1; i < MAX_HEIGHT; ++i)
      for (int j = 1; j < MAX_WIDTH; ++j)
          res[i*j] = theImageArray[i][j];
    return res;
}

int** pack(int Array[1024*1024]){
    int packed [1024][1024];
    int counter=0;
    for(int i = 0; i<1024; i++){
      for (int j=0; j<024; j++){
        packed [i][j] = Array[counter];
        counter++;
      }
    }
    return packed;
}


int main(){
    int height  = 0 ;
    int width = 0 ;
    int maxPixel = 0 ;

    char* pgmInFileName = "in.pgm" ;
    char* pgmOutFileName = "out.pgm";

    read_pgm_file_into_array (theImageArray, &height, &width, &maxPixel, pgmInFileName );
    int* flattened;
    flattened = flatten(theImageArray);
    int* converted;
    converted = binary1d(flattened);
    int** packed;
    packed = pack(converted);

    write_pgm_file_from_array ( pgmOutFileName, packed, "# JR test file", height, width, maxPixel);


    return 0;
}
