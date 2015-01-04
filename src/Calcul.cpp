#include "Calcul.h"

unsigned int 	Calcul::findX(unsigned int pos) {
	int tmp = pos;
	int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 47;	
	}
	return (ret);
}

unsigned int 	Calcul::findY(unsigned int pos) {
	int tmp = pos;
	int ret = 0;
	while (tmp > 0) {
		ret++;
		tmp -= 47;
	}
	return (ret);
}
