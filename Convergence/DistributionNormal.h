/**
 * @file DistributionNormal
 * This file contains the functions of the normal distribution.
 *
 * @brief Implementation of the normal distribution.
 *
 */


#ifndef DistributionNormal_H
#define DistributionNormal_H

    namespace RbStatistics {
    
        namespace Normal {
        
            double                      cdf(double x);                                                          /*!< Normal(0,1) cumulative probability */
            double                      cdf(double mu, double sigma, double x);                                 /*!< Normal(mu,sigma) cumulative probability */
	    }
	}

#endif
