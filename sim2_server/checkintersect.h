/**
 * \file checkintersect.h
 * \author Thiago Jose de Campos - PIBITI
 **/
#ifndef CHECKMINTERSECT_H
#define CHECKMINTERSECT_H

#include <math.h>

#include "trigtable.h"
#include "point2d.h"

/**
 * Classe abstrata que checa interseccoes entre retas e circunferencias
 */
class CheckIntersect {
	public:
		/**
		 * Uma vez que o ponto check esta na reta definita por p1,p2 a funcao verifica se ele esta no segmento de reta de p1 a p2.
		 * \param p1 limite p1 da reta
		 * \param p2 limite p2 da reta
		 * \param check ponto a ser checado se esta dentro da reta
		 * \return true em caso afirmativo e false caso contrario
		 */
		static bool inSegment (const Point2d &p1, const Point2d &p2, const Point2d &check);
		/**
		 * Verifica interseccao entre o robo definido pelo centro (center) e pelo raio (radius) e a reta b0,b1 e retorna a interseccao interseccao. O retorno da funcao eh um valor inteiro, com o numero de interseccoes encontradas, variando de 0 a 2.
		 * \param center centro da circunferencia
		 * \param radius raio da circunferencia
		 * \param p1 limite p1 da reta
		 * \param p2 limite p2 da reta
		 * \param intersect[] vetor de pontos, em que houve interseccao
		 * \return numero de interseccoes encontradas
		 */
		static int getIntersect (const Point2d &center, const int radius, const Point2d &p1, const Point2d &p2, Point2d intersect[]);
		/**
		 * Verifica interseccao entre retas definidas por a0,a1 e b0,b1 e retorna a interseccao intersect. Em caso de nao encontrar a interseccao retorna false, caso contrario retorna true.
		 * \param a0 limite p1 da reta 1
		 * \param a1 limite p2 da reta 1
		 * \param b0 limite p1 da reta 2
		 * \param b1 limite p2 da reta 2
		 * \param intersect pontos em que houve interseccao
		 * \return retorna true em caso de interseccao e false em caso contrario, se as retas forem paralelas sempre retorna false
		 */
		static bool getIntersect (const Point2d &a0, const Point2d &a1, const Point2d &b0, const Point2d &b1, Point2d &intersect);
};
#endif
