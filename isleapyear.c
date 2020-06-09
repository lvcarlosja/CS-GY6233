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
// compliing the source code. Here, the program is calling a header file. stdio.h is the standard
// C library header and provides functionality for displaying output.
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int main (int argc, char *argv[0]) {

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
    
return 0;
}




    // The percent sign is modulo. Therefore, it will divide 1900 by 4. If there is a remainder, 
    // it will display the left over value. 
    // result = A << 4 ^ B >> 1;
    // results = c && d;
    // if (results = 0) {
    //     printf("False");
    //     return 0;
    // }

    // printf("%d<< 4 ^ %d >> 1 = %d\n", A, B, result);
    // printf("%d", results);



/******************************************************************************************************
** int main (int argc, char *argv[]) {
**  double width = 155.4;
**  double height = 32.5;
**  double perimeter = 0.0;
**  double area = 0.0;
**
**  perimeter = 2.0 * (height + width);
**  area = width * height;
**
**  printf("The perimeter of the rectangle is: %.f\n", perimeter);
**  printf("The area of the rectangle is: %.2f\n", area);
**
**
**  return 0;
**}
************************************************************************************
*/

// *********************************************************************************
// {
//     int var = 20;
//     int *ip;

//     ip = &var;

//     printf("Address of var variable: %x\n", &var  );

//     printf("Address stored in ip variable: %x\n", ip  );

//     printf("Value of *ip variable: %d\n", *ip   );

//     return 0;
// }

// ******************************************************************************************************

// {
//     int leapyear;
//     leapyear = % d / 4;

//     // Declare variables
//     int value1 = % d / 4;
//     int value2 = 100;
//     int sum;

//     // Takes text and converts it to integers or floats, etc.
//     scanf("%d", &i, str);

//     printf("This is a leap year\n", i);

//     // Prints an output to the screen
//     printf("Use me for debugging");

//     return 0;
// }

   // int numberOfArguments = argc;
    // char *argument1 = argv[0];
    // char *argument2 = argv[1];

    // printf("Numer of Arguments: %d\n", numberOfArguments);
    // printf("Argument 1 is the program name: %s\n", argument1);
    // printf("Argument 2 is the command line argument: %s\n", argument2);