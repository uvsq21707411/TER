#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gmp.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "encryption.h"

using namespace std;

int main(int argc,char **argv){
	mpz_t N,p,q,phi_n,m,beta,a,b,g,theta; 
    generate_PK(N,phi_n,p,q,m,beta,g,a,b,theta);



    mpz_clear(N);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi_n);
    mpz_clear(m);
	mpz_clear(beta);
    mpz_clear(a);
    mpz_clear(b);

	return 0;
}
