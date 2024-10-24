#include "linearInterpolation.h"

#define MINIMUM_DATA_POINTS_FOR_INTERPOLATION 2

/**********************************************************************************************
Function Name: Train_Interpolation
Author: Sadat Rafi
Date Of Last Modification: 20 Oct 2024
Description: 
This function takes two arrays of x and y values representing data points and the number of data points. 
It calculates the LineSegment (slope and intercept) of linear equations for each consecutive pair of 
points, representing the linear interpolation between them.

Parameters:
- float* x_values: Pointer to the array of x-values.
- float* y_values: Pointer to the array of y-values.
- unsigned int dataPoints: Number of data points in the x and y arrays.
- LineSegment* targetCurve: Pointer to an array of LineSegment structures to store the result.

Returns:
- INTERPOLATION_SUCESSFUL (1) if the model is trained successfully.
- ERROR_NUMBER_OF_DATA_POINTS_EXCEED_LIMIT (-1) if the number of data points exceeds the defined limit.
- ERROR_SUCESSIVE_X_VALUES_SAME (-2) if successive x-values are identical (within a tolerance), making the slope undefined.
- ERROR_INSUFFICIENT_DATA_POINTS (-3) if fewer than two data points are provided (interpolation not possible).

**********************************************************************************************/
int Train_Interpolation(float* x_values, float* y_values, unsigned int dataPoints, LineSegment *targetCurve)
{
	if (targetCurve == NULL || x_values == NULL || y_values == NULL)
	{
		return ERROR_NULL_POINTER;
	}
	// Check if there are enough data points for interpolation
    if (dataPoints < 2)
    {
        return ERROR_INSUFFICIENT_DATA_POINTS;
    }

    // Iterate through data points to calculate the interpolation for each segment
    for (unsigned int index = 0; index < (dataPoints - 1); index++)
    {
        // Check for successive identical x-values using tolerance
        if (fabsf(x_values[index] - x_values[index + 1]) < FLOAT_TOLERANCE)
        {
            return ERROR_SUCESSIVE_X_VALUES_SAME;
        }

        // Accessing and storing segment data in local variables (may help the compiler's analysis)
        float x1 = x_values[index];
        float y1 = y_values[index];
        float x2 = x_values[index + 1];
        float y2 = y_values[index + 1];

        // Collect the start and end point of the current line segment
        targetCurve[index].x1 = x1;
        targetCurve[index].y1 = y1;
        targetCurve[index].x2 = x2;
        targetCurve[index].y2 = y2;

        // Calculate the slope and intercept for the straight-line equation [y = mx + c]
        float slope = (y2 - y1) / (x2 - x1);
        float intercept = y1 - (slope * x1);

        // Store the results in the current line segment
        targetCurve[index].slope = slope;
        targetCurve[index].intercept = intercept;
    }

    return INTERPOLATION_SUCESSFUL;
}

/**********************************************************************************************
Function Name: Return_Y_Value
Author: Sadat Rafi
Date Of Last Modification: 23 Oct 2024
Description: 
This function takes an x-value (independent variable) and returns the corresponding y-value 
(dependent variable) by looking up the correct line segment from a set of precomputed linear 
interpolation segments. The interpolation segments are passed through the 'referenceCurve' 
array, which contains 'numberOfSegments' segments. The function checks if the given x-value 
falls within the range [x1, x2] of any of the segments for positive slopes, or between [x2, x1] 
for negative slopes. It then uses the corresponding segment's slope and intercept to compute the 
y-value using the equation:

    y = slope * x + intercept

The function handles both positive and negative slopes to ensure proper interpolation between 
segments in all cases.

Parameters:
- float xValue: The x-coordinate (input) for which the corresponding y-value (output) is requested.
- LineSegment *referenceCurve: Pointer to an array of precomputed line segments, each with 
                               a slope, intercept, and the x1, x2 bounds of the segment.
- unsigned int numberOfSegments: The number of segments in the referenceCurve array.

Returns:
- The corresponding y-value for the given xValue if it falls within the range of any segment.
- If the xValue is out of the range of all segments, the function returns NaN to indicate 
  that the result is not available.

Handling of Positive and Negative Slopes:
- For segments with positive slopes, the function checks if the xValue lies between x1 and x2.
- For segments with negative slopes, the function checks if the xValue lies between x2 and x1 
  (i.e., reversed bounds) to correctly account for the decreasing relationship between x and y.

**********************************************************************************************/

float Return_Y_Value(float xValue, LineSegment *referenceCurve, unsigned int numberOfSegments)
{
    // Loop through the line segments to find where xValue lies between x1 and x2
    for (unsigned int i = 0; i < numberOfSegments; i++)
    {
			if(referenceCurve[i].slope >= 0)
			{
        // Check if xValue lies between x1 and x2 of the current segment, with a small tolerance
        if (xValue >= (referenceCurve[i].x1 - FLOAT_TOLERANCE) && xValue <= (referenceCurve[i].x2 + FLOAT_TOLERANCE))
        {
            // Calculate yValue using the equation y = mx + c
            return (referenceCurve[i].slope * xValue) + referenceCurve[i].intercept;
        }
			}
			else if(referenceCurve[i].slope < 0)
			{
				// Check if xValue lies between x1 and x2 of the current segment, with a small tolerance
        if (xValue <= (referenceCurve[i].x1 - FLOAT_TOLERANCE) && xValue >= (referenceCurve[i].x2 + FLOAT_TOLERANCE))
        {
            // Calculate yValue using the equation y = mx + c
            return (referenceCurve[i].slope * xValue) + referenceCurve[i].intercept;
        }
			}
    }

    // If the xValue is not within the range of any segment, return NaN to indicate out of range
    return NAN;  // NaN (Not a Number) indicates xValue was out of range
}


