    /*********************************************************************************************
     * 
     * Author: Carlos Almeyda
     * 
     * Purpose: Write a program for determining if a year is a leap year. In the Gregorian calendar
     * system you can check if it is a leap year if it is divisible by 4 but not by 100 
     * unless it is also divisible by 400. 
     * 
     * Date: June 2020
     * 
     * School: New York University Tandon School of Engineering
     * 
     *********************************************************************************************
     */

// The pound sign below is a "pre-processor" directive. Tells the compiler to do something before
// compliing the source code. Here, the program is calling a header file. stdio.h in the standard
// C library header and provides functionality for displaying output.
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int main (int argc, char *argv[0]) {

    // So, above there is an argc which = argument count. After that you have argv which = argument vector. 
    // Argument count is used to determine the number of command line arguments.
    // Argument vector holds the names of all command line arguments (including the name of your program).
    // Prior to defining the variable below, if you were to run the program without it, the program would simply
    // output "2" because there are only two arguments. By defining "yearEntered" to = atoi(argv[1], you POINT the input
    // (yearEntered) to the THIRD argument (argv[1]) and "atoi" converts a string to an integer. To prove that the input
    // from the command line is "argv[1]" you can throw a printf statement at the bottom of the program. 
    // For example: "printf("%d\n", yearEntered;".
    int yearEntered = atoi(argv[1]);

// The first if statement is attempting to perform a modulo operation. If the remainder equals zero
// then it will perform another if statement.
    if ( yearEntered % 4 == 0) { 
        // Here is another modulo operation. The double pipes indicates an OR. So, the input is applied to both operations. If the 
        // remainder is equal to zero for either operation, than it is a leap year. 
        if ( yearEntered % 100 != 0 || yearEntered % 400 == 0)
            printf("%d was a leap year\n", yearEntered);
        // If there is a remained, then it is not a leap year. 
        else
            printf("%d was not a leap year\n", yearEntered);
    }
    // If the number does not match any of the above, then it is not a leap year. 
    else {
        printf("%d was not a leap year\n", yearEntered); 
    }
    printf("%d\n", yearEntered);
    
return 0;
}

