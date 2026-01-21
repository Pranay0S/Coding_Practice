/*
    Day 1 Advent of Code Challenge
    Author: Pranay Srivastava
    Date: 1/20/2026
    Purpose:
        Using prior knowledge on C concepts, develop a program to read a list of commands
        and provide the amount of times a '0' is the final number after rotations. A "dial"
        that has wrapping from 0-99 backwards and forwards is the conceptual object we are 
        attempting to unlock.

    Version: 1.0.0
*/

// --- Libraries/Definitions/Global Variables ---
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 16
#define RANGE 100

// -- Functions ---

#include <ctype.h>
#include <limits.h>

static long long zero_Count = 0;
static int position = 0;

static long long count_hits_zero(int pos, char dir, int n) {
    if (n <= 0) return 0;

    int first;
    if (dir == 'R') {
        first = (RANGE - pos) % RANGE;
        if (first == 0) first = RANGE;
    } else { // 'L'
        first = pos % RANGE;
        if (first == 0) first = RANGE;
    }

    if (n < first) return 0;
    return 1LL + (long long)(n - first) / RANGE;
}

/*
    read_file_line(): 
    -   Produces a 0 resulting from a proper read file under name of input parameter.
    -   Reads the file line by line.
    -   Performs wrapping of position on "dial" and count for occurrences of zero.
*/
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
        char dir;
int val;

if (sscanf(line_buffer, " %c%d", &dir, &val) != 2) {
    fprintf(stderr, "Invalid line: %s\n", line_buffer);
    continue;
}
dir = (char)toupper((unsigned char)dir);
if (dir != 'L' && dir != 'R') {
    fprintf(stderr, "Unknown direction: %c\n", dir);
    continue;
}

zero_Count += count_hits_zero(position, dir, val);

// update final position after the whole rotation
int delta = (dir == 'R') ? val : -val;
int new_pos = position + delta;
position = (new_pos % RANGE + RANGE) % RANGE;

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

// - Driver Function -
int main(){
    // Start position is set to 50
    position = 50;

    // Call file reader and print if error occurs
    if(read_file_line("day1_input.txt") != 0){
        fprintf(stderr, "File reading operation failure.\n");
        return EXIT_FAILURE;
    }

    // Print Security Count for Answer
    printf("\nSecurity Number: %d", zero_Count);    // My case : 1100
    
    // You can remove files using this function call
    //remove("day1_input.txt");
    return 0;
}