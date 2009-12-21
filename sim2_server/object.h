/**
 * \file object.h
 * \author Thiago Jose de Campos - PIBITI
 **/
#ifndef OBJECT_H
#define OBJECT_H

#include <list>
#include <SDL/SDL.h>
#include "SDL/SDL_gfxPrimitives.h"      // SDL_gfx Primitives

#include "drawing.h"
#include "point2d.h"
#include "trigtable.h"

using std::list;

/**
 * Objeto de sumulacao, classe virtual pura.
 */
class Object{
	private:
		Uint32 color;
		int id;
		bool enable;
	public:
		/**
		 * Construtor da classe objeto, recebe como parametros:
		 * \param id id do objeto (nao pode ser duplicado e nao pode ser alterado posteriormente)
		 * \param color cor do objeto em 0xRRGGBBAA
		 * \param enable objeto ativo para simulacao e impressao na tela
		 */
		Object(int id, Uint32 color, bool enable);
		/**
		 * Altera a cor do objeto, parâmetro:
		 * \param color cor do objeto em 0xRRGGBBAA
		 */
		void setColor(Uint32 color);
		/**
		 * Funcao que verifica a cor do objeto
		 * \return cor do objeto em 0xRRGGBBAA
		 */
		Uint32 getColor();
		/** 
		 * Funcao que verifica o id do objeto
		 * \return um inteiro com o id do objeto, o id e unico em cada objeto
		 */
		int getId();
		/**
		 * Ativa o objeto para impressao na tela e simulacao, parametros:
		 * \param enable booleana, se true ativa o objeto, se false ignora-o
		 */
		void setEnable(bool enable);
		/**
		 * Verifica se o objeto esta ativo
		 * \return true se o objeto esta ativo para simulacao e impressao e false caso contrario
		 */
		bool getEnable();
		/**
		 * Deve ser implementada de forma com que desenhe o objeto na tela, recebe s, uma interface para desenho. FUNCAO VIRTUAL PURA
		 * \param s classe que desenha os objetos na tela
		 */
		virtual void draw(Drawing &s) = 0;
		/**
		 * Deve executar uma etapa de simulacao, ou seja, movimentacao e deteccao de colisao, se necessario. FUNCAO VIRTUAL PURA
		 * \param s classe que desenha os objetos na tela
		 * \param tick duracao do frame atual
		 * \param objects lista de objetos, para verificacao de colisao
		 */
		virtual void runStep(Drawing &s, int tick, list<Object*> &objects) = 0;
};
#endif
