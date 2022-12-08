
#ifndef PASSIVE_RESISTOR_H_
#define PASSIVE_RESISTOR_H_

#include <math.h>
#include "EIA.h"
#include "helper_functions.h"

#define RESISTOR_MAX_POWER		6

float RESISTOR_E3[ 3 * ( RESISTOR_MAX_POWER + 1 ) ];
float RESISTOR_E6[ 6 * ( RESISTOR_MAX_POWER + 1 ) ];
float RESISTOR_E12[ 12 * ( RESISTOR_MAX_POWER + 1 ) ];
float RESISTOR_E24[ 24 * ( RESISTOR_MAX_POWER + 1 ) ];
float RESISTOR_E48[ 48 * ( RESISTOR_MAX_POWER + 1 ) ];
float RESISTOR_E96[ 96 * ( RESISTOR_MAX_POWER + 1 ) ];

/******	Function declarations *****/

void RESISTOR_init();

float RESISTOR_ER2S(float R1, float R2);
float RESISTOR_ER2P(float R1, float R2);
float RESISTOR_ER3S(float R1, float R2, float R3);
float RESISTOR_ER3P(float R1, float R2, float R3);

float RESISTOR_1R(float R,EIA_standard RESISTOR_EIA_standard);
void RESISTOR_2RS(float R,EIA_standard RESISTOR_EIA_STANDARD, float* R1, float* R2);
void RESISTOR_2RP(float R,EIA_standard RESISTOR_EIA_STANDARD, float* R1, float* R2);

float RESISTOR_1R_SD(float R, float T);

/**************************	Function definitions **************************/

/*****
 *
 * RESISTOR_init() : Initializes the standard resistor values.
 *
 *****/

void RESISTOR_init()
{
	int i;
	int j;

	/*	Get standard resistor values. */

	for( i = 0 ; i <= RESISTOR_MAX_POWER ; i++ )
	{
		for( j = 0 ; j < 3 ; j++ )
		{
			RESISTOR_E3[ 3*i + j ] = EIA_STANDARD_E3_SET[j] * pow( 10.0f, (float)i );
		}

		for( j = 0 ; j < 6 ; j++ )
		{
			RESISTOR_E6[ 6*i + j ] = EIA_STANDARD_E6_SET[j] * pow( 10.0f, (float)i );
		}

		for( j = 0 ; j < 12 ; j++ )
		{
			RESISTOR_E12[ 12*i + j ] = EIA_STANDARD_E12_SET[j] * pow( 10.0f, (float)i );
		}

		for( j = 0 ; j < 24 ; j++ )
		{
			RESISTOR_E24[ 24*i + j ] = EIA_STANDARD_E24_SET[j] * pow( 10.0f, (float)i );
		}

		for( j = 0 ; j < 48 ; j++ )
		{
			RESISTOR_E48[ 48*i + j ] = EIA_STANDARD_E48_SET[j] * pow( 10.0f, (float)i );
		}

		for( j = 0 ; j < 96 ; j++ )
		{
			RESISTOR_E96[ 96*i + j ] = EIA_STANDARD_E96_SET[j] * pow( 10.0f, (float)i );
		}
	}
}

/*
 *
 * RESISTOR_ER2S(R1,R2)
 *
 * DESCRIPTION:
 *
 * Returns the equivalent resistance when R1 and R2 are connected in series.
 *
 */

float RESISTOR_ER2S(float R1, float R2)
{
	return( R1 + R2 );
}

/*
 *
 * RESISTOR_ER2P(R1,R2)
 *
 * DESCRIPTION:
 *
 * Returns the equivalent resistance when R1 and R2 are connected in parallel.
 *
 */

float RESISTOR_ER2P(float R1, float R2)
{
	return( ( R1 * R2 ) / ( R1 + R2 ) );
}

/*
 *
 * RESISTOR_ER3S(R1,R2,R3)
 *
 * DESCRIPTION:
 *
 * Returns the equivalent resistance when R1, R2 and R3 are connected in series.
 *
 */

float RESISTOR_ER3S(float R1, float R2, float R3)
{
	return( R1 + R2 + R3 );
}

/*
 *
 * RESISTOR_ER3P(R1,R2,R3)
 *
 * DESCRIPTION:
 *
 * Returns the equivalent resistance when R1, R2 and R3 are connected in parallel.
 *
 */

float RESISTOR_ER3P(float R1, float R2, float R3)
{
	return( 1.0f / ( ( 1.0f / R1 ) + ( 1.0f / R2 ) + ( 1.0f / R3 ) ) );
}

/*
 *
 * RESISTOR_1R(R, RESISTOR_EIA_standard)
 *
 * DESCRIPTION:
 *
 * Returns the standard resistor value corresponding to a EIA standard
 * closest to the specified resistor value.
 *
 *	@parameter R:							Target resistor value.
 *	@parameter RESISTOR_EIA_standard:		EIA standard set from which resistor is to
 *											be selected.
 *
 */

float RESISTOR_1R(float R, EIA_standard RESISTOR_EIA_standard)
{
	float error;
	float R_current;
	float R_optimal;
	float* R_set;
	float error_min;

	int i;

	error_min = pow( 10.0f, (float)RESISTOR_MAX_POWER + 1.0f );

	//	Choose resistor set from where to select.

	switch(RESISTOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; 	break;
	}

	//	Start search.

	for( i = 0 ; i < RESISTOR_EIA_standard*RESISTOR_MAX_POWER ; i++ )
	{
		R_current = R_set[i];

		error = R_current - R;

		if( error < 0.0f ) error = -error;

		if( error < error_min )
		{
			error_min = error;
			R_optimal = R_current;
		}
	}

	return(R_optimal);
}

/*****
 *
 * RESISTOR_2RS(R,RESISTOR_EIA_standard, R1, R2)
 *
 * DESCRIPTION:
 *
 * Returns two values of resistors from selected resistor when connected in series,
 * given equivalent resistance closest to target value.
 *
 * @parameter	R:							Target resistor value.
 * @parameter	RESISTOR_EIA_standard:		resistor set from which value should be selected.
 * @parameter	R1:							Pointer to resistor 1.
 * @parameter	R2:							Pointer to resistor 2.
 *
 *****/

void RESISTOR_2RS(float R, EIA_standard RESISTOR_EIA_standard, float* R1, float* R2 )
{
	float error;
	float error_min;
	float* R_set;
	float R1_optimal;
	float R2_optimal;
	float R_series;

	int i,j;
	int limit;

	limit = RESISTOR_MAX_POWER*RESISTOR_EIA_standard;

	error_min = pow( 10.0f, (float)( RESISTOR_MAX_POWER + 1 ) );

	switch(RESISTOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; 	break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			R_series = R_set[i] + R_set[j];
			error = R_series - R;

			if( error < 0.0f )
			{
				error = -error;
			}

			if( error < error_min )
			{
				error_min = error;
				R1_optimal = R_set[i];
				R2_optimal = R_set[j];
			}
		}
	}

	*R1 = R1_optimal;
	*R2 = R2_optimal;
}

/*****
 *
 * RESISTOR_2RP(R,RESISTOR_EIA_standard, R1, R2)
 *
 * DESCRIPTION:
 *
 * Returns two values of resistors from selected resistor when connected in parallel,
 * given equivalent resistance closest to target value.
 *
 * @parameter	R:							Target resistor value.
 * @parameter	RESISTOR_EIA_standard:		resistor set from which value should be selected.
 * @parameter	R1:							Pointer to resistor 1.
 * @parameter	R2:							Pointer to resistor 2.
 *
 *****/

void RESISTOR_2RP(float R, EIA_standard RESISTOR_EIA_standard, float* R1, float* R2 )
{
	float error;
	float error_min;
	float* R_set;
	float R1_optimal;
	float R2_optimal;
	float R_parallel;

	int i,j;
	int limit;

	limit = RESISTOR_MAX_POWER*RESISTOR_EIA_standard;

	error_min = pow( 10.0f, (float)( RESISTOR_MAX_POWER + 1 ) );

	switch(RESISTOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; 	break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			R_parallel = ( R_set[i] * R_set[j] ) / ( R_set[i] + R_set[j] );
			error = R_parallel - R;

			if( error < 0.0f )
			{
				error = -error;
			}

			if( error < error_min )
			{
				error_min = error;
				R1_optimal = R_set[i];
				R2_optimal = R_set[j];
			}
		}
	}

	*R1 = R1_optimal;
	*R2 = R2_optimal;
}


