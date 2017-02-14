//----------------------------------------
// Copyright 2015 Corey Toler-Franklin, 
// University of Florida
// utility functions
// utilities.cpp
//----------------------------------------



#include "utilities.h"
#include <limits>


//------------------------------------
// conversions
//------------------------------------

// converts a unsigned char to a float
float UcharToFloat(unsigned char c) 
{
    return(c/255.0f);
}


// converts a float to unsigned char 
unsigned char floatToUchar (float f) 
{
    return((unsigned char)(f * 255));
}