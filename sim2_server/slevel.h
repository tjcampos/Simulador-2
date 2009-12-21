/**
 * \file slevel.h
 * \author Thiago Jose de Campos - PIBITI
 **/

#ifndef SLEVEL_H
#define SLEVEL_H

/**
 * Nivel de deteccao do sensor
 */
class SLevel {
	public:
		/**
		 * Id do robo que possui o sensor
		 */
		int rId;
		/**
		 * Id do sensor no robo
		 */
		int sId;
		/**
		 * Nivel de deteccao
		 */
		int sLevel;
};
#endif
