#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double
median7 (double yy, double kaa, double koo, double nee, double vii, double kuu,
				 double see)
{
	double array[7];
	double tmp;
	int i, j;

	array[0] = yy;
	array[1] = kaa;
	array[2] = koo;
	array[3] = nee;
	array[4] = vii;
	array[5] = kuu;
	array[6] = see;

	for (j = 0; j < 7 - 1; j++)
		for (i = 0; i < 7 - 1 - j; i++) {
			if (array[i] > array[i + 1]) {
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
		}
	return (array[3]);
}

double
median6 (double yy, double kaa, double koo, double nee, double vii, double kuu)
{
	double array[6];
	double tmp;
	int i, j;

	array[0] = yy;
	array[1] = kaa;
	array[2] = koo;
	array[3] = nee;
	array[4] = vii;
	array[5] = kuu;

	for (j = 0; j < 6 - 1; j++)
		for (i = 0; i < 6 - 1 - j; i++) {
			if (array[i] > array[i + 1]) {
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
		}
	return (array[3]);
}

double
median5 (double yy, double kaa, double koo, double nee, double vii)
{
	double array[5];
	double tmp;
	int i, j;

	array[0] = yy;
	array[1] = kaa;
	array[2] = koo;
	array[3] = nee;
	array[4] = vii;


	for (j = 0; j < 5 - 1; j++)
		for (i = 0; i < 5 - 1 - j; i++) {
			if (array[i] > array[i + 1]) {
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
		}
	return (array[2]);
}

double
median4 (double yy, double kaa, double koo, double nee)
{
	double array[4];
	double tmp;
	int i, j;

	array[0] = yy;
	array[1] = kaa;
	array[2] = koo;
	array[3] = nee;


	for (j = 0; j < 4 - 1; j++)
		for (i = 0; i < 4 - 1 - j; i++) {
			if (array[i] > array[i + 1]) {
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
		}
	return (array[2]);
}


double
median3 (double yy, double kaa, double koo)
{
	double array[3];
	double tmp;
	int i, j;

	array[0] = yy;
	array[1] = kaa;
	array[2] = koo;


	for (j = 0; j < 3 - 1; j++)
		for (i = 0; i < 3 - 1 - j; i++) {
			if (array[i] > array[i + 1]) {
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
		}
	return (array[1]);
}
