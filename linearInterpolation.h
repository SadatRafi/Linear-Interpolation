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
#define ERROR_NULL_POINTER -4

/*********************************************************************/

typedef struct 
{
	float slope;
	float intercept;
	float x1, y1;
	float x2, y2;
} LineSegment;  // Renaming to clarify that it represents a line segment between two points

/**********************************************************************************************
 * Function: Train_Interpolation
 * Purpose: Computes the linear interpolation coefficients (slope and intercept) for each segment 
 *          between consecutive (x, y) points.
 * Usage: int result = Train_Interpolation(x_values, y_values, numberOfSegments, targetCurve);
 * Parameters:
 *    - x_values: Array of x-values (independent variable).
 *    - y_values: Array of y-values (dependent variable).
 *    - numberOfSegments: Number of segments (should be one less than the number of data points).
 *    - targetCurve: Pointer to an array of LineSegment structs where computed segments are stored.
 **********************************************************************************************/
int Train_Interpolation(float* x_values, float* y_values, unsigned int numberOfSegments, LineSegment *targetCurve);


/**********************************************************************************************
 * Function: Return_Y_Value
 * Purpose: Returns the interpolated y-value for a given x-value using precomputed line segments.
 * Usage: float y_value = Return_Y_Value(xValue, referenceCurve, numberOfSegments);
 * Parameters:
 *    - xValue: The x-coordinate (input) for which the corresponding y-value is requested.
 *    - referenceCurve: Pointer to an array of precomputed line segments (from Train_Interpolation).
 *    - numberOfSegments: Number of segments in the referenceCurve.
 **********************************************************************************************/
float Return_Y_Value(float xValue, LineSegment *referenceCurve, unsigned int numberOfSegments);

