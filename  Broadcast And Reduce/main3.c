#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <mpi.h>

#define MAX_HEIGHT 1025
#define MAX_WIDTH 1025
#define MAX_PIXELS_PER_LINE 25
#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )


int world_rank;
int world_size;


int image_array[1025][1025];
int oneDimension[1025*1025];
int packed[1025][1025];
int converted[1025*1025]={0};
int temp [1025*1025];

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
                fprintf (fp, "%ud", imageArray[row][col]) ;
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

void covert1d(void){
    int k=0;
    for (int i = 0; i < MAX_HEIGHT; ++i) {
        for (int j = 0; j < MAX_WIDTH; ++j) {
            oneDimension[k] = image_array[i][j];
            k++;
        }
    }
}

void pack(void){
    int k=0;
    for (int i = 0; i < MAX_HEIGHT; ++i) {
        for (int j = 0; j < MAX_WIDTH; ++j) {
            packed[i][j]= converted[k];
            k++;
        }
    }
}

int main(void) {
    int height, width, maxPixel;
    FILE *f = fopen("log.txt", "w");
    char *pgmInFileName1 = "In.pgm";
    char *pgmOutFileName1 = "Out.pgm";

    read_pgm_file_into_array(image_array, &height, &width, &maxPixel, pgmInFileName1);
    covert1d();


    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);

    if(world_rank==0) {
        MPI_Bcast(oneDimension, (1025 * 1025), MPI_INT, 0, MPI_COMM_WORLD);
        int length = MAX_HEIGHT * MAX_WIDTH;
        int div = length / world_size;
        int startIndex = 0;
        int endindex = div;

        for (int i = startIndex; i < endindex; i++) {
            if (oneDimension[i] > 122) {
                converted[i] = 245;
            } else {
                converted[i] = 0;
            }
        }
        for(int i = 1; i<world_size; i++){
            MPI_Recv(temp, 1025*1025, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < 1025*1025; ++j) {
                converted[j] =  temp[j] + converted [j];
            }
        }
        pack();
        write_pgm_file_from_array (pgmOutFileName1, packed, "# JR test file", height, width, maxPixel);
    }
    else{
        int recieved [1025*1025];
        MPI_Bcast(recieved,(1025*1025),MPI_INT,0,MPI_COMM_WORLD);
        int length = MAX_HEIGHT*MAX_WIDTH;
        int div = length/world_size;
        int startIndex = world_rank * div;
        int endindex = startIndex+div;
        for(int i = startIndex; i < endindex; i++){
            if(recieved[i] > 122) {
                temp[i] = 245;
            }
            else {
                temp[i] = 0;
            }
        }
        MPI_Send(temp, 1025*1025, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();


    return 0;
}