#ifndef ARGPROCESSOR_JARSCONTROL_RDPTOOLSBETA_RDPTOOLBETA_H_
#define ARGPROCESSOR_JARSCONTROL_RDPTOOLSBETA_RDPTOOLBETA_H_

#include <exception>
#include <string>
#include <iostream>
using namespace std;

#include </opt/intel/ipp/include/ipp.h>
#include <cmath>

#include "JicaHeader/JicaHeader.h"

//-------------------------------------------------------------------
#define Data_Win_Err					0
#define Acq_DH_Err					1

class RdpToolsExcep : public exception //clase:superclase
{
public:
//genera 3 string: logfilename: guarda la direccion, info especifica el error y se adjunta a msg, msg nos da el error con tiempo.
//Creará un archivo .log con: la información del error, la fecha y hora del error.
	RdpToolsExcep(int err,char* logpath)//(Data_Win_Err,m_sBaseDirectory);directorio donde se guardará
	{
		time_t seconds;
		char *ptime;

		logfilename.append(logpath);
		logfilename.append("/ProcessErr.log");
		msg.append("Error:\n\t");
		seconds = time(NULL);//NULL=no toma en consideración el parámetro pero igual te da la respuesta en la variable seconds
		ptime =ctime(&seconds);//nos da la hora en formato humano
		switch(err)
		{
			case Data_Win_Err:
				info.append("MyExpParam->MyGPParam.FixPP.m_nData_Windows <= 0");
				msg.append(info);
				info.append("\n\t");
				break;
			case Acq_DH_Err:
				info.append("MyExpParam->MyGRCParam.Dyn_sfAcqDH[0] <= 0");
				msg.append(info);
				info.append("\n\t");
				break;

		}
		//agrega la hora  y fecha del error
		info+="Date: ";
		info+=ptime;info+="\n";
		//DEBUG implementar esto aqui
		msg.append("\n\nRead the ProcessErr.log for more information.");
	}
	~RdpToolsExcep() throw(){}
//-----------------------------------------------------------------------------------------------
	const char* what() const throw()
	{
		FILE* pRdpToolsLog;
		pRdpToolsLog = fopen(logfilename.c_str(),"a");
		//fprintf(pRdpToolsLog,info.c_str());
		fputs(info.c_str(),pRdpToolsLog);
		fclose(pRdpToolsLog);
		return msg.c_str();
	}

private:
	string msg;//se guardará el error
	string info;//informa el error
	string logfilename;//se anexará (append) la direccion del .racp
};
//----------------------------------------------------------------------------------------------

//**************************************************************************************************************************************
//**************************************************************************************************************************************

class RdpToolsBeta
{
public:
	RdpToolsBeta();
	~RdpToolsBeta();
//---------------------------------------------------------------------------------------
//Obtiene punteros a objetos ExpParameters y MemoryManager, para acceder a los parametros
//y a los buffers que se necesitaran para la adquisicion y procesamiento.
	void GetExtParameters(ExpParameters* ExpParam,MemoryManager* MemManger)throw();

/////////////////////////////////////////////////////////////////////////////////////////
private:
	//punteros para acceder a los parametros del experimento y a los buffers creados para
	//este.
	ExpParameters* MyExpParam;
	MemoryManager* MyMemManager;

//---------------------------------------------------------------------------------------
//funcion encargada de cargar los parametros en una estructura tipo params y de cargar
//las funciones a el arreglo process_functions(params&)
	bool initVariables()throw();
};


//*************************************************************************************************************************************
//*************************************************************************************************************************************

