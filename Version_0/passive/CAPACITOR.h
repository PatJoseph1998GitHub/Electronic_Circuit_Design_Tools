
#ifndef PASSIVE_CAPACITOR_H_
#define PASSIVE_CAPACITOR_H_

#include <math.h>

#include "EIA.h"
#include "helper_functions.h"

#define CAPACITOR_MAX_POWER		-2
#define CAPACITOR_MIN_POWER		-12
#define CAPACITOR_POWER_RANGE	10

float CAPACITOR_E3[ 3 * CAPACITOR_POWER_RANGE ];
float CAPACITOR_E6[ 6 * CAPACITOR_POWER_RANGE ];
float CAPACITOR_E12[ 12 * CAPACITOR_POWER_RANGE ];
float CAPACITOR_E24[ 24 * CAPACITOR_POWER_RANGE ];
float CAPACITOR_E48[ 48 * CAPACITOR_POWER_RANGE ];
float CAPACITOR_E96[ 96 * CAPACITOR_POWER_RANGE ];

/*********		Function declarations.		****************/

void CAPACITOR_init();

float CAPACITOR_EC2S(float C1, float C2);
float CAPACITOR_EC2P(float C1, float C2);
float CAPACITOR_EC3S(float C1, float C2, float C3);
float CAPACITOR_EC3P(float C1, float C2, float C3);
float CAPACITOR_ECnS(float* C, int N);
float CAPACITOR_ECnP(float* C, int N);


/*********		Function definitions.		****************/

/*
 *
 * CAPACITOR_init()
 *
 * Description:
 *
 * Initializes standard set of resistors.
 *
 */

void CAPACITOR_init()
{
	int i,j;

	for( i = 0 ; i < CAPACITOR_POWER_RANGE ; i++ )
	{
		for( j = 0 ; j < 3 ; j++ )
		{
			CAPACITOR_E3[ 3*i + j ] = EIA_STANDARD_E3_SET[j] * pow( 10.0f, (float)( CAPACITOR_MIN_POWER + i ) );
		}

		for( j = 0 ; j < 6 ; j++ )
		{
			CAPACITOR_E6[ 6*i + j ] = EIA_STANDARD_E6_SET[j] * pow( 10.0f, (float)( CAPACITOR_MIN_POWER + i ) );
		}

		for( j = 0 ; j < 12 ; j++ )
		{
			CAPACITOR_E12[ 12*i + j ] = EIA_STANDARD_E12_SET[j] * pow( 10.0f, (float)( CAPACITOR_MIN_POWER + i ) );
		}

		for( j = 0 ; j < 24 ; j++ )
		{
			CAPACITOR_E24[ 24*i + j ] = EIA_STANDARD_E24_SET[j] * pow( 10.0f, (float)( CAPACITOR_MIN_POWER + i ) );
		}

		for( j = 0 ; j < 48 ; j++ )
		{
			CAPACITOR_E48[ 48*i + j ] = EIA_STANDARD_E48_SET[j] * pow( 10.0f, (float)( CAPACITOR_MIN_POWER + i ) );
		}

		for( j = 0 ; j < 96 ; j++ )
		{
			CAPACITOR_E96[ 96*i + j ] = EIA_STANDARD_E96_SET[j] * pow( 10.0f, (float)( CAPACITOR_MIN_POWER + i ) );
		}
	}
}

/*
 * 	CAPACITOR_EC2S(C1, C2)
 *
 *  Description:
 *
 *  This function calculates the equivalent series capacitance of C1 and C2.
 *
 *  @parameter	C1, C2			:	Capacitance of capacitors connected in series.
 *
 */

float CAPACITOR_EC2S(float C1, float C2)
{
	float result;

	result = ( 1.0f / C1 ) + ( 1.0f / C2 );
	result = 1.0f / result;

	return( result );
}


/*
 * 	CAPACITOR_EC2P(C1, C2)
 *
 *  Description:
 *
 *  This function calculates the equivalent parallel capacitance of C1 and C2.
 *
 *  @parameter	C1, C2			:	Capacitance of capacitors connected in parallel.
 *
 */

