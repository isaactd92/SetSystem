#ifndef ARGPROCESSOR_JARSCONTROL_JARSCONTROL_H_
#define ARGPROCESSOR_JARSCONTROL_JARSCONTROL_H_

#include "RdpToolsBeta/RdpToolsBeta.h"
//************************#include "arriba/\"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

#include <string.h>
#include <zmq.hpp>

#include  <vector>
#include <stdint.h>
#include <assert.h>

#include <bits/stdc++.h>

#include <sys/socket.h>
#include <netinet/in.h>//define las estructuras : struct sockaddr_in, struct in_addr
#include <arpa/inet.h>
#include <netdb.h>

//******************************* librerías para socket UDP bind ****************************************************
#include <gnuradio/math.h>
#include <gnuradio/prefs.h>
#include <stdexcept>
#include <errno.h>

#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <gnuradio/thread/thread.h>

//********************************************************************************************************************
//************************************Structura fpga_con_t *******************************************************

//boost::asio::ip::udp::endpoint local_endpoint;
boost::asio::ip::udp::socket* local_socket;
boost::asio::io_service local_io_service;

boost::asio::ip::udp::endpoint destino_endpoint_to;

void fpga_con_init(char* host, int lport);
ssize_t fpga_con_send( const char *buf, size_t len );
ssize_t fpga_con_recv(char *dbuf, size_t dsize );

void IPstr_to_bytearray(char *IPstr, char *parts);
void MACstr_to_bytearray(char *MACstr, char *parts);
void intToBytes(int number, char *arrayOfByte, size_t size);
void bytearray_to_IPstr(const char *bytes, char *IPstr);
void bytearray_to_int(const char *byte_array, int num);
void bytearray_to_MACstr(const char *bytes, char *MACstr);
char* itoa(int num, char* str, int base);

//*****************************************************************************************************************************
//****************************** Clase SP601_command ********************************************************************
#define RCV_BUFSIZE 1472

enum JARS_CMD {	NOOP, SET_SP601_IP, SET_SP601_PORT, GET_SP601_MAC, SET_COMMS_IP, SET_COMMS_PORT, SET_COMMS_MAC, GET_VALUE, DATA_LOOPS, SEND_COMMAND, CHECK_ACK, SEND_FILTER};

struct address{
   const char* d_path_file;
   std::string d_mac_block;
   int d_port_block;
   std::string d_ip_host;
};

// Se utilizan las definiciones de comandos del archivo ExperimentConstants.h
#define		RST_CTRL				0x05
#define		MODE_OPER				0x03
#define		ELECTION_RXD				0x04
#define		POWER_RXD				0x06
#define		PROG_RXD				0x09
#define		ENABLE_TRANSF				0x0A
#define		DISABLE_TRANSF				0x0B

//Declara la estructura jars_cmd: {"NOOP",0,0,false}
struct jars_cmd{
	const char *name;
	char val;
	char size;
	bool ack;
};


class sp601_command
{
public:
	sp601_command();
	~sp601_command();
	void init(address host_address);
	ssize_t receive(char *buffer_rcv);
	void send(uint8_t cmd, char code, const char *payload, size_t size_payload);
};


//********************************* Clase _JARSControl *********************************************************************
//**************************************************************************************************************************
class _JARSControl
{
protected:

	void InternalRcv();
	void InternalThreadEntry();
	void InternalCallback();

public:

       //**********************************************************************
	_JARSControl();
	~_JARSControl();
    	//Parameters of Experiment (luego pasar a AcquisitionManager.h)
	ExpParameters* MyExpParam;
	int m_SizeofBuffer;//adquiere el valor del tamaño del buffer
	void* m_AcqBuffer;//arreglo del buffer que guardará la data obtenida dependiendo si es short or float en tipo 16sc
	//Pointer to client function in order to get advised when interrupt came
	void (*ptrFunc)(bool success);//_AcquisitionManager//toma el valor de ptrClientFunc asignado en jro_AssignMemory
    	//Function that receives a pointer from ExperimentParameters

	void jro_MatchParameters(ExpParameters* ExpParam);
	void jro_AssignMemory(MemoryManager* MemManager, void (*ptrClientFunc)(bool sucess),address host_address);
	bool jro_InitAcquisition();
	bool jro_StopAcquisition();
	static void * InternalRcvFunc(void * This);
	static void * InternalThreadEntryFunc(void * This);
	static void * InternalCallbackFunc(void * This);

private:
	//Instanciacion de sp601_command
	sp601_command* MySP601;
	pthread_t _thread_rcv;		// thread for acquire UDP packets
	pthread_t _thread_jars;		// thread for acquire UDP packets
	pthread_t _thread_jars_rcv;		// thread for acquire UDP packets
	pthread_t _thread_config;		// thread for acquire UDP packets
	int VarSetSystem;//valor tomado si está mal seteado
	int16_t m_nChannelsMask; //variable q contiene la mascara de canales adquirir
	int16_t m_nCardsMask; //variable q contiene la mascara de programacion de tarjetas conectadas
	uint16_t m_nFilterCoeff[2047]; // arreglo donde se guardan los coefficientes del filtro
	size_t    m_nCountCoeff; // contador de coeficientes

	//Number of Marks, el valor para el JARS es 2
	int m_NumMarks;
	//Mark in Data Real
	int m_MarkRe;
		//Pointer to Acquired Buffer
	void* m_AcqNIBuffer;//buffer más grande separado en memoria
	//Pointer to double memory used for Traditional NIDAQ
	void* m_AcqNIDoubleBuffer;//doble buffer más grande separado en memoria
	//Payload to send jars command
	char payload[16];
	/*************************************************************/
	void RemoveMark(); //Fx to remove marks in data
  	/************************************************************/
	bool RESET_CTRL_COMMAND();
	bool MODE_OPER_COMMAND();
	bool SELECT_RXD_COMMAND(); //enviado pero no procesado.
	bool PW_RXD_COMMAND();
	bool PROG_RXD_COMMAND();
	bool HAB_TRANS_COMMAND();
	bool DESHAB_TRANS_COMMAND();
	/************************************************************/
	bool LoadMask(); // Fx q carga la máscara de programación
	bool ConfigDataTransfer(); // Fx q envia la cantidad de muestras del perfil y NTX que se debe adquirir
	bool SetSystem(address host_address); // Funcion encargada de dejar listo el sistema para adquisicion
	bool LoadFilter(); // Fx q carga la los coefcicientes del filtro
	bool WriteFilter(); // Fx q escribe la los coefcicientes del filtro

};

//*************************************************************************************************************************

_JARSControl JARSControl;

//*************************************************************************************************************************
//********************************Clase sp601_config **********************************************************************
class sp601_config
{
public:

    char *SP601_MAC;   		        //  Must convert to hex if used//Espacio de memoria donde se guarda el valor de la MAC del SP601 + null
    char *SP601_IP;          		// Defined in Xilnx ISE ethernet_control.v//Espacio de memoria donde se guarda el valor de la IP del SP601 + null
    int SP601_PORT;                     // Defined in Xilnx ISE ethernet_control.v//Espacio de memoria donde se guarda el valor del puerto del SP601 + null
    string sp601_ip_string;		// IP del SP601 usado cuando definimos un endpoint tipo boost.
    char *IP_host;			// Se usará para mostrar info de la IP switch-send
    char *MAC_host;			// Se usará para mostrar info del MAC en switch-send
    int PORT_host;			// Se usará para mostrar info del puerto en switch-send

    char REPLY_START_DATA_PAYLOAD[2];   // AB, defined in DEFAULT_START_DATA_PAYLOAD (ethernet_control.v)
    char UDP_timeout;

    bool VERBOSE_MODE;			// Atributo de sp601_config
    sp601_config();			// Declara un constructor
};

//***************************************************************

sp601_config cfg;// objeto de sp601_config

//*****************************************************************

//********************************************************************************************************************  ^
//******************************************* Declara clases -----------------------------------------------------------|


//******************************************* Define clases  -----------------------------------------------------------|
//********************************************************************************************************************  v
//******************************************* Define la clase sp601_config *******************************************

