#include <stdbool.h> 
#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 
#define MAXCHAR 1000

//Función para buscar los signos de puntuación en  el programa
bool signosPuntuacion(char signo) 
{ 
	if ( signo == ' ' || signo == '*' || signo == '-' || signo == '+' 
		|| signo == '/' || signo == ',' || signo == ';' || signo == '=' 
		|| signo == '<' || signo == '>' || signo == '(' || signo == ')' 
		|| signo == '[' || signo == ']' || signo == '{' || signo == '}' 
		/*|| signo == '#' */){
			return (true); 
		} 
	return (false); 
} 

//Función para comparar las subcadenas con las 32 palabras reservadas del lenguaje C
bool reservada(char* cad) 
{ 
	if (!strcmp(cad, "auto") || !strcmp(cad, "break") || !strcmp(cad, "case") || !strcmp(cad, "char") 
		|| !strcmp(cad, "const") || !strcmp(cad, "continue") || !strcmp(cad, "default") || !strcmp(cad, "do") 
		|| !strcmp(cad, "double") || !strcmp(cad, "else") || !strcmp(cad, "enum") || !strcmp(cad, "extern") 
		|| !strcmp(cad, "float") || !strcmp(cad, "for") || !strcmp(cad, "goto") || !strcmp(cad, "if") 
		/*|| !strcmp(cad, "include") */|| !strcmp(cad, "int") ||  !strcmp(cad, "long") || !strcmp(cad, "register") || !strcmp(cad, "return") 
		|| !strcmp(cad, "short") || !strcmp(cad, "signed") || !strcmp(cad, "sizeof") || !strcmp(cad, "static") 
		|| !strcmp(cad, "struct") || !strcmp(cad, "switch") || !strcmp(cad, "typedef") || !strcmp(cad, "union")
		|| !strcmp(cad, "unsigned") || !strcmp(cad, "void") || !strcmp(cad, "volatile") || !strcmp(cad, "while")){
			return (true); // Si la subcadena es una palabra reservada regresamos verdadero
		} 
	return (false); 
} 

//Función encargada de obtener las subcadenas para su evaluación
char* subCadenas(char* cad, int izquierda, int derecha) 
{ 
	int j; 
	char* subCadena = (char*)malloc(sizeof(char) * (derecha - izquierda + 2)); 

	for (j = izquierda; j <= derecha; ++j){
		subCadena[j - izquierda] = cad[j];
	} 
	subCadena[derecha - izquierda + 1] = '\0'; 
	return (subCadena); 
} 

//Función para evaluar las subcadenas y determinar si son palabras reservadas
void encuentraPR(char* cad) 
{ 
	int longitud = strlen(cad); 
	int izquierda = 0, derecha = 0; 


	while (derecha <= longitud && izquierda <= derecha) { 
		if (signosPuntuacion(cad[derecha]) == false) {
			derecha++; 
		}

		 if (signosPuntuacion(cad[derecha]) == true && izquierda == derecha) { 
		 	derecha++; 
		 	izquierda = derecha; 
		 } else if (signosPuntuacion(cad[derecha]) == true && izquierda != derecha 
		 		|| (derecha == longitud && izquierda != derecha)) { 
		 	char* subCadena = subCadenas(cad, izquierda, derecha - 1); 

			if (reservada(subCadena) == true){
				printf("'%s'\n", subCadena); 
			}
			izquierda = derecha; 
		} 
	} 
} 

//Función principal
int main() 
{ 
	char cadena[MAXCHAR];
	FILE *fptr;

	if ((fptr = fopen("C:\\Users\\Anzen Digital\\Documents\\Compiladores\\Tarea1\\examen1.c","r")) == NULL){
		printf("Error! No se puede abrir el archivo \a");
		exit(1); //Termina el programa con error = 1
	}

	while (fgets(cadena, MAXCHAR, fptr) != NULL){
		encuentraPR(cadena); //Llamado a la función de identificación de palabras reservadas
	}

	fclose(fptr); 
	return (0); 
} 
