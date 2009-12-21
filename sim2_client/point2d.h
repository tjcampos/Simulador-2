/**
 * \file point2d.h
 * \author Thiago Jose de Campos - PIBITI
 **/

#ifndef POINT2D_H
#define POINT2D_H

#include <SDL/SDL.h>
#include <memory>

using namespace std;

/**
 * Ponto com 2 dimensoes
 */
class Point2d{
	public:
		/**
		 * coordenada x do ponto
		 */
		int x;
		/**
		 * coordenada y do ponto
		 */
		int y;

		/**
		 * Construtor da classe
		 * \param x coordenada x
		 * \param y coordenada y
		 */
		Point2d(int x = 0, int y = 0);
		/**
		 * Operacao usual de atribuicao
		 * \param p operando
		 * \return valor a ser atribuido
		 */
		Point2d &operator= (const Point2d &p);
		/**
		 * Operacao usual de +=
		 * \param p operando
		 * \return valor a ser atribuido
		 */
		Point2d &operator+= (const Point2d &p);
		/**
		 * Operacao usual de soma
		 * \param p operando
		 * \return valor a ser atribuido
		 */
		const Point2d operator+ (const Point2d &p) const;
		/**
		 * Operacao multiplicacao por escalar 
		 * \param p operando
		 * \return valor a ser atribuido
		 */
		Point2d &operator*= (const int &p);
		/**
		 * Operacao multiplicacao por escalar 
		 * \param p operando
		 * \return valor a ser atribuido
		 */
		const Point2d operator* (const int &p) const;
		/**
		 * Operacao divisao por escalar
		 * \param p operando
		 * \return valor a ser atribuido
		 */
		Point2d &operator/= (const int &p);
		/**
		 * Operacao divisao por escalar
		 * \param p operando
		 * \return valor a ser atribuido
		 */
		const Point2d operator/ (const int &p) const;
};
#endif
