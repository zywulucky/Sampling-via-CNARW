#include "sfmt/SFMT.h"
#include "fileProcess.h"
#include "memoryusage.h"
#include <time.h>
#include <cmath>

int main(int argn, char **argv)
{
        vector<vector<int> > graph ;
	sfmt_t sfmtSeed ;
        int N ;
	int c1, c2, c3, c4 ;
	c1 = c2 = c3 = c4 = 0;

        sfmt_init_gen_rand(&sfmtSeed, (unsigned)time(NULL)*1234567) ;

        string path;
        for(int i=0; i<argn; i++)
                if(argv[i] == string("-dataset")) 
			path = string(argv[i+1]) ;

        if(path == "")
                cout<< "argument dataset missing" <<endl ;

        graph = readFile(path.c_str(), N) ;

        FILE *fp = fopen("./Flickr_Age.txt", "a+") ;

        for(int i=0; i<N; i++)
        {
		double p = sfmt_genrand_real1(&sfmtSeed) ;
		if(p < 0.3)
		{
			int age = sfmt_genrand_uint32(&sfmtSeed) % 16 + 10 ;
			fprintf(fp, "%d\n", age) ;
			c1 += 1 ;
		}
		else if(p < 0.7)
		{
			int age = sfmt_genrand_uint32(&sfmtSeed) % 15 + 26 ;
			fprintf(fp, "%d\n", age) ;
			c2 += 1 ;
		}
		else if(p < 0.9)
		{
			int age = sfmt_genrand_uint32(&sfmtSeed) % 15 + 41 ;
			fprintf(fp, "%d\n", age) ;
			c3 += 1 ;
		}
		else if(p < 1.0)
		{
			int age = sfmt_genrand_uint32(&sfmtSeed) % 15 + 56 ;
			fprintf(fp, "%d\n", age) ;
			c4 += 1 ;
		}
        }
	fclose(fp) ;
	
	cout << "10~25: " << c1*1.0 / N << endl;
	cout << "26~40: " << c2*1.0 / N << endl;
	cout << "41~55: " << c3*1.0 / N << endl;
	cout << "56~70: " << c4*1.0 / N << endl;
        return 0 ;
}
