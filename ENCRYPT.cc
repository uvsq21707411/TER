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
	string vote("");
	while((vote != "0") && (vote != "1")){
		
		cout << "Choix du candidat?(0/1)" << endl;
		cin >> vote;
	}
	mpz_t chiffré, message_clair,g,N;
	mpz_init_set_str(message_clair,vote);
	mpz_inits(chiffré,g,N);
	//Encryption(chiffré,message_clair,g,N);
	mpz_clears(chiffré,message_clair,g,N);
	return 0;
}

