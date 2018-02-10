#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "memoryusage.h"
#include <time.h>
#include <cmath>

int main(int argn, char **argv)
{
        vector<int> age ;
	int tmp ;
        sfmt_t sfmtSeed ;
        int N ;
        int c1, c2, c3, c4 ;
        c1 = c2 = c3 = c4 = 0;

        sfmt_init_gen_rand(&sfmtSeed, (unsigned)time(NULL)*1234567) ;

        FILE *fp = fopen("./Flickr_Age.txt", "r") ;
        FILE *fp1 = fopen("./Flickr_A.txt", "a+") ;

	while(fscanf(fp, "%d", &tmp) == 1)
		age.push_back(tmp) ;

	N = age.size() ;
	cout << N << endl; 

        for(int i=0; i<N; i++)
        {
		tmp = age[i] ;
                if(tmp <= 25)
                {
      		        double p = sfmt_genrand_real1(&sfmtSeed) ;
			if (p <= 0.8)
			{
				fprintf(fp1, "%d\n", 1) ;
				c1 += 1 ;
			}
			else
                        	fprintf(fp1, "%d\n", 0) ;
                }
                else if(tmp <= 40)
                {
      		        double p = sfmt_genrand_real1(&sfmtSeed) ;
			if (p <= 0.5)
			{
				fprintf(fp1, "%d\n", 1) ;
				c2 += 1 ;
			}
			else
                        	fprintf(fp1, "%d\n", 0) ;
                }
                else if(tmp <= 55)
                {
      		        double p = sfmt_genrand_real1(&sfmtSeed) ;
			if (p <= 0.5)
			{
				fprintf(fp1, "%d\n", 1) ;
				c3 += 1 ;
			}
			else
                        	fprintf(fp1, "%d\n", 0) ;
                }
                else if(tmp <= 70)
                { 
      		        double p = sfmt_genrand_real1(&sfmtSeed) ;
			if (p <= 0.2)
			{
				fprintf(fp1, "%d\n", 1) ;
				c4 += 1 ;
			}
			else
                        	fprintf(fp1, "%d\n", 0) ;
                }
        }
        fclose(fp) ;
	fclose(fp1) ;

	int C = c1 + c2 + c3 + c4 ;

        cout << "10~25: " << c1*1.0 / C << endl;
        cout << "26~40: " << c2*1.0 / C << endl;
        cout << "41~55: " << c3*1.0 / C << endl;
        cout << "56~70: " << c4*1.0 / C << endl;
        return 0 ;
}
