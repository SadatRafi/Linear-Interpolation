#include "linearInterpolation.h"

#define MAXIMUM_DATA_POINTS 20

#define ERROR_NUMBER_OF_DATA_POINTS_EXCEED_LIMIT -1
#define ERROR_SUCESSIVE_X_VALUES_SAME -2

int Train_Model(float* x_values, float* y_values, int dataPoints);


/*********************************************************************/

typedef struct 
{
	double slope;
	double intercept;
}InterpolationCoefficients;
static InterpolationCoefficients calculatedCoefficients[MAXIMUM_DATA_POINTS];

typedef struct
{
	float minimumValue;
	float maximumValue;
}Boundary;
Boundary xValueRange;


int Train_Model(float* x_values, float* y_values, int dataPoints)
{
	//First Find the minimum and maximum range of x_values
	xValueRange.minimumValue = x_values[0];
	xValueRange.maximumValue = x_values[0];	
	for(int tempVariable = 1; tempVariable < dataPoints; tempVariable++)
	{
		if(x_values[tempVariable] < xValueRange.minimumValue)
		{
			xValueRange.minimumValue = x_values[tempVariable];
		}
		else if(x_values[tempVariable] > xValueRange.minimumValue)
		{
			xValueRange.maximumValue = x_values[tempVariable];
		}
		else
		{
			return ERROR_SUCESSIVE_X_VALUES_SAME;
		}
	}
}