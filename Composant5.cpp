// Composant5.cpp : Defines the exported functions for the DLL application
#include <iostream>
#include "Composant5.h"
#include "Signature.h"
#include "Bloc.h"
#include "Hacheur.h"
#include "FileInterface.h"
#include <string>
#include <vector>

//using namespace std;
// This is the constructor of a class that has been exported.
// see Composant5.h for the class definition
CComposant5::CComposant5()
{
	std::cout << "constructeur" << std::endl;
}
using namespace std;

typedef std::string chars_to_string(unsigned char* source)
{
	return std::string str(source, source + 64);
}

bool CComposant5::verify_transaction_input(TXI* txi) {
	Bloc* b_input = &(findByIndex((txi->nBloc)));
	//Bloc* b_input;

	return (validateSignature(chars_to_string(b_input->tx1.UTXOs[0].hash), chars_to_string(b_input->tx1.UTXOs[0].dest), chars_to_string(txi->signature)))
		;
}

//méthode permettant de la vérification d'une transaction.
//elle retourne true si la transactio répond aux caractéristique définies de false dans le cas contraire.
bool CComposant5::verify_transaction(TXI tx) {
	std::vector<TXI> v = tx->TXIs;
	for (std::size_t i = 0; i<v.size(); ++i) {
		if (!verify_transaction_input(&v[i]))
			return false;
	}
	return true;
}

//méthode permettant de la vérification d'un bloc.
//elle retourne true si le bloc répond aux caractéristique définies de false dans le cas contraire.
bool CComposant5::verify_bloc(Bloc* b, std::string hash_bloc_precedant) {
	return ((chars_to_string(b->previous_hash).compare(hash_bloc_precedant)) && verify_transaction(&(b->tx1)));
}