float CAPACITOR_EC2P(float C1, float C2)
{
	return( C1 + C2 );
}


/*
 * 	CAPACITOR_EC3S(C1, C2, C3)
 *
 *  Description:
 *
 *  This function calculates the equivalent series capacitance of C1, C2 and C3.
 *
 *  @parameter	C1, C2, C3			:	Capacitance of capacitors connected in series.
 *
 */

float CAPACITOR_EC3S(float C1, float C2, float C3)
{
	float result;

	result = ( 1.0f / C1 ) + ( 1.0f / C2 ) + ( 1.0f / C3 );
	result = 1.0f / result;

	return( result );
}


/*
 * 	CAPACITOR_EC3P(C1, C2, C3)
 *
 *  Description:
 *
 *  This function calculates the equivalent parallel capacitance of C1, C2 and C3.
 *
 *  @parameter	C1, C2, C3			:	Capacitance of capacitors connected in parallel.
 *
 */

float CAPACITOR_EC3P(float C1, float C2, float C3)
{
	return( C1 + C2 + C3 );
}


/*
 * 	CAPACITOR_ECnS( C[], N)
 *
 * 	Description:
 *
 * 	This function calculates the equivalent of a set of capacitors C[] connected in series.
 *
 * 	@parameter	C[]				:	Array containing capacitor values.
 * 	@parameter	N				:	Number of capacitors.
 *
 */

float CAPACITOR_ECnS(float* C, int N)
{
	float result = 0.0f;
	int i;

	for( i = 0 ; i < N ; i++ )
	{
		result += ( 1.0f / C[i] );
	}

	result = 1.0f / result;

	return(result);
}

/*
 * 	CAPACITOR_ECnP( C[], N)
 *
 * 	Description:
 *
 * 	This function calculates the equivalent of a set of capacitors C[] connected in parallel.
 *
 * 	@parameter	C[]				:	Array containing capacitor values.
 * 	@parameter	N				:	Number of capacitors.
 *
 */

float CAPACITOR_ECnP(float* C, int N)
{
	float result = 0.0f;
	int i;

	for( i = 0 ; i < N ; i++ )
	{
		result += C[i];
	}

	return(result);
}

/*
 * 	CAPACITOR_1C( C, CAPACITOR_EIA_standard )
 *
 * 	Description:
 *
 *	Selects a standard capacitor value from the standard capacitor set.
 *
 *	@parameter	C							:	Capacitor value to be selected.
*	@parameter	CAPACITOR_EIA_standard		:	EIA standard from which capacitor is to be selected.
 *
 */

float CAPACITOR_1C( float C, EIA_standard CAPACITOR_EIA_standard )
{
	float error;
	float error_min;
	float C_optimal;
	float* C_set;

	int i;
	int limit;

	error_min = pow(1.0f, (float)CAPACITOR_MAX_POWER + 1.0f);
	limit = CAPACITOR_POWER_RANGE*CAPACITOR_EIA_standard;

	switch(CAPACITOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; break;
	}

	for( i = 0 ; i < limit ; i++ )
	{
		error = C_set[i] - C;

		if( error < 0.0f ) error = -error;

		if( error < error_min )
		{
			error_min = error;
			C_optimal = C_set[i];
		}
	}

	return(C_optimal);
}



/*****
 *
 * CAPACITOR_2CS(C,CAPACITOR_EIA_standard, C1, C2)
 *
 * DESCRIPTION:
 *
 * Returns two values of capacitors from selected capacitor when connected in series,
 * given equivalent capacitance closest to target value.
 *
 * @parameter	C:							Target capacitor value.
 * @parameter	CAPACITOR_EIA_standard:		capacitor set from which value should be selected.
 * @parameter	C1:							Pointer to capacitor 1.
 * @parameter	C2:							Pointer to capacitor 2.
 *
 *****/

void CAPACITOR_2CS(float C, EIA_standard CAPACITOR_EIA_standard, float* C1, float* C2 )
{
	float error;
	float error_min;
	float* C_set;
	float C1_optimal;
	float C2_optimal;
	float C_series;

	int i,j;
	int limit;

	limit = CAPACITOR_POWER_RANGE*CAPACITOR_EIA_standard;

	error_min = pow( 10.0f, (float)( CAPACITOR_POWER_RANGE + 1 ) );

	switch(CAPACITOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; 	break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			C_series = CAPACITOR_EC2S( C_set[i], C_set[j] );
			error = C_series - C;

			if( error < 0.0f )
			{
				error = -error;
			}

			if( error < error_min )
			{
				error_min = error;
				C1_optimal = C_set[i];
				C2_optimal = C_set[j];
			}
		}
	}

	*C1 = C1_optimal;
	*C2 = C2_optimal;
}

/*****
 *
 * CAPACITOR_2CP(C,CAPACITOR_EIA_standard, C1, C2)
 *
 * DESCRIPTION:
 *
 * Returns two values of capacitors from selected capacitor when connected in parallel,
 * given equivalent capacitance closest to target value.
 *
 * @parameter	C:							Target capacitor value.
 * @parameter	CAPACITOR_EIA_standard:		capacitor set from which value should be selected.
 * @parameter	C1:							Pointer to capacitor 1.
 * @parameter	C2:							Pointer to capacitor 2.
 *
 *****/

void CAPACITOR_2CP(float C, EIA_standard CAPACITOR_EIA_standard, float* C1, float* C2 )
{
	float error;
	float error_min;
	float* C_set;
	float C1_optimal;
	float C2_optimal;
	float C_parallel;

	int i,j;
	int limit;

	limit = CAPACITOR_POWER_RANGE*CAPACITOR_EIA_standard;

	error_min = pow( 10.0f, (float)( CAPACITOR_POWER_RANGE + 1 ) );

	switch(CAPACITOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; 	break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			C_parallel = CAPACITOR_EC2P( C_set[i], C_set[j] );
			error = C_parallel - C;

			if( error < 0.0f )
			{
				error = -error;
			}

			if( error < error_min )
			{
				error_min = error;
				C1_optimal = C_set[i];
				C2_optimal = C_set[j];
			}
		}
	}

	*C1 = C1_optimal;
	*C2 = C2_optimal;
}


/*****
 *
 * CAPACITOR_3CS(C,CAPACITOR_EIA_standard, C1, C2, C3)
 *
 * DESCRIPTION:
 *
 * Returns three values of capacitors from selected resistor when connected in series,
 * given equivalent capacitor closest to target value.
 *
 * @parameter	C:							Target capacitor value.
 * @parameter	CAPACITOR_EIA_standard:		capacitor set from which value should be selected.
 * @parameter	C1:							Pointer to capacitor 1.
 * @parameter	C2:							Pointer to capacitor 2.
 * @parameter 	C3:							Pointer to capacitor 3.
 *
 *****/

void CAPACITOR_3CS(float C, EIA_standard CAPACITOR_EIA_standard, float* C1, float* C2, float* C3)
{
	float error;
	float error_min;
	float* C_set;
	float C1_optimal;
	float C2_optimal;
	float C3_optimal;
	float C_series;

	int i,j,k;
	int limit;

	limit = CAPACITOR_POWER_RANGE*CAPACITOR_EIA_standard;

	error_min = pow( 10.0f, (float)( CAPACITOR_POWER_RANGE + 1 ) );

	switch(CAPACITOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; 	break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			for( k = 0 ; k < limit ; k ++ )
			{
				C_series = CAPACITOR_EC3S( C_set[i], C_set[j], C_set[k] );
				error = C_series - C;

				if( error < 0.0f )
				{
					error = -error;
				}

				if( error < error_min )
				{
					error_min = error;
					C1_optimal = C_set[i];
					C2_optimal = C_set[j];
					C3_optimal = C_set[k];
				}
			}
		}
	}

	*C1 = C1_optimal;
	*C2 = C2_optimal;
	*C3 = C3_optimal;
}


/*****
 *
 * CAPACITOR_3CP(C,CAPACITOR_EIA_standard, C1, C2, C3)
 *
 * DESCRIPTION:
 *
 * Returns two values of resistors from selected resistor when connected in parallel,
 * given equivalent resistance closest to target value.
 *
 * @parameter	R:							Target resistor value.
 * @parameter	CAPACITOR_EIA_standard:		resistor set from which value should be selected.
 * @parameter	C1:							Pointer to capacitor 1.
 * @parameter	C2:							Pointer to capacitor 2.
 * @parameter	C3:							Pointer to capacitor 3.
 *
 *****/

void CAPACITOR_3CP(float C, EIA_standard CAPACITOR_EIA_standard, float* C1, float* C2, float* C3)
{
	float error;
	float error_min;
	float* C_set;
	float C1_optimal;
	float C2_optimal;
	float C3_optimal;
	float C_parallel;

	int i,j,k;
	int limit;

	limit = CAPACITOR_POWER_RANGE*CAPACITOR_EIA_standard;

	error_min = pow( 10.0f, (float)( CAPACITOR_POWER_RANGE + 1 ) );

	switch(CAPACITOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; 	break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			for( k = 0 ; k < limit ; k++ )
			{
				C_parallel = CAPACITOR_EC3P( C_set[i], C_set[j], C_set[k] );
				error = C_parallel - C;

				if( error < 0.0f )
				{
					error = -error;
				}

				if( error < error_min )
				{
					error_min = error;
					C1_optimal = C_set[i];
					C2_optimal = C_set[j];
					C3_optimal = C_set[k];
				}
			}
		}
	}

	*C1 = C1_optimal;
	*C2 = C2_optimal;
	*C3 = C3_optimal;
}