//Constructor de sp601_config
//**************************** Establece los parámetros de RED ******************************************
sp601_config::sp601_config()
{
  //************************ Define values for network parameters ********************************
  //IP,MAC,puerto del sp601
  char sp601_ip[] = "192.168.1.6";//"Para el ROJ:10.10.30.123";//localizador de mi host en la red
  char sp601_mac[] = "30:9c:23:d0:1b:ca";//Para el ROJ: "00:0a:35:02:05:f2";//dirección única MAC, que identifica un elemento de la capa de enlace de datos(tarjeta   	de red)//Se establece en el main
  int sp601_port = 9097; //Para el ROJ: 52428;

  //IP y puerto del sp601 en string
  string sp601_ip_string = string(sp601_ip);

  //IP,MAC,puerto de la tarjeta de red serán dados por el bloque

  //****Guarda los valores de la red establecidos en memoria con su null (ya que estamos en size_t correctito)
  //Guarda el valor de la ip del sp601
  SP601_IP=(char *)malloc(strlen(sp601_ip)+1);//toma el término null caracter (string literal)
  memcpy(SP601_IP,sp601_ip,strlen(sp601_ip)+1);
  //Guarda el valor de la mac del sp601
  SP601_MAC=(char *)malloc(strlen(sp601_mac)+1);//
  memcpy(SP601_MAC,sp601_mac,strlen(sp601_mac)+1);
  //el valor del puerto de la sp601 es guardado en SP601_PORT
  SP601_PORT = sp601_port;
  //Establece los parámetros de UDP
  UDP_timeout = 100;
  VERBOSE_MODE = true;
}

//*********************************************************************************************************************
//******************************************* Define la clase JARSControl *********************************************
_JARSControl::_JARSControl()
{
	m_NumMarks=2;                  //2 elementos de la cabecera por eliminar
	m_MarkRe=-21846;	       //marca para comprobar la cabecera del JARS 2.0
	m_SizeofBuffer=0;              // se igualará a m_iSizeNIBuffer
	m_AcqNIBuffer=NULL;            //Doble Buffer
	m_AcqNIDoubleBuffer=NULL;      //Doble Buffer
	m_AcqBuffer=NULL;              //Buffer de adquisición
	m_nChannelsMask=0;             //Define los canales a energizar y adquirir
	m_nCardsMask=0;                //Se envía al JARS pero no definen canales físicos.Se usó para simular canales
	VarSetSystem=0;                //valor tomado para ver el estado de seteado
	MySP601 = new sp601_command(); //Crea un objeto de la clase sp601_command.

}

_JARSControl::~_JARSControl()
{
  JARSControl.jro_StopAcquisition();
  printf("Terminating program...\n");
  sleep(1);
  exit(1);//termina el proceso
}

//Define los parámetros del experimento (MyExpParam) con el parámetro ExpParam introducido en jro_MatchParameters
//Define MyExpParam para un objeto de la clase _JARSControl. Este objeto se usará para sincronizar la data en tiempo real
//entre threads.
void _JARSControl::jro_MatchParameters(ExpParameters* ExpParam)
{
	MyExpParam=ExpParam;
	//Usado en ConfigDataTransfer
	JARSControl.MyExpParam=ExpParam; // agregado para q actualice campo MyExpParam de JARSControl
	return;
}

//Llamará a los buffers de adquisición, doble buffers , al puntero de la función que comenzará el almacenamiento en disco
//y establecerá el sistema con SetSystem
void _JARSControl::jro_AssignMemory(MemoryManager* MemManager,void (*ptrClientFunc)(bool sucess),address host_address)
{	//Asigna los buffer de adquisición y memoria
	m_SizeofBuffer=MemManager->m_iSizeNIBuffer;//tamaño del buffer más grande (sin integraciones)
	m_AcqBuffer=MemManager->m_mAcqBuffer[0];//buffer de adquisición
	m_AcqNIBuffer=MemManager->m_nNIBuffer;//buffer más grande separado en memoria //buffer para threads
	m_AcqNIDoubleBuffer=MemManager->m_nNIDoubleBuffer;//doble buffer más grande separado en memoria//buffer para threads
	ptrFunc=ptrClientFunc;

	if (!SetSystem(host_address))//si es seteado correctamente, regresa true//Se puede llamar a métodos que pertenecen a la misma clase dentro de otros métodos
	   VarSetSystem=1;
	usleep(100000);/**/ //microsegundos
	return;
}

//****** Define el socket y establece las direcciones de puertos ********************************
//****** Establece las máscaras (tarjeta y canales) y el filtro***************************************************************
//****** Envía los comandos de configuración del JARS:RESET,MODE_OPER,SELECT_RXD,PW_RXD,PROG_RXD,WRT_FILT*******
//**** Nos dice si el seteado del sistema se realizó correctamente devolviendo un true ***********
bool _JARSControl::SetSystem(address host_address)
{
	//-------------- Define el socket y Establece las direcciones de puertos -------------------------------
	//-------------- Definiremos sockets UDP de GNU Radio --------------------------------------------------
	MySP601->init(host_address);// Inicializar parametros para comunicacion con tarjeta SP601 (tarjeta de bus)(nvia los puetos de la Pc y la SP601 a la SP601)
	//---------Detecta si las máscaras utilizadas por el objeto JARSControl fueron definidas----------------------------
	//---------Define parte del paquete (máscara) que será enviado para encender y seleccionar los canales de adquisición.
	if(!JARSControl.LoadMask()) // Lee la máscara de programacion del *.racp
		return false;
	usleep(50000);//suspende la ejecución por 50 seg.
	//----------Utiliza el .jars para establecer las direcciones del filtro---------------------------------------------
	if(!JARSControl.LoadFilter()) // Carga el archivo del filtro y define los valores para el AD6620
	    return false;
	usleep(50000);/**/
	//----------- Envía un comando para resetear el JARS ------------------------------------------
	if(!JARSControl.RESET_CTRL_COMMAND()) // Resetea el sistema, reinicia todos los FPGA's
		return false;
	//---------- if GENERATE OWN SAMPLING WINDOW=YES del .racp----------------------------------
	if(MyExpParam->OwnWindow)
	////----------  Envía el comando MODE_OPER al JARS ---------------------------------------------
	  if(!JARSControl.MODE_OPER_COMMAND())
	    return false;
	usleep(50000);/**/
	//------------- Envía el comando ELECTION_RXD al JARS -----------------------------------------
	if(!JARSControl.SELECT_RXD_COMMAND())//selecciona las tarjetas de adquisición//usado para simular , no procesado
		return false;
	usleep(50000);
	//------------- Envía el comando POWER_RXD al JARS -----------------------------------------
	//Enciende las tarjetas de adquisición y envia las máscaras de los canales
	if(!JARSControl.PW_RXD_COMMAND()) // Alimenta los receptores digitales y envia la mascara de los canales seleccionados
		return false;
	usleep(50000);/**/
	//------------- Envía el comando PROG_RXD al JARS -----------------------------------------
	if(!JARSControl.PROG_RXD_COMMAND()) // Envía el comando que permitirá programar el DSP AD6620
		return false;
	usleep(50000);/**/
	//------------- Relacionado con filter -----------------------------------------
	if(!JARSControl.WriteFilter()) // Envía a través del puerto de datos los coeficientes del filtro
	     return false;
	usleep(50000);/**/
	return true;
}

//******* Define las máscaras de las tarjetas conectadas y los canales seleccionados ********************************
//******* Define parte del paquete que será enviado para encender y seleccionar los canales de adquisición.
//JARSControl.m_nChannelsMask: define los canales a energizar y adquirir
//JARSControl.m_nCardsMask: se envía al JARS pero no definen canales físicos.Se usó para simular canales
bool _JARSControl::LoadMask()
{
	//----------------(Carga de máscara de tarjetas conectadas) Para simular   --------------------------------
	//****************m_nCardsMask= 11 elementos : ceros = (# tarjetas-1), unos = 11- # ceros *******************
	for(uint8_t i=0; i<MyExpParam->MyGPParam.m_nCards; i++)//uint8_t = unsigned char
	{
		if (MyExpParam->MyGPParam.Dyn_nCardSequence[i]==0)
		{	continue;}
		else//Dyn_nCardSequence = 8bits. Corren un bit a la izquierda <<
			//Adquiere el valor de la máscara de cada tarjeta (m_nCardsMask inicializado en 0 en el constructor)
			JARSControl.m_nCardsMask=JARSControl.m_nCardsMask | (1<<(MyExpParam->MyGPParam.Dyn_nCardSequence[i]-1));// | es un bitwise OR
	}
	JARSControl.m_nCardsMask^=255; //^ es un XOR .Se realiza un XOR entre: m_nCardsMask y 255 y nos da m_nCardsMask
	JARSControl.m_nCardsMask=JARSControl.m_nCardsMask | 1792;
	printf("Cards mask was loaded\n");
	//------------------ Carga de mascara de canales seleccionados --------------------------------
	//******************m_nChannelsMask= 11 elementos : ceros = # canales, unos = 11- # canales *******************
	for(int i=(MyExpParam->MySystemParam.m_nChannels-1); i>=0; i--)
	{
		if (MyExpParam->MySystemParam.m_nNumberOfChannel[i]==0)
		{	continue;}
		else
			JARSControl.m_nChannelsMask=JARSControl.m_nChannelsMask | (1<<(MyExpParam->MySystemParam.m_nNumberOfChannel[i]-1));
	}
	JARSControl.m_nChannelsMask^=255;
	JARSControl.m_nChannelsMask=JARSControl.m_nChannelsMask | 1792;
	printf("Channels mask was loaded\n");
	return true;
}

