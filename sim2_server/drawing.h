/**
 * \file draing.h
 * \author Thiago Jose de Campos - PIBITI
 **/
#ifndef DRAWING_H
#define DRAWING_H

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>      // SDL_gfx Primitives
#include <SDL/SDL_framerate.h>  // SDL_gfx Framerate Manager
#include <string>

#include "point2d.h"

using namespace std;

/**
 * Classe responsavel por tratar da parte grafica e prover funcoes para desenhar na tela
 */
class Drawing{
	private:
		SDL_Surface *scr;
		char *currFont;
		double xScale, yScale, scale; //relacao entre o tamanho da tela e o do mundo

	public:
		/**
		 * Construtor da classe drawing recebe com parâmetro:
		 * \param realWidth altura do mundo em centímetros
		 * \param realHeigth largura do mundo em centímetros
		 * \param scrWidth altura da tela em pixels
		 * \param scrHeigth largura da tela em pixels
		 * \param fontFile ponteiro para arquivo de fontes
		 * \param fSize numero máximo de chars da fonte
		 * \param cw alttura do character
		 * \param ch largura do character
		 */
		Drawing(int realWidth = 800, int realHeigth = 600, int scrWidth = 800, int scrHeigth = 600, char *fontFile = (char*) "./fonts/9x18.fnt", unsigned int fSize = 9216, int cw = 9, int ch = 18);
		/**
		 * Remove todos os objetos desenhados
		 */
		void clearScr();
		/**
		 * atualiza a tela para q todas as mudanças sejam exibidas
		 */
		void updateScr();
		/**
		 * desenha um circulo na tela
		 * \param center centro da circunferencia
		 * \param size raio da circunferencia
		 * \param color cor da circunferencia em 0xRRGGBBAA
		 */
		void drawCircle(const Point2d &center, int size, Uint32 color); 
		/**
		 * desenha um poligono na tela
		 * \param vertices[] vetor com as posições dos vertices do poligono
		 * \param nvertices numero de vertices do poligono
		 * \param color cor da circunferencia em 0xRRGGBBAA
		 */
		void drawPolygon(Point2d vertices[], int nvertices, Uint32 color); 
		/**
		 * desenha um poligono na tela
		 * \param ini vetor com as posições x dos vertices do poligono
		 * \param fim vetor com as posições y dos vertices do poligono
		 * \param color cor da circunferencia em 0xRRGGBBAA
		 */
		void drawLine(const Point2d &ini, Point2d &fim, Uint32 color); 
		/**
		 * imprime um texto na tela
		 * \param text texto a ser impresso na tela
		 * \param pos posicao do texto
		 * \param color cor do texto em 0xRRGGBBAA
		 */
		void drawText(string text,Point2d pos, Uint32 color = 0xffffffff);
		~Drawing();
};

#endif
