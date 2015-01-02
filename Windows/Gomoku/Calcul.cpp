#include "Calcul.h"

unsigned int 	Calcul::findX(unsigned int pos) {
	unsigned int tmp = pos;
	unsigned int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 50;	
	}
	return (ret);
}

unsigned int 	Calcul::findY(unsigned int pos) {
	unsigned int tmp = pos;
	unsigned int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 35;
	}
	return (ret);
}
