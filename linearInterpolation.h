#include <stdio.h>
#include <math.h>

/**********************************************************************************************
Note: IEEE 754 Single-Precision Floating-Point Format causes rounding error and hence comparing 
      two floating points is not recommended. That's why a small tolerance has been used in 
      floating point comparison.
**********************************************************************************************/
#define FLOAT_TOLERANCE 1e-6f  // Define a small tolerance for comparison

#define MAXIMUM_DATA_POINTS 20

#define INTERPOLATION_SUCESSFUL 1
#define ERROR_NUMBER_OF_DATA_POINTS_EXCEED_LIMIT -1
#define ERROR_SUCESSIVE_X_VALUES_SAME -2
#define ERROR_INSUFFICIENT_DATA_POINTS -3

/*********************************************************************/

typedef struct 
{
	float slope;
	float intercept;
	float x1, y1;
	float x2, y2;
} LineSegment;  // Renaming to clarify that it represents a line segment between two points

int Train_Interpolation(float* x_values, float* y_values, unsigned int dataPoints, LineSegment *targetCurve);
float Return_Y_Value(float xValue, LineSegment *referenceCurve, unsigned int numberOfSegments);
