#ifndef ARGPROCESSOR_ARGPROCESSOR_H_
#define ARGPROCESSOR_ARGPROCESSOR_H_

#include "JarsControl/JarsControl.h"//llama al objeto JARControl
#include <string>

class ArgProcessor
{
private:
	ExpParameters &MyParameters;

public:
	ArgProcessor(ExpParameters &MyParameters);
	~ArgProcessor();

	void jro_arguments(const char* path);
};

//*** Define el atributo private de ArgProcessor igual a los parámetros del constructor
ArgProcessor::ArgProcessor(ExpParameters &params)
:MyParameters(params)//El atributo private MyParameters será igual a params para que no haya error de inicialización//la referencias siempre deben ser declaradas.
{}
ArgProcessor::~ArgProcessor()
{}

//*****Dependiendo de los parámetros que entran en el main, guarda las direcciones de los objetos de los modos de operación en ** AcqMan
void ArgProcessor::jro_arguments(const char* path)
{
	
	if(!MyParameters.ReadRACPFileParameters(path))//Obtenido de GNU Radio
	 {
	   printf("\n Error en leer el RacpFile \n");

	 }

}

#endif
