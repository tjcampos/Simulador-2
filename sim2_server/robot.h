/**
 * \file robot.h
 * \author Thiago Jose de Campos - PIBITI
 **/

#ifndef ROBOT_H
#define ROBOT_H

#include <list>
#include <math.h>

#include "drawing.h"
#include "point2d.h"
#include "trigtable.h"
#include "object.h"
#include "obstacle.h"
#include "checkintersect.h"
#include "slevel.h"
#include "rsensor.h"

using std::list;

class RSensor;

/**
 * Classe Robot (robo) do simulador, deriva de Object
 */
class Robot : public Object{
	private:
		Point2d pos;
		int size;
		int rot;
		int vl, vr;
		list<RSensor> sensors; 
		bool collision, lastCollision;
		int newEvent;
		list<SLevel> lastDetections;
	protected:
		/**
		 * Desenha os sensores do robo na tela
		 * \param s objeto para desenho na tela
		 */
		void drawSensor(Drawing &s);
		/**
		 * Encontra um sensor
		 * \param id id do sensor a ser buscado
		 * \return iterador para o sensor
		 */
		list<RSensor>::iterator findSensor(int id);
		/**
		 * Verifica se o a posicao de uma circunferencia nao colide com demais objetos
		 * \param begin iterador para o inicio da lista de objetos
		 * \param end iterador para o fim da lista de objetos
		 * \param pos posicao central da circunferencia
		 * \param size diametro da circunferencia
		 * \return true em caso de caminho livre, ou false em caso de algo estar bloquando o caminho
		 */
		bool isValidPosition(list<Object*>::iterator begin, list<Object*>::iterator end, Point2d pos, int size);
		/**
		 * Trunca o valor do angulo para algo entre 0 e 360
		 * \param rot valor atual do angulo
		 */
		void setFineRot(int rot);
	public:
		/**
		 * Construtor da classe Robot
		 * \param id id do objeto (nao pode ser duplicado e nao pode ser alterado posteriormente)
		 * \param color cor do objeto em 0xRRGGBBAA
		 * \param posx posicao do robo no eixo x
		 * \param posy posicao do robo no eixo y
		 * \param size raio do robo
		 * \param rot angulo de rotacao do robo
		 * \param vl velocidade da roda direita
		 * \param vr velocidade da roda esquerda
		 * \param enable objeto ativo para simulacao e impressao na tela
		 */
		Robot(int id, Uint32 color, int posx, int posy, int size, int rot = 0, int vl = 0, int vr = 0, bool enable = true);
		/**
		 * Altera a posicao do robo
		 * \param pos nova posicao do robo
		 */
		void setPos(Point2d pos);
		/**
		 * Verifia a posicao do robo
		 * \return posicao do robo
		 */
		Point2d getPos();
		/**
		 * muda o diametro do robo
		 * \param size novo diametro do robo
		 */
		void setSize(int size);
		/**
		 * Verifica o diametro do robo
		 * \return diametro do robo
		 */
		int getSize();
		/**
		 * muda o angulo de rotacao do robo
		 * \param rot novo angulo de rotacao do robo
		 */
		void setRot(int rot);
		/**
		 * Verifica o angulo de rotacao do robo
		 * \return angulo de rotacao do robo
		 */
		int getRot();
		/**
		 * muda a velocidade do robo
		 * \param vl velocidade da roda esquerda
		 * \param vr velocidade da roda direita
		 */
		void setSpeed(int vl, int vr);
		/**
		 * verifica a velocidade do robo
		 * \param vl velocidade da roda esquerda
		 * \param vr velocidade da roda direita
		 */
		void getSpeed(int &vl, int &vr);
		void draw(Drawing &s);
		/**
		 * calcula a proxima posicao do robo e checa a validade desta posicao chamando o metodo isValidPosition, em caso de movimento valido executa a operacao
		 * \param s classe para desenho do robo
		 * \param tick duracao do frame atual
		 * \param objects lista de objetos para checagem de colisao
		 */
		void runStep(Drawing &s, int tick, list<Object*> &objects);
		/**
		 * Adiciona um sensor ao robo
		 * \param id id do sensor, deve ser unico entre sensores
		 * \param pos posicao do sensor em graus em torno do robo
		 * \param length comprimento do sensor
		 * \param width largura do sensor
		 * \param rot angulo formado entre o sensor e a reta tangente da circunferencia que passa pela origem do sensor
		 * \return true em caso de sucesso e false caso contrario
		 */
		bool addSensor(int id, int pos , int length, int width, int rot = 0);
		/**
		 * Deleta o sensor com o id selecionado
		 * \param id id do sensor a ser removido
		 * \return true em caso de sucesso e false caso contrario
		 */
		bool delSensor(int id);
		/**
		 * recebe informacoes de um sensor do robo
		 * \param id id do sensor a ter informacoes recebidas
		 * \param pos posicao do sensor em graus em torno do robo
		 * \param length comprimento do sensor
		 * \param width largura do sensor
		 * \param rot angulo formado entre o sensor e a reta tangente da circunferencia que passa pela origem do sensor
		 * \return true em caso de sucesso e false caso contrario
		 */
		bool getSensor(int id, int &pos , int &length, int &width, int &rot);
		/**
		 * Edita um sensor do robo
		 * \param id id do sensor a ser editado
		 * \param pos posicao do sensor em graus em torno do robo
		 * \param length comprimento do sensor
		 * \param width largura do sensor
		 * \param rot angulo formado entre o sensor e a reta tangente da circunferencia que passa pela origem do sensor
		 * \return true em caso de sucesso e false caso contrario
		 */
		bool setSensor(int id, int pos , int length, int width, int rot = 0);
		/**
		 * Verifica os sensores do Robo atual e executa deteccao com a lista de Object.
		 * \param objects lista de objetos a serem detectados pelo sensor
		 * \param max valor maximo do sensor, objeto muito proximo
		 * \param min valor minimo do sensor, objeto muito distante
		 * \return lista com as deteccoes,o valor da deteccao sera um numero entre min e max
		 */
		list<SLevel> const checkSensors(list<Object*> &objects, int max = 10, int min = 0);
		/**
		 * Checa se o robo esta colidindo com algum objeto
		 * \return true em caso de colisao e false caso contrario
		 */
		bool getCollision(); 
		/**
		 * Checa novos eventos
		 * \return retorna 1 se houve alteracoes nos sensores e 2 se houve aulteracao na colisao
		 */
		int getNewEvents();
		/**
		 * Limpa todos os eventos que estao prontos para serem enviados
		 */
		void clearEvents();

};

