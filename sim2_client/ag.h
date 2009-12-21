#ifndef AG_H
#define AG_H
#define DET_LEVEL 5

#include <vector>

using namespace std;

class Ag {
	private:
		int **cromossomos;
		int *fitness;
		int nbots;
		int nsensors;
		int ngenes;
		int noutputs;
	protected:
		//faz crossover de r1 e r2 e atribui em r1
		void crossover(int r1, int r2);
		//mutRate é a porcentagem de ocorrer uma mutação
		void mutation(int id, int mutRate=10);
	public:
		/*
		 * Construtor que cria os vetores para os cromossomos
		 */
		Ag(int nbots, int nsensors=3, int noutputs=3);
		~Ag();
		
		/*
		 * Sorteia valores aleatorios para os cromossomos de robo de id 'id'
		 */
		void randomize(int id);
		/*
		 * Sorteia valores aleatorios para os cromossomos de todos os robos
		 */
		void randomize();
		/*
		 * Soma p ao fitness do robo de id 'id'
		 */
		int updateFitness(int id, int p);
		/*
		 * Reseta o Fitness de todos os robos para 'v'
		 */
		void resetFitness(int v = 0);
		/*
		 * Faz crossover e mutacao para toda populacao
		 */
		void newPop();
		/*
		 * Recebe do AG qual a resposta para a disposicao atual dos sensores
		 */
		int getAction(int id, vector<int> sensors);
};

#endif //AG_H
