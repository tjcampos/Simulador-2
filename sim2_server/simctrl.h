/**
 * \file simctrl.h
 * \author Thiago Jose de Campos - PIBITI
 **/

#ifndef SIMCTRL_H
#define SIMCTRL_H

#include <list>

#include <iostream>
#include <sstream>
#include <SDL/SDL.h>
#include <SDL/SDL_framerate.h>

#include "object.h"
#include "robot.h"
#include "obstacle.h"
#include "drawing.h"
#include "sockserv.h"

using std::list;

/**
 * Classe que guarda o id dos robos e o valor do evento que ocorreu com ele
 */
class Event {
	public:
		/**
		 * id do objeto ao qual o evento esta relacionado
		 */
		int id;
		/**
		 * valor do evento, seguem os valores:
		 * 1 - deteccao de sensores
		 * 2 - colisao
		 */
		int value;
};

/**
 * Utilizado para armazenar os clientes e suas interrupcoes
 */
class Interruption {
	public:
		/**
		 * Valor do socket que esta associado a interrupcao
		 */
		int socket;
		/**
		 * Id do robo que esta sendo monitorado
		 */
		int rid;
};

/**
 * Utilizado para armazenar as interrupcoes de tempo
 */
class TimeInterruption {
	public:
		/**
		 * Valor do socket que esta associado a interrupcao de tempo
		 */
		int socket;
		/**
		 * Tempo em que sera executada a interrupcao
		 */
		unsigned long int time;
};

/**
 * Classe que controla todos os eventos de simulacao
 */
class SimCtrl {
	private:
		bool running, started;
		unsigned long int simTime; //unidade: sec*10E-4
		int fps, tick, speedMultiply;
		bool fast, limitFps;
		list<Object*> objects; 
		FPSmanager fpsm;
		list<SLevel> detections;
		list<Interruption> interruptions;
		list<TimeInterruption> timeir;
	protected:
		/**
		 * busca na lista de Objects e retorna o Object com o id procurado, retorna null
		 * em caso de nao encontrar
		 */
		template <typename T>
		Object *findObject(int id){
			list<Object*>::iterator it;
			for (it = objects.begin(); it != objects.end(); it++)
				if ((*it)->getId() == id)
					return (*it);
			return NULL;
		}
		/**
		 * efetua um delay
		 * \param time valor do delay em ms
		 */
		static void delay(int time = 20);
	public:
		/**
		 * Construtor da classe
		 * \param fast ativa o modo de simulacao acelerado
		 * \param speedMultiply especifica o numero de vezes a velocidade real, nota: Valores grandes podem resultar em imprecisao
		 * \param fps especifica o numero de frames por segundo da simulacao, valores grandes causam dados mais fieis e consomem mais CPU
		 */
		SimCtrl(bool fast = false, int speedMultiply = 1, int fps = 30);
		/**
		 * Funcao que checa se a simulacao esta ativa
		 * \return true em caso da simulacao estar ativa e false caso contrario
		 */
		bool isRunning();
		/**
		 * Termina a simulacao
		 */
		void stopSimulation();
		/**
		 * Funcao que checa se a simulacao ja foi iniciada
		 * \return true em caso da simulacao ter sido iniciada e false caso contrario
		 */
		bool isStarted();
		/**
		 * inicia a simulacao
		 */
		void start();
		/**
		 * Configura se a simulacao deve ser feita em modo rapido, onde nada e desenhado na tela para ganho de desempenho e limite de fps e desetivado
		 * \param fast configura para modo rapido em caso de true e para modo normal em caso de false
		 */
		void setFast(bool fast);
		/**
		 * Verifica se a simulacao esta em modo acelerado
		 * \return retorna true em caso da simulacao estar em modo acelerado e false caso contrario
		 */
		int getFast();
		/**
		 * Configura o valor da aceleracao de tempo, valores altos sao podem gerar imprecisao em troca de uma simulacao mais rapida 
		 * \param sm numero de vezes em que a velocidade de simulacao sera multiplicada
		 */
		void setSpeedMult(int sm);
		/**
		 * Verifica a velocidade da simulacao
		 * \return velocidade de semulacao em relacao a real
		 */
		int getSpeedMult();
		/**
		 * Configura o numero de frames por segundo de simulacao, valores maiores geram maior precisao a custo de maior uso de CPU
		 * \param fps numero de frames por segundo
		 */
		void setFps(int fps);
		/**
		 * Verifica o numero de frames por segundo da simulacao
		 * \return numero de frames por segundo
		 */
		int getFps();
		/**
		 * Adiciona um objeto a lista de objetos
		 * \param o objeto a ser adicionado a simulacao
		 * \return true se conseguir adicionar o objeto e false caso contrario
		 */
		bool addObject(Object &o);
		/**
		 * Remover objeto
		 * \param id id do objeto a ser removido
		 * \return true em caso de conseguir remover o objeto e false caso contrario
		 */
		bool delObject(int id);
		/**
		 * Acessa um objeto da simulacao
		 * \param id id do objeto a ser acessado
		 * \return Retorna o objeto desejado, ou NULL em caso de nao encontra-lo
		 */
		template <typename A>
		A *getObject(int id){
			A *o = (A*) findObject<A>(id);
			if (typeid(*o) == typeid(A))
				return o;
			return NULL;
		}
		/**
		 * Desenha na tela todos os objetos
		 * \param s objeto para desenho
		 */
		void draw(Drawing &s);
		/**
		 * Roda uma etapa de simulacao
		 * \param s objeto para desenho
		 */
		void runStep(Drawing &s);
		/**
		 * Verifica detecoes de sensores
		 * \return lista com todas as deteccoes
		 */
		list<SLevel>* const getDetections();
		/**
		 * Verifica o tempo atual de simulacao
		 * \return tempo de simulacao, em ms
		 */
		unsigned long int getSimTime();
		/**
		 * Altera o tempo de simulacao
		 * \param time tempo de simulacao em ms
		 */
		void setSimTime(unsigned long int time);
		/**
		 * Verifica eventos que ocorreram a robos
		 * \return lista de eventos
		 */
		list<Event> const getNewEvents();
		/**
		 * Envia os eventos que um socket deseja escutar
		 * \param sock socket que recebara os eventos correspondentes
		 */
		void sendEvents(SockServ &sock);
		/**
		 * Adiciona um robo a lista de verificacoes de um socket
		 * \param sock socket que escutara os eventos
		 * \param rId robo que sera adicionado a lista
		 */
		void addInterrupt(int sock, int rId);
		/**
		 * Remove um robo da lista de verificacoes de um socket
		 * \param sock socket que deixara de escutar os eventos
		 * \param rId robo que sera removido a lista
		 */
		void delInterrupt(int sock, int rId);
		/**
		 * Alerta um socket quando um tempo chegar
		 * \param sock socket que recebera o alerta
		 * \param time tempo desejado
		 */
		void addTimeAlert(int sock, unsigned long int time);
		/**
		 * Remove um alerta de tempo
		 * \param sock socket que estava escalado para receber o alerta
		 * \param time tempo a ser removido
		 */
		void delTimeAlert(int sock, unsigned long int time);
		/**
		 * Checa e envia aos sockets os alertas de tempo
		 * \param sock classe SockServ com os sockets do simulador
		 */
		void sendTimeAlert(SockServ &sock);
		/**
		 * Reinicia a simulacao, configurando o tempo para zero e deletando todos os robos e obstaculos e interrupcoes e volta o tempo para zero
		 */
		void restart();

};

#endif
