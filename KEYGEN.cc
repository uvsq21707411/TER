#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <gmp.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "encryption.h"

using namespace std;

int main(int argc,char **argv){
	mpz_t N,p,q,phi_n,m,beta,a,b,g,theta; 
    generate_PK(N,phi_n,p,q,m,beta,g,a,b,theta);
    
    ofstream monFlux("/home/user/Bureau/TER/KEYGEN.txt");
    char * str = NULL; //ne reconnait pas les string en c++

    if(monFlux)    
    {
        monFlux << "N "<< mpz_get_str(str,10,N)<<endl;
        monFlux << "phi_n "<< mpz_get_str(str,10,phi_n)<<endl;
        monFlux << "p "<< mpz_get_str(str,10,p)<<endl;
        monFlux << "q "<< mpz_get_str(str,10,q)<<endl;
        monFlux << "m "<< mpz_get_str(str,10,m)<<endl;
        monFlux << "beta "<< mpz_get_str(str,10,beta)<<endl;
        monFlux << "g "<< mpz_get_str(str,10,g)<<endl;
        monFlux << "a "<< mpz_get_str(str,10,a)<<endl;
        monFlux << "b "<< mpz_get_str(str,10,b)<<endl;
        monFlux << "theta "<< mpz_get_str(str,10,theta)<<endl;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

    delete(str);
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
