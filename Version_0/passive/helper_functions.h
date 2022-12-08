
#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include <math.h>

/*	Function to calculate mean. */

float mean(float* arr, int N)
{
	float result = 0.0f;
	int i = 0;

	for( i = 0 ; i < N ; i++ ) result += arr[i];

	return( result / (float)N );
}

/*	Function to calculate standard deviation. */

float standard_deviation(float* arr, int N)
{
	float _mean;
	float result = 0.0f;

	int i;

	_mean = mean(arr,N);

	for( i = 0 ; i < N ; i++ )
	{
		result += (  ( arr[i] - _mean ) * ( arr[i] - _mean ) );
	}

	result /= (float)N;

	result = sqrt(result);

	return( result );
}

#endif /* HELPER_FUNCTIONS_H_ */
