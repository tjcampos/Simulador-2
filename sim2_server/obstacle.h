/**
 * \file obstacle.h
 * \author Thiago Jose de Campos - PIBITI
 **/

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <list>
#include <SDL/SDL.h>
#include "SDL/SDL_gfxPrimitives.h"      // SDL_gfx Primitives

#include "drawing.h"
#include "point2d.h"
#include "object.h"

using std::list;

/**
 * Obstaculo da simulacao
 */
class Obstacle : public Object{
	private:
		int nvertices;
		Point2d *vertices;
	public:
		/**
		 * Construtor da classe Obstacle, cria um objeto inanimado na tela e que os demais objetos podem colidir
		 * \param id id do obstaculo (nao pode ser duplicado e nao pode ser alterado posteriormente)
		 * \param color cor do objeto em 0xRRGGBBAA
		 * \param nvertices numero de vertices do objeto
		 * \param *vertices vetor com os pontos do cada vertice
		 * \param enable objeto ativo para simulacao e impressao na tela
		 */
		Obstacle(int id, Uint32 color, int nvertices, Point2d *vertices, bool enable = true);
		/**
		 * \return numero de vertices do objeto
		 */
		int getNVertices();
		/**
		 * \return lista com os pontos de cada vertice do objeto
		 */
		Point2d const *getVertices();
		/**
		 * Altera a forma do poligono, parametros:
		 * \param nvertices numero de vertices do novo poligono
		 * \param vertices vetor com os pontos de cada vertice
		 */
		void setVertices(int nvertices, Point2d *vertices);
		/**
		 * Desenha o obstaculo na tela, parametros
		 * \param s interface com metodos para desenho
		 */
                void draw(Drawing &s);
		/**
		 * Executa uma etapa da simulacao, uma vez que um objeto nao se move, a funcao fica em branco
		 * \param s classe que desenha os objetos na tela
		 * \param tick duracao do frame atual
		 * \param objects lista de objetos, para verificacao de colisao
		 */
                void runStep(Drawing &s, int tick , list<Object*> &objects);
};
#endif
