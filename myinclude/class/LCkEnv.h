#ifndef LCkEnv_h
#define LCkEnv_h 1

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "LRoot.h"

using namespace std;
extern char **environ;

class LCkEnv:{
	public:
		LCkEnv();
		LCkEnv(TString v_imput);
		~LCkEnv();
		TString GetEnv(TString v_input);
	private:
		TString input;
		TString value;
};


inline LCkEnv::LCkEnv():input(NULL),value(NULL){;}

inline LCkEnv::~LCkEnv(){;}

inline LCkEnv::LCkEnv(TString v_input){
	input=v_input;
}

inline TString LCkEnv::GetEnv(){
	if (input != NULL)
	{
		value = getenv(input);
		return value;
	}
	else return NULL;
}

inline TString LCkEnv::GetEnv(TString v_input){
	input = v_input;
	value = getenv(input);
	return input;
}

#endif
