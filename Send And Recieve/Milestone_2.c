#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX_HEIGHT 1025
#define MAX_WIDTH 1025
#define MAX_PIXELS_PER_LINE 25
#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) )

int image_array1[1025][1025];
int image_array2[1025][1025];
int image_array3[1025][1025];

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

void binary(int theImageArray[1025][1025]){
  for (int i = 0; i < MAX_HEIGHT; ++i){
    for (int j = 0; j < MAX_WIDTH; ++j){
        if (theImageArray[i][j] > 122)
            theImageArray[i][j]= 245;
        else
            theImageArray[i][j] = 0;
    }
  }
}



int main(){
    int height, width, maxPixel;
    int h, w, mP;

    char* pgmInFileName1 = "test_cases/test_case1.pgm" ;
    char* pgmInFileName2 = "test_cases/test_case2.pgm" ;
    char* pgmInFileName3 = "test_cases/test_case3.pgm" ;

    char* pgmOutFileName1 = "test_cases/Results/test_case1_output.pgm";
    char* pgmOutFileName2 = "test_cases/Results/test_case2_output.pgm";
    char* pgmOutFileName3 = "test_cases/Results/test_case3_output.pgm";


    int world_size, world_rank;

    MPI_Init(NULL, NULL);

    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    // Root Process Rank0
    if(world_rank == 0)
    {
        int img_specs[3];


        // Reading Image1 and sending to process rank1
        read_pgm_file_into_array (image_array1, &height, &width, &maxPixel, pgmInFileName1);

        img_specs[0] = height; img_specs[1] = width; img_specs[2] = maxPixel;

        MPI_Send(img_specs, 3, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&(image_array1[0][0]), 1025 * 1025, MPI_INT, 1, 10, MPI_COMM_WORLD);


        // Reading Image2 and sending to process rank2
        read_pgm_file_into_array (image_array2, &height, &width, &maxPixel, pgmInFileName2);

        img_specs[0] = height; img_specs[1] = width; img_specs[2] = maxPixel;

        MPI_Send(img_specs, 3, MPI_INT, 2, 1, MPI_COMM_WORLD);
        MPI_Send(&(image_array2[0][0]), 1025 * 1025, MPI_INT, 2, 11, MPI_COMM_WORLD);

         // Reading Image3 and sending to process rank3
        read_pgm_file_into_array (image_array3, &height, &width, &maxPixel, pgmInFileName3);

        img_specs[0] = height; img_specs[1] = width; img_specs[2] = maxPixel;

        MPI_Send(img_specs, 3, MPI_INT, 3, 2, MPI_COMM_WORLD);
        MPI_Send(&(image_array3[0][0]), 1025 * 1025, MPI_INT, 3, 12, MPI_COMM_WORLD);


    }

    // Process Rank1 recieve image1's and its data, execute and write as output file 1
    else if(world_rank == 1)
    {
        int img_specs[3];

        MPI_Recv(image_array1, 1025 * 1025, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(img_specs, 3, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


        binary(image_array1);
        write_pgm_file_from_array (pgmOutFileName1, image_array1, "# JR test file", img_specs[0], img_specs[1], img_specs[2]);
    }

    // Process Rank1 recieve image2's and its data, execute and write as output file 2
    else if(world_rank == 2)
    {
        int img_specs[3];

        MPI_Recv(image_array2, 1025 * 1025, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(img_specs, 3, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


        binary(image_array2);
        write_pgm_file_from_array (pgmOutFileName2, image_array2, "# JR test file", img_specs[0], img_specs[1], img_specs[2]);
    }

    // Process Rank3 recieve image3's and its data, execute and write as output file 3
    else if(world_rank == 3)
    {
        int img_specs[3];

        MPI_Recv(image_array3, 1025 * 1025, MPI_INT, 0, 12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(img_specs, 3, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


        binary(image_array3);
        write_pgm_file_from_array (pgmOutFileName3, image_array3, "# JR test file", img_specs[0], img_specs[1], img_specs[2]);
    }




    MPI_Finalize();

    return 0;
}
