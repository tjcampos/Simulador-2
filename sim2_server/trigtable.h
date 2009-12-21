/**
 * \file trigtable.h
 * \author Thiago Jose de Campos - PIBITI
 **/

#ifndef TRIGTABLE_H
#define TRIGTABLE_H

#include <math.h>
#include <cstdlib>

#define DPI (float) (3.141592653589793*2)

/**
 * Classe que possui tabelas com valores matematicos, para acelerar calculos
 */
class Trigtable {
	private:
		static bool generated;
		static float *sintable;
		static float *costable;
	public:
		/**
		 * Cria a tabela de senos
		 */
		static void generate();
		/**
		 * calcula do seno valor tabelado
		 * \param x valor do anguro em graus
		 * \return valor do seno de x
		 */
		static float tsin(int x);
		/**
		 * calcula cosseno valor tabelado
		 * \param x valor do anguro em graus
		 * \return valor do cosseno de x
		 */
		static float tcos(int x);
};
#endif
