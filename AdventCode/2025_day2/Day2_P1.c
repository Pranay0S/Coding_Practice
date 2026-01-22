/*
    Day 2 Advent of Code Challenge
    Author: Pranay Srivastava
    Date: 1/2022026
    Purpose:
        Input of various ranges separated by commas in a single line have to be read. The
        ranges have ID that are invalid if repeated numbers are detected. For example, 998-1012
        contains the invalid ID 1010. The objective is to print the sum of invalid IDs as
        an input to the system.

    Version: 1.0.0
*/

// --- Libraries/Definitions/Global Variables ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long sum;

// -- Functions --

/*
    verification_protocol():
    -   Input of number n & output of 1 for invalid ID or 0 for valid ID
    -   Allocating space to store the decimal digits of 9 (19 digits max)
*/
int verification_protocol(long long n){
    char s[32];
    sprintf(s, "%lld", n);  // Convert n to a string

    // Count digits before '\0' for length
    int len = strlen(s);

    // Reject the odd-length numbers such as 121
    if (len%2 != 0) { return 0; }

    // Compute the midpoint
    // Determine if the first half == second half
    int half = len / 2;

    if (strncmp(s, s+half, half) == 0) { return 1; }
    return 0;
}

/*
    read_file_parsed():
    -   Reads a file from ptr and stores whole line in buffer
    -   Splits the line at the commas, which then stores the start and end of the range in variables
    -   Calls function verification_protocol() to determine if a value from start to end is invalid.
    -   Stores and returns sum variable of all invalid IDs.
*/
int read_file_parsed(const char* filename){
    FILE* file_ptr;
    char buffer[4096];

    // Open file with checks for errors
    file_ptr = fopen(filename, "r");
    if (file_ptr == NULL){
        perror("ERROR opening file\n");
        return -1;
    }

    if (!fgets(buffer, sizeof(buffer), file_ptr)){
        fclose(file_ptr);
        return -1;
    }
    
    // Separate at comma
    char *token = strtok(buffer, ",");
    // Loop to store start and end of range and check each number
    while (token != NULL){
        long long start, end;

        sscanf(token, "%lld-%lld", &start, &end);
        
        for (long long id = start; id <= end; id++){
            if (verification_protocol(id)){
                sum += id;
            }
        }
        
        token = strtok(NULL, ",");
    }

    // Close ptr
    fclose(file_ptr);
    return 0;
}

// - Driver Function -
int main(){

    if(read_file_parsed("id_input.txt") != 0){
        fprintf(stderr, "File reading operation failure.\n");
        return EXIT_FAILURE;
    }

    printf("Invalid ID Sum: %lld", sum);

    return 0;
}