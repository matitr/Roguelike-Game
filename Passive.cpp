#include "Passive.h"



Passive::Passive(PassiveActivateOn activationOn) : passActivateOn(activationOn) {

}


Passive::~Passive() {
	if (buffFromPassive)
		delete buffFromPassive;
}
