/*
    Day 1 Advent of Code Challenge
    Author: Pranay Srivastava
    Date: 1/20/2026
    Purpose:
        Using prior knowledge on C concepts, develop a program to read a list of commands
        and provide the amount of times a '0' passed over or landed on after rotations. A "dial"
        that has wrapping from 0-99 backwards and forwards is the conceptual object we are 
        attempting to unlock.

    Version: 1.2.9
*/

// --- Libraries/Definitions/Global Variables ---
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define MAX_LINE_LENGTH 16
#define RANGE 100

static long long zero_Count = 0;    // Swap to prevent overflow from ints
static int position = 0;

// -- Functions ---

/*
    count_hits_zero():
    -   Dial positions are 0-99, wrapping enabled, and can cross 0 multiple times
    -   Using parameters of direction, current position, and difference returns 
        number of times the dial points at 0 during this rotation.
*/
static long long count_hits_zero(int pos, char dir, int n) {
    /*
        Example Usage:
        position = 20 = first
        n = 350

        first hit at 350 - 20 = 330
        additional hits = 330/100 = 3

        total = 1 + 3 = 4
        return 4
    */

    // If dial moves 0 or less clicks, return a 0
    if (n <= 0) return 0;

    int first;
    /* 
       Determine how many steps it takes to hit 0 the first time starting at position
       Right rotations reach 0 after (100 - pos) steps, a full loop = 100 steps from pos == 0
       Left rotations reach 0 after pos steps, a full loop (100 steps) from pos == 0
    */

    // Right rotations
    if (dir == 'R') {
        first = (RANGE - pos) % RANGE;
        if (first == 0) first = RANGE;
    } 
    // Left rotations
    else {
        first = pos % RANGE;
        if (first == 0) first = RANGE;
    }

    // If the total movement is smaller than the steps needed to reach the first 0, zero is never hit
    if (n < first) return 0;
    // Otherwise: we hit 0 once and every additional hit is 100 steps for 0
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
        char dir; int val;

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