#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Variables Globales
int indice = 0, longitud = 0;
//contadores
int i = 0, j = 0;

//Reglas de la gramatica E->E+T , E->T , T->T*F, T->F, F->(E), F->i
char input[16], reduce[20], stack[15], accion[10];

//Las funciones conjunto# analizan la pila en busqueda de expresiones que se puedan reducir
void conjunto1(){
	// Coping string to be printed as action
	strcpy(reduce,"REDUCE TO E -> ");

	// longitud=length of input string
	for(indice = 0; indice < longitud; indice++){
		//Verificando regla E->T
		if(stack[indice] == 'T'){
			printf("%sT", reduce);
			stack[indice] = 'E';
            //stack[indice + 1] = '\0';
            //stack[indice + 2] = '\0';
			printf("\n$%s\t%s$\t", stack, input);
			//i = i - 1;
		}
	}

	for(indice = 0; indice < longitud - 2; indice++){
		//Verificando regla E->E+T
		if(stack[indice] == 'E' && stack[indice + 1] =='+' && stack[indice + 2] == 'T'){
			printf("%sE+T", reduce);
			stack[indice] = 'E';
			stack[indice + 1] = '\0';
            stack[indice + 1] = '\0';
			printf("\n$%s\t%s$\t", stack, input);
			i = i - 2;
		}
	}
	return;
}

void conjunto2(){
	//Imprimimos la accion a realizar
	strcpy(reduce,"REDUCE TO T -> ");

	//longitud=length of input string
	for(indice = 0; indice < longitud; indice++){
		//Verificando regla T->F
		if(stack[indice] == 'F'){
			printf("%sF", reduce);
			stack[indice] = 'T';
			//stack[indice + 1] = 'E';
			//stack[indice + 2] = '\0';
			printf("\n$%s\t%s$\t", stack, input);
            //i = i - 2;
		}
	}


	for(indice = 0; indice < longitud - 2; indice++){
		//Verificando regla T->T*F
		if(stack[indice] == 'T' && stack[indice + 1] =='*' && stack[indice + 2] == 'F'){
			printf("%sT*F", reduce);
			stack[indice] = 'T';
			stack[indice + 1] = 'E';
			stack[indice + 2] = '\0';
			printf("\n$%s\t%s$\t", stack, input);
			i = i - 2;
		}
	}
	conjunto1();
	return;
}

void conjunto3(){
	//Imprimimos la accion a realizar
	strcpy(reduce,"REDUCE TO F -> ");

	//longitud=length of input string
	for(indice = 0; indice < longitud; indice++){
		//Verificando regla F->i
		if(stack[indice] == 'i'){
			printf("%si", reduce);
			stack[indice] = 'F';
			//stack[indice + 1] = 'T';
			//stack[indice + 2] = 'E';
			//stack[indice + 3] = '\0';
			printf("\n$%s\t%s$\t", stack, input);
            //i = i - 1;

		}
	}

	for(indice = 0; indice < longitud - 2; indice++){
		//Verificando regla F->(E)
		if(stack[indice] == '(' && stack[indice + 1] =='E' && stack[indice + 2] == ')'){
			printf("%s(E)", reduce);
			stack[indice] = 'F';
			stack[indice + 1] = 'T';
			stack[indice + 2] = 'E';
			stack[indice + 3] ='\0';
			printf("\n$%s\t%s$\t", stack, input);
			i = i - 3;
		}
	}
    conjunto2();
	return; //return to main
}

//Driver Function
int main(){
	printf("GRAMMAR is: \nE->E+T \nE->T \nT->T*F\nT->F\nF->(E)\nF->id\n");

	//Cadena de entrada
	strcpy(input,"i+i*i");

	//longitud de la cadena de entrada
	longitud=strlen(input);

	//SHIFT
	strcpy(accion,"SHIFT");

	printf("\nstack \t input \t action");
	printf("\n$\t%s$\t", input); //Valores iniciales

	for(i = 0; j < longitud; i++, j++){
		printf("%s", accion); //Imprimimos la accion a realizar
		stack[i] = input[j]; //Avanzamos a la siguiente posición en la pila
		stack[i + 1] = '\0'; //Declaramos la siguiente posición como vacio
		input[j]=' '; //Movemos el apuntador
		printf("\n$%s\t%s$\t", stack, input); //Imprimimos la accion

		//De abajo hacia arriba realizamos las reducciones de posibles utilizando las reglas de la gramatica
		conjunto3();
	}

	//conjunto3(); //Verificamos si existe alguna reducción posible
	//conjunto2();
	//conjunto1();

	//Si el tope de la pila contiene solo $E, se acepta el parseo
	if(stack[0] == 'E' && stack[1] == '\0'){
        printf("Aceptada\n");
	}
	else{
		printf("Rechazada\n");
    }
}
