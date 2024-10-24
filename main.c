#include "stm32f4xx.h"                  // Device header
#include "linearInterpolation.h"

#define TOTAL_DATA_POINTS 21

LineSegment ntcTempVsResCurve[TOTAL_DATA_POINTS -1];
float test_variable=0.0f;

int main(void)
{
	float temperture[TOTAL_DATA_POINTS] = {-30.0f,-25.0f, -20.0f, -15.0f, -10.0f, -5.0f, 0.0f, 5.0f, 10.0f, 15.0f, 20.0f, 25.0f,
																				 30.0f, 35.0f, 40.0f, 45.0f, 50.0f, 55.0f, 60.0f, 65.0f, 70.0f};
	float resistance[TOTAL_DATA_POINTS] = {114.34f,88.381f, 68.915f, 53.65f, 42.889f, 34.196f, 27.445f, 22.165f, 18.01f, 14.72f,
																				 12.099f, 10.0f, 8.309f, 6.948f, 5.824f, 4.911f, 4.16f, 3.539f, 3.024f, 2.593f,
																				 2.233f};
 
	Train_Interpolation(&resistance[0], &temperture[0], TOTAL_DATA_POINTS, &ntcTempVsResCurve[0]);
	while(1)
	{
		test_variable = Return_Y_Value(53.0f,&ntcTempVsResCurve[0],(TOTAL_DATA_POINTS -1)); 
	}
	
}