//Lee el archivo .jars que contiene la configuracion de los filtros del DSP.
//*********Define el arreglo m_nFilterCoeff donde sus elementos son valores hexadecimales que definen los registros del DSP y establecen los parámetros del filtros (decimació)
//Solo define , no  envía.
//Pd: Exsite un protocolo entre el FPGA de Programacion y el DSP antes de establecer los valores
bool _JARSControl::LoadFilter()
{
	int Adress300=0x300, Adress0=0x0, AdressTemp;
	int16_t CoeffTemp;

	FILE* MyRacpFile;
	char StrTemp[100];
	char* StrPtr;

	printf("%s\n", MyExpParam->MySystemParam.m_sFilterPath);
	MyRacpFile=fopen(MyExpParam->MySystemParam.m_sFilterPath,"r");//abre la direccion solo lectura
	if((MyRacpFile)==0)
	{
		printf("No filtro ingresado, tomando filtro por defecto\n");
	}

	for(;;)
	{	if(feof(MyRacpFile))//si llega al final
		{	fclose(MyRacpFile);
			break;
		}
		fgets(StrTemp,100,MyRacpFile);//lee las 100 primeras variables de MyRacpFile , incluyendo el null-character
		if (StrTemp[0]=='3' || StrTemp[0]==' ')
		{	if (StrTemp[0]=='3')
				AdressTemp=Adress300++; // primer  bloque de direcciones 300h -> 30Dh

			if (StrTemp[0]==' ')
				AdressTemp=Adress0++;// segundo bloque de direcciones 000h -> ?
			JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]=(((AdressTemp>>8) & 0x000000FF ) | 0x00000700);
			JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]= ((AdressTemp & 0x000000FF) | 0x00000600);

			StrPtr=strstr(StrTemp, "->");
			StrPtr+=2;
			if (AdressTemp==0x302)
			{	for(int j=0; j<4; j++)
				JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]=(0xFF | (3-j)<<8);
			}
			else
			{
				for(int j=0;j<4;j++)
				{	if ((((CoeffTemp=(atoi(StrPtr)>>((3-j)<<3))& 0x00FF)==0) & (j!=3)) && AdressTemp>=0x300)
						continue;
					else
					{	JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff]=(CoeffTemp |(3-j)<<8);
						JARSControl.m_nCountCoeff++;}
				}
			}
		}

		if (StrTemp[0]=='R') // Se terminan de leer los coefficientes, creo los ultimos caracteres finales
		{	JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]= 0x03 | 0x00000700;
			JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]= 0x00 | 0x00000600; // 300h
			JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]= 0x01 | 0x00000000; // 0x01
			JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]= 0x03 | 0x00000700;
			JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]= 0x00 | 0x00000600; // 301h
			JARSControl.m_nFilterCoeff[JARSControl.m_nCountCoeff++]= 0x00 | 0x00000000; // 0x00
			fclose(MyRacpFile);
			printf("Filter was loaded\n");
			return true;
		}
	}
  return true;
}

//--------- Define el payload de RST_CTRL para ser enviado en formato de bytes y lo envía----------
//********* Imprime: Nombre de comando,tipo de operación,paquete de dato recibido*******
bool _JARSControl::RESET_CTRL_COMMAND()
{
	int	cmd_jars=0;//4 bytes
	char payload[16]={};
	size_t size_payload=3;//24 bits
	//unsigned long int size_payload=3;
	printf("Reset JARS\n");
	cmd_jars = SYNCHRO;
	cmd_jars = (cmd_jars<<2)^CHIP_ALL;
	cmd_jars = (cmd_jars<<4)^RST_CTRL;//**define tipo de operación
	cmd_jars = (cmd_jars<<1)^BY_CMD;
	cmd_jars = (cmd_jars<<11)^0x00;
	cmd_jars = (int)cmd_jars;
	//Define el payload como 3 bytes de cmd_jars
	intToBytes(cmd_jars,payload,size_payload);
	//Envía el cmd_array con los bytes configurados para el comando RST_CTRL
	MySP601->send(SEND_COMMAND,0,payload,size_payload);
	//da valor a los elementos del buffer payload igual a cero
	memset(payload,0,strlen(payload));
  return true;
}

//------- Define el payload de MODE_OPER para ser enviado en formato de bytes. Esto hace que JARS 2.0 genere su propio win sin el CR------
//******************* Imprime: Nombre de comando,tipo de operación,paquete de dato recibido*******
bool _JARSControl::MODE_OPER_COMMAND()
{
	int	cmd_jars=0;
	char payload[16]={};
	size_t size_payload=3;
	printf("Operation Mode JARS\n");
	cmd_jars = SYNCHRO;
	cmd_jars = (cmd_jars<<2)^CHIP_ALL;
	cmd_jars = (cmd_jars<<4)^MODE_OPER;//**define tipo de operación
	cmd_jars = (cmd_jars<<1)^BY_CMD;
	cmd_jars = (cmd_jars<<11)^0x00;
	cmd_jars = (int)cmd_jars;
	//Define el payload como 3 bytes de cmd_jars
	intToBytes(cmd_jars,payload,size_payload);
	//Envía el cmd_array con los bytes configurados para el comando MODE_OPER.Imprime los arreglos seleccionados
	MySP601->send(SEND_COMMAND,0,payload,size_payload);
	//da valor a los elementos del buffer payload igual a cero
	memset(payload,0,strlen(payload));
  return true;
}

//------------------- Define el payload de ELECTION_RXD para ser enviado en formato de bytes// Simulacion de canales------
//******************* Imprime: Nombre de comando,tipo de operación,paquete de dato recibido*******
bool _JARSControl::SELECT_RXD_COMMAND()
{
	int	cmd_jars=0;
	char payload[16]={};
	size_t size_payload=3;
	printf("Select receivers\n");
	cmd_jars = SYNCHRO;
	cmd_jars = (cmd_jars<<2)^CHIP_ALL;
	cmd_jars = (cmd_jars<<4)^ELECTION_RXD;//**define tipo de operación
	cmd_jars = (cmd_jars<<1)^BY_CMD;
	cmd_jars = (cmd_jars<<11)^JARSControl.m_nCardsMask;
	cmd_jars = (int)cmd_jars;
	//Define el payload como 3 bytes de cmd_jars
	intToBytes(cmd_jars,payload,size_payload);
	//Envía el cmd_array con los bytes configurados para el comando ELECTION_RXD.Imprime los arreglos seleccionados
	MySP601->send(SEND_COMMAND,0,payload,size_payload);
	//da valor a los elementos del buffer payload igual a cero
	memset(payload,0,strlen(payload));
  return true;
}

//------------------- Define el payload de POWER_RXD para ser enviado en formato de bytes --------
//******************* Imprime: Nombre de comando,tipo de operación,paquete de dato recibido ******
bool _JARSControl::PW_RXD_COMMAND()
{
	int	cmd_jars=0;
	char payload[16]={};
	size_t size_payload=3;
	printf("Power the selected receivers\n");
	cmd_jars = SYNCHRO;
	cmd_jars = (cmd_jars<<2)^CHIP_COMAND;
	cmd_jars = (cmd_jars<<4)^POWER_RXD;//**define tipo de operación
	cmd_jars = (cmd_jars<<1)^BY_CMD;
	cmd_jars = (cmd_jars<<11)^JARSControl.m_nChannelsMask;
	cmd_jars = (int)cmd_jars;
	//Define el payload como 3 bytes de cmd_jars
	intToBytes(cmd_jars,payload,size_payload);
	//Envía el cmd_array con los bytes configurados para el comando POWER_RXD.Imprime los arreglos seleccionados
	MySP601->send(SEND_COMMAND,0,payload,size_payload);
	//da valor a los elementos del buffer payload igual a cero
	memset(payload,0,strlen(payload));
  return true;
}

//--------------Define el payload de PROG_RXD para ser enviado en formato de bytes--------------
//**************Imprime: Nombre de comando,tipo de operación,paquete de dato recibido***********
bool _JARSControl::PROG_RXD_COMMAND()
{
	int	cmd_jars=0;
	char payload[16]={};
	size_t size_payload=3;
	printf("Program the selected receivers\n");
	cmd_jars = SYNCHRO;
	cmd_jars = (cmd_jars<<2)^CHIP_COMAND;
	cmd_jars = (cmd_jars<<4)^PROG_RXD;//**define tipo de operación
	cmd_jars = (cmd_jars<<1)^BY_DATA;
	cmd_jars = (cmd_jars<<11)^JARSControl.m_nCountCoeff;
	cmd_jars = (int)cmd_jars;
	//Define el payload como 3 bytes de cmd_jars
	intToBytes(cmd_jars,payload,size_payload);
	//Envía el cmd_array con los bytes configurados para el comando PROG_RXD.Imprime los arreglos seleccionados
    MySP601->send(SEND_COMMAND,0,payload,size_payload);
    //da valor a los elementos del buffer payload igual a cero
	memset(payload,0,strlen(payload));
  return true;
}

