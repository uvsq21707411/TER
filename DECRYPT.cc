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

int main(){
    mpz_t N,p,q,phi_n,m,beta,a,b,g,theta; 
    mpz_inits(N,p,q,phi_n,m,beta,a,b,g,theta); 
    //RECUPERER LES CLES POUR LES OPERAIONS
    ifstream monFlux("/home/user/Bureau/TER/KEYGEN.txt");  //Ouverture d'un fichier en lecture

        if(monFlux)
        {
            string mot;
            while(monFlux.eof() == false){
               
                monFlux >> mot;
                if(mot == "N")
                { 
                    monFlux >> mot;
                    mpz_set_str(N,mot.c_str(),10);
                }
                if(mot == "p")
                { 
                    monFlux >> mot;
                    mpz_set_str(p,mot.c_str(),10);
                }
                if(mot == "q")
                { 
                    monFlux >> mot;
                    mpz_set_str(q,mot.c_str(),10);
                }
                if(mot == "phi_n")
                { 
                    monFlux >> mot;
                    mpz_set_str(phi_n,mot.c_str(),10);
                }
                if(mot == "m")
                { 
                    monFlux >> mot;
                    mpz_set_str(m,mot.c_str(),10);
                }
                if(mot == "beta")
                { 
                    monFlux >> mot;
                    mpz_set_str(beta,mot.c_str(),10);
                }
                if(mot == "a")
                { 
                    monFlux >> mot;
                    mpz_set_str(a,mot.c_str(),10);
                }
                if(mot == "b")
                { 
                    monFlux >> mot;
                    mpz_set_str(b,mot.c_str(),10);
                }
                if(mot == "g")
                { 
                    monFlux >> mot;
                    mpz_set_str(g,mot.c_str(),10);
                }
                if(mot == "theta")
                { 
                    monFlux >> mot;
                    mpz_set_str(theta,mot.c_str(),10);
                }
            }
           
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }

        monFlux.close();

    gmp_printf ("Value main N: %Zd\n",N);
    //RECUPERER TUPLE VIA LA DB EN SQL


    //FAIRE LE PRODUIT DE TOUS LES VOTES 
    //COMPTER EN RETIRANT 1 A CHAQUE ITERATION

    mpz_clear(N);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi_n);
    mpz_clear(m); 
    mpz_clear(beta);mpz_clear(a);
    mpz_clear(b);
    mpz_clear(g);
    mpz_clear(theta);
	return 0;
}

