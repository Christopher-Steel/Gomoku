#include "Calcul.h"

unsigned int 	Calcul::findX(unsigned int pos) {
	unsigned int tmp = pos;
	int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 40;	
	}
	return (ret);
}

unsigned int 	Calcul::findY(unsigned int pos) {
	unsigned int tmp = pos;
	int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 40;
	}
	return (ret);
}
