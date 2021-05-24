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
	
	mpz_t chiffré, message_clair, g, N;
	mpz_inits(chiffré, message_clair, g, N);
	
	string vote("");
	while((vote != "0") && (vote != "1")){
		
		cout << "Choix du candidat?(0/1)" << endl;
		cin >> vote;
	}
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
                if(mot == "g")
                { 
                    monFlux >> mot;
                    mpz_set_str(g,mot.c_str(),10);
                }
            }
           
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }

        monFlux.close();

	mpz_set_str(message_clair,vote.c_str(),10);
	
	Encryption(chiffré,message_clair,g,N);
	gmp_printf("Chiffré = %Zd\n", chiffré);
	mpz_clears(chiffré,message_clair,g,N);
	return 0;
}

