// Nome: Subdiscover - Subdomain Discover

// Autor: Pedro Otávio
// Email: pedr_ofs@hotmail.com
// Atualização: 23/03/2022

// Este programa tem por finalidade realizar a descoberta de subdominios de um determinado dominio.
// O método utilizado para descobrir subdominios é através de tentativas e erros de resolução de nomes por DNS,
// aplicando uma lista de subdominios e verificando o retorno da consulta DNS.


#include <stdio.h>	// Biblioteca padrão para entrada e saída de dados.
#include <string.h>	// Biblioteca que contém a função strcat.
#include <arpa/inet.h>	// Biblioteca que contém a função inet_ntoa.
#include <netdb.h>	// Biblioteca que contém a função gethostbyname.

int main(int argc, char *argv[]){

	// Verifica se o usuário entrou como o número de argumentos corretos.
	if(argc < 3){
		printf("%s alvo lista.txt", argv[0]);
	return(0);
	}

	// Cria um ponteiro do tipo char de nome resultado.
	char *alvo;

	// Atribui o promeiro argumento ao ponteiro alvo.
	alvo = argv[1];

	// Estrutura hostent.
	struct hostent *host;

	// Cria um ponteiro do tipo char de nome resultadod.
	char *resultado;

	// Cria variável do tipo char de 50 caracteres.
	char txt[50];

	// Cria um ponteiro do tipo FILE de nome lista.
	FILE *lista;

	// Cria um ponteiro do tipo FILE de nome subdominios.
	FILE *subdominios;

	// Lê o arquivo lista inserido no segundo argumento.
	lista = fopen(argv[2],"r");

	// Enquanto não for o fim do arquivo.
	while(fscanf(lista, "%s", &txt) != EOF){

		// Concatena o possível subdominio como o dominio.
		resultado = (char *) strcat(txt,alvo);

		// Realiza a consulta DNS através da função gethostbyname.
		host=gethostbyname(resultado);

		// Se o retorno da função gethostbyname for nulo:
		if(host == NULL){

			// Continue
			continue;
		}

		// Converte o retorno da função através da função inet_ntoa para um endereço IP decimal e o imprime na tela.
		printf("Subdominio encontrado: %s -> IP: %s \n", resultado, inet_ntoa(*((struct in_addr *)host->h_addr)));

		// Abre o arquivo em mode escrita.
		subdominios = fopen("subdominios", "a");

		// Insere o resultado no arquivo subdominios.
		fprintf(subdominios,"Subdominio encontrado: %s -> IP: %s \n",resultado, inet_ntoa(*((struct in_addr *)host->h_addr)));

		// Fecha o arquivo subdominios.
		fclose(subdominios);
	}
	return(0);
}
