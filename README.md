# SetSystem

Código de prueba de la interfaz JARSControl.
Error de configuración o reconocimiento de la librería ZeroMQ en la implementación de los ZMQ sockets. (Top_block.py)

Estuve probando la interfaz en GNU Radio pero el fin de semana encontré un pequeño retraso...Estaba corriendo la interfaz método por método, todo andaba bien hasta que llegue al método JARSControl, aparecía un error en el archivo python generado. 
Este error es el siguiente: 

File "/home/itupac/workarea-gnuradio/Labs/SetRecv/top_block.py", line 100, in __init__
    self.SetSystem_SetSystem_0 = SetSystem.SetSystem('/home/itupac/RACP/Test1MHz.racp', '00:1f:c6:8c:75:53', 9096, '192.168.1.5')
AttributeError: 'module' object has no attribute 'SetSystem'
Descubrí que este error es producido debido a los ZMQ sockets. Mis sospechas son que el python no agrega la librería ZMQ al crear el archivo top_block.py, el cual agrupa los bloques del diagrama de flujo de GNU Radio en código. Esto hasta donde creo entender se debería a que tengo que configurar el archivo CMakelist.txt y agregar tal librería. El problema es que hay varios archivos CMakelsit.txt y cada uno presenta varias lineas de código, por lo que estoy averiguando y aprendiendo cómo configurarlo...