//***************** Envía los coeficientes de configuracion establecidos en el LoadFilter al SP601 *******************
//***************** Recibe el buffer_rcv de respuesta y lo muestra en formato hexadecimal ****************************
bool _JARSControl::WriteFilter()
{
    char vector_coeff[256];
    char payload[4]={};
    size_t size_vector_coeff=2*(JARSControl.m_nCountCoeff+1);//envia en char, considera en peso el '0'
    // Write Filter
    printf("Write Filter\n");
    printf("%lu coefficients\n",size_vector_coeff);
    vector_coeff[0]=0; vector_coeff[1]=0;
    //printf("%i,%i\n",vector_coeff[0],vector_coeff[1]);
    //***Define el vector_coeff el cual será enviado como payload en send***
    for(unsigned int i=0;i<JARSControl.m_nCountCoeff;i++){
        intToBytes(JARSControl.m_nFilterCoeff[i],payload,2);//los coeficientes los pasa a bytes (2 partes)
        vector_coeff[2*i+2]=payload[0];//guarda la primera parte
        vector_coeff[2*i+3]=payload[1];//guarda la segunda parte
    }
    MySP601->send(SEND_FILTER,0,vector_coeff,size_vector_coeff);//ENVIA EN BYTES
  return true;
}

//** Verifica si se habilitó la transferencia de comandos y el configDataTransfer************
bool _JARSControl::jro_InitAcquisition()//
{
  if(VarSetSystem)//VarSetSystem=0 está bien
    return false;
  //Habilitado la transferencia de datos , nos da true al final
  if(!JARSControl.HAB_TRANS_COMMAND())  // Activa los receptores digitales
    return false;
  // Inicializa la adquisición, la generación de threads zmq y define el parámetro del puntero de función
  if(!JARSControl.ConfigDataTransfer())
  	return false;
  usleep(50000);
  return true;
}

//----- Define el payload de ENABLE_TRANSF q habilita la tranf de comandos y lo envía al SP601-----------
//***** Imprime: Nombre de comando,tipo de operación,paquete de dato recibido*************
bool _JARSControl::HAB_TRANS_COMMAND()
{
	int  cmd_jars=0;
	char payload[16]={};
	size_t size_payload=3;
	printf("Enable data transfer\n");
	cmd_jars = SYNCHRO;
	cmd_jars = (cmd_jars<<2)^CHIP_ALL;
	cmd_jars = (cmd_jars<<4)^ENABLE_TRANSF;//**define tipo de operación
	cmd_jars = (cmd_jars<<1)^BY_CMD;
	cmd_jars = (cmd_jars<<11)^0x00;
	cmd_jars = (int)cmd_jars;
	//Define el payload como 3 bytes de cmd_jars
	intToBytes(cmd_jars,payload,size_payload);
	//Envía el cmd_array con los bytes configurados para el comando ENABLE_TRANSF.Imprime los arreglos seleccionados
	MySP601->send(SEND_COMMAND,0,payload,size_payload);
  return true;
}

//**************   Método que inicializa la adquisición, la generación de threads zmq y el guardado de la data en disco
//**************   La única forma de salir de los bucles de los threads es con una interrupción externa Cnt+c
bool _JARSControl::ConfigDataTransfer()
{	float IPP,DH;
	unsigned int NTX, Nchannels, Nsamples_by_channel;
	unsigned int Nsamples;
	unsigned int Nprofilesperblock;
	unsigned int IPPu;

	char payload[4];
	//************ Establece parámetros de adquisición del radar para ser enviados **************************************************
	IPP=(float)(JARSControl.MyExpParam->MyGRCParam.FixRCP.m_fIPP);//valor de la Ipp del .racp
	NTX = (unsigned int)(JARSControl.MyExpParam->MyGRCParam.FixRCP.m_nNTX);//numero de ipp por synchr
	DH = (float)(JARSControl.MyExpParam->MyGRCParam.Dyn_sfAcqDH[0]);//resolución de altura
	IPPu = ceil(IPP/DH);//redondea para arriba //cantidad de DHs por Ipp
	Nchannels = (unsigned int)(JARSControl.MyExpParam->MySystemParam.m_nChannels);
	Nsamples_by_channel=(unsigned int)(JARSControl.MyExpParam->MyGRCParam.Dyn_snAcqNSA[0]);// número de muestras por canal para un perfil
	Nsamples = Nchannels*Nsamples_by_channel+1;//numero de muestra en todos los canales para un perfil
	Nprofilesperblock = MyExpParam->MyGPParam.m_nProfilesperBlock;

	if(IPPu>65536){
		printf("Units of IPP exceeded! %i",IPPu);
		exit(1);
	}else printf("IPP(Km/units): %.1f, %i\n",IPP,IPPu);

	if(NTX>65536){
		printf("Number of NTX exceeded! %i",NTX);
		exit(1);
	}else printf("Number of NTX: %i\n",NTX);

	printf("Resolution: %.4f\n",DH);

	if(Nsamples>4294967296) {
		printf("Number of samples per profile exceeded! %i\n",Nsamples);
		exit(1);
	}else printf("Number of Samples per profile: %i\n",Nsamples);

	printf("Number of Profiles per block: %i\n",Nprofilesperblock);
	printf("Number of Samples for all profiles: %i\n",Nsamples*Nprofilesperblock);

	//IPP=1000
	//payload[0]=0x03;payload[1]=0x20
	payload[0]=(char)(IPPu>>8); payload[1]=(char)(IPPu);	// Load IPPunits
	//payload[2]= 0x00 ; payload[3]=0x96
	payload[2]=(char)(NTX>>8); payload[3]=(char)(NTX);	// Load NTX
	//payload[4]=0x00 ; payload[5]= 0x00
	payload[4]=(char)(Nsamples>>24); payload[5]=(char)(Nsamples>>16);	// Load SamplesperProfile
	//payload[6]=0x03 ; payload[7]=0xE9
	payload[6]=(char)(Nsamples>>8); payload[7]=(char)(Nsamples);
	MySP601->send(DATA_LOOPS,0,payload,8); // 2 bytes for IPPunits, 2 bytes for NTX, 4 bytes for SamplesperProfile

//************************Se crean threads paralelos en el proceso JARSControl que realizan las tareas de Internalx***********************
//Ejecuta la parte del socket para la recepcion de paquetes
	if(pthread_create(&JARSControl._thread_rcv, NULL, JARSControl.InternalRcvFunc, this)==0)
		printf("Now the packets receiver thread starts\n");
	if(pthread_create(&JARSControl._thread_jars, NULL, JARSControl.InternalThreadEntryFunc, this)==0)
		printf("Now the block constructor thread starts\n");
	if(pthread_create(&JARSControl._thread_jars_rcv, NULL, JARSControl.InternalCallbackFunc, this)==0)//define el puntero
	{
	   printf("Now the block save thread s_thread_configtarts\n");
	   return true;
	}
	else
	{
	  return false;
	}
}

//verifica si se detuvo la adquisicion mediante el envio del comando de deshabilitacion y reseteo del JARS
//Envia un request de cancelación al thread de origen de bloques
bool _JARSControl::jro_StopAcquisition()
{
	if(!JARSControl.DESHAB_TRANS_COMMAND())//Envía el comando de deshabilitación
		return false;
	if(!JARSControl.RESET_CTRL_COMMAND()) // Resetea el sistema, reincia todos los FPGA's
		return false;
	// Terminating acquisition thread
	printf("Terminating acquisition thread...\n");
	pthread_cancel(JARSControl._thread_jars);	// Sending cancellation request//cancela el thread por si queda data guardada
	sleep(0.5);
	return true;
}

