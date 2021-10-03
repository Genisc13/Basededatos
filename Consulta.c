//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	int edad;
	char nombre[10];
	char consulta [80];
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi??n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BBDDv1",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexi??n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
		
		// Ahora vamos a buscar el nombre de las personas que han ganado contra la persona puesta en consola
		// dado por el usuario
		printf ("Dame el nombre de la persona de la qual quieres saber contra quien ha perdido\n"); 
		scanf ("%s", nombre);
		// construimos la consulta SQL
		strcpy (consulta,"Select partidas.ganador FROM (jugador,participacion,partidas) WHERE jugador.nombre= '"); 
		strcat (consulta, nombre);
		strcat (consulta,"'");
		strcat (consulta," AND participacion.idJ=jugador.id AND participacion.idP=partidas.id AND NOT partidas.ganador= '"  );
		strcat (consulta, nombre);
		strcat (consulta,"'");
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		row = mysql_fetch_row (resultado);
		if (row == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else{
			int i=0;
			while(row !=NULL){
			// El resultado debe ser una matriz con una sola fila
			// y una columna que contiene el nombre
			printf ("Nombre de la persona: %s\n", row[0]);
			row = mysql_fetch_row (resultado);
			}
		}
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}
