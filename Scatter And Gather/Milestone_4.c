#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <assert.h>

#define MAX_HEIGHT 1025
#define MAX_WIDTH 1025
#define MAX_PIXELS_PER_LINE 25
#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )
#define ARR_LEN(x)  (sizeof(x) / sizeof((x)[0]))

int image_array[1025][1025];


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

void binary1(int* theImageArray, int dims){
    // printf("%d \n", theImageArray[200]);
  for(int i=0; i< dims; i++){
      if (theImageArray[i] >  122)
      {
        theImageArray[i] = 245;
      }

     else
     {
        theImageArray[i] = 0;
     }

    }
}


void scatter_gather() {

    int world_size, world_rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    int height, width, maxPixel;
    read_pgm_file_into_array (image_array, &height, &width, &maxPixel, "test_cases/grayscale.pgm");

    int image1d[width * height];
    int k = 0;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            image1d[k] = image_array[i][j];
            k++;
        }
    }

    int process_range = (width * height) / world_size;

    int* recv_data = (int *)malloc(sizeof(int) * process_range);
    MPI_Scatter(image1d, process_range, MPI_INT, recv_data, process_range, MPI_INT, 0, MPI_COMM_WORLD);


    binary1(recv_data, process_range);

    int *gathered_image1d = NULL;
    if(world_rank == 0) {
        gathered_image1d = (int *)malloc(sizeof(int) * width * height);
        assert(gathered_image1d != NULL);
    }

    MPI_Gather(recv_data, process_range, MPI_INT, gathered_image1d, process_range, MPI_INT, 0, MPI_COMM_WORLD);

    if(world_rank == 0) {
        int z = 0;
        for (int i = 0; i < height; i++){
           for (int j = 0; j < width; j++){
              image_array[i][j] =  gathered_image1d[z];
              z++;
          }
        }
        write_pgm_file_from_array ( "test_cases/Results/test_case1_output.pgm", image_array, "# JR test file", height, width, maxPixel);
    }
    MPI_Finalize();
}

int main(void){
    scatter_gather();
    return 0;
}
