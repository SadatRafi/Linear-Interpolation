#include "linearInterpolation.h"

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
    // Check if there are enough data points for interpolation
    if (dataPoints < 2)
    {
        return ERROR_INSUFFICIENT_DATA_POINTS;
    }

    for (unsigned int index = 0; index < (dataPoints - 1); index++)
    {
        // Check for successive identical x-values using tolerance
        if (fabsf(x_values[index] - x_values[index + 1]) < FLOAT_TOLERANCE)
        {
            return ERROR_SUCESSIVE_X_VALUES_SAME;
        }

        // Collect the start and end point of a line segment
        targetCurve[index].x1 = x_values[index];
        targetCurve[index].y1 = y_values[index];
        targetCurve[index].x2 = x_values[index + 1];
        targetCurve[index].y2 = y_values[index + 1];

        // Calculate the slope and intercept for the straight-line equation [y = mx + c]
        targetCurve[index].slope = (targetCurve[index].y2 - targetCurve[index].y1) / (targetCurve[index].x2 - targetCurve[index].x1);
        targetCurve[index].intercept = targetCurve[index].y1 - (targetCurve[index].slope * targetCurve[index].x1);
    }

    return INTERPOLATION_SUCESSFUL;
}

float Return_Y_Value(float xValue, LineSegment *referenceCurve, unsigned int numberOfSegments)
{
    // Loop through the line segments to find where xValue lies between x1 and x2
    for (unsigned int i = 0; i < numberOfSegments; i++)
    {
        // Check if xValue lies between x1 and x2 of the current segment
        if (xValue >= referenceCurve[i].x1 && xValue <= referenceCurve[i].x2)
        {
            // Calculate yValue using the equation y = mx + c
            return (referenceCurve[i].slope * xValue) + referenceCurve[i].intercept;
        }
    }

    // If the xValue is not within the range of any segment, return an error or a default value
    // For example, returning a special value like NaN (not a number) or a large error value.
    // Alternatively, you could handle this more gracefully depending on the application.
    return -9999.0f;  // Error value indicating xValue was out of range
}
