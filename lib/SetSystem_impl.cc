/* -*- c++ -*- */
/* 
 * Copyright 2020 gr-SetSystem author.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "SetSystem_impl.h"

#include <stdio.h>
#include <stdlib.h>		// para usar exit(-1)
#include <string>
#include <string.h>

#include <exception>
#include <iostream>
#include <signal.h>
#include <vector>

namespace gr {
  namespace SetSystem {
 
    // Do <+signal processing+>
    /*********************************/
    /*FILE REPORT RESTARTING*/
    /*********************************/
    //Por Remover
    bool FlagFunction=false;//Usado en un blucle para que no se core dumb-por remover
    int timmer;//Usado en un blucle para que no se core dumb-por remover.
    #define TimeLimit (10000)

    /*********************************/
    //Define los objetos que usarán los métodos
    ExpParameters MyParameters;//Objeto de experiment parameters con atributos de experiment parameters
    MemoryManager MyMemManager;
    JicaHeader MyHeader;//Objeto de JicaHeader
    RdpToolsBeta MyProcess;//Objeto de RdpToolsBeta
   
    void MyCallbackFunction(bool);

    SetSystem::sptr
    SetSystem::make(const char* path_file, const std::string mac_block, int port_block, const std::string ip_host)
    {
      return gnuradio::get_initial_sptr
        (new SetSystem_impl(path_file, mac_block, port_block, ip_host));
    }

    /*
     * The private constructor
     */
    SetSystem_impl::SetSystem_impl(const char* path_file, const std::string mac_block, int port_block, const std::string ip_host)
      : gr::block("SetSystem",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(int))),
	c_path_file(path_file),c_mac_block(mac_block),c_port_block(port_block),c_ip_host(ip_host)
    {}

    /*
     * Our virtual destructor.
     */
    SetSystem_impl::~SetSystem_impl()
    {
    }

    void
    SetSystem_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    SetSystem_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        int *out = (int *) output_items[0];

       //******************** Define un objeto de la estructura address *********************************      	
	address host;
        host.d_path_file = c_path_file;
	host.d_mac_block = c_mac_block;
	host.d_port_block = c_port_block;
	host.d_ip_host =  c_ip_host;		
	///////////////////////////////////////////////////////////////////////////////////////////////////
     	//Inicializa la IP estática y la MAC

	//****** Estable el reconocimiento de la MAC y la IP de la SP601 para la comunicación directa**arp(protocolo de resolución de direcciones***
	system("sudo arp -s 10.10.30.123 00:0a:35:02:05:f2");//inicializa la IP estática y la mac de la SP601 en la PC para que pueda reconocerla.
	//**** Maximiza el tamaño del buffer de recepción o lectura del socket para minimizar los paquetes de datos perdidos
	system("sudo sysctl -w net.core.rmem_max=26214400");//máxima capacidad del buffer de la tarjeta de red para una mejor performance cuando se trabaje en 		gigabit ethernet

	//**********Define el objeto ArgProcess que establece el objeto MyParameters de ExpParameters para la lectura del .racp
	ArgProcessor ArgProcess(MyParameters);
	ArgProcess.jro_arguments(host.d_path_file);//ejecuta el método jro_arguments (lectura del .racp)

	//***************Ingresa parametros y memoria a RdpToolsBeta
	//Ejecuta el método GetExtParameters , el cual ingresa los atributos leídos del .racp mediante un puntero al objeto MyParameters
	//y los atributos declarados de memory manager mediante un puntero al objeto MyMemManager.
	//Ejecuta initVariables():Da valor a los parámetros de ventana (H0,NSA,DH) y define Dyn_snCode
	//*****Utiliza los objetos de ExperimentParameters y MemoryManager para establecer sus atributos y métodos en el objeto de RdpToolsBeta
	MyProcess.GetExtParameters(&MyParameters,&MyMemManager);

	//******Usando el objeto MyMemManager y el objetoMyParameters: crea todos los buffers necesarios para iniciar la adquisicion
	//Crea los arreglos de adquisicion m_mAcqBuffer en formato complex<short> separados en memoria donde se guardará la data adquirida
	//Separa en memoria el espacio donde se almacenará las muestras de adquisición: m_nNIBuffer
	if(!MyMemManager.AllocateMemory(&MyParameters))
	{
		printf("\nError allocating memory\n");
		return -1;
	}

	//**Define en el objeto de JicaHeader los atributos del experimento de longHeader
	//ingresa los parametros para crear las cabeceras del formato Jicamarca.
	//Separa en memoria y establece los atributos de las cabecera long header
	MyHeader.GetExpParameters(&MyParameters);

	//***Dependiendo si pAcquisitionManager apunta a un objeto tipo JARSControl o cooperball ejecuta el método jro_MatchParameters
	//JARSControl: Da los valores de los atributos de ExperimentParameters al obejto de JARSControl?¿
	JARSControl.jro_MatchParameters(&MyParameters);

	//***Dependiendo si pAcquisitionManager apunta a un objeto tipo JARSControl o cooperball:
	//JARSControl:Define los buffers de memoria de MemoryManager en el objeto JARSControl (RemoveMark),define el puntero ptrClientFunc igual al address 		MyCallbackFunction y setea el JARS por comandos
	JARSControl.jro_AssignMemory(&MyMemManager,&MyCallbackFunction,host);

	for (int i = 0 ; i<noutput_items;i++)	 	      
	  out[i]=2;
      
      	//****************** Si no funciona, probar con la implementacion de udp_Source_impl.cc************************
      	// Tell runtime system how many input items we consumed on
      	// each input stream.
      	consume_each (noutput_items);

      	// Tell runtime system how many output items we produced.
      	return noutput_items;
    }

  } /* namespace SetSystem */
} /* namespace gr */

