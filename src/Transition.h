/*
 * Transition.h
 *
 *  Created on: Jan 31, 2017
 *      Author: diepbp
 */

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include "utils.h"

struct Transition{
	int in;
	int label;
	int out;

	Transition(int _out, int _label, int _in) : in(_in), label(_label), out(_out){}
	Transition(){}

	std::string toString(){
		return std::to_string(out) + "--(" + std::to_string(label) + ")--" + std::to_string(in);
	}

	std::string createVar(std::string name){
		return name + "_e_" + std::to_string(out) + "_" + std::to_string(in);
	}

	bool isEqual(Transition t) {
		if (in != t.in)
			return false;
		if (out != t.out)
			return false;
		if (label != t.label)
			return false;
		return true;
	}
};


#endif /* TRANSITION_H_ */
