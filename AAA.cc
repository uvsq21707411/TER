#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gmp.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "encryption.h"

using namespace std;

int main(){
	float temps;
    clock_t time1, time2;
    time1 = clock();

	mpz_t N,p,q,phi_n,m,beta,a,b,g,SK,theta; //p_prime,q_prime : ne sont pas utilisés
	mpz_t ai[99];
	int nb_parts = 5;
	generate_PK(N,phi_n,p,q,m,beta,g,a,b,theta);
	generate_SK_share_table_ai(ai,beta,m,N,SK,nb_parts);
	/*gmp_printf ("Value N: %Zd\n",N);
	gmp_printf ("Value phi_n: %Zd\n",phi_n);
    gmp_printf ("Value m: %Zd\n",m);
	gmp_printf ("Value p: %Zd\n",p);
	gmp_printf ("Value q: %Zd\n",q);
	gmp_printf ("Value beta: %Zd\n",beta);
	gmp_printf ("Value a: %Zd\n",a);
	gmp_printf ("Value b: %Zd\n",b);
	gmp_printf ("Value g: %Zd\n",g);
	gmp_printf ("Value SK: %Zd\n",SK);
	gmp_printf ("Value theta: %Zd\n",theta);
	for(int i = 0; i <nb_parts; ++i){
		gmp_printf ("Value a%d: %Zd\n",i,ai[i]);
	}*/

	mpz_t f_x;
	mpz_init(f_x);
	//F(4) = share si of 4th server 
	F_shamir(f_x,4,ai,nb_parts,N,m);

	mpz_t M,C;
	mpz_init(M);
	mpz_init(C);
	//mpz_urandomm(M,state,N);
	Encryption(C,M,g,N);

	time2 = clock();
    temps = (float)(time2-time1)/CLOCKS_PER_SEC;
    cout<<"Temps d'exécution :"<<temps<<"s"<<endl;
   
   //combining_decryption(C,a,N,theta,delta,j,S);
    
   //Test fonction L
   
  //θ = L(g^mβ) = amβ mod N
	mpz_t Test_L, Test_L_prime, g_m_beta, m_beta,N_2;
	mpz_init(Test_L);
	mpz_init(Test_L_prime);
	mpz_init(g_m_beta);
	mpz_init(m_beta);
	mpz_init_set(N_2,N);
	mpz_mul(N_2,N_2,N);
	
	//m * beta
	mpz_mul(m_beta, m, beta);
	gmp_printf ("m: %Zd\nbeta:%Zd \nm_beta :%Zd\n",m,beta,m_beta);
	//mpz_mod(m_beta,m_beta,N);
	//g puissance m*beta
	mpz_powm(g_m_beta, g, m_beta,N_2);
    gmp_printf ("gmbeta: %Zd\n",g_m_beta);
	//L(gmβ)
	L_function(Test_L, g_m_beta, N);
	


	//amβ mod N
	mpz_set(Test_L_prime,a);
	mpz_mul(Test_L_prime,Test_L_prime,m_beta);
	mpz_mod(Test_L_prime,Test_L_prime,N);
	
	gmp_printf ("Test_L: %Zd \nTest_L_prime : %Zd\n",Test_L, Test_L_prime);
	if(mpz_cmp(Test_L,Test_L_prime) == 0) cout<<"égalité";
	else cout<<"différents";
	cout<<"\n";
    

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
	
	mpz_clear(Test_L);
	mpz_clear(Test_L_prime);
	mpz_clear(g_m_beta);
	mpz_clear(m_beta);
	mpz_clear(N_2);

    for(int i = 0 ; i < 5; i++){ // <- Les 5 premiers éléments sont alloués actuellement 
		mpz_clear(ai[i]);
    }
/* 	mpz_clear(p_prime);
    mpz_clear(q_prime);
   */
	return 0;
}

// make AAA et ./AAA
// ou make

// https://gmplib.org/#DOWNLOAD
// https://gmplib.org/gmp-man-6.2.1.pdf
