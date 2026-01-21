#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 16
#define RANGE 100

static int zero_Count = 0;
static int position = 0;

int read_file_line(const char* filename){
    FILE* file_ptr;
    char line_buffer[MAX_LINE_LENGTH];      // Buffer to hold each line read from file

    file_ptr = fopen(filename, "r");        // Open File in read mode

    // Check for successful opening of file
    if (file_ptr == NULL) {
        perror("ERROR opening file...\n");
        return -1;
    }

    printf("--- Reading file %s ---\n", filename);

    // Read the file line by line using fgets() -- which reads until it detects a newline character
    while (fgets(line_buffer, MAX_LINE_LENGTH, file_ptr) != NULL){
        char dir; int val;

        // Partse the direction and number
        if (sscanf(line_buffer, " %c%d", &dir, &val) != 2){
            fprintf(stderr, "Invalid line: %s\n", line_buffer);
            continue;
        }

        switch(dir){
            case 'R': position += val; break;
            case 'L': position -= val; break;
            default: fprintf(stderr, "Uknown direction: %c\n", dir);
            continue;
        }

        // Wrapper function
        position = (position % RANGE + RANGE) % RANGE;

        if (position == 0) {zero_Count++;}

    }

    // Check for potetnial reading errors 
    if (ferror(file_ptr)){
        perror("ERROR reading file...\n");
    }

    // Close the file when finished and tell user file is read
    fclose(file_ptr);

    printf("\n--- Finished reading file ---\n");

    return 0;
}

int main(){
    // Start position is set to 50
    position = 50;

    if(read_file_line("day1_input.txt") != 0){
        fprintf(stderr, "File reading operation failure.\n");
        return EXIT_FAILURE;
    }

    printf("\nSecurity Number: %d", zero_Count);
    
    // You can remove files using this function call
    //remove("day1_input.txt");
    return 0;
}