/*****
 *
 * RESISTOR_3RS(R,RESISTOR_EIA_standard, R1, R2, R3)
 *
 * DESCRIPTION:
 *
 * Returns three values of resistors from selected resistor when connected in series,
 * given equivalent resistance closest to target value.
 *
 * @parameter	R:							Target resistor value.
 * @parameter	RESISTOR_EIA_standard:		resistor set from which value should be selected.
 * @parameter	R1:							Pointer to resistor 1.
 * @parameter	R2:							Pointer to resistor 2.
 * @parameter 	R3:							Pointer to resistor 3.
 *
 *****/

void RESISTOR_3RS(float R, EIA_standard RESISTOR_EIA_standard, float* R1, float* R2, float* R3)
{
	float error;
	float error_min;
	float* R_set;
	float R1_optimal;
	float R2_optimal;
	float R3_optimal;
	float R_series;

	int i,j,k;
	int limit;

	limit = RESISTOR_MAX_POWER*RESISTOR_EIA_standard;

	error_min = pow( 10.0f, (float)( RESISTOR_MAX_POWER + 1 ) );

	switch(RESISTOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; 	break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			for( k = 0 ; k < limit ; k ++ )
			{
				R_series = RESISTOR_ER3S( R_set[i], R_set[j], R_set[k] );
				error = R_series - R;

				if( error < 0.0f )
				{
					error = -error;
				}

				if( error < error_min )
				{
					error_min = error;
					R1_optimal = R_set[i];
					R2_optimal = R_set[j];
					R3_optimal = R_set[k];
				}
			}
		}
	}

	*R1 = R1_optimal;
	*R2 = R2_optimal;
	*R3 = R3_optimal;
}


/*****
 *
 * RESISTOR_3RP(R,RESISTOR_EIA_standard, R1, R2, R3)
 *
 * DESCRIPTION:
 *
 * Returns two values of resistors from selected resistor when connected in parallel,
 * given equivalent resistance closest to target value.
 *
 * @parameter	R:							Target resistor value.
 * @parameter	RESISTOR_EIA_standard:		resistor set from which value should be selected.
 * @parameter	R1:							Pointer to resistor 1.
 * @parameter	R2:							Pointer to resistor 2.
 * @parameter	R3:							Pointer to resistor 3.
 *
 *****/

void RESISTOR_3RP(float R, EIA_standard RESISTOR_EIA_standard, float* R1, float* R2, float* R3)
{
	float error;
	float error_min;
	float* R_set;
	float R1_optimal;
	float R2_optimal;
	float R3_optimal;
	float R_parallel;

	int i,j,k;
	int limit;

	limit = RESISTOR_MAX_POWER*RESISTOR_EIA_standard;

	error_min = pow( 10.0f, (float)( RESISTOR_MAX_POWER + 1 ) );

	switch(RESISTOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; 	break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; 	break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; 	break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; 	break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; 	break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; 	break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			for( k = 0 ; k < limit ; k++ )
			{
				R_parallel = RESISTOR_ER3P( R_set[i], R_set[j], R_set[k] );
				error = R_parallel - R;

				if( error < 0.0f )
				{
					error = -error;
				}

				if( error < error_min )
				{
					error_min = error;
					R1_optimal = R_set[i];
					R2_optimal = R_set[j];
					R3_optimal = R_set[k];
				}
			}
		}
	}

	*R1 = R1_optimal;
	*R2 = R2_optimal;
	*R3 = R3_optimal;
}