//Constructor
RdpToolsBeta::RdpToolsBeta()
{
	MyExpParam=NULL;
	MyMemManager=NULL;

}
//---------------------------------------------------------
RdpToolsBeta::~RdpToolsBeta()
{}
//---------------------------------------------------------
//Inicializa algunas variables (HO,NSA,DH) de Experiment Parameters
//Inicializa los punteros de ExpParameters y MemoryManager
void RdpToolsBeta::GetExtParameters(ExpParameters* ExpParam,MemoryManager* MemManger)throw() //la funcion no generará ninguna excepcion
{	//almacena puntero a objeto con informacion del experimento
	MyExpParam=ExpParam;
	//almacena puntero a objeto con informacion de memoria
	MyMemManager=MemManger;
	//inicializa variables
	initVariables();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//funciones de inicicalizacion de procesos
//Da valor a los parámetros de ventana (H0,NSA,DH),genera excepciones RdpToolsExcepdefine,si las hay, y define Dyn_snCode
//Dyn_snCode=code_binaries=arreglo de arreglos donde cada elemento es un complemento a 2 dependiendo del code_binaries
bool RdpToolsBeta::initVariables()throw()
{
	//numero de muestras que se van a restar debido a la decodificacion
	int restNSA=0;
	//ancho de estas muestras en km
	float restNSAkm=0;

//------------------------------------------------------------------------------------------
	//establece numero de ventanas a m_nData_Windows
	//m_nProcessWindows inicializado como 0 en ExperimentParameters y queda ese valor.
	if(MyExpParam->MyGPParam.m_nProcessWindows>0)
	{
		MyExpParam->MyGPParam.FixPP.m_nData_Windows = MyExpParam->MyGPParam.m_nProcessWindows;
	}
	else
	{
		MyExpParam->MyGPParam.FixPP.m_nData_Windows = MyExpParam->MyGRCParam.FixRCP.m_nNum_Windows;
	}
// Nos genera una excepcion de error
	if(MyExpParam->MyGPParam.FixPP.m_nData_Windows <= 0)//m_nData_Windows será mínimo 1
	{
		throw RdpToolsExcep(Data_Win_Err,MyExpParam->MyGPParam.m_sBaseDirectory);//genera la excepcion definida en RdpToolsExceptions
	}																			 //Excepcion de error
//--------------------------------------------------------------------------------------------------------------
	//crea arreglos para almacenar los valores de los parametros de las ventanas
	//Altura inicial,número de muestras,resolución(problema m_nData_Windows inicializado con 1 ¿Cuándo cambia?)

	MyExpParam->MyGPParam.Dyn_sfDataH0 = new float[MyExpParam->MyGPParam.FixPP.m_nData_Windows];
	MyExpParam->MyGPParam.Dyn_snDataNSA = new unsigned int [MyExpParam->MyGPParam.FixPP.m_nData_Windows];
	MyExpParam->MyGPParam.Dyn_sfDataDH = new float[MyExpParam->MyGPParam.FixPP.m_nData_Windows];

	//ingresa los valores de los parametros de ventana dependiendo de m_nData_Windows
	//Da valores de H0,NSAyDh a DataHo,NSA y DH
	for(size_t i=0;i<MyExpParam->MyGPParam.FixPP.m_nData_Windows;i++)
	{
		//en muestras(¿Por qué se van a restar muestras en decodificación?)
		restNSA = -int(restNSAkm/MyExpParam->MyGRCParam.Dyn_sfAcqDH[i]);//numero de muestras adquiridas
		restNSA+= (restNSAkm==0)?0:1;//será cero.
		MyExpParam->MyGPParam.Dyn_sfDataH0[i]  = MyExpParam->MyGRCParam.Dyn_sfAcqH0[i];//el valor del .racp es guardado dentro de Dyn_sfDataH0
		MyExpParam->MyGPParam.Dyn_snDataNSA[i] = MyExpParam->MyGRCParam.Dyn_snAcqNSA[i] +restNSA;//Para hallar el valor de Dyn_snDataNSA se resta del .racp debido a la decodificacion?
		MyExpParam->MyGPParam.Dyn_sfDataDH[i]  = MyExpParam->MyGRCParam.Dyn_sfAcqDH[i];//el valor del .racp es guardado dentro de Dyn_sfDataDH
	}
	//---------------------------------------------------------------------
	//Initialization of m_sCodeArray_char
	//---------------------------------------------------------------------
	//Nos lleva a RdpToolsExcep si se cumple la condición
	if(MyExpParam->MyGRCParam.Dyn_sfAcqDH[0] <= 0)
	{
		throw RdpToolsExcep(Acq_DH_Err,MyExpParam->MyGPParam.m_sBaseDirectory);
	}

	return true;
}

//---------------------------------------------------------------------------

#endif


