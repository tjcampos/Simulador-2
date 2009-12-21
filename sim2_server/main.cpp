#include <iostream>
#include <string>
#include <sstream>

#include "drawing.h"
#include "kbddecoder.h"
#include "simctrl.h"
#include "eventmanager.h"
#include "trigtable.h"
#include "checkintersect.h"
#include "sockserv.h"

using namespace std;

int main(){
	Trigtable::generate();
	Drawing *s;
	SimCtrl sc;
	stringstream evt;
	string resp;
	SockServ socket;
	int cliTmp;

	//espera um socket se conectar (espera ocupada)
	while (!socket.acceptClient() && sc.isRunning()){
		SDL_Delay(200);
		evt << KbdDecoder::decodeKbdEvent();
		EventManager::runEvent(evt, sc);
		evt.clear();
	}

	//espera definir dimensoes do mundo
	while (!sc.isStarted() && sc.isRunning()){
		SDL_Delay(200);
		evt << KbdDecoder::decodeKbdEvent();
		EventManager::runEvent(evt, sc);
		evt.clear();
		socket.recvStart();
		while (socket.hasNext()){
			evt << socket.recvNext(&cliTmp);
			s = EventManager::startSim(evt, sc);
			if (s != NULL)
				break;
		}
		evt.clear();
	}

	//inicia laco de simulacao
	while (sc.isRunning()){
		socket.acceptClient();
		s->clearScr();
		evt.clear();
		evt << KbdDecoder::decodeKbdEvent();
		EventManager::runEvent(evt, sc);
		socket.recvStart();
		while (socket.hasNext()){
			evt.clear();
			evt << socket.recvNext(&cliTmp);
			resp = EventManager::runEvent(evt, sc, cliTmp);
			if (resp.size())
				socket.sends(resp,cliTmp);
		}
		sc.sendEvents(socket);
		sc.sendTimeAlert(socket);
		sc.runStep(*s);
		sc.draw(*s);
		s->updateScr();
	}
}