/**
 *
 * RESISTOR_1R_SD(R,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the resistances for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter R						:	Resistor value.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float RESISTOR_1R_SD(float R, float T)
{
	float R_buffer[2];
	float result;

	R_buffer[0] = R * ( 1 + 0.01f * T );
	R_buffer[1] = R * ( 1 - 0.01f * T );

	result = standard_deviation( R_buffer, 2 ) / R;

	return( 100.0f * result );
}


/**
 *
 * RESISTOR_2RS_SD(R1,R2,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the resistances for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter R1, R2				:	Resistor values.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float RESISTOR_2RS_SD(float R1, float R2, float T)
{
	float R_buffer[4];
	float result;
	float R;
	float t;

	t = 0.01f * T;
	R = RESISTOR_ER2S(R1,R2);

	R_buffer[0] = RESISTOR_ER2S( R1 * ( 1 + t ), R2 * ( 1 + t ) );
	R_buffer[1] = RESISTOR_ER2S( R1 * ( 1 + t ), R2 * ( 1 - t ) );
	R_buffer[2] = RESISTOR_ER2S( R1 * ( 1 - t ), R2 * ( 1 + t ) );
	R_buffer[3] = RESISTOR_ER2S( R1 * ( 1 - t ), R2 * ( 1 - t ) );

	result = standard_deviation( R_buffer, 4 ) / R;

	return( 100.0f * result );
}


/**
 *
 * RESISTOR_2RP_SD(R1,R2,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the resistances for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter R1, R2				:	Resistor values.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float RESISTOR_2RP_SD(float R1, float R2, float T)
{
	float R_buffer[4];
	float result;
	float R;
	float t;

	t = 0.01f * T;
	R = RESISTOR_ER2P(R1,R2);

	R_buffer[0] = RESISTOR_ER2P( R1 * ( 1 + t ), R2 * ( 1 + t ) );
	R_buffer[1] = RESISTOR_ER2P( R1 * ( 1 + t ), R2 * ( 1 - t ) );
	R_buffer[2] = RESISTOR_ER2P( R1 * ( 1 - t ), R2 * ( 1 + t ) );
	R_buffer[3] = RESISTOR_ER2P( R1 * ( 1 - t ), R2 * ( 1 - t ) );

	result = standard_deviation( R_buffer, 4 ) / R;

	return( 100.0f * result );
}

/**
 *
 * RESISTOR_3RS_SD(R1,R2,R3,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the resistances for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter R1, R2, R3			:	Resistor values.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float RESISTOR_3RS_SD(float R1, float R2, float R3, float T)
{
	float R_buffer[8];
	float result;
	float R;
	float t;

	t = 0.01f * T;
	R = RESISTOR_ER3S(R1,R2,R3);

	R_buffer[0] = RESISTOR_ER3S( R1 * ( 1 + t ), R2 * ( 1 + t ), R3 * ( 1 + t ) );
	R_buffer[1] = RESISTOR_ER3S( R1 * ( 1 + t ), R2 * ( 1 + t ), R3 * ( 1 - t ) );
	R_buffer[2] = RESISTOR_ER3S( R1 * ( 1 + t ), R2 * ( 1 - t ), R3 * ( 1 + t ) );
	R_buffer[3] = RESISTOR_ER3S( R1 * ( 1 + t ), R2 * ( 1 - t ), R3 * ( 1 - t ) );
	R_buffer[4] = RESISTOR_ER3S( R1 * ( 1 - t ), R2 * ( 1 + t ), R3 * ( 1 + t ) );
	R_buffer[5] = RESISTOR_ER3S( R1 * ( 1 - t ), R2 * ( 1 + t ), R3 * ( 1 - t ) );
	R_buffer[6] = RESISTOR_ER3S( R1 * ( 1 - t ), R2 * ( 1 - t ), R3 * ( 1 + t ) );
	R_buffer[7] = RESISTOR_ER3S( R1 * ( 1 - t ), R2 * ( 1 - t ), R3 * ( 1 - t ) );

	result = standard_deviation( R_buffer, 8 ) / R;

	return( 100.0f * result );
}


/**
 *
 * RESISTOR_3RP_SD(R1,R2,R3,T)
 *
 * DESCRIPTION:
 *
 *This function calculates the resistances for given tolerance and returns the standard deviation
 *of these values as a percentage of the nominal value.
 *
 * @parameter R1, R2, R3			:	Resistor values.
 * @parameter T						:	Tolerance of resistor (in percentage).
 *
 */

