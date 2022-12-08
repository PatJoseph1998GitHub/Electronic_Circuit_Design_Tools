
#ifndef PASSIVE_WIRE_H_
#define PASSIVE_WIRE_H_

#include <math.h>

#define MU_0		1e-7 * M_PI * 4.0f				//	Permeability of freespace.
#define RHO_CU		1.68e-8							//	Resistivity of copper in ohm-m.
#define RHO_AL		2.65e-8							//	Resistivity of aluminium in ohm-m.

//	Contains SWG wire gauges with diameters mentioned in milli-meters.

float SWG[46] =
{
		8.230f, 7.620f, 7.010f, 6.400f, 5.890f, 5.380f, 4.880f, 4.470f, 4.060f, 3.660f, 3.250f,
		2.950f, 2.640f, 2.340f, 2.030f, 1.830f, 1.630f, 1.420f, 1.220f, 1.020f, 0.914f, 0.813f,
		0.711f, 0.610f, 0.559f, 0.508f, 0.457f, 0.417f, 0.376f, 0.345f, 0.315f, 0.295f, 0.274f,
		0.254f, 0.234f, 0.213f, 0.193f, 0.173f, 0.152f, 0.132f, 0.122f, 0.112f, 0.102f, 0.091f,
		0.081f, 0.071f
};

//	List of availble SWG standards.

typedef enum
{
	SWG_0, SWG_1, SWG_3, SWG_4, SWG_5, SWG_6, SWG_7, SWG_8, SWG_9,
	SWG_10, SWG_11, SWG_12, SWG_13, SWG_14, SWG_15, SWG_16, SWG_17, SWG_18, SWG_19, SWG_20,
	SWG_21, SWG_22, SWG_23, SWG_24, SWG_25, SWG_26, SWG_27, SWG_28, SWG_29, SWG_30,
	SWG_31, SWG_32, SWG_33, SWG_34, SWG_35, SWG_36, SWG_37, SWG_38, SWG_39, SWG_40,
	SWG_41, SWG_42, SWG_43, SWG_44, SWG_45
}SWG_t;


//	Conductor types.

typedef enum{ COPPER, ALUMINIUM } conductor_t;

/*
 * WIRE_getSkinDepth(Conductor_Type, f)
 *
 * Returns the skin depth of a conductor when a signal passes through it with given
 * frequency.
 *
 * @parameter Conductor_Type	:	type of conductor used.
 * @parameter f					:	frequency of signal in Hz.
 *
 */

float WIRE_getSkinDepth(conductor_t Conductor_Type, float f)
{
	float rho;
	float t;
	float delta;
	float mu_r = 1.0f;

	switch( Conductor_Type )
	{
		case(COPPER):{ rho= RHO_CU; }; break;
		case(ALUMINIUM):{ rho = RHO_AL; }; break;
	}

	t = M_PI * f * MU_0 * mu_r;
	delta = sqrt(rho/t);

	return(delta);
}

/*
 *
 * WIRE_getMaxGauge(Conductor_Type, I_max, J_max, f)
 *
 * Function to get a wire of maximum SWG based on the following factors:
 *
 *	I_max	: maximum current through the conductor expressed in A.
 *	J_max	: maximum current density for the conductor expressed in J/(mm^2).
 *  f 	 	: Frequency of the signal passing through the wire expressed in Hertz.
 *
 */

SWG_t WIRE_getMaxGauge(conductor_t Conductor_Type, float I_max, float J_max, float f)
{
	float delta;
	float r_max;
	float error;
	float error_min = 100.0f;

	int gauge;
	int gauge_optimal;

	delta = WIRE_getSkinDepth(Conductor_Type, f);

	J_max = 1000.0f * 1000.0f * J_max;

	r_max = I_max/J_max + delta*delta;
	r_max = r_max / ( 2.0f * M_PI * delta );

	for( gauge = 0 ; gauge < 46 ; gauge++ )
	{
		error = r_max*1000.0f - SWG[gauge];

		if( error < 0.0f ) error = -error;

		if( error < error_min )
		{
			error_min = error;
			gauge_optimal = gauge;
		}
	}

	return(gauge_optimal);
}


/*
 *
 * WIRE_getMinGauge(Conductor_Type, I_max, J_max, f)
 *
 * Function to get a wire of maximum SWG based on the following factors:
 *
 *	I_max	: maximum current through the conductor expressed in A.
 *	J_max	: maximum current density for the conductor expressed in J/(mm^2).
 *  f 	 	: Frequency of the signal passing through the wire expressed in Hertz.
 *
 */



SWG_t WIRE_getMinGauge(conductor_t Conductor_Type, float I_max, float J_max, float f)
{
	float delta;
	float error;
	float error_min = 100.0f;

	int gauge;
	int gauge_optimal;

	delta = WIRE_getSkinDepth(Conductor_Type, f);

	for( gauge = 0 ; gauge < 46 ; gauge++ )
	{
		error = delta*1000.0f - SWG[gauge];

		if( error < 0.0f ) error = -error;

		if( error < error_min )
		{
			error_min = error;
			gauge_optimal = gauge;
		}
	}

	return(gauge_optimal);
}


/*
 * WIRE_getParameters(Conductor_Type, I_max, J_max, f, gauge, area_eff, R)
 *
 * Returns the following parametes:
 *
 * equivalent SWG gauge
 * effective cross-section area considering skin effects.
 * equivalent resistance of the wire per meter.
 *
 */

void WIRE_getParameters(conductor_t Conductor_Type, float radius, float f, float* delta, float* A_c, float* r)
{
	float rho;

	switch( Conductor_Type )
	{
		case(COPPER):{ rho= RHO_CU; }; break;
		case(ALUMINIUM):{ rho = RHO_AL; }; break;
	}

	*delta = WIRE_getSkinDepth(Conductor_Type,f);
	*A_c   = M_PI * ( 2.0f * radius * ( *delta ) - (*delta) * (*delta) );
	*r     = rho/(*A_c);
}

#endif /* PASSIVE_WIRE_H_ */
