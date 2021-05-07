
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gmp.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "encryption.h"

// mpz_t N, mpz_t phi_n, mpz_t p, mpz_t q, mpz_t m, mpz_t beta, mpz_t g, mpz_t a, mpz_t b, mpz_t theta
void generate_PK(mpz_t N, mpz_t phi_n, mpz_t p, mpz_t q, mpz_t m, mpz_t beta, mpz_t g, mpz_t a, mpz_t b, mpz_t theta){
	mpz_t p_1,q_1,p_prime,q_prime,N_square,SK;
	gmp_randstate_t state;
	gmp_randinit_default(state);
	srand(time(NULL));
	unsigned long seed = rand()%1999;    
	gmp_randseed_ui(state,seed);

	mpz_t base,max;
	unsigned long exp;
	mpz_init_set_str(base,"2",10);
	mpz_init(max);
	exp = 80 + rand()%20;
	mpz_pow_ui(max, base, exp);

	mpz_t gcd_N_phi_n;
	mpz_init(gcd_N_phi_n);
	mpz_init(N);
	mpz_init(m);
	mpz_init(p_1);
	mpz_init(q_1);
	mpz_init(phi_n);

	int test_gcd_N_phi_n = 0;
	while(test_gcd_N_phi_n == 0){
		// Génération d'un premier p
		mpz_init(p);
		mpz_init(p_prime);
		int test_p = 0;
		while(test_p==0){
			mpz_urandomm (p_prime,state,max);
			mpz_mul_ui(p,p_prime,2);
			mpz_add_ui(p,p,1);
			int is_prime_p = mpz_probab_prime_p(p,10000);
			if(is_prime_p == 1 || is_prime_p == 2){
				// cout<<"is_prime_p: "<<is_prime_p<<endl;
				// gmp_printf ("%sValue of p_: %Zd\n","", p_prime);
				// gmp_printf ("%sValue of p: %Zd\n","", p);
				test_p = 1;
			}
		}		
		// Génération d'un premier q
		mpz_init(q);
		mpz_init(q_prime);
		int test_q = 0;
		while(test_q==0){
			mpz_urandomm (q_prime,state,max);
			mpz_mul_ui(q,q_prime,2);
			mpz_add_ui(q,q,1);
			int is_prime_q = mpz_probab_prime_p(q,10000);
			if(is_prime_q == 1 || is_prime_q == 2){
				// cout<<"is_prime_q: "<<is_prime_q<<endl;
				// gmp_printf ("%sValue of q_: %Zd\n","", q_prime);
				// gmp_printf ("%sValue of q: %Zd\n","", q);
				test_q = 1;
			}
		}	
		// Obtention de N=p*q, phi_n,...
		mpz_mul(N,p,q);
		mpz_mul(m,p_prime,q_prime);
		mpz_sub_ui(p_1,p,1);
		mpz_sub_ui(q_1,q,1);
		mpz_mul(phi_n,p_1,q_1);
		mpz_gcd(gcd_N_phi_n,N,phi_n);
		if(mpz_cmp_ui(gcd_N_phi_n,1) == 0){
			test_gcd_N_phi_n = 1;
		}
	}
	// Génération de beta dans ZN
	int test_gcd_beta_N = 0;
	mpz_t gcd_beta_N;
	mpz_init(gcd_beta_N);
	mpz_init(beta);
	while(test_gcd_beta_N == 0){
		mpz_urandomm (beta,state,N);
		mpz_gcd(gcd_beta_N,beta,N);
		if(mpz_cmp_ui(gcd_beta_N,1) == 0){
			test_gcd_beta_N = 1;
		}
	}
	// Génération de a dans ZN
	int test_gcd_a_N = 0;
	mpz_t gcd_a_N;
	mpz_init(gcd_a_N);
	mpz_init(a);
	while(test_gcd_a_N == 0){
		mpz_urandomm (a,state,N);
		mpz_gcd(gcd_a_N,a,N);
		if(mpz_cmp_ui(gcd_a_N,1) == 0){
			test_gcd_a_N = 1;
		}
	} 
	// Génération de b dans ZN 
	int test_gcd_b_N = 0;
	mpz_t gcd_b_N;
	mpz_init(gcd_b_N);
	mpz_init(b);
	while(test_gcd_b_N == 0){
		mpz_urandomm (b,state,N);
		mpz_gcd(gcd_b_N,b,N);
		if(mpz_cmp_ui(gcd_b_N,1) == 0){
			test_gcd_b_N = 1;
		}
	} 
	// Calcul de g=(1+N)^a*b^N % N²
	mpz_t N__1,N__1_a,b_N;
	mpz_init(N__1);
	mpz_init(N_square);
	mpz_init(g);
	mpz_init(N__1_a);
	mpz_init(b_N);
	mpz_add_ui(N__1,N,1);
	mpz_mul(N_square,N,N);
	mpz_powm(N__1_a,N__1,a,N_square);
	mpz_powm(b_N,b,N,N_square);
	mpz_mul(g,N__1_a,b_N);
	mpz_mod(g,g,N_square);

	// PUBLIC KEY PART theta , do L(g^m*beta) later, ambeta mod N below
	mpz_t am;
	mpz_init(am);
	mpz_init(theta);
	mpz_mul(am,a,m);
	mpz_mul(theta,am,beta);
	mpz_mod(theta,theta,N);
}