float RESISTOR_3RP_SD(float R1, float R2, float R3, float T)
{
	float R_buffer[8];
	float result;
	float R;
	float t;

	t = 0.01f * T;
	R = RESISTOR_ER3P(R1,R2,R3);

	R_buffer[0] = RESISTOR_ER3P( R1 * ( 1 + t ), R2 * ( 1 + t ), R3 * ( 1 + t ) );
	R_buffer[1] = RESISTOR_ER3P( R1 * ( 1 + t ), R2 * ( 1 + t ), R3 * ( 1 - t ) );
	R_buffer[2] = RESISTOR_ER3P( R1 * ( 1 + t ), R2 * ( 1 - t ), R3 * ( 1 + t ) );
	R_buffer[3] = RESISTOR_ER3P( R1 * ( 1 + t ), R2 * ( 1 - t ), R3 * ( 1 - t ) );
	R_buffer[4] = RESISTOR_ER3P( R1 * ( 1 - t ), R2 * ( 1 + t ), R3 * ( 1 + t ) );
	R_buffer[5] = RESISTOR_ER3P( R1 * ( 1 - t ), R2 * ( 1 + t ), R3 * ( 1 - t ) );
	R_buffer[6] = RESISTOR_ER3P( R1 * ( 1 - t ), R2 * ( 1 - t ), R3 * ( 1 + t ) );
	R_buffer[7] = RESISTOR_ER3P( R1 * ( 1 - t ), R2 * ( 1 - t ), R3 * ( 1 - t ) );

	result = standard_deviation( R_buffer, 8 ) / R;

	return( 100.0f * result );
}


/*
 * 	RESISTOR_RATIO_1R(ratio, RESISTOR_EIA_standard,R_max, R_min, R1, R2)
 *
 * 	Description:
 *
 * 	This function calculates two resistors limited between two bounds which are in the ratio
 * 	closest to the target ratio.
 *
 * 	@parameter	ratio					:	Target ratio.
 * 	@parameter	RESISTOR_EIA_standard	:	EIA standard from which the resistor values are chosen.
 * 	@parameter	R_max,	R_min			:	Maximum and minimum bounds for resistors R1 and R2.
 * 	@parameter	R1, R2					:	Pointer to resistors R1 and R2.
 *
 */

void RESISTOR_RATIO_1R(
		float ratio,
		EIA_standard RESISTOR_EIA_standard,
		float R_max, float R_min,
		float* R1, float* R2
		)
{
	int i,j,limit;
	int condition_1, condition_2;
	float* R_set;
	float error, error_min;

	error_min = pow( 10.0f, (float)RESISTOR_MAX_POWER + 1.0f );
	limit = RESISTOR_MAX_POWER*RESISTOR_EIA_standard;

	switch(RESISTOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; break;
	}


	for( i = 0 ; i < limit ; i++ )
	{
		for( j = 0 ; j < limit ; j++ )
		{
			condition_1 = ( R_set[i] >= R_min ) && ( R_set[i] <= R_max );
			condition_2 = ( R_set[j] >= R_min ) && ( R_set[j] <= R_max );

			if( condition_1 && condition_2 )
			{
				error = ( R_set[i] / R_set[j] ) - ratio;

				if( error < 0.0f ) error = -error;

				if( error < error_min )
				{
					error_min = error;
					*R1 = R_set[i];
					*R2 = R_set[j];
				}
			}
		}
	}
}


/*
 * RESISTOR_RATIO_2RS(ratio, RESISTOR_EIA_standard, R_max, R_min, R1_A, R1_B, R2_A, R2_B)
 *
 *	@parameter	ratio					:	Desired ratio of ( R1_A + R1_B ) to ( R2_A + R2_B ).
 *	@parameter	RESISTOR_EIA_standard	:	EIA standard from which the resistor values are to be chosen.
 *	@parameter	R_max, R_min			:	Maximum and minimum resistance bounds for the resistor values.
 *	@parameter	R1_A, R1_B, R2_A, R2_B	:	Pointers to the selected resistor values.
 *
 */