/**
 * Sensor para ser colocado em robos
 */
class RSensor{
	private:
		int id;
		//angulo de rotacao
		int rot;
		int length;
		int width;
		//posicao em graus em volta do robo
		int pos;
		Point2d vertices[4];
		list<Point2d> detections;
	public:
		/**
		 * Construtor da classe RSensor
		 * \param id id do sensor, os valores podem ser repetidos entre diferentes robos
		 * \param pos posicao no perimetro do robo
		 * \param length alcance do sensor
		 * \param width alcance lateral do sensor
		 * \param rot inclinacao do sensor
		 */
		RSensor(int id, int pos , int length, int width, int rot = 0);
		/**
		 * Verifica o id no sensor, unico entre sensores
		 * \return id do sensor
		 */
		int getId();
		/**
		 * Altera a posicao do sensor em graus*10 do sensor em volta do robo
		 * \param pos posicao do sensor em graus*10 do sensor em volta do robo
		 */
		void setPos(int pos);
		/**
		 * Verifica a posicao do sensor
		 * \return posicao do sensor em volta do robo (graus*10)
		 */
		int getPos();
		/**
		 * Altera o angulo formado entre o sensor e a reta tangente da circunferencia que passa pela origem do sensor, em (graus*10)
		 * \param rot angulo formado entre o sensor e a reta tangente da circunferencia que passa pela origem do sensor, em (graus*10)
		 */
		void setRot(int rot);
		/**
		 * Verifica o angulo formado entre o sensor e a reta tangente da circunferencia que passa pela origem do sensor, em (graus*10)
		 * \return o angulo formado entre o sensor e a reta tangente da circunferencia que passa pela origem do sensor, em (graus*10)
		 */
		int getRot();
		/**
		 * altera o comprimento do sensor
		 * \param length novo comprimento do sensor
		 */
		void setLength(int length);
		/**
		 * Verifica o comprimento do sensor
		 * \return comprimento do sensor
		 */
		int getLength();
		/**
		 * altera a largura do sensor
		 * \param width nova largura do sensor
		 */
		void setWidth(int width);
		/**
		 * Verifica a largura do sensor
		 * \return largura do sensor
		 */
		int getWidth();
		/**
		 * Verifica a deteccao do sensor atual
		 * \param objects utilizada para  deteccao de colisao
		 * \param r robo que possui o sensor, para evitar que o sensor detecte seu proprio robo
		 * \param max objeto encontra-se muito proximo ao robo
		 * \param min quando nada e detectado
		 * \param maxBufferSize define o numero maximo de deteccoes que devem ser armazenados para impressao esta opcao influencia apenas na funcao draw, nao tendo efeito sobre os demais aspectos da simulacao, eh usada para evitar problemas em casos em que a funcao draw nao eh chamada, alocando memoria indefinidamente, se o buffer atinge o tamnho maximo ele e limpo
		 * \return inteiro com o valor da deteccao que sera um numero entre min e max
		 */
		int scan(list<Object*> &objects, Robot *r, int max, int min, int maxBufferSize = 1024);
		/**
		 * desenha o sensor
		 * \param s objeto para desenho do sensor
		 */
		void draw(Drawing &s);
};

#endif
