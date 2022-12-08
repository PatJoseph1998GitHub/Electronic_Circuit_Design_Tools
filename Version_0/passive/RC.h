
#ifndef PASSIVE_RC_H_
#define PASSIVE_RC_H_

#include <math.h>

#include "RESISTOR.h"
#include "CAPACITOR.h"

/*****			Function declarations			*****/

void RC_init();

/*****			Function definitions			*****/

/*
 * 	RC_init()
 *
 * 	DECSRIPTION:
 *
 * 	Initializes standard values of resistors and capacitors.
 *
 */

void RC_init()
{
	RESISTOR_init();
	CAPACITOR_init();
}


/*
 * RC_TC_1R1C(float R, float C)
 *
 * Description:
 *
 * Calculates the RC time constant of a simple RC circuit.
 *
 * @parameter	R				:	Resistor R in ohms.
 * @parameter	C				:	Capacitor C in farads.
 *
 */

float RC_TC_1R1C(float R, float C)
{
	return(R*C);
}

/*
 * RC_TC_2RS1C(float R1, float R2, float C)
 *
 * Description:
 *
 * Calculates the RC time constant of a simple RC circuit consisting of 2 resistors in series.
 *
 * @parameter	R1, R2			:	Resistor values in ohms.
 * @parameter	C				:	Capacitor values in farads.
 *
 */

float RC_TC_2RS1C(float R1, float R2, float C)
{
	return( RESISTOR_ER2S(R1,R2) *C );
}


/*
 * RC_TC_2RP1C(float R1, float R2, float C)
 *
 * Description:
 *
 * Calculates the RC time constant of a simple RC circuit consisting of 2 resistors in parallel.
 *
 * @parameter	R1, R2			:	Resistor values in ohms.
 * @parameter	C				:	Capacitor values in farads.
 *
 */

float RC_TC_2RP1C(float R1, float R2, float C)
{
	return( RESISTOR_ER2P(R1,R2) *C );
}


/*
 * RC_TC_3RS1C(float R1, float R2, float R3, float C)
 *
 * Description:
 *
 * Calculates the RC time constant of a simple RC circuit consisting of 3 resistors in series.
 *
 * @parameter	R1, R2, R3		:	Resistor values in ohms.
 * @parameter	C				:	Capacitor values in farads.
 *
 */

float RC_TC_3RS1C(float R1, float R2, float R3, float C)
{
	return( RESISTOR_ER3S(R1,R2,R3) *C );
}


/*
 * RC_TC_2RP1C(float R1, float R2, float R3, float C)
 *
 * Description:
 *
 * Calculates the RC time constant of a simple RC circuit consisting of 3 resistors in parallel.
 *
 * @parameter	R1, R2, R3		:	Resistor values in ohms.
 * @parameter	C				:	Capacitor values in farads.
 *
 */

float RC_TC_3RP1C(float R1, float R2, float R3, float C)
{
	return( RESISTOR_ER3P(R1,R2,R3) *C );
}


/*
 * RC_1R1C(tau, RESISTOR_EIA_std, CAPACITOR_EIA_std, R_max, R_min, C_max, C_min, R, C )
 *
 * Description:
 *
 * Gives the values of R and C corresponding to the given EIA standard set and resistor and capacitor
 * values bounded between a maximum and minimum limit.
 *
 * @parameter	tau								:	RC time constant in seconds.
 * @parameter	RESISTOR_EIA_std				:	EIA standard set from which resistor are chosen.
 * @parameter	CAPACITOR_EIA_std				:	EIA standard set from which capacitor are chosen.
 * @parameter	R_max							:	Maximum value of resistor.
 * @parameter	R_min							:	Minimum value of resistor.
 * @parameter	C_max							:	Maximum value of capacitor.
 * @parameter	C_min							:	Minimum value of capacitor.
 * @parameter	R								:	Pointer to chosen value of resistor.
 * @parameter	C								:	Pointer to chosen value of capacitor.
 *
 */

void RC_1R1C( float tau,
			  EIA_standard RESISTOR_EIA_std,
			  EIA_standard CAPACITOR_EIA_std,
			  float R_max,
			  float R_min,
			  float C_max,
			  float C_min,
			  float* R,float* C)
{
	float* R_set;
	float* C_set;

	float error, error_min;

	int i,j, R_limit, C_limit;
	int condition_1, condition_2;

	//	Select resistor and capacitor standard sets.

	switch(RESISTOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; break;
	}

	switch(CAPACITOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; break;
	}

	//	Set search limits and error bounds.

	R_limit = RESISTOR_MAX_POWER * RESISTOR_EIA_std;
	C_limit = CAPACITOR_POWER_RANGE * CAPACITOR_EIA_std;

	error_min = 10.0f * R_set[R_limit-1] * C_set[C_limit-1];

	//	Start search.

	for( i = 0 ; i < R_limit ; i++ )
	{
		for( j = 0 ; j < C_limit ; j++ )
		{
			condition_1 = ( R_set[i] >= R_min ) && ( R_set[i] <= R_max );
			condition_2 = ( C_set[j] >= C_min ) && ( C_set[j] <= C_max );

			//	Only if current resistor and capacitor values are within bounds,
			//	proceed further.

			if( condition_1 && condition_2 )
			{
				error = ( R_set[i] * C_set[j] ) - tau;

				if( error < 0.0f ) error = -error;

				if( error < error_min )
				{
					error_min = error;
					*R = R_set[i];
					*C = C_set[j];
				}
			}
		}
	}
}


/*
 * RC_2RS1C(tau, RESISTOR_EIA_std, CAPACITOR_EIA_std, R_max, R_min, C_max, C_min, R1, R2, C )
 *
 * Description:
 *
 * Gives the values of R and C corresponding to the given EIA standard set and resistor and capacitor
 * values bounded between a maximum and minimum limit.
 *
 * @parameter	tau								:	RC time constant in seconds.
 * @parameter	RESISTOR_EIA_std				:	EIA standard set from which resistor are chosen.
 * @parameter	CAPACITOR_EIA_std				:	EIA standard set from which capacitor are chosen.
 * @parameter	R_max							:	Maximum value of resistor.
 * @parameter	R_min							:	Minimum value of resistor.
 * @parameter	C_max							:	Maximum value of capacitor.
 * @parameter	C_min							:	Minimum value of capacitor.
 * @parameter	R1, R2							:	Pointers to chosen value of resistors.
 * @parameter	C								:	Pointer to chosen value of capacitor.
 *
 */

void RC_2RS1C( float tau,
			  EIA_standard RESISTOR_EIA_std,
			  EIA_standard CAPACITOR_EIA_std,
			  float R_max,
			  float R_min,
			  float C_max,
			  float C_min,
			  float* R1, float* R2, float* C)
{
	float* R_set;
	float* C_set;

	float error, error_min;

	int i, j, k, R_limit, C_limit;
	int condition_1, condition_2, condition_3;

	//	Select resistor and capacitor standard sets.

	switch(RESISTOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; break;
	}

	switch(CAPACITOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; break;
	}

	//	Set search limits and error bounds.

	R_limit = RESISTOR_MAX_POWER * RESISTOR_EIA_std;
	C_limit = CAPACITOR_POWER_RANGE * CAPACITOR_EIA_std;

	error_min = 10.0f * R_set[R_limit-1] * C_set[C_limit-1];

	//	Start search.

	for( i = 0 ; i < R_limit ; i++ )
	{
		for( j = 0 ; j < R_limit ; j++ )
		{
			for( k = 0 ; k < C_limit ; k++ )
			{
				condition_1 = ( R_set[i] >= R_min ) && ( R_set[i] <= R_max );
				condition_2 = ( R_set[j] >= R_min ) && ( R_set[j] <= R_max );
				condition_3 = ( C_set[k] >= C_min ) && ( C_set[k] <= C_max );

				if( condition_1 && condition_2 && condition_3 )
				{
					error = RC_TC_2RS1C( R_set[i], R_set[j], C_set[k] ) - tau;

					if( error < 0.0f ) error = -error;

					if( error < error_min )
					{
						error_min = error;
						*R1 = R_set[i];
						*R2 = R_set[j];
						*C  = C_set[k];
					}
				}
			}
		}
	}
}


/*
 * RC_2RP1C(tau, RESISTOR_EIA_std, CAPACITOR_EIA_std, R_max, R_min, C_max, C_min, R1, R2, C )
 *
 * Description:
 *
 * Gives the values of R and C corresponding to the given EIA standard set and resistor and capacitor
 * values bounded between a maximum and minimum limit.
 *
 * @parameter	tau								:	RC time constant in seconds.
 * @parameter	RESISTOR_EIA_std				:	EIA standard set from which resistor are chosen.
 * @parameter	CAPACITOR_EIA_std				:	EIA standard set from which capacitor are chosen.
 * @parameter	R_max							:	Maximum value of resistor.
 * @parameter	R_min							:	Minimum value of resistor.
 * @parameter	C_max							:	Maximum value of capacitor.
 * @parameter	C_min							:	Minimum value of capacitor.
 * @parameter	R1, R2							:	Pointers to chosen value of resistors.
 * @parameter	C								:	Pointer to chosen value of capacitor.
 *
 */

void RC_2RP1C( float tau,
			  EIA_standard RESISTOR_EIA_std,
			  EIA_standard CAPACITOR_EIA_std,
			  float R_max,
			  float R_min,
			  float C_max,
			  float C_min,
			  float* R1, float* R2, float* C)
{
	float* R_set;
	float* C_set;

	float error, error_min;

	int i, j, k, R_limit, C_limit;
	int condition_1, condition_2, condition_3;

	//	Select resistor and capacitor standard sets.

	switch(RESISTOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; break;
	}

	switch(CAPACITOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; break;
	}

	//	Set search limits and error bounds.

	R_limit = RESISTOR_MAX_POWER * RESISTOR_EIA_std;
	C_limit = CAPACITOR_POWER_RANGE * CAPACITOR_EIA_std;

	error_min = 10.0f * R_set[R_limit-1] * C_set[C_limit-1];

	//	Start search.

	for( i = 0 ; i < R_limit ; i++ )
	{
		for( j = 0 ; j < R_limit ; j++ )
		{
			for( k = 0 ; k < C_limit ; k++ )
			{
				condition_1 = ( R_set[i] >= R_min ) && ( R_set[i] <= R_max );
				condition_2 = ( R_set[j] >= R_min ) && ( R_set[j] <= R_max );
				condition_3 = ( C_set[k] >= C_min ) && ( C_set[k] <= C_max );

				if( condition_1 && condition_2 && condition_3 )
				{
					error = RC_TC_2RP1C( R_set[i], R_set[j], C_set[k] ) - tau;

					if( error < 0.0f ) error = -error;

					if( error < error_min )
					{
						error_min = error;
						*R1 = R_set[i];
						*R2 = R_set[j];
						*C  = C_set[k];
					}
				}
			}
		}
	}
}



/*
 * RC_3RS1C(tau, RESISTOR_EIA_std, CAPACITOR_EIA_std, R_max, R_min, C_max, C_min, R1, R2, R3, C )
 *
 * Description:
 *
 * Gives the values of R and C corresponding to the given EIA standard set and resistor and capacitor
 * values bounded between a maximum and minimum limit.
 *
 * @parameter	tau								:	RC time constant in seconds.
 * @parameter	RESISTOR_EIA_std				:	EIA standard set from which resistor are chosen.
 * @parameter	CAPACITOR_EIA_std				:	EIA standard set from which capacitor are chosen.
 * @parameter	R_max							:	Maximum value of resistor.
 * @parameter	R_min							:	Minimum value of resistor.
 * @parameter	C_max							:	Maximum value of capacitor.
 * @parameter	C_min							:	Minimum value of capacitor.
 * @parameter	R1, R2, R3						:	Pointers to chosen value of resistors.
 * @parameter	C								:	Pointer to chosen value of capacitor.
 *
 */

void RC_3RS1C( float tau,
			  EIA_standard RESISTOR_EIA_std,
			  EIA_standard CAPACITOR_EIA_std,
			  float R_max,
			  float R_min,
			  float C_max,
			  float C_min,
			  float* R1, float* R2, float* R3, float* C)
{
	float* R_set;
	float* C_set;

	float error, error_min;

	int i, j, k, m, R_limit, C_limit;
	int condition_1, condition_2, condition_3, condition_4;

	//	Select resistor and capacitor standard sets.

	switch(RESISTOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; break;
	}

	switch(CAPACITOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; break;
	}

	//	Set search limits and error bounds.

	R_limit = RESISTOR_MAX_POWER * RESISTOR_EIA_std;
	C_limit = CAPACITOR_POWER_RANGE * CAPACITOR_EIA_std;

	error_min = 10.0f * R_set[R_limit-1] * C_set[C_limit-1];

	//	Start search.

	for( i = 0 ; i < R_limit ; i++ )
	{
		for( j = 0 ; j < R_limit ; j++ )
		{
			for( k = 0 ; k < R_limit ; k++ )
			{
				for( m = 0 ; m < C_limit ; m++ )
				{
					condition_1 = ( R_set[i] >= R_min ) && ( R_set[i] <= R_max );
					condition_2 = ( R_set[j] >= R_min ) && ( R_set[j] <= R_max );
					condition_3 = ( R_set[k] >= R_min ) && ( R_set[k] <= R_max );
					condition_4 = ( C_set[m] >= C_min ) && ( C_set[m] <= C_max );

					if( condition_1 && condition_2 && condition_3 && condition_4 )
					{
						error = RC_TC_3RS1C( R_set[i], R_set[j], R_set[k], C_set[m] ) - tau;

						if( error < 0.0f ) error = -error;

						if( error < error_min )
						{
							error_min = error;
							*R1 = R_set[i];
							*R2 = R_set[j];
							*R3 = R_set[k];
							*C  = C_set[m];
						}
					}
				}
			}
		}
	}
}



/*
 * RC_3RP1C(tau, RESISTOR_EIA_std, CAPACITOR_EIA_std, R_max, R_min, C_max, C_min, R1, R2, R3, C )
 *
 * Description:
 *
 * Gives the values of R and C corresponding to the given EIA standard set and resistor and capacitor
 * values bounded between a maximum and minimum limit.
 *
 * @parameter	tau								:	RC time constant in seconds.
 * @parameter	RESISTOR_EIA_std				:	EIA standard set from which resistor are chosen.
 * @parameter	CAPACITOR_EIA_std				:	EIA standard set from which capacitor are chosen.
 * @parameter	R_max							:	Maximum value of resistor.
 * @parameter	R_min							:	Minimum value of resistor.
 * @parameter	C_max							:	Maximum value of capacitor.
 * @parameter	C_min							:	Minimum value of capacitor.
 * @parameter	R1, R2, R3						:	Pointers to chosen value of resistors.
 * @parameter	C								:	Pointer to chosen value of capacitor.
 *
 */

void RC_3RP1C( float tau,
			  EIA_standard RESISTOR_EIA_std,
			  EIA_standard CAPACITOR_EIA_std,
			  float R_max,
			  float R_min,
			  float C_max,
			  float C_min,
			  float* R1, float* R2, float* R3, float* C)
{
	float* R_set;
	float* C_set;

	float error, error_min;

	int i, j, k, m, R_limit, C_limit;
	int condition_1, condition_2, condition_3, condition_4;

	//	Select resistor and capacitor standard sets.

	switch(RESISTOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ R_set = RESISTOR_E3; }; break;
		case(EIA_STANDARD_E6):{ R_set = RESISTOR_E6; }; break;
		case(EIA_STANDARD_E12):{ R_set = RESISTOR_E12; }; break;
		case(EIA_STANDARD_E24):{ R_set = RESISTOR_E24; }; break;
		case(EIA_STANDARD_E48):{ R_set = RESISTOR_E48; }; break;
		case(EIA_STANDARD_E96):{ R_set = RESISTOR_E96; }; break;
	}

	switch(CAPACITOR_EIA_std)
	{
		case(EIA_STANDARD_E3):{ C_set = CAPACITOR_E3; }; break;
		case(EIA_STANDARD_E6):{ C_set = CAPACITOR_E6; }; break;
		case(EIA_STANDARD_E12):{ C_set = CAPACITOR_E12; }; break;
		case(EIA_STANDARD_E24):{ C_set = CAPACITOR_E24; }; break;
		case(EIA_STANDARD_E48):{ C_set = CAPACITOR_E48; }; break;
		case(EIA_STANDARD_E96):{ C_set = CAPACITOR_E96; }; break;
	}

	//	Set search limits and error bounds.

	R_limit = RESISTOR_MAX_POWER * RESISTOR_EIA_std;
	C_limit = CAPACITOR_POWER_RANGE * CAPACITOR_EIA_std;

	error_min = 10.0f * R_set[R_limit-1] * C_set[C_limit-1];

	//	Start search.

	for( i = 0 ; i < R_limit ; i++ )
	{
		for( j = 0 ; j < R_limit ; j++ )
		{
			for( k = 0 ; k < R_limit ; k++ )
			{
				for( m = 0 ; m < C_limit ; m++ )
				{
					condition_1 = ( R_set[i] >= R_min ) && ( R_set[i] <= R_max );
					condition_2 = ( R_set[j] >= R_min ) && ( R_set[j] <= R_max );
					condition_3 = ( R_set[k] >= R_min ) && ( R_set[k] <= R_max );
					condition_4 = ( C_set[m] >= C_min ) && ( C_set[m] <= C_max );

					if( condition_1 && condition_2 && condition_3 && condition_4 )
					{
						error = RC_TC_3RP1C( R_set[i], R_set[j], R_set[k], C_set[m] ) - tau;

						if( error < 0.0f ) error = -error;

						if( error < error_min )
						{
							error_min = error;
							*R1 = R_set[i];
							*R2 = R_set[j];
							*R3 = R_set[k];
							*C  = C_set[m];
						}
					}
				}
			}
		}
	}
}


#endif /* PASSIVE_RC_H_ */
