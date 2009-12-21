/**
 * \file kbddecoder.h
 * \author Thiago Jose de Campos - PIBITI
 **/
#ifndef KBDDECODER_H
#define KBDDECODER_H

#include <iostream>
#include <SDL/SDL.h>
#include <string>

using namespace std;

/**
 * Classe que trata eventos de teclado
 */
class KbdDecoder {
	public:
		/**
		 * Recebe eventos do teclado e gera um evento representando-o
		 * @return mensagem do evento decodificada
		 */
		static string decodeKbdEvent();
};
#endif