//--- Define un payload con comando 0x00 y el payload de DISABLE_TRANSF para ser enviado en formato de bytes-----------
//comando 0x00: crea el arreglo cmd_array.NO crea  info_Str,buffer_rcv
//comando DISABLE_TRANSF: genera el cmd_array,info_str, recive en el buffer_rcv,imprime el nombre de comando, estdo de comando de config y buffer_rcv.NO imprime el cmd_array
//***** Espera la finalizacion de la adquisición y envia el comando de deshabilitación.
bool _JARSControl::DESHAB_TRANS_COMMAND()
{
	int  cmd_jars=0;
	char payload[16]={};
	size_t size_payload=3;

	// ********close all the threads
	// ********Espera a que el hilo _thread_rcv acabe (termina el hilo _thread_rcv y devuelve NULL a nuestro hilo de trabajo)
	//Al terminar ese thread, continuará esta parte.Los demás threads continuarán
	pthread_join(_thread_rcv, NULL);
	//************ Previous command to exit JARS from acquisition loop
	//sp601_command('NOOP',0,int_to_bytearray(0,3))
	//************ Crea el payload antes del comando de deshabilitación ***********
	//************ Por qué envía 0x00
	cmd_jars = SYNCHRO;
	cmd_jars = (cmd_jars<<2)^CHIP_ALL;
	cmd_jars = (cmd_jars<<4)^0x00;
	cmd_jars = (cmd_jars<<1)^BY_CMD;
	cmd_jars = (cmd_jars<<11)^0x00;
	cmd_jars = (int)cmd_jars;
	//Define el payload como 3 bytes de cmd_jars
	intToBytes(cmd_jars,payload,size_payload);
	//Envía el cmd_array con los bytes configurados para el comando NOOP
	MySP601->send(NOOP,0,payload,size_payload); // No muestra nada
	usleep(50000);//suspende la ejecución por 0.5 segundos

	//********** Crea el payload oara el comando de deshabilitacion *****************
	printf("Disabling data transfer...\n");
	cmd_jars = SYNCHRO;
	cmd_jars = (cmd_jars<<2)^CHIP_ALL;
	cmd_jars = (cmd_jars<<4)^DISABLE_TRANSF;
	cmd_jars = (cmd_jars<<1)^BY_CMD;
	cmd_jars = (cmd_jars<<11)^0x00;
	cmd_jars = (int)cmd_jars;
	//Define el payload como 3 bytes de cmd_jars
	intToBytes(cmd_jars,payload,size_payload);
	//Envía el cmd_array con los bytes configurados para el comando DISABLE_TRANSF
	MySP601->send(SEND_COMMAND,0,payload,size_payload);

	return true;
}

//this pointer: puntero al OBJETO del método que lo llama
//**************this = Objeto de InternalRcvFunc**************************
//Ejecuta el método InternalRcv: Crea el socket zmq que almacena los paquetes de datos adquiridos,por marca,y los envía
void *_JARSControl::InternalRcvFunc(void * This) {
	((_JARSControl *)This)->InternalRcv(); return NULL;//This es el puntero del objeto de la clase JARSControl
}

//******** Crea un soquet ZMQ_PUSH, recibe bytes del socket fpga y los envía a través del socket ZMQ al cliente definido en InternalThreadEntry ******************
//zmq solo almacena la data adquirida del buffer de la tarjeta de red para que no se pierda en un espacio de memoria de la RAM
//********************* Comprueba que la marca del bloque es la correcta verificando así que el bloque de llegada es el correcto *****************

//Crea el socket zmq que almacena los paquetes de datos adquiridos, por marca, y los envía
void _JARSControl::InternalRcv(){
	char buffer_rcv[1472];//buffer donde se guardará el mensaje que viene

	// Create server socket
	zmq::socket_t server (context, ZMQ_PUSH);
	server.bind("ipc://5559");//Revisar si está bien declarado y si es el correcto protocolo inproc.
	uint16_t prev_mark = 0, new_mark, dif_mark;

	printf("Acquisition threads begin...\n");
	for (;;) {
		//pthread_mutex_lock(&estado_mutex);
		// Recibir paquetes de datos en formato de bytes (0x41,0x42,0xaa,0xaa,0xaa,0xam,dat_0[])
		ssize_t size_rcv_buf=MySP601->receive(buffer_rcv);//Recive por el socket UDP//paquete de 1472 bytes
		//Por cada bloque UDP se genera una marca.Esta marca es de 32bits y el último es el contador.
		new_mark = (int)(0x0F & buffer_rcv[5]);
		dif_mark = new_mark - prev_mark;
		// Review the correct sequence of the marks, acumulacion de subperfiles
		//(=1), siguiente marca;(=0),UDP en el mismo windows;(=0),recién comienza
		if((dif_mark == 1) || (dif_mark == 65521) || (dif_mark == 0) || (prev_mark==0)){
		}
		else{
			printf("Error..\n");
			printf("Lost packet: %i\n", dif_mark);
			printf("Mark_prev: %x\n", prev_mark);
			printf("Mark_new: %x\n", new_mark);
		}
		prev_mark = new_mark;
		//*****************Inicializa y envía un mensaje por el socket ZMQ *****************************************
		//inicializa un mensaje de size_rcv_buf bytes
		zmq::message_t reply(size_rcv_buf);
		//.data:retrieve pointer to message content
		//Copia el mensaje que llega en reply.data()
		memcpy((void *) reply.data(), buffer_rcv, size_rcv_buf);//void * memset ( void * ptr, int value, size_t num );
		server.send(reply);//envía el mensaje de llegada por el soquet ZMQ

	}
}

//**************this = Objeto de InternalThreadEntryFunc**************************
//Ejecuta el método InternalThreadEntry:almacena la cantidad de perfile por bloque*****************************
void *_JARSControl::InternalThreadEntryFunc(void * This) {
	((_JARSControl *)This)->InternalThreadEntry(); return NULL;
}

/*************** Tarea que adquiere los paquetes y convierte a perfiles hasta completar un bloque ************************/
//**************Almacena la data por cada sync (NTX) en TempAcqNIDoubleBuffer hasta llegar al total de perfiles por bloque
//**** Al llegar a la cantidad de perfiles por bloque lo guarda en TempAcqNIBuffer y envía "Block received" por el socket.
//**** Nos da el tiempo de demora entre bloques
void _JARSControl::InternalThreadEntry(){

	uint16_t prev_mark = 0, new_mark, dif_mark;
	long int num_prof=1;
	long int cnt_subprof=0;
	long int ind_buffer=0;

	uint16_t buffer_rcv_2[1472];
	ssize_t size_rcv_buf;
	int size_rcv_buf_2;
	long TmInit,TmFinal;

	// Create client socket
	zmq::socket_t client (context, ZMQ_PULL);
	client.connect("ipc://5559");//Revisar si está bien declarado y si es el correcto protocolo inproc.
	zmq::message_t msg;//inicializa el objeto mensaje msg de zmq

	std::string msg_recv;
	zmq::socket_t server (context, ZMQ_PUSH);
	server.bind("ipc://5557");
	uint16_t* TempAcqNIBuffer=(uint16_t*)JARSControl.m_AcqNIBuffer;//definido en jro_AssignMemory
	uint16_t* TempAcqNIDoubleBuffer=(uint16_t*)JARSControl.m_AcqNIDoubleBuffer;//definido en jro_AssignMemory

	for(;;){
			client.recv(&msg);
			msg_recv = string(static_cast<char*>(msg.data()), msg.size());//transforma data de tipo char a string
			size_rcv_buf = msg.size();//tamaño con cabecera

			// Reconstruir datos en formato de 16 bits (Real e Imaginario)
			size_rcv_buf_2 = (size_rcv_buf-2)/2;//le resta dos bytes de la cabecera (0x41 0x42) (/2) ya q lo almacena en 16bits//numero de dieciseis avos
			for(int i=0;i<size_rcv_buf_2;i++){
			//lo cambia de posicion para que sea visto en display// el FPGA lo vuelve a cambiar a la posición correcta
				buffer_rcv_2[i] = ((0x00FF & msg_recv[2*i+3])<<8) + (0x00FF & msg_recv[2*i+2]);//no toma los dos primeros ya q estan borrados
			}
			new_mark = (int)(0x0F & msg_recv[5]);
			dif_mark = new_mark - prev_mark;
			// Review the correct sequence of the marks, acumulacion de subperfiles
			if((dif_mark == 1) || (dif_mark == 65521) || (dif_mark == 0) || (prev_mark==0)){
			//revisar si hay cambio de marca valida, para reiniciar el contador de subperfiles
			if(dif_mark==1 || (dif_mark == 65521)){
				if(num_prof == (MyExpParam->MyGPParam.m_nProfilesperBlock/MyExpParam->MyGRCParam.FixRCP.m_nNTX)){//perfiles por bloque por cada ipp
				    std::string msgToClient("Block received");//define msgToCliente
				    memcpy((uint16_t *)TempAcqNIBuffer,(uint16_t *)TempAcqNIDoubleBuffer,ind_buffer*2);//copia los datagramas por bloque y al revés, con solo la primera cabecera,guardados en TempAcqNIDoubleBuffer a TempAcqNIBuffer
																										   // 0xaa 0xaa 0xam 0xaa Dato [1] Dato[0]
				    zmq::message_t reply(msgToClient.size()+1);//crea el mensaje tipo ZMQ de 14 bytes+1 null
				    memcpy((void *) reply.data(), (msgToClient.c_str()), msgToClient.size()+1);//c_string : string+'\0'//char *str = s; // error: can't initialize a char* from a string // const char *str = s.c_str(); // ok
						 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 //Se debe sumar +1 al final
				    server.send(reply);//envía el mensaje "Block received" en formato const char []
				    num_prof=1;
				    ind_buffer=0;
						}
						else num_prof = num_prof + 1;//recibirá un bloque con dos marcas diferentes
						cnt_subprof=0;
				}
				/**************Almacenar data recibida en TempAcqNIDobleBuffer con la cabecera aa aa aa am********************/
				if(cnt_subprof==0){ // El primer perfil del bloque con cabecera pero sin 0x41 y 0x42
					memcpy((uint16_t *)(TempAcqNIDoubleBuffer+ind_buffer),buffer_rcv_2,size_rcv_buf-2);
					ind_buffer += size_rcv_buf_2;
				}
				else{///a partir del SEGUNDO perfil guarda el dato adquirido sin cabecera  (quita toda la cabecera . incluso la marca)
					memcpy((uint16_t *)(TempAcqNIDoubleBuffer+ind_buffer),(uint16_t *)(buffer_rcv_2+2),size_rcv_buf-6);//buffer_rcv_2+2 le sacan los dos shorts de cabecera , size_rcv_buf-6 eliminida los 6 bytes de cabecera en el tamaño
					ind_buffer += size_rcv_buf_2-2;
				}
				cnt_subprof++;//contador de paquetes (muestras)
			}
			else{
				printf("Lost packet: %i\n", dif_mark);
				printf("Mark_prev: %x\n", prev_mark);
				printf("Mark_new: %x\n", new_mark);
				JARSControl.DESHAB_TRANS_COMMAND();
				exit(1);
				}
			prev_mark = new_mark;     // actualizar la marca anterior
	}
};