// ai[] contient les valeurs des bouts de clés 
void generate_SK_share_table_ai(mpz_t ai[], mpz_t beta, mpz_t m, mpz_t N, mpz_t SK, int nb_parts){
	gmp_randstate_t state;
	gmp_randinit_default(state);
	srand(time(NULL));
	unsigned long seed = rand()%1999;    
	gmp_randseed_ui(state,seed);
	mpz_init(SK);
	mpz_mul(SK,beta,m);
	int t = nb_parts; // t nombre de parts de SK
	// Tableau ai[] stockant les parts de SK
	mpz_init(ai[0]);
	mpz_set(ai[0],SK);
	mpz_t N_0_m_1,m_1;
	mpz_init(m_1);
	mpz_sub_ui(m_1,m,1);
	mpz_init(N_0_m_1);
	mpz_mul(N_0_m_1,N,m_1);
	for (int i=1;i<nb_parts; ++i){
		mpz_init(ai[i]); 
		mpz_urandomm (ai[i],state,N_0_m_1);	
	}
	// ai[] contient les valeurs des bouts de clés 
}

// L(u) = (u-1)/N
void L_function(mpz_t lu, mpz_t u, mpz_t N){
	// to do ?: check u<N² and u = 1 mod N
	mpz_t u_1;
	mpz_init(u_1);
	mpz_sub_ui(u_1,u,1);
	// Il faut trouver lz moyen de bien faire la division, pas avec mpz_divexact qui suppose que M divise den
	mpz_divexact(lu,u_1,N);
	//gmp_printf ("Value divexact: %Zd\n",lu);
	// maybe implement div..
	//div(lu,u_1,N); 
	//mpz_invert();
}

// Calcule f_x = f(num_server) = si grâce à ai[] tableau des bouts de clé
void F_shamir(mpz_t f_x, unsigned long int num_server,mpz_t ai[], unsigned long int size_ai, mpz_t N, mpz_t m){
	mpz_t tmp,Nm;
	mpz_init(tmp);
	mpz_init(Nm);
	mpz_mul(Nm,N,m);
	unsigned long int prod;
	for(unsigned long int i = 0; i < size_ai; ++i){
		prod = pow(num_server,i); 
		mpz_mul_ui(tmp,ai[i],prod);
		mpz_add(f_x,f_x,tmp);
	}
	mpz_powm_ui(f_x,f_x,1,Nm);
	//gmp_printf ("Value of F(%ld): %Zd\n",num_server, f_x);
}

// Multicandidate: generate M = A^j, j:chosen candidate, A=nb_voters+1 > nb_voters
void Generate_vote(mpz_t M, unsigned long int candidate, mpz_t nb_voters){
	mpz_t A;
	mpz_init(A);
	mpz_add_ui(A,nb_voters,1);
	mpz_pow_ui(M,A,candidate);
}
// Après déchiffrement, décomposer la somme des votes en base A
// Obtenir v0+v1*A+...+ vk−1*A^k−1, où vj est le nombre de votes pour le candidat j, vj=<l<A


// Fonctions de Key Generation


// C contient le chiffré du vote M
void Encryption(mpz_t C, mpz_t M, mpz_t g, mpz_t N){
	mpz_t x,N_square,gM,xN,res;
	mpz_init(gM);
	mpz_init(xN);
	mpz_init(x);
	mpz_init(N_square);
	mpz_init(res);
	mpz_mul(N_square,N,N);

	int test_x = 0;
	mpz_t gcd_x_N;
	mpz_init(gcd_x_N);

	//TO DO: Check if x is prime ?
	gmp_randstate_t state;
	gmp_randinit_default(state);
	srand(time(NULL));
	unsigned long seed = rand()%1999;    
	gmp_randseed_ui(state,seed);
	mpz_urandomm (x,state,N);
	
	mpz_powm(gM,g,M,N_square);
	mpz_powm(xN,x,N,N_square);
	mpz_mul(res,gM,xN);
	mpz_mod(C,res,N_square);
	//gmp_printf ("Value of C: %Zd\n",C);
}

// ci contient la partial decryption share ci du i^th player
void share_ci(mpz_t ci, mpz_t c, unsigned long int nb_servers, unsigned long int num_server,mpz_t ai[], unsigned long int size_ai, mpz_t si, mpz_t N, mpz_t m){
	mpz_t delt, delta_si, delt_si_2, N_squ;
	F_shamir(si, num_server, ai, size_ai, N, m);
	//si contient le share key du i^th player
	mpz_init(delt);
	mpz_init(delta_si);
	mpz_init(delt_si_2);
	mpz_init(N_squ);
	mpz_fac_ui(delt,nb_servers);
	mpz_mul(delta_si,delt,si);
	mpz_mul_ui(delt_si_2,delta_si,2);
	mpz_mul(N_squ,N,N);
	mpz_powm(ci,c,delt_si_2,N_squ);
}

// Utilisée dans combining_decryption
unsigned long int mu_0j_S(unsigned long int delta, unsigned long int j, unsigned long int S){
	unsigned long int res = delta;
	for(unsigned long int j_ = 1; j_ < S+1; ++j_){
		if(j_ != j) res *= j_/(j_-j);
		else;
	}
	return res;
}

// Utilise toutes les partial decryption cj pour retrouver M
// M devra être décomposé en base A pour faire le décompte des votes
// v0+v1*A+...+ vk−1*A^k−1, où vj est le nombre de votes pour le candidat j, vj=<l<A
void combining_decryption(mpz_t M, mpz_t cj[], mpz_t N, mpz_t theta, unsigned long int delta, unsigned long int j, unsigned long int S){
	unsigned long int exp,delta_2;
	mpz_t N_2, den, prod, tmp; 
	mpz_init(N_2);
	mpz_mul(N_2,N,N);
	delta_2 = pow(delta,2);
	mpz_mul_ui(den,theta,delta_2);
	mpz_mul_ui(den,den,4);
	for(unsigned long int j = 1; j < S+1; ++j){
		exp = mu_0j_S(delta,j,S);
		exp *= 2;
		mpz_powm_ui(tmp,cj[j],exp,N_2);
		mpz_mul(prod,prod,tmp);
	}
	// Apply L à prod
	L_function(M,prod,N);
	// Diviser le résultat par den, apply mod N
	// Il faut trouver lz moyen de bien faire la division, pas avec mpz_divexact qui suppose que M divise den
	mpz_divexact(M,M,den);
	mpz_mod(M,M,N);

}