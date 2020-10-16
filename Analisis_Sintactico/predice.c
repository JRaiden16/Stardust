#include<ctype.h>
#include<stdio.h>
#include<string.h>

//Funciones para encontrar el follow de los elementos de la gramática
void prfollow(char, int, int);
void buscaSiguiente(char c);

//Funciones para encontrar el first
void encuentraPrimeros(char, int, int);

//Arreglo para almacenar los first encontrados
char calc_first[13][50];

//Arreglo para almacenar los follow encontrados
char calc_follow[13][50];

//variables globales
int leidas, n = 0;
int k, e, m = 0;

//Guarda las reglas de la gramática leida
char reglasGramatica[13][10];
char primeras[13], encontradas[13];
char valorActual;

int main(int argc, char **argv){
	int x = 0; int y = 0;
	int i;
	char reglaActual;

	leidas = 11;

	//Reglas de la gramatica
	strcpy(reglasGramatica[0], "E=TD");
	strcpy(reglasGramatica[1], "D=+TD");
	strcpy(reglasGramatica[2], "D=-TD");
	strcpy(reglasGramatica[3], "D=#");
	strcpy(reglasGramatica[4], "T=FW");
	strcpy(reglasGramatica[5], "W=*FW");
	strcpy(reglasGramatica[6], "W=/FW");
	strcpy(reglasGramatica[7], "W=#");
  	strcpy(reglasGramatica[8], "F=(E)");
  	strcpy(reglasGramatica[9], "F=n");
  	strcpy(reglasGramatica[10], "F=i");

  	printf("GRAMATICA INGRESADA: \n\n");
  	for(i = 0; i < leidas; i++){
        printf("  %s\n", reglasGramatica[i]);
  	}
  	printf("\n\n");

	int w; int indice = -1;
    char guardadas[leidas];

	//Inicializamos el arreglo para los PRIMEROS para evitar errores
	for(k = 0; k < leidas; k++){
		for(w = 0; w < 50; w++){
			calc_first[k][w] = '!';
		}
	}

	int apuntador = 0, apuntador2, bandera;

	for(k = 0; k < leidas; k++){
		reglaActual = reglasGramatica[k][0];
		apuntador2 = 0;
		bandera = 0;

		//Revisamos si el PRIMERO encontrado ya fue calculado e indexado
		if(indice != -1){
            for(w = 0; w <= indice; w++){
                if(reglaActual == guardadas[w]){
                    bandera = 1;
                }
            }
		}


		if(bandera == 1){
            continue;
		}

		encuentraPrimeros(reglaActual, 0, 0);
		indice = indice + 1;

		guardadas[indice] = reglaActual;
		calc_first[apuntador][apuntador2++] = reglaActual;

		for(i = 0 + x; i < n; i++){
			int l = 0, b = 0;
			for(l = 0; l < apuntador2; l++){
				if(encontradas[i] == calc_first[apuntador][l])
				{
					b = 1;
					break;
				}
			}
			if(b == 0)
			{
				calc_first[apuntador][apuntador2++] = encontradas[i];
			}
		}
		x = n;
		apuntador++;
	}
	char guardadasfl[leidas];
	indice = -1;

	// Initializing the calc_follow array
	for(k = 0; k < leidas; k++) {
		for(w = 0; w < 50; w++) {
			calc_follow[k][w] = '!';
		}
	}
	apuntador = 0;
	int land = 0;
	for(e = 0; e < leidas; e++)
	{
		valorActual = reglasGramatica[e][0];
		apuntador2 = 0;
		bandera = 0;

		// Checking if Follow of valorActual
		// has alredy been calculated
		for(w = 0; w <= indice; w++)
			if(valorActual == guardadasfl[w])
				bandera = 1;

		if (bandera == 1)
			continue;
		land += 1;

		buscaSiguiente(valorActual);
		indice = indice + 1;

		guardadasfl[indice] = valorActual;
		printf(" SIGUIENTES( %c ) = { ", valorActual);
		calc_follow[apuntador][apuntador2++] = valorActual;

		for(i = 0 + y; i < m; i++) {
			int l = 0, b = 0;
			for(l = 0; l < apuntador2; l++)
			{
				if (primeras[i] == calc_follow[apuntador][l])
				{
					b = 1;
					break;
				}
			}
			if(b == 0)
			{
				printf("%c, ", primeras[i]);
				calc_follow[apuntador][apuntador2++] = primeras[i];
			}
		}
		printf(" }\n\n");
		y = m;
		apuntador++;
	}
}

void buscaSiguiente(char regla)
{
	int i, j;

	//Añadimos # como simbolo inicial
	if(reglasGramatica[0][0] == regla){
		primeras[m] = '#';
		m++;
	}

	for(i = 0; i < 13; i++){
		for(j = 2;j < 10; j++){
			if(reglasGramatica[i][j] == regla){
				if(reglasGramatica[i][j+1] != '\0'){
					// Se calcula el PRIMERO del siguiente simbolo no terminal de la regla
					prfollow(reglasGramatica[i][j+1], i, (j+2));
				}

				if(reglasGramatica[i][j+1]=='\0' && regla!=reglasGramatica[i][0])
				{
					//Buscamos el valor del follow del simbolo no terminal
					buscaSiguiente(reglasGramatica[i][0]);
				}
			}
		}
	}
}

void encuentraPrimeros(char regla, int renglon, int columna)
{
	int j;

	//El primer elemento es terminal
	if(!(isupper(regla))){
		encontradas[n++] = regla;
	}

	for(j = 0; j < leidas; j++){
		if(reglasGramatica[j][0] == regla){
			if(reglasGramatica[j][2] == '#'){
				if(reglasGramatica[renglon][columna] == '\0'){
					encontradas[n++] = '#';
				}else if(reglasGramatica[renglon][columna] != '\0' && (renglon != 0 || columna != 0)){
					encuentraPrimeros(reglasGramatica[renglon][columna], renglon, (columna+1));
				}
				else{
                    encontradas[n++] = '#';
				}
			}
			else if(!isupper(reglasGramatica[j][2])){
				encontradas[n++] = reglasGramatica[j][2];
			}else{
			    //Si aun no encontramos un tereminal avanzamos a la siguiente posición
				encuentraPrimeros(reglasGramatica[j][2], j, 3);
			}
		}
	}
}

void prfollow(char regla, int renglon, int columna)
{

	//Simbolo terminal como primer elemento
	if(!(isupper(regla))){
		primeras[m++] = regla;
	}else{
		int i = 0, j = 1;
		for(i = 0; i < leidas; i++){
			if(calc_first[i][0] == regla){
				break;
			}
		}

		//Nos aseguramos de descartar espacios vacios en el first
		while(calc_first[i][j] != '!'){
			if(calc_first[i][j] != '#'){ //Caso en el que el primer caracter es final
				primeras[m] = calc_first[i][j];
				m++;
			}else{
				if(reglasGramatica[renglon][columna] == '\0'){
					//Si encontramos el elemento vacio llegamos al final de la regla
					buscaSiguiente(reglasGramatica[renglon][0]); //Debemos ir a la siguiente regla y buscar el first y follow
				}else{
					//Simbolo terminal
					prfollow(reglasGramatica[renglon][columna], renglon, columna+1);
				}
			}
			j++;
		}
	}
}
