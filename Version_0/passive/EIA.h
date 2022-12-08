

/*
 *
 * 	Holds standard EIA coefficients.
 *
 */

#ifndef PASSIVE_EIA_H_
#define PASSIVE_EIA_H_

typedef enum{
	EIA_STANDARD_E3 = 3,
	EIA_STANDARD_E6 = 6,
	EIA_STANDARD_E12 = 12,
	EIA_STANDARD_E24 = 24,
	EIA_STANDARD_E48 = 48,
	EIA_STANDARD_E96 = 96
}EIA_standard;

float EIA_STANDARD_E3_SET[3] = { 1.00f, 2.20f, 4.70f };

float EIA_STANDARD_E6_SET[6] = { 1.00f, 1.50f, 2.20f, 3.30f, 4.70f, 6.80f };

float EIA_STANDARD_E12_SET[12] =
{
	1.00f, 1.20f, 1.50f, 1.80f, 2.20f, 2.70f, 3.30f, 3.90f, 4.70f, 5.60f, 6.80f, 8.20f
};

float EIA_STANDARD_E24_SET[24] =
{
	1.00f, 1.10f, 1.20f, 1.30f, 1.50f, 1.60f, 1.80f, 2.00f,	2.20f, 2.40f, 2.70f, 3.00f,
	3.30f, 3.60f, 3.90f, 4.30f, 4.70f, 5.10f, 5.60f, 6.20f, 6.80f, 7.50f, 8.20f, 9.10f
};

float EIA_STANDARD_E48_SET[48] =
{
	1.00f, 1.05f, 1.10f, 1.15f, 1.21f, 1.27f, 1.33f, 1.40f, 1.47f, 1.54f, 1.62f, 1.69f,
	1.78f, 1.87f, 1.96f, 2.05f, 2.15f, 2.26f, 2.37f, 2.49f, 2.61f, 2.74f, 2.87f, 3.01f,
	3.16f, 3.32f, 3.48f, 3.65f, 3.83f, 4.02f, 4.22f, 4.42f, 4.64f, 4.87f, 5.11f, 5.36f,
	5.62f, 5.90f, 6.19f, 6.49f, 6.81f, 7.15f, 7.50f, 7.87f, 8.25f, 8.66f, 9.09f, 9.53f
};

float EIA_STANDARD_E96_SET[96] =
{
	1.00f, 1.02f, 1.05f, 1.07f, 1.10f, 1.13f, 1.15f, 1.18f, 1.21f, 1.24f, 1.27f, 1.30f,
	1.33f, 1.37f, 1.40f, 1.43f, 1.47f, 1.50f, 1.54f, 1.58f, 1.62f, 1.65f, 1.69f, 1.74f,
	1.78f, 1.82f, 1.87f, 1.91f, 1.96f, 2.00f, 2.05f, 2.10f, 2.15f, 2.21f, 2.26f, 2.32f,
	2.37f, 2.43f, 2.49f, 2.55f, 2.61f, 2.67f, 2.74f, 2.80f, 2.87f, 2.94f, 3.01f, 3.09f,
	3.16f, 3.24f, 3.32f, 3.40f, 3.48f, 3.57f, 3.65f, 3.74f, 3.83f, 3.92f, 4.02f, 4.12f,
	4.22f, 4.32f, 4.42f, 4.53f, 4.64f, 4.75f, 4.87f, 4.99f, 5.11f, 5.23f, 5.36f, 5.49f,
	5.62f, 5.76f, 5.90f, 6.04f, 6.19f, 6.34f, 6.49f, 6.65f, 6.81f, 6.98f, 7.15f, 7.32f,
	7.50f, 7.68f, 7.87f, 8.06f, 8.25f, 8.45f, 8.66f, 8.87f, 9.09f, 9.31f, 9.53f, 9.76f
};

#endif /* PASSIVE_EIA_H_ */
