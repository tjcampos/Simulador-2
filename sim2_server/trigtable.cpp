#include "trigtable.h"

bool Trigtable::generated = false;
float *(Trigtable::sintable) = NULL;
float *(Trigtable::costable) = NULL;

void Trigtable::generate(){
	if (!generated){
		sintable = new float[3600];
		costable = new float[3600];
		for (int i = 0; i < 3600; i++){
			sintable[i] = sin((i*DPI)/3600);
			costable[i] = cos((i*DPI)/3600);
		}
		generated = true;
	}
}

float Trigtable::tsin(int x){
	if (!generated)
		return 0;
	if (x >= 3600 || x < 0){
		if (x > 0){
			x = x%3600;
		}
		else{
			x = 3600 + x%3600;
		}
	}
	return sintable[x];
}

float Trigtable::tcos(int x){
	if (!generated)
		return 0;
	if (x >= 3600 || x < 0){
		if (x > 0){
			x = x%3600;
		}
		else{
			x = 3600 + x%3600;
		}
	}
	return costable[x];
}
