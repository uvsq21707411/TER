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
	float temps;
    clock_t time1, time2;
    time1 = clock();

    gmp_randstate_t state;
	gmp_randinit_default(state);
	srand(time(NULL));
	unsigned long seed = rand()%1999;    
	gmp_randseed_ui(state,seed);
	
	int nb_parts = 10;
	mpz_t N,p,q,phi_n,m,beta,a,b,g,SK,theta; 
	mpz_t ai[nb_parts];
	mpz_t ci[nb_parts],si[nb_parts]; 
	
	for(int i = 0; i < nb_parts+1; ++i){
		mpz_init(ci[i]);
		mpz_init(si[i]);
	}
	generate_PK(N,phi_n,p,q,m,beta,g,a,b,theta);
	generate_SK_share_table_ai(ai,beta,m,N,SK,nb_parts);

	mpz_t f_x;
	mpz_init(f_x);

	mpz_t M,C,M_prime;
	mpz_init(M);
	mpz_init(C);
	mpz_init(M_prime);

	cout<<"Encryption\n";
	//M=0,1
	mpz_set_ui(M,1);
	
	Encryption(C,M,g,N);
	gmp_printf ("Value main M: %Zd\n",M);
	gmp_printf ("Value main C: %Zd\n",C);

    //génération des partial decryption cj(share)
    for(int i = 0; i <nb_parts+1; ++i){
		share_ci(ci[i],C,nb_parts,i,ai,nb_parts,si[i],N,m);
		gmp_printf ("Share c%d: %Zd\n",i,ci[i]);
	}
    //delta
	unsigned long int delta = factorial(nb_parts);

	cout<<"Combining decryption\n";
	//déchiffrement
	combining_decryption(M_prime,ci,N,theta,delta,si,nb_parts);
	gmp_printf ("M_prime = %Zd\n",M_prime);

	// Libération de la mémoire
	mpz_clear(N);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi_n);
    mpz_clear(m);
	mpz_clear(beta);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(g);
    mpz_clear(SK);
    mpz_clear(theta);
   	mpz_clear(f_x);
    mpz_clear(M);
    mpz_clear(C);

    for(int i = 0 ; i < nb_parts+1; i++){  
		mpz_clear(ai[i]);
		mpz_clear(ci[i]);
		mpz_clear(si[i]);
    }
	

    time2 = clock();
    temps = (float)(time2-time1)/CLOCKS_PER_SEC;
    cout<<"Temps d'exécution :"<<temps<<"s"<<endl;
	return 0;
}

// make AAA et ./AAA
// ou make

// https://gmplib.org/#DOWNLOAD
// https://gmplib.org/gmp-man-6.2.1.pdf