//********** Ejecuta el método InternalCallback mediante el objeto seleccionado por this.
//el cual :Guarda la data adquirida sin marca en m_AcqBuffer[0] y ordena el comienzo del procesamiento y guardado en disco
void *_JARSControl::InternalCallbackFunc(void * This) {
	((_JARSControl *)This)->InternalCallback(); return NULL;
}

//Guarda la data adquirida sin marca en m_AcqBuffer[0] y ordena el comienzo del procesamiento y guardado en disco
void _JARSControl::InternalCallback(){
	bool ClientValue=false;
	long TmInit,TmFinal;
	// Create client socket
	zmq::socket_t client (context, ZMQ_PULL);
	client.connect("ipc://5557");
	zmq::message_t msg;
	std::string msg_recv;

	uint16_t* TempAcqNIBuffer=(uint16_t*)JARSControl.m_AcqNIBuffer;//Puntero al buffer grande NI,JARSControl.m_AcqNIBuffer,con la data adquirida previamente por 		el thread InternalThreadEntry
	uint16_t prev_mark;
	for(;;){
		client.recv(&msg);//recive el mensaje "Block received"
		msg_recv = string(static_cast<char*>(msg.data()), msg.size());
		//guarda la marca para su verificación ya que adquiere el thread anterior y guarda en este thread "simultaneamente"
		prev_mark = TempAcqNIBuffer[1];//TempAcqNIBuffer[1]= 0xam 0xaa
		if(TempAcqNIBuffer[0]==(0xFFFF&JARSControl.m_MarkRe)){//m_MarkRe=-21846//1010101010101010(0xaa 0xaa)
			ClientValue=true;
			JARSControl.RemoveMark();
			//*******verifica si el bloque adquirido del anterior thread es correcto
			if(TempAcqNIBuffer[1]!=prev_mark){ // Error producido cuando los datos se actualizan al escribir en disco
				printf("Incorrect data\n");
				JARSControl.DESHAB_TRANS_COMMAND(); //*******FALTA
				bool flagError= true;
				exit(1);
			}
		}
		else{
			ClientValue = false;//no save data (atributo que se define para la función MyCallbackFunction
		}
		//*********ptrFunc: Arreglo de funciones definido en main que inicializa el procesamiento y lo guarda en disco con fwrite
		//Tiempo de demora de procesamiento y guardado en disco de la data adquirida
		if(JARSControl.ptrFunc!=NULL)
			JARSControl.ptrFunc(ClientValue);//ClientValue = true da inicio a la función MyCallbackFunction.
		//Tiempo que se demora en adquirir y guardar(jicaheader-fwite)
		printf("Almacenamiento en disco en %ld milisegundos\n",TmFinal-TmInit);
	}
	client.close();//The zmq_close() function shall destroy the socket referenced by the socket argument
};

//*********** Remueve la marca y guarda la data adquirida por bloque en *TempAcqBuffer=*m_AcqBuffer[0] sin marca
void _JARSControl::RemoveMark()
{
	complex<short>* TempAcqNIBuffer=(complex<short>*)m_AcqNIBuffer;//buffer separado con marca
	complex<short>* TempAcqBuffer=(complex<short>*)m_AcqBuffer;//buffer separado sin marca
	int Samples=MyExpParam->MySystemParam.m_nSamples;//NSA de .racp
	int Channels=MyExpParam->MySystemParam.m_nChannels;//canales del .racp
	int NTX=MyExpParam->MyGRCParam.FixRCP.m_nNTX;//IPPs por synchr del .racp
	int Profiles=MyExpParam->MySystemParam.m_nProfiles;//ACQUIRED PROFILES del .racp
	int jump=Samples*Channels*NTX;
	size_t jumpInBytes= jump*4;//1 muestra en formato complex<short> tiene 4 bytes
	//*******************Copia lo que hay en el buffer grande total m_nNIBuffer en en AcqBuffer[0]************
	//************Copia desde la posición 1 de TempAcqNIBuffer , que es de donde comienza la data adquirida****
	for(int i=0;i<Profiles/NTX;i++)//perfiles adquiridos en cada synchro
		memcpy(&TempAcqBuffer[i*jump],&TempAcqNIBuffer[i*(jumpInBytes+m_NumMarks)+m_NumMarks],jumpInBytes);
	return;//guardo los perfiles con tamaño jump (ChHP) hasta completar un bloque
}

//********************************************************************************************************************
//******************************************* Define clase sp601_command *********************************************
//Array of structures: {const char *name,char val,char size,bool ack}
struct jars_cmd JARS_CMD[] = {
	[NOOP]			=	 	{"NOOP",0,0,false},			// No effect or ACK
	[SET_SP601_IP]		=		{"SET_SP601_IP",1,4,true},		// Set IP address for SP601. No ACK since we might not be able to see it if 												the COMMS_IP has not been setup
	[SET_SP601_PORT]	=		{"SET_SP601_PORT",2,2,true},		// Set Port address for SP601
	[GET_SP601_MAC]		=		{"GET_SP601_MAC",3,6,true},		// Get MAC address for SP601. Note that we don't get to SET this. It's done 												in HW through DIP switches
	[SET_COMMS_IP]		=		{"SET_COMMS_IP",4,4,true},		// Set IP address for communication PC
	[SET_COMMS_PORT]	=		{"SET_COMMS_PORT",5,2,true}, 		// Set Port address for communication PC
	[SET_COMMS_MAC]		= 		{"SET_COMMS_MAC",6,6,true}, 		// Set MAC address for communication PC
	[GET_VALUE]		=	 	{"GET_VALUE",8,0,false}, 		// Get different values stored in FPGA
	[DATA_LOOPS]		= 		{"DATA_LOOPS",63,8,false}, 		// Up to 16-bits to loop packet sending. 16-bit (effective 14 bits in HW) 												for packet size. This is used to test for bandwidth in the Gigabit Connection
	[SEND_COMMAND]	  	= 		{"SEND_COMMAND",64,3,false}, 		// Up to 16-bits (effective 14 bits in HW) to request #32-bit words to start 												burst data transfer. Note, due to IP packet packaging, should be no more 												than 367 words
	[CHECK_ACK]		= 		{"CHECK_ACK",65,1,false}, 		// ack-command
	[SEND_FILTER]		=	 	{"SEND_FILTER",66,0,false} 		// Send filter
};

sp601_command::sp601_command()
{}

