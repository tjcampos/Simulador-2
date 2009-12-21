#include "ag.h"
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iostream>
#include <cmath>

Ag::Ag(int nbots, int nsensors, int noutputs){
	cromossomos = (int **) malloc(sizeof(int*) * nbots);
	this->nbots = nbots;
	this->nsensors = nsensors;
	this->ngenes = pow(2,nsensors);
	this->noutputs = noutputs;
	fitness = (int*) calloc(nbots, sizeof(int*));
	
	for (int i=0; i < nbots; i++)
		cromossomos[i] = (int*) calloc(ngenes, sizeof(int));
}

Ag::~Ag(){
	for (int i=0; i < nbots; i++)
		free(cromossomos[i]);
	free(fitness);
	free(cromossomos);
}

int Ag::updateFitness(int id, int p){
	return fitness[id] += p;
}

void Ag::resetFitness(int v){
	memset(fitness, v, nbots*sizeof(int));
}

void Ag::crossover(int r1, int r2){
	for (int i=0; i < ngenes; i++)
		cromossomos[r1][i] = (rand()%2)?(cromossomos[r1][i]):(cromossomos[r2][i]);
}

void Ag::mutation(int id, int mutRate){
	for (int i=0; i < ngenes; i++)
		cromossomos[id][i] = (rand()%100 < mutRate)?(rand()%noutputs):(cromossomos[id][i]);
}

void Ag::randomize(int id){
	for (int i=0; i < ngenes; i++)
		cromossomos[id][i] = rand()%noutputs;
}

void Ag::randomize(){
	for (int i=0; i < nbots; i++)
		randomize(i);
}

void Ag::newPop(){
	int max = 0;
	int sum = fitness[0];
	int *tmp;

	for (int i=1; i < nbots; i++){
		if (fitness[i] > fitness[max])
			max = i;
		sum += fitness[i];
	}
	cout << "Melhor: " << fitness[max] << " Media: " << sum/nbots << endl;
	
	tmp = cromossomos[max];
	cromossomos[max] = cromossomos[0];
	cromossomos[0] = tmp;
	
	for (int i=1; i < nbots; i++){
		crossover(i, 0);
		mutation(i);
	}
}

int Ag::getAction(int id, vector<int> sensors){
	assert(nsensors == (int) sensors.size());
	int pos=0;
	
	for(int i=0; i < nsensors; i++)
		pos += (sensors[i] > DET_LEVEL)?(pow(2,i)):(0);
	
	return cromossomos[id][pos];
}
