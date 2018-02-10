/**
 * @file DistributionNormal
 * This file contains the functions of the normal distribution.
 *
 * @brief Implementation of the normal distribution.
 *
 */

#include <cmath>

#include "DistributionNormal.h"


/*!
 * This function calculates the cumulative probability 
 * for a standard normally-distributed random variable.
 *
 * \brief Standard normal cumulative probability.
 * \param x is the normal random variable. 
 * \return Returns the cumulative probability.
 * \see Adams, A. G. 1969. Areas under the normal curve. Cojputer J. 12:197-198.
 * \throws Does not throw an error.
 */
double RbStatistics::Normal::cdf(double x) {
    
	double cdf;
	double q;
    
	/* |X| <= 1.28 */
	if ( fabs(x) <= 1.28 )
        {
		double a1 = 0.398942280444;
		double a2 = 0.399903438504;
		double a3 = 5.75885480458;
		double a4 = 29.8213557808;
		double a5 = 2.62433121679;
		double a6 = 48.6959930692;
		double a7 = 5.92885724438;
		double y = 0.5 * x * x;
		q = 0.5 - fabs(x) * ( a1 - a2 * y / ( y + a3 - a4 / ( y + a5 + a6 / ( y + a7 ) ) ) );
        }
	else if ( fabs(x) <= 12.7 )
        {
		double b0 = 0.398942280385;
		double b1 = 3.8052E-08;
		double b2 = 1.00000615302;
		double b3 = 3.98064794E-04;
		double b4 = 1.98615381364;
		double b5 = 0.151679116635;
		double b6 = 5.29330324926;
		double b7 = 4.8385912808;
		double b8 = 15.1508972451;
		double b9 = 0.742380924027;
		double b10 = 30.789933034;
		double b11 = 3.99019417011;
		double y = 0.5 * x * x;
		q = exp(-y) * b0 / (fabs(x) - b1 + b2 / (fabs(x) + b3 + b4 / (fabs(x) - b5 + b6 / (fabs(x) + b7 - b8 / (fabs(x) + b9 + b10 / (fabs(x) + b11))))));
        }
	else
        {
		q = 0.0;
        }
	if ( x < 0.0 )
        {
		/* negative x */
		cdf = q;
        }
	else
        {
		/* positive x */
		cdf = 1.0 - q;
        }
	return cdf;
}

/*!
 * This function calculates the cumulative probability 
 * for a normally-distributed random variable.
 *
 * \brief Normal cumulative probability.
 * \param mu is the mean parameter of the normal. 
 * \param sigma is the variance parameter of the normal. 
 * \param x is the normal random variable. 
 * \return Returns the cumulative probability.
 * \see Adams, A. G. 1969. Areas under the normal curve. Cojputer J. 12:197-198.
 * \throws Does not throw an error.
 */
double RbStatistics::Normal::cdf(double mu, double sigma, double x) {
    
	double cdf;
	double q;
	double z = (x - mu) / sigma;
    
	/* |X| <= 1.28 */
	if ( fabs(z) <= 1.28 )
        {
		double a1 = 0.398942280444;
		double a2 = 0.399903438504;
		double a3 = 5.75885480458;
		double a4 = 29.8213557808;
		double a5 = 2.62433121679;
		double a6 = 48.6959930692;
		double a7 = 5.92885724438;
		double y = 0.5 * z * z;
		q = 0.5 - fabs(z) * ( a1 - a2 * y / ( y + a3 - a4 / ( y + a5 + a6 / ( y + a7 ) ) ) );
        }
	else if ( fabs(z) <= 12.7 )
        {
		double b0 = 0.398942280385;
		double b1 = 3.8052E-08;
		double b2 = 1.00000615302;
		double b3 = 3.98064794E-04;
		double b4 = 1.98615381364;
		double b5 = 0.151679116635;
		double b6 = 5.29330324926;
		double b7 = 4.8385912808;
		double b8 = 15.1508972451;
		double b9 = 0.742380924027;
		double b10 = 30.789933034;
		double b11 = 3.99019417011;
		double y = 0.5 * z * z;
		q = exp(-y) * b0 / (fabs(z) - b1 + b2 / (fabs(z) + b3 + b4 / (fabs(z) - b5 + b6 / (fabs(z) + b7 - b8 / (fabs(z) + b9 + b10 / (fabs(z) + b11))))));
        }
	else
        {
		q = 0.0;
        }
	if ( z < 0.0 )
        {
		/* negative x */
		cdf = q;
        }
	else
        {
		/* positive x */
		cdf = 1.0 - q;
        }
	return cdf;
}