/**
 *
 * CAPACITOR_1C_SD(R,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the capacitor for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter C						:	Capacitor value.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float CAPACITOR_1C_SD(float C, float T)
{
	float C_buffer[2];
	float result;

	C_buffer[0] = C * ( 1 + 0.01f * T );
	C_buffer[1] = C * ( 1 - 0.01f * T );

	result = standard_deviation( C_buffer, 2 ) / C;

	return( 100.0f * result );
}


/**
 *
 * CAPACITOR_2CS_SD(C1,C2,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the capacitance for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter C1, C2				:	Capacitor values.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float CAPACITOR_2CS_SD(float C1, float C2, float T)
{
	float C_buffer[4];
	float result;
	float C;
	float t;

	t = 0.01f * T;
	C = CAPACITOR_EC2S(C1,C2);

	C_buffer[0] = CAPACITOR_EC2S( C1 * ( 1 + t ), C2 * ( 1 + t ) );
	C_buffer[1] = CAPACITOR_EC2S( C1 * ( 1 + t ), C2 * ( 1 - t ) );
	C_buffer[2] = CAPACITOR_EC2S( C1 * ( 1 - t ), C2 * ( 1 + t ) );
	C_buffer[3] = CAPACITOR_EC2S( C1 * ( 1 - t ), C2 * ( 1 - t ) );

	result = standard_deviation( C_buffer, 4 ) / C;

	return( 100.0f * result );
}


/**
 *
 * CAPACITOR_2CP_SD(C1,C2,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the capacitance for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter C1, C2				:	Capacitor values.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float CAPACITOR_2CP_SD(float C1, float C2, float T)
{
	float C_buffer[4];
	float result;
	float C;
	float t;

	t = 0.01f * T;
	C = CAPACITOR_EC2P(C1,C2);

	C_buffer[0] = CAPACITOR_EC2P( C1 * ( 1 + t ), C2 * ( 1 + t ) );
	C_buffer[1] = CAPACITOR_EC2P( C1 * ( 1 + t ), C2 * ( 1 - t ) );
	C_buffer[2] = CAPACITOR_EC2P( C1 * ( 1 - t ), C2 * ( 1 + t ) );
	C_buffer[3] = CAPACITOR_EC2P( C1 * ( 1 - t ), C2 * ( 1 - t ) );

	result = standard_deviation( C_buffer, 4 ) / C;

	return( 100.0f * result );
}

/**
 *
 * CAPACITOR_3CS_SD(C1,C2,C3,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the capacitance for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter C1, C2, C3			:	Capacitor values.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float CAPACITOR_3CS_SD(float C1, float C2, float C3, float T)
{
	float C_buffer[8];
	float result;
	float C;
	float t;

	t = 0.01f * T;
	C = CAPACITOR_EC3S(C1,C2,C3);

	C_buffer[0] = CAPACITOR_EC3S( C1 * ( 1 + t ), C2 * ( 1 + t ), C3 * ( 1 + t ) );
	C_buffer[1] = CAPACITOR_EC3S( C1 * ( 1 + t ), C2 * ( 1 + t ), C3 * ( 1 - t ) );
	C_buffer[2] = CAPACITOR_EC3S( C1 * ( 1 + t ), C2 * ( 1 - t ), C3 * ( 1 + t ) );
	C_buffer[3] = CAPACITOR_EC3S( C1 * ( 1 + t ), C2 * ( 1 - t ), C3 * ( 1 - t ) );
	C_buffer[4] = CAPACITOR_EC3S( C1 * ( 1 - t ), C2 * ( 1 + t ), C3 * ( 1 + t ) );
	C_buffer[5] = CAPACITOR_EC3S( C1 * ( 1 - t ), C2 * ( 1 + t ), C3 * ( 1 - t ) );
	C_buffer[6] = CAPACITOR_EC3S( C1 * ( 1 - t ), C2 * ( 1 - t ), C3 * ( 1 + t ) );
	C_buffer[7] = CAPACITOR_EC3S( C1 * ( 1 - t ), C2 * ( 1 - t ), C3 * ( 1 - t ) );

	result = standard_deviation( C_buffer, 8 ) / C;

	return( 100.0f * result );
}


/**
 *
 * CAPACITOR_3CP_SD(C1,C2,C3,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the capacitances for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter C1, C2, C3			:	Capacitor values.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float CAPACITOR_3CP_SD(float C1, float C2, float C3, float T)
{
	float C_buffer[8];
	float result;
	float C;
	float t;

	t = 0.01f * T;
	C = CAPACITOR_EC3P(C1,C2,C3);

	C_buffer[0] = CAPACITOR_EC3P( C1 * ( 1 + t ), C2 * ( 1 + t ), C3 * ( 1 + t ) );
	C_buffer[1] = CAPACITOR_EC3P( C1 * ( 1 + t ), C2 * ( 1 + t ), C3 * ( 1 - t ) );
	C_buffer[2] = CAPACITOR_EC3P( C1 * ( 1 + t ), C2 * ( 1 - t ), C3 * ( 1 + t ) );
	C_buffer[3] = CAPACITOR_EC3P( C1 * ( 1 + t ), C2 * ( 1 - t ), C3 * ( 1 - t ) );
	C_buffer[4] = CAPACITOR_EC3P( C1 * ( 1 - t ), C2 * ( 1 + t ), C3 * ( 1 + t ) );
	C_buffer[5] = CAPACITOR_EC3P( C1 * ( 1 - t ), C2 * ( 1 + t ), C3 * ( 1 - t ) );
	C_buffer[6] = CAPACITOR_EC3P( C1 * ( 1 - t ), C2 * ( 1 - t ), C3 * ( 1 + t ) );
	C_buffer[7] = CAPACITOR_EC3P( C1 * ( 1 - t ), C2 * ( 1 - t ), C3 * ( 1 - t ) );

	result = standard_deviation( C_buffer, 8 ) / C;

	return( 100.0f * result );
}


#endif /* PASSIVE_CAPACITOR_H_ */
