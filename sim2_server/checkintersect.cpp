#include "checkintersect.h"

bool CheckIntersect::inSegment (const Point2d &p1, const Point2d &p2, const Point2d &check){
	//verifica se a precisao eh maior calculando baseado em x
	if ( abs(p1.x - p2.x) < 5) {
		int ymin, ymax;

		//verifica-se qual dos pontos possui coordenada y maior, atribui ymin e ymax
		if ( p1.y < p2.y ) {
			ymin = p1.y;
			ymax = p2.y;
		}
		else {
			ymin = p2.y;
			ymax = p1.y;
		}
		//se o ponto check estiver entre ymin e ymax, ele está no segmento, logo a função retorna 1
		if (ymin <= check.y && ymax >= check.y) return true;
		//caso contrário a função retorna 0
		else return false;
	}
	//caso a reta a precisão seja maior baseado em y
	else {
		int xmin, xmax;

		//verifica-se qual dos pontos possui coordenada x maior, atribui xmin e xmax
		if (p1.x < p2.x) {
			xmin = p1.x;
			xmax = p2.x;
		}
		else {
			xmin = p2.x;
			xmax = p1.x;
		}

		//se o ponto check estiver entre xmin e xmax, ele está no segmento, logo a função retorna 1
		if (xmin <= check.x && xmax >= check.x) return true;
		//caso contrário a função retorna 0
		else return false;
	}
}

bool CheckIntersect::getIntersect (const Point2d &a0, const Point2d &a1, const Point2d &b0, const Point2d &b1, Point2d &intersect){

	float Ma, Mb;

	//verifica se a reta a é vertical
	if ( abs(a1.x - a0.x) < 5) {

		//verifica se a reta b é aproximadamente vertical
		if ( b1.x == b0.x )
			//logo as retas são paralelas, não há intersecção
			return 0;
		else {
			//se as retas não forem paralelas, calcula-se a intersecção
			Mb = (float) (b1.y - b0.y)/(b1.x - b0.x);
			intersect.x = a0.x;
			intersect.y = (int) (Mb*(intersect.x - b0.x)+b0.y);

			//verifica-se se a intersecção se deu em um segmento válido da reta
			if ( CheckIntersect::inSegment(a0, a1, intersect) && CheckIntersect::inSegment(b0, b1, intersect) ) return true;
			else return false;
		}

	}

	//verifica se a reta b é aproximadamente vertical
	else if ( abs(b1.x - b0.x) < 5) {

		//calcula-se a intersecção
		Ma = (float) (a1.y - a0.y)/(a1.x - a0.x);
		intersect.x = b0.x;
		intersect.y = (int) (Ma*(intersect.x - a0.x) + a0.y);

		//verifica-se se a intersecção se deu em um segmento válido da reta
		if ( CheckIntersect::inSegment(a0, a1, intersect) && CheckIntersect::inSegment(b0, b1, intersect) ) return true;
		else return false;
	}

	//as retas a e b não são verticais
	else{
		//calcula-se a intersecção
		Ma = (float) (a1.y-a0.y)/(a1.x-a0.x);
		Mb = (float) (b1.y-b0.y)/(b1.x-b0.x);
		intersect.x = (int) ((Ma*a0.x - a0.y - Mb*b0.x + b0.y) / (Ma-Mb));
		//verifica-se se a intersecção se deu em um segmento válido da reta
		if (CheckIntersect::inSegment(a0, a1, intersect) && CheckIntersect::inSegment(b0, b1, intersect) ) {
			intersect.y = (int) (Ma*(intersect.x - a0.x) + a0.y);
			return true;
		}
		else
			return false;
	}
}

int CheckIntersect::getIntersect (const Point2d &center, const int radius, const Point2d &p1, const Point2d &p2, Point2d intersect[]){

	//verifica se a reta a é aproximadamente vertical
	if ( abs(p1.x - p2.x) < 5 ) {
		//calcula-se as intersecções
		intersect[0].x = p1.x;
		intersect[0].y = (int) (center.y + sqrt(radius*radius - ((p1.x-center.x)*(p1.x-center.x)) ));

		intersect[1].x = p1.x;
		intersect[1].y = (int) (center.y - sqrt(radius*radius - ((p1.x-center.x)*(p1.x-center.x)) ));

		//verifica-se se a primeira intersecção se deu em um segmento válido da reta
		if (inSegment(p1, p2, intersect[0])){
			//verifica-se se a segunda intersecção se deu em um segmento válido da reta
			if (inSegment(p1, p2, intersect[1]))
				//se ambas as intersecções forem válidas, retorna 2
				return 2;
			else
				//se apenas a primeira intersecção for válida, retorna 1
				return 1;
		}
		else{
			if (inSegment(p1, p2, intersect[1])) { 
				//se apenas a segunda intersecção for válida, copia a intesecção para a 
				//primeira posição do vetor e retorna 1
				intersect[0] = intersect[1];
				return 1;
			}
			else 
				//se nenhuma intersecção for válida, retorna zero
				return 0;
		}

	}

	//para retas não verticais
	float delta;
	float m;
	float a, b, c ,k;

	//calcula-se as intesecções
	m = (float) (p2.y - p1.y)/(p2.x - p1.x);


	k = p1.y-center.y;

	a = (m*m + 1);
	b = (2*k*m - 2*center.x - 2*m*m*p1.x);
	c = (center.x*center.x + m*m*p1.x*p1.x - 2*k*m*p1.x + k*k-radius*radius);

	delta = b*b - 4*a*c;

	//se o delta da eq resultante for negativo, retorna zero
	if ( delta < 0 ) return 0;
	//senão continua
	else
	{
		//calcula-se uma possível solução
		intersect[0].x = (int) ((-b + sqrt((float) delta) )/(2*a));
		intersect[0].y = (int) (m*(intersect[0].x-p1.x)+p1.y);

		//se possui 2 soluções
		if (delta > 0) {
			//calcula-se a segunda possível solução
			intersect[1].x = (int) ((-b - sqrt((float) delta) )/(2*a));
			intersect[1].y = (int) (m*(intersect[1].x-p1.x)+p1.y);

			//verifica-se se a primeira intersecção se deu em um segmento válido da reta
			if ( inSegment (p1, p2, intersect[0]) ) 
				//verifica-se se a segunda intersecção se deu em um segmento válido da reta
				if ( inSegment (p1, p2, intersect[1]) ) 
					//se ambas as intersecções forem válidas, retorna 2
					return 2;
				else 
					//se apenas a primeira intersecção for válida, retorna 1
					return 1;
			else
				if ( inSegment (p1, p2, intersect[1]) ) {
					//se apenas a segunda intersecção for válida, copia a intesecção para a
					//primeira posição do vetor e retorna 1
					intersect[0] = intersect[1];
					return 1;
				}
				else
					//se nenhuma intersecção for válida, retorna zero
					return 0;
		}
		if ( inSegment (p1, p2, intersect[0]) )
			//se possui apenas uma solução e esta é válida, retorna 1
			return 1;
		else
			//se possui apenas uma solução e esta não é válida, retorna 0
			return 0;
	}
}