sp601_command::~sp601_command()
{}
//***** Define el socket y establece las direcciones de los puertos, la MAC y la IP de la Pc y el SP601**********************
void sp601_command::init(address host_address)
{
	//****************** Convierte de string a char* la ip y mac local	
	int mac_size= ((host_address.d_mac_block).size());
	char mac_array_char [mac_size+1]={};
	strcpy (mac_array_char,(host_address.d_mac_block).c_str());
	
	int ip_size= ((host_address.d_ip_host).size());
	char ip_array_char [ip_size+1]={};
	strcpy (ip_array_char,(host_address.d_ip_host).c_str());

	//******************* Empieza el envio de comandos 
	char payload[16]={};//lo define así ya que usa los subindices para contar
	printf("Connecting to %s...\n", cfg.SP601_IP);//muestra la IP del SP601
	//************** Define el socket : crea , direcciona y configura el socket UDP*****************************************************
	fpga_con_init(ip_array_char,host_address.d_port_block);//Declar estos valores en el .h y definirlos en el constructor//char * IP
	printf("Se creó el socket UDP con dirección de IP del host igual a : %s\n",ip_array_char );
	//************** Envía y establece la dirección IP del SP601 ************************
	//el valor de solo los números de la dirección de la IP es guardado en payload de tipo char
	IPstr_to_bytearray(cfg.SP601_IP, payload);
	//Envia el valor de la IP del SP601 al SP601
	send(SET_SP601_IP,0,payload,4);//4 bytes del IP
	//setea a cero char los valores del payload
	memset(payload,0,strlen(payload));
	//************** Envía y establece la dirección IP de la PC ************************
	//el valor de solo los números de la dirección de la IP es guardado en payload de tipo char
	IPstr_to_bytearray(ip_array_char, payload); //valor de IP-host en char* dado por el GNURadio block
	//Envia el valor de la IP de la PC al SP601
 	send(SET_COMMS_IP,0,payload,4);
 	//setea a cero char los valores del payload
	memset(payload,0,strlen(payload));
	//************** Envía y establece la MAC de la PC  ************************************
	//Los valores hexadecimales de la mascará de la PC son guardados en payload en formato tipo char
	MACstr_to_bytearray(mac_array_char, payload); // valor del MAC -host en char* dado por el GNURadio block
	//Envia el valor de la MAC de la PC al SP601
	send(SET_COMMS_MAC,0,payload,6);
	//setea a cero char los valores del payload
	memset(payload,0,strlen(payload));
	//************** Envía y establece el puerto de la PC ************************************
	//Divide el puerto de la PC y lo guarda en el payload
	intToBytes(host_address.d_port_block, payload, 2);
	//Envía el valor del puerto de la PC al SP601
	send(SET_COMMS_PORT,0,payload,2);
	//setea a cero char los valores del payload
	memset(payload,0,strlen(payload));
	//************** Envía y establece el puerto del SP601 ************************************
	//Divide el puerto de la SP601 y lo guarda en el payload
	intToBytes(cfg.SP601_PORT,payload,2);
	//Envía el valor del puerto de la SP601 al SP601
	send(SET_SP601_PORT,0,payload,2);
	//setea a cero char los valores del payload
	memset(payload,0,strlen(payload));
	//We can check the current values for MAC, IP and PORT
}

//****************************** Nos da el número de bytes recibidos
ssize_t sp601_command::receive(char *buffer_rcv)
{
	ssize_t size_rcv_buf = fpga_con_recv(buffer_rcv,RCV_BUFSIZE);
	//printf("Recibido\n");
	return size_rcv_buf;
}
//********************************************************************************************************************
//******************************************* Define la clase fpga_com ***********************************************
//fpga_con_init(&fc, cfg.SP601_IP, cfg.COMMS_PORT, cfg.SP601_PORT)
//**************************** Define y establece el socket con las caracteísticas respectivas******************************
//void fpga_con_init( fpga_con_t *con, const char *daddr, int lport, int dport ) {
void fpga_con_init(char* host,int lport ) { //(#HOST y # PORT llamados desde el bloque)

	//******************** Define un endpoint local , crea y abre un sovlet local , setea el socket local y lo bind al endpoint local
	//Creamos un endpoint:representing all IP addresses available on the host and the specified port number.
	boost::asio::ip::udp::endpoint local_endpoint(boost::asio::ip::address_v4::any(),lport);
        //Crea un puntero a un socket
 	local_socket = new boost::asio::ip::udp::socket(local_io_service);
        local_socket->open(local_endpoint.protocol()); // abre el socket especificando el protocolo asociado al endpoint-udp protocolo
	//******************************* Setea el socket *************************************************************
	boost::asio::socket_base::reuse_address roption(true);//implementa la opción SOL_SOCKET/SO_REUSEADDR para el del socket
	local_socket->set_option(roption);//Establece la opción roption en el socket
	boost::asio::socket_base::receive_buffer_size option(2097152);//Máximo valor que obtendrá para guardar por si se quedan = 2097152
	local_socket->set_option(option);
	//*****************************
	local_socket->bind(local_endpoint);//enlaza el socket al endpoint establecido// Le da al socket dirección y puerto en la red

	//************************************ Define un endpoint de destino  *************************************************************************************
	boost::asio::ip::address ip_destino = boost::asio::ip::address::from_string(cfg.sp601_ip_string);
	boost::asio::ip::udp::endpoint destino_endpoint(ip_destino, cfg.SP601_PORT);
	destino_endpoint_to=destino_endpoint;
}

// ssize_t is the same as size_t, but is a signed type - read ssize_t as “signed size_t”.
//ssize_t is able to represent the number -1, which is returned by several system calls and library functions as a way to indicate error.
//***************Envía los paquetes de datos de buf a través del socket especificado en fpga_con_t********************************************************************************
ssize_t fpga_con_send(const char *buf, size_t len ) { //ssize_t , is read signed size_t , which can give us -1 as an error.
/*The sendto function transmits the data in the buffer through the socket socket to the destination
 address specified by the addr and length arguments. The size argument specifies the number of bytes to
 be transmitted. */

    ssize_t bytes_send = local_socket->send_to(boost::asio::buffer(buf, len), destino_endpoint_to);//(void*) buf//se puede quitar el boost::asio::buffer pero al ver GNURadio UDP sink y source lo usan sin problemas

    if( bytes_send < 0 ) {
	     printf("Error en el envío. Revisar fpga_con_send\n");
    }
    return bytes_send;
    
}

/*blocking receive: this call will block until a packet is received*/
//****************** Recibirá data y luego lo bloqueará hasta que haya alguna data por leer*********************
ssize_t fpga_con_recv(char *dbuf, size_t dsize ) {

	ssize_t bytes_receive = local_socket->receive(boost::asio::buffer(dbuf, dsize));//no se especificó en endpoint de envío

	if( bytes_receive < 0 ) {
		 printf("Error en la recepción. Revisar fpga_con_recv\n");
	}
	return bytes_receive;

}