void RESISTOR_RATIO_2RS(
		float ratio,
		EIA_standard RESISTOR_EIA_standard,
		float R_max, float R_min,
		float* R1_A, float* R1_B, float* R2_A, float* R2_B
	)
{
	float error;
	float error_min;
	float* R_set;
	float R1_eff;
	float R2_eff;

	int limit;
	int i,j,m,n;
	int condition_1, condition_2, condition_3, condition_4;

	error_min = pow( 10.0f, (float)RESISTOR_MAX_POWER + 1.0f );
	limit = RESISTOR_MAX_POWER * RESISTOR_EIA_standard;


	switch(RESISTOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; break;
	}

	for( i = 0 ; i < limit ; i++ )
	{
	for( j = 0 ; j < limit ; j++ )
	{
	for( m = 0 ; m < limit ; m++ )
	{
	for( n = 0 ; n < limit ; n++ )
	{
		condition_1 = ( R_set[i] >= R_min ) && ( R_set[i] <= R_max );
		condition_2 = ( R_set[j] >= R_min ) && ( R_set[j] <= R_max );
		condition_3 = ( R_set[m] >= R_min ) && ( R_set[m] <= R_max );
		condition_4 = ( R_set[n] >= R_min ) && ( R_set[n] <= R_max );

		if( condition_1 && condition_2 && condition_3 && condition_4 )
		{
			R1_eff = RESISTOR_ER2S(R_set[i], R_set[j]);
			R2_eff = RESISTOR_ER2S(R_set[m], R_set[n]);

			error = ratio - ( R1_eff / R2_eff );

			if( error < 0.0f ) error = -error;

			if( error < error_min )
			{
				error_min = error;
				*R1_A = R_set[i];
				*R1_B = R_set[j];
				*R2_A = R_set[m];
				*R2_B = R_set[n];
			}
		}
	}
	}
	}
	}
}




/*
 * RESISTOR_RATIO_2RP(ratio, RESISTOR_EIA_standard, R_max, R_min, R1_A, R1_B, R2_A, R2_B)
 *
 *	@parameter	ratio					:	Desired ratio of ( R1_A || R1_B ) to ( R2_A || R2_B ).
 *	@parameter	RESISTOR_EIA_standard	:	EIA standard from which the resistor values are to be chosen.
 *	@parameter	R_max, R_min			:	Maximum and minimum resistance bounds for the resistor values.
 *	@parameter	R1_A, R1_B, R2_A, R2_B	:	Pointers to the selected resistor values.
 *
 */

void RESISTOR_RATIO_2RP(
		float ratio,
		EIA_standard RESISTOR_EIA_standard,
		float R_max, float R_min,
		float* R1_A, float* R1_B, float* R2_A, float* R2_B
	)
{
	float error;
	float error_min;
	float* R_set;
	float R1_eff;
	float R2_eff;

	int limit;
	int i,j,m,n;
	int condition_1, condition_2, condition_3, condition_4;

	error_min = pow( 10.0f, (float)RESISTOR_MAX_POWER + 1.0f );
	limit = RESISTOR_MAX_POWER * RESISTOR_EIA_standard;


	switch(RESISTOR_EIA_standard)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; break;
	}

	for( i = 0 ; i < limit ; i++ )
	{
	for( j = 0 ; j < limit ; j++ )
	{
	for( m = 0 ; m < limit ; m++ )
	{
	for( n = 0 ; n < limit ; n++ )
	{
		condition_1 = ( R_set[i] >= R_min ) && ( R_set[i] <= R_max );
		condition_2 = ( R_set[j] >= R_min ) && ( R_set[j] <= R_max );
		condition_3 = ( R_set[m] >= R_min ) && ( R_set[m] <= R_max );
		condition_4 = ( R_set[n] >= R_min ) && ( R_set[n] <= R_max );

		if( condition_1 && condition_2 && condition_3 && condition_4 )
		{
			R1_eff = RESISTOR_ER2P(R_set[i], R_set[j]);
			R2_eff = RESISTOR_ER2P(R_set[m], R_set[n]);

			error = ratio - ( R1_eff / R2_eff );

			if( error < 0.0f ) error = -error;

			if( error < error_min )
			{
				error_min = error;
				*R1_A = R_set[i];
				*R1_B = R_set[j];
				*R2_A = R_set[m];
				*R2_B = R_set[n];
			}
		}
	}
	}
	}
	}
}


#endif /* PASSIVE_RESISTOR_H_ */