//void send(uint8_t cmd, char code, const char *payload,char size_payload)
//void send(uint8_t cmd, char code, const char *payload,size_t size_payload)
//void sp601_command::send(uint8_t cmd, char code, const char *payload, char size_payload)
//**********************Dependiendo del cmd y el payload genera el buffer que guardará el comando de envio: cmd_array**************************
//**********************Genera el buffer que guardará el paquete de data recibido: buffer_rcv**************************
//**********************Verifica los buffers creados imprimiéndolos (printf)******************************************
//********************** Envía el comando respectivo (PC->SP601) y recibe el comando de respuesta (SP601->PC) /Revisar Excel*******************
void sp601_command::send(uint8_t cmd, char code, const char *payload, size_t size_payload)
{
	char cmd_array[16];
	char buffer_rcv[RCV_BUFSIZE];//buffer donde se guardará el mensaje que recibe
	char size_rcv_buf=0;
	bool ack_received;
	//char size_payload;
	size_t size_cmd_array;
	uint8_t *info_str;
	//define VERBOSE_MODE para el objeto cfg
	cfg.VERBOSE_MODE = true;//********
	//printf("%i\n",payload[0]);printf("%i\n",payload[1]);printf("%i\n",payload[2]);
	//size_payload = strlen(payload);
	//size_payload = payload.__size;
	//printf("%i",size_payload);
	size_cmd_array = 3+size_payload;//tamaño total después de agregar cmd_array[0],[1],[2]
	//printf("%i",size_cmd_array);
	//**************************** Crea el buffer de comando cmd_array ************************************
	cmd_array[0] = JARS_CMD[cmd].val;
	cmd_array[1] = code;//siempre será cero aparentemente
	cmd_array[2] = JARS_CMD[cmd].size;
	//guarda el valor de payload ,del tamaño de size_payload,a partir de cmd_array[3]
	memcpy(cmd_array+3,payload,size_payload);//Completa: val,code,size,direccion
	//**************envia los paquetes de datos del arreglo cmd_array a través del socket
 	fpga_con_send(cmd_array,size_cmd_array);//

	ack_received = false;//*******
	//crea el buffer de adquisición si el ack es true
	if(JARS_CMD[cmd].ack)
	{
		size_rcv_buf = fpga_con_recv(buffer_rcv,RCV_BUFSIZE);//pone el valor en bytes del buffer receptor 1472
		ack_received = true;//******
	}

	//************************* Da valor al arreglo info_str dependiendo del tipo de configuración ****************************************************
	//******PAsa de char [] a uint8_t
	switch (cmd) {
		case SET_SP601_IP:	//Guarda el valor de la IP del SP601 en formato literal string en info_str para mostrar en pantalla
					bytearray_to_IPstr(payload,cfg.SP601_IP);//pasa los números de char a int de la IP  y los guarda en formato ...
					info_str = (uint8_t *)malloc(strlen(cfg.SP601_IP)+1);
					memcpy(info_str,cfg.SP601_IP,strlen(cfg.SP601_IP)+1);
					break;
		case SET_SP601_PORT:	//Guarda el valor del puerto en info_str (char)
					bytearray_to_int(payload,cfg.SP601_PORT);
					info_str = (uint8_t *)malloc(10);
					itoa(cfg.SP601_PORT,(char *)info_str,10);
					break;
		case SET_COMMS_IP:	//Guarda el valor de la IP de la PC en formato literal string en info_str para mostrar en pantalla
					bytearray_to_IPstr(payload,cfg.IP_host);
					info_str = (uint8_t *)malloc(strlen(cfg.IP_host)+1);
					memcpy(info_str,cfg.IP_host,strlen(cfg.IP_host)+1);
					break;
		case SET_COMMS_PORT:	//Guarda el valor del puerto en info_str (char)
					bytearray_to_int(payload,cfg.PORT_host);
					//printf("%i\n", cfg.COMMS_PORT);
					info_str = (uint8_t *)malloc(10);
					//guarda el valor del puerto en info_str (char)
					//Lo cambia de int a char para mostrarlo como string
					itoa(cfg.PORT_host,(char *)info_str,10);
					break;
		case SET_COMMS_MAC:	//****Guarda el valor de la MAC de la PC en formato literal string en info_str para mostrar en pantalla
					bytearray_to_MACstr(payload,cfg.MAC_host);
					info_str = (uint8_t *)malloc(strlen(cfg.MAC_host)+1);
					memcpy(info_str,cfg.MAC_host,strlen(cfg.MAC_host)+1);
					break;
		case SEND_COMMAND:
					//******************* Creará un arreglo(info_str) donde se guardará el estado del 						JARS:RST_CTRL,RST_CTRL,SELECT_RXD,POWER_RXD,PROG_RXD,ENABLE_TRANSF,DISABLE_TRANSF************
					//********** Recibirá el primer paquete de datos mediante recv()*****************************
					//-----------Verifica mediante el payload[1] que se haya enviado el modo correcto de configuración------------------
					info_str = (uint8_t *)malloc(10);
					memset(info_str,0,10);//define el espacio de memoria info_str con 10 ceros.
					//Crea un indicador que define el arreglo de estados info_str
					char cmd_acq;
					cmd_acq = (payload[1]>>4)&15;//parece que el payload guarda el comando de estado
					if(cmd_acq==RST_CTRL) sprintf((char *)(info_str), "%s", "RST_CTRL");
					//else if(cmd_acq==MODE_OPER) sprintf((char *)(info_str), "%s", "RST_CTRL");
					else if(cmd_acq==MODE_OPER) sprintf((char *)(info_str), "%s", "MODE_OPER");
					else if(cmd_acq==ELECTION_RXD) sprintf((char *)(info_str), "%s", "SELECT_RXD");
					else if(cmd_acq==POWER_RXD) sprintf((char *)(info_str), "%s", "POWER_RXD");
					else if(cmd_acq==PROG_RXD) sprintf((char *)(info_str), "%s", "PROG_RXD");
					else if(cmd_acq==ENABLE_TRANSF) sprintf((char *)(info_str), "%s", "ENABLE_TRANSF");
					else if(cmd_acq==DISABLE_TRANSF) sprintf((char *)(info_str), "%s", "DISABLE_TRANSF");
					// Get the value returned from the UDP receiver thread
					// First packet
					size_rcv_buf = fpga_con_recv(buffer_rcv,RCV_BUFSIZE);//Recibe el paquete en el buffer de 1472 bytes de tamaño
					// Revisar los respectivos bits de buffer_rcv para colocar el info_str el comando que fue enviado
					break;
		case DATA_LOOPS:
					info_str = (uint8_t *)malloc(10);
					cfg.VERBOSE_MODE = false;
					break;
		case GET_VALUE:
					info_str = (uint8_t *)malloc(10);
					break;
		case SEND_FILTER:
					//Recibe el paquete de respuesta de envio del sp601
					info_str = (uint8_t *)malloc(12);
					memset(info_str,0,12);//establece el arreglo info_str con 12 ceros, pero tipo char
					sprintf((char *)(info_str), "%s", "WRITE_FILTER");
					//Get the value returned from the UDP receiver thread
					//First packet.
					size_rcv_buf = fpga_con_recv(buffer_rcv,RCV_BUFSIZE);
					printf("Filter received\n");
					break;
		case NOOP:		//No muestra nada
					info_str = (uint8_t *)malloc(10);
					cfg.VERBOSE_MODE = false;
					break;
		default:
					printf("Error: Command Not Found[%s]\n", JARS_CMD[cmd].name);
					break;
	}

	//**************** Imprime el nombre del comando enviado y el estado del JARS y se lee el paquete recibido en formato hexadecimal
	if((cfg.VERBOSE_MODE == true) && (cmd != GET_VALUE))
	{
	/*	printf("%s : %s\n", JARS_CMD[cmd].name,(uint8_t *)info_str);//muestra el name y el info_str en uint8_t(uint8_t* para asegurar)
		printf("Received: ");
		for(uint16_t i = 0 ; i<size_rcv_buf ; i++)//numero de bytes leidos en el buffer
		{
			printf("%02X,",(uint8_t)buffer_rcv[i]);//Se lee el char que llega en formato hexadecimal
		}
   		printf("\n");*/
		//size_t size_info_str = sizeof(info_str);
		//memset(info_str,0,size_info_str);
          printf("el valor que llegó fue: %s",buffer_rcv );

	}

	//**************** Muestra todos los elementos del buffer: cmd_array en hexadecimal *********************
	/*if(JARS_CMD[cmd].ack && ack_received)
	{	if(cfg.VERBOSE_MODE)
		{
			printf("[OK] Validation for command [%s][%i][",JARS_CMD[cmd].name,code);//code sera siempre cero
			for(uint16_t i = 0 ; i<(size_cmd_array-1) ; i++)
			{
				printf("%02X,",(uint8_t)cmd_array[i]);
			}
			printf("%02X]",(uint8_t)cmd_array[size_cmd_array-1]);
			printf("\n");
		}
	}*/

}

//******************** Métodos usados por swich en send **************************************************
//*************** Guarda cada numero de la IP dentro del arreglo parts en formato char *******************
void IPstr_to_bytearray(char *IPstr, char *parts){
  char * pch;
  uint8_t ii=0;
  pch = strtok (IPstr,".");//divide el IPstr , dilimitado por .
  while (pch != NULL)
  {
    parts[ii] = (char)atoi(pch);//convierte string a int y luego lo guarda como char
    pch = strtok (NULL, ".");
    ii=ii+1;
  }
}

//************************** Nos da la IP en forma binaria y string ****************************************
void bytearray_to_IPstr(const char *bytes, char *IPstr){
  sprintf(IPstr,"%i.%i.%i.%i",(uint8_t)bytes[0],(uint8_t)bytes[1],(uint8_t)bytes[2],(uint8_t)bytes[3]);
  //printf("%s\n", IPstr);
}

//************************** Convierte de bytes a enteros **************************************************
void bytearray_to_int(const char *byte_array, int num){
  for (size_t i = 0; i < 2; i++) {
    num += (uint16_t)((uint8_t)byte_array[i] << (i*8));
  }
}

//*************** Guarda cada numero hexadecimal de la máscara dentro del arreglo parts en formato char *******************
void MACstr_to_bytearray(char *MACstr, char *parts){
  char *pch;
  uint8_t ii=0;
  pch = strtok (MACstr,":");
  while (pch != NULL)
  {//long int strtol(const char *str, char **endptr, int base)
    parts[ii] = (char)strtol(pch,NULL,16);//cambia de string a long int, tomando el valor hexadecimal 16, y lo guarda como tipo char
    //printf("p[%i]: %i\n", ii,(uint8_t)parts[ii]);
    pch = strtok (NULL, ":");
    ii=ii+1;
  }
}

//*************** Divide el numero por bytes y lo guarda en arrayOfByte *****************************************************
void intToBytes(int number, char *arrayOfByte, size_t size){
  for (size_t i = size; i > 0; i--) {
    arrayOfByte[size-i] = (char)(number >> ((i-1)*8));
  }
}

//*************** Guarda los valores del hexadecimal en un arreglo string literal ********************************************
void bytearray_to_MACstr(const char *bytes, char *MACstr){
  sprintf(MACstr,"%02X:%02X:%02X:%02X:%02X:%02X",(uint8_t)bytes[0],(uint8_t)bytes[1],(uint8_t)bytes[2],(uint8_t)bytes[3],(uint8_t)bytes[4],(uint8_t)bytes[5]);
}

// Implementation of itoa()
//itoa(cfg.COMMS_PORT,(char *)info_str,10);
//************** Guarda dentro de str los valores del num en caracteres char[] ***************
char* itoa(int num, char* str, int base){
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    //guarda cada digito de num en str (el último dígito en el primer elemnto del str)/al reves
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    int n = strlen(str);

    // Swap character starting from two
    // corners
    for (int i=0; i<n/2; i++)
       swap(str[i], str[n-i-1]);

    return str;
}

#endif
