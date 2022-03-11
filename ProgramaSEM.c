#include <stdio.h>
#include <stdlib.h>
#include "Estructuras.h"
#include<string.h>
struct usuarios *insertarusu (struct usuarios *, struct usuarios *);
void contNroControl (long *);
struct usuarios *archivoUsu (struct usuarios *);
struct recargas* altarecarga(struct usuarios *);
void insertarRecarga (struct recargas**, struct recargas**);
void actualizaSaldo (struct usuarios *, char* , float*, float);
void asignarec (struct recargas**, struct usuarios *);
struct recargas *InsRecUsu (struct recargas *, struct recargas *);
struct recargas *archiRecUsu (struct recargas *);
void altausuario(struct usuarios *);
int comparaCadena (char *, struct usuarios *, int);
void VerRecUsu(struct usuarios *);
struct recargas *iniciaRec ();
void consultasaldo(struct usuarios *);
void cargafecha(int*, int*, int*);
void cargahora(int*, int*);
//Movimientos
struct usuarios* insertarListUsu(struct usuarios *, struct usuarios *);
struct Movimientos* buscarantMovimientos(long int, struct Movimientos *);
struct usuarios* RecargaListUsua(struct usuarios *);
void insertarMovimientos(struct Movimientos **, struct Movimientos **);
struct Movimientos* borrarlistaMovimientos(struct Movimientos *);
void archivoMovDia(struct Movimientos *);
struct Movimientos* iniciarEstacionamiento(struct usuarios *,struct Movimientos *);
void imprimirMovDia(struct Movimientos *);
void inicioNroControl();
int generarNroControl();
void guardaNroControl(int);
void imprimirMovDia();
struct Movimientos* insertarListMovDia(struct Movimientos *, struct Movimientos *);
struct Movimientos* RecargaListMovDia(struct Movimientos *);
struct Movimientos* buscarnodo(int, struct Movimientos *);
void archivoMovHisto(struct Movimientos *);
struct Movimientos* finalizarEstacionamiento(struct usuarios *,struct Movimientos *);
void RecargaListMovHistorico(struct usuarios *);
void VerHistoricos(struct usuarios *);
void imprimirusuarios(struct usuarios *);
//Infracciones
void recorrerIRD (struct arbol *a);
void INFRACCIONES ();
void Cargar ();
void Consultar ();
void Buscarmedio(struct Inf*, struct arbol **); 
void contNroacta (long *acta);
void recorrerygrabar (struct Inf*);
void borrarlista (struct Inf *);
void borrararbol (struct arbol *);
void arbolinfractores (struct Fecha, struct Fecha, struct arbol *);
void insertar2 (struct Inf **, struct Inf **);
struct Inf* insertar3 (struct Inf *, struct Inf *);
struct arbol *insertararb (struct arbol *, struct arbol *);
struct Inf * insertar (struct Inf *, struct Inf *);
struct Inf * recorrerysubir (struct Inf *);
struct Inf *archivoinf;
FILE *puntinf;
char n = '1';
int bandinf = 0;

main (){
	
	int volver = 1;
	struct usuarios *L=NULL, *nuevo=NULL, *auxusu=NULL;
	struct recargas *rec=NULL;
	struct archiusu carga;
	struct Movimientos *MovDia=NULL;
	FILE *archbin;
	if ((archbin=fopen("Usuarios.b","rb"))!=NULL){ //carga la lista de usuarios del archivo
		fread(&carga,sizeof(carga),1,archbin);
		while (!feof(archbin)){
			nuevo = (struct usuarios*)malloc(sizeof(struct usuarios));
			if(nuevo!=NULL){
				strcpy(nuevo->nroCuenta, carga.nroCuenta);
				strcpy(nuevo->patente,carga.patente);
				nuevo->saldo=carga.saldo;
				nuevo->MovHistoricos=NULL;
				nuevo->recUsu=NULL;
				nuevo->sgte=NULL;
				L = insertarusu (nuevo, L);
			}
			else
				printf("Error de asignacion de memoria\n");
			fread(&carga,sizeof(carga),1,archbin);
		}
		fclose(archbin);
	}
	else
		printf ("Error de apertura de archivo \n");
		
	rec = iniciaRec (); //crea lista recargas históricas que están en el archivo
	asignarec (&rec, L);  //asigna a cada usuario sus recargas
	RecargaListMovHistorico(L);
	
int op, op1;
	
	while(volver == 1){
		
	 system("cls");	
	 printf("\t\t\t------------------------------------------\n");
	 printf ("\t\t\t------------BIENVENIDO A SEM--------------\n");
	 printf("\t\t\t------------------------------------------\n");
	 printf(" 1) USUARIOS\n");
	 printf(" 2) INSPECTORES\n");
	 printf(" 3) SALIR\n");
	 printf("Elija una opcion: ");
	 fflush(stdin);
	 scanf("%d",&op);
	 system("cls");
		switch(op){
			case  1:
				printf(" 1) Registrar usuario\n");
				printf(" 2) Realizar recarga\n");
				printf(" 3) Ver recargas\n");
				printf(" 4) Consultar saldo\n");
				printf(" 5) Inicializar estacionamiento\n");
				printf(" 6) Finalizar estacionamiento\n");
				printf(" 7) Ver historial de movimientos\n");
				printf("Elija una opcion: ");
				fflush(stdin);
				scanf("%d",&op1);
				system("cls");
				switch(op1){
					case  1:
						altausuario(L);
						break;
					case  2:
						rec = altarecarga(L); 
						asignarec (&rec, L);
						break;
					case  3:
						VerRecUsu(L);
						break;
					case  4:
						consultasaldo(L);
						break;
					case  5:
						MovDia = iniciarEstacionamiento(L, MovDia);
						break;
					case  6:
						MovDia = finalizarEstacionamiento(L, MovDia);
						break;
					case  7:
						VerHistoricos(L);
						break;
				}
			break;
			case  2:
				printf(" 1) Ver usuarios\n");
				printf(" 2) Ver movimientos del dia\n");
				printf(" 3) Ir al menu de infracciones\n");
				printf("Elija una opcion: ");
				fflush(stdin);
				scanf("%d",&op1);
				system("cls");
				switch(op1){
					case  1:
						imprimirusuarios(L);
						break;
					case  2:
						imprimirMovDia(MovDia);
						break;
					case 3:
						INFRACCIONES ();
						break;
				}
				break;
			case  3:
				printf("Gracias por usar nuestro servicio. Buen Dia!\n");
				volver = 0;
				break;
			default:
				printf ("Valor introducido invalido\n");
		}
		system("pause");
	}	

	
	remove ("Recargas.b"); //se elimina el archivo Recargas para volver a crear uno nuevo con las cargas nuevas hechas
	auxusu = L;
	while (auxusu!=NULL){ //al finalizar el programa crea un nuevo archivo de recargas y libera las listas
		if (auxusu->recUsu!=NULL)
			auxusu->recUsu = archiRecUsu (auxusu->recUsu);
		auxusu = auxusu->sgte;
	}
	L= archivoUsu (L); //al finalizar el programa crea un nuevo archivo usuario y libera la lista
}	
struct usuarios *insertarusu (struct usuarios *p, struct usuarios *r){ //función recursiva que va insertando los nodos al final
	if (r!=NULL)
		r->sgte = insertarusu (p,r->sgte);
	else
		r = p;
	return (r);
}
struct usuarios *archivoUsu (struct usuarios *rc){ //función que crea un nuevo archivo con lo que tiene los nodos y los va liberando
	struct usuarios *bor;
	struct archiusu carga;
	FILE *archbin;

	if ((archbin=fopen("Usuarios.b","wb"))!=NULL){
		while (rc!=NULL){
			strcpy(carga.nroCuenta,rc->nroCuenta);
			strcpy(carga.patente,rc->patente);
			carga.saldo=rc->saldo;
			fwrite(&carga,sizeof(carga),1,archbin);
			bor = rc;
			bor->MovHistoricos = borrarlistaMovimientos(bor->MovHistoricos);
			rc = rc->sgte;
			bor->sgte = NULL;
			free (bor);
		}
		fclose(archbin);
	}
	else
		printf ("Error de apertura de archivo \n");
	return (NULL);
}
struct recargas* altarecarga(struct usuarios *ini){	//procedimiento que permite hacer nuevas recargas
	struct recargas *L=NULL, *nuevoRec=NULL;
	int busqRec=0;
	char  band='1', celular[12];
	while (band!='0'){
		switch (band){	//controla que se ingresen valores válidos
			case '1':{
				nuevoRec = (struct recargas*)malloc(sizeof(struct recargas));
				if (nuevoRec!= NULL){
					printf("Ingrese el celular del usuario que desea realizar la recarga\n");
					fflush(stdin);
					fgets(celular,11,stdin);
					busqRec = comparaCadena (celular,ini,1);
					if(busqRec == 1){	//si existe permite continuar con la carga
						busqRec = 0;
						strcpy(nuevoRec->nroCuenta,celular);
						contNroControl(&nuevoRec->nroControl);
						printf("Ingrese el monto a recargar (minimo $50)\n");
						scanf("%f", &nuevoRec->monto);
						while (nuevoRec->monto<50){	//controla que se cargue como mínimo $50
							printf("Ingreso un valor inferior a $50. Intente de nuevo\n");
							scanf("%f", &nuevoRec->monto);
						}
						actualizaSaldo (ini, celular, &nuevoRec->saldoPrevio, nuevoRec->monto); //procedimiento que actualiza los saldos
						cargafecha(&nuevoRec->fecha.dia,&nuevoRec->fecha.mes,&nuevoRec->fecha.anio);
						cargahora(&nuevoRec->horarc.hora,&nuevoRec->horarc.min);
						nuevoRec->sgte = NULL;
						insertarRecarga (&nuevoRec, &L);
						printf("Desea realizar otra recarga?\n0) No\n1) Si\n");
						fflush(stdin);
						scanf ("%c",&band);
					}
					else{
						busqRec = 0;
						free (nuevoRec);
						printf ("El numero ingresado no existe en la base de dato\n");
						printf("Desea realizar otra recarga?\n0) No\n1) Si\n");
						fflush(stdin);
						scanf ("%c",&band);
					}
				}
				else
					printf("Error de asignacion de memoria\n");
				break;
			}
			default:{
				printf ("Valor introducido invalido\n");
				printf("Desea realizar otra recarga?\n0) No\n1) Si\n");
				fflush(stdin);
				scanf ("%c",&band);
			}
		}
	}
	return (L);
}
void cargafecha(int*Dia1, int*Mes1, int*Anio1){
	printf("Ingrese el dia\n");	
	fflush(stdin);
	scanf ("%d",&(*Dia1));
//	printf("%d",*Dia1);
	while ((*Dia1) < 1 || (*Dia1) > 31){
		printf ("Escribio un dia no valido. Intente de nuevo\n");
	
		scanf ("%d",&(*Dia1));
	}
	printf("Ingrese el mes\n");
	fflush(stdin);
	scanf ("%d",&(*Mes1));
	while ((*Mes1) < 1 || (*Mes1)>12){
		printf ("Escribio un mes no valido. Intente de nuevo\n");
		fflush(stdin);
		scanf ("%d",&(*Mes1));
	}
	printf("Ingrese el anio\n");
	fflush(stdin);
	scanf ("%d",&(*Anio1));
	while ((*Anio1) < 2020 || (*Anio1)>2040){
		printf ("Escribio un anio no valido. Intente de nuevo\n");
		fflush(stdin);
		scanf ("%d",&(*Anio1));
	}
}
void cargahora(int*Hora1, int*Minuto1){
	printf("Ingrese la hora\n");
	fflush(stdin);
	scanf ("%d",&(*Hora1));
	while ((*Hora1) < 0 || (*Hora1)>23){
		printf ("Escribio una hora no valida. Intente de nuevo\n");
		fflush(stdin);
		scanf ("%d",&(*Hora1));
	}
	printf("Ingrese los minutos\n");
	fflush(stdin);
	scanf ("%d",&(*Minuto1));
	while ((*Minuto1) < 0 || (*Minuto1)>59){
		printf ("Escribio unos minutos no validos. Intente de nuevo\n");
		fflush(stdin);
		scanf ("%d",&(*Minuto1));
	}
}
void contNroControl (long *carga){ //contador para el numero de control de las recargas
	struct contadorcontrol conta;
	FILE  *puntcont;
	int i=-1;
	if((puntcont=fopen("NumeroControl.b","r+b"))!=NULL){
		fread(&conta,sizeof(conta),1,puntcont); //lee el archivo
		conta.nroControl++; //suma uno a lo que hay en el archivo (la primera y unica posicion)
		*carga = conta.nroControl;
		fseek(puntcont,sizeof(conta)*i,SEEK_CUR); //vuelve a la posicion anterior para poder sobreescribir
		fwrite(&conta,sizeof(conta),1,puntcont);
		fclose(puntcont);
	}
	else
		printf("Error de apertura de archivo \n");
}
void insertarRecarga (struct recargas**nv, struct recargas**ini){ 	//las nuevas recargas van al final. No hay orden
	struct recargas *rc, *post;
	int ultimo=0;
	if (*ini==NULL){
		(*nv)->sgte = (*ini);
		(*ini) = (*nv);
	}
	else{
		rc = (*ini);
		post =(*ini)->sgte;
		while(rc!=NULL && ultimo==0){
			if (post==NULL){
				rc->sgte = (*nv);
				ultimo = 1;
			}
			else{
				rc = rc->sgte;
				post = rc->sgte;
			}
		}
	}
	(*nv)=NULL;
}
void actualizaSaldo (struct usuarios *ini, char* dato, float*previo, float carga){
	while (ini!=NULL){
		if (strcmp(dato,ini->nroCuenta)==0){
			*previo = ini->saldo;	//actualiza el campo "saldo previo" cuando se realiza una nueva recarga
			ini->saldo += carga;	//actualiza el saldo del usuario en la lista de usuarios
			ini = NULL;
		}
		else
			ini = ini->sgte;
	}
}
void asignarec (struct recargas**nodorecar, struct usuarios *usu){ 	//procedimiento que va asignando las recargas a cada usuario
	struct usuarios *rcusu=NULL;
	struct recargas *post=NULL;
	int ultimo=0;
	while (*nodorecar!=NULL){ //primero recorre la lista de recargas
		rcusu = usu;
		while (rcusu!=NULL){ //luego va recorriendo la lista de usuarios para encontrar al usuario
			if(strcmp(rcusu->nroCuenta,(*nodorecar)->nroCuenta)==0){
				post = (*nodorecar)->sgte; //guarda la posición del posterior al nodo a sacar
				(*nodorecar)->sgte = NULL; 
				rcusu->recUsu = InsRecUsu ((*nodorecar),rcusu->recUsu); //función para insertar
				rcusu=NULL;
			}
			else
				rcusu = rcusu->sgte;
		}
		(*nodorecar) = post; //se usa el posterior para hacer avanzar el recorrido de la lista recargas
	}
}
struct recargas *InsRecUsu (struct recargas *rec, struct recargas *L){ //función recursiva que va insertando los nodos al final
	if (L!=NULL)
		L->sgte = InsRecUsu (rec,L->sgte);
	else
		L = rec;
	return (L);
}
struct recargas *archiRecUsu (struct recargas *rc){ //función que crea un nuevo archivo recarga y va liberando los nodos
	struct recargas*bor;
	struct archirec carga;
	FILE *archbin;
	if ((archbin=fopen("Recargas.b","ab"))!=NULL){
		while (rc!=NULL){
			carga.nroControl=rc->nroControl;
			strcpy(carga.nroCuenta,rc->nroCuenta);
			carga.monto=rc->monto;
			carga.saldoPrevio=rc->saldoPrevio;
			carga.fecha.dia = rc->fecha.dia;
			carga.fecha.mes = rc->fecha.mes;
			carga.fecha.anio = rc->fecha.anio;
			carga.horarc.hora = rc->horarc.hora;
			carga.horarc.min = rc->horarc.min;
			fwrite(&carga,sizeof(carga),1,archbin);
			bor = rc;
			rc = rc->sgte;
			bor->sgte = NULL;
			free (bor);
		}
		fclose(archbin);
	}
	else
		printf ("Error de apertura de archivo \n");
	return (NULL);
}
void altausuario(struct usuarios *ini){	//procedimiento que permite ingresar nuevos usuarios
	struct usuarios *nuevoUsu=NULL;
	int  busqUsu;
	char celular[12];
	printf("Ingrese el celular del usuario\n");
	fflush(stdin);
	fgets(celular,11,stdin);
	busqUsu = comparaCadena (celular,ini,1);
	if (busqUsu==1)	//si existe el usuario no le permite volver a cargar el mismo
		printf ("El usuario ya existe\n");
	else{
		nuevoUsu = (struct usuarios*)malloc(sizeof(struct usuarios));
		if (nuevoUsu!= NULL){
			strcpy(nuevoUsu->nroCuenta,celular);
			printf("Ingrese la patente del usuario\n");
			fflush(stdin);
			fgets(nuevoUsu->patente,9,stdin);
			busqUsu = comparaCadena (nuevoUsu->patente,ini,2); //Busca si existe la patente en la lista		
			while (busqUsu==1){ //No permite que una patente tenga dos usuarios
				printf ("Patente existente. Elija otra\n");
				fflush(stdin);
				fgets(nuevoUsu->patente,9,stdin);
				busqUsu = comparaCadena (nuevoUsu->patente,ini,2);
			}
			nuevoUsu->saldo=0;
			nuevoUsu->MovHistoricos=NULL;
			nuevoUsu->recUsu = NULL;
			nuevoUsu->sgte = NULL;
			ini = insertarusu (nuevoUsu, ini);
		}
		else
			printf("Error de asignacion de memoria\n");	
	}					
}
int comparaCadena (char *dato, struct usuarios *rc, int bandera){ //sirve para ver si existe un celular o una patente
	int encontrado = 0;
	switch (bandera){
		case 1:{ //este caso se usa cuando se necesita comparar por el número de celular
			while (rc!=NULL){
				if(strcmp(dato,rc->nroCuenta)==0){
					encontrado = 1;
					rc = NULL;
				}
				else
					rc = rc->sgte;
			}
			break;
		}
		case 2:{ //este caso se usa cuando se necesita comparar por la patente
			while (rc!=NULL){
				if(strcmp(dato,rc->patente)==0){
					encontrado = 1;
					rc = NULL;
				}
				else
					rc = rc->sgte;
			}
			break;
		}
	}
	return (encontrado);
}
void VerRecUsu(struct usuarios *iniusu){ //permite ver las recargas de un usuario en particular
	struct recargas *rcrec=NULL;
	int encontrado=0;
	char celular[12];
	printf ("Escriba el celular del usuario que desea ver las recargas\n");
	fflush(stdin);
	fgets(celular,11,stdin);
	while (iniusu!=NULL && encontrado==0){
		if(strcmp(celular,iniusu->nroCuenta)==0)
			encontrado = 1;
		else
			iniusu = iniusu->sgte;
	}
	if (encontrado==1){
		rcrec = iniusu->recUsu;
		printf ("El usuario con celular %s, patente %s y saldo %.2f tiene las siguientes recargas\n", iniusu->nroCuenta, iniusu->patente, iniusu->saldo);
		while (rcrec!=NULL){
			printf ("Recarga nro: %ld\n", rcrec->nroControl);
			printf ("Monto: %.2f\n", rcrec->monto);
			printf("Saldo previo: %.2f\n", rcrec->saldoPrevio);
			printf("Fecha: %d / %d / %d\n",rcrec->fecha.dia,rcrec->fecha.mes,rcrec->fecha.anio);
			printf ("Hora: %d : %d\n", rcrec->horarc.hora,rcrec->horarc.min);
			printf ("--------------\n");
			rcrec = rcrec->sgte;
		}
	}else
		printf ("Usuario inexistente en la base de datos\n");
	
}
struct recargas *iniciaRec (){ //Al iniciar el programa crea una lista con lo que haya en el archivo de recargas
	struct recargas *nuevo=NULL, *L=NULL;
	struct archirec carga;
	FILE *archbin;
	if ((archbin=fopen("Recargas.b","rb"))!=NULL){
		fread(&carga,sizeof(carga),1,archbin);
		while (!feof(archbin)){	
			nuevo = (struct recargas*)malloc(sizeof(struct recargas));
			if (nuevo!=NULL){
				nuevo->nroControl=carga.nroControl;
				strcpy(nuevo->nroCuenta,carga.nroCuenta);
				nuevo->monto=carga.monto;
				nuevo->saldoPrevio=carga.saldoPrevio;
				nuevo->fecha.dia = carga.fecha.dia;
				nuevo->fecha.mes = carga.fecha.mes;
				nuevo->fecha.anio = carga.fecha.anio;
				nuevo->horarc.hora = carga.horarc.hora;
				nuevo->horarc.min = carga.horarc.min;
				nuevo->sgte = NULL;
				insertarRecarga (&nuevo, &L);
			}
			else
				printf("Error de asignacion de memoria\n");
			fread(&carga,sizeof(carga),1,archbin);
		}
		fclose(archbin);
		
	}
	else
		printf ("Error de apertura de archivo \n");
	return (L);
}
void consultasaldo(struct usuarios *ini){ //muestra el saldo de un usuario
	int encontrado=0;
	char celular[12];
	printf ("Escriba el celular del usuario que desea consultar su saldo\n");
	fflush(stdin);
	fgets(celular,11,stdin);
	while (ini!=NULL && encontrado==0){
		if(strcmp(celular,ini->nroCuenta)==0)
			encontrado = 1;
		else
			ini = ini->sgte;
	}
	if (encontrado==1)
		printf ("Su saldo es de $%.2f\n",ini->saldo);
	else
		printf ("Usuario inexistente\n");
}

//MOVIMIENTO DIA
 
//FUNCION BUSCAR ANTERIOR DE MOVIMIENTOS: MOVDIA Y MOVHISTORICOS
struct Movimientos* buscarantMovimientos(long int dato, struct Movimientos *Mv){
	struct Movimientos *ant;
	ant = NULL;
	while(Mv != NULL){
		if(Mv->NroControl >= dato){// compara por numero de control
			Mv = NULL;
		}else{
			ant = Mv;
			Mv = Mv->sgte;
		}
	}
	return ant;
}

//FUNCION INSERTAR LISTA DE MOVIMIENTOS: MOVDIA Y MOVHISTORICOS
void insertarMovimientos(struct Movimientos **nodo, struct Movimientos **Mov){
	struct Movimientos *ant;
	ant = buscarantMovimientos((*nodo)->NroControl,*Mov);
	if(ant != NULL){
		(*nodo)->sgte = ant->sgte;
		ant->sgte = (*nodo);
	}else{
		(*nodo)->sgte = (*Mov);
		(*Mov)= (*nodo);
	}
	
	(*nodo) = NULL;
	

}

//FUNCION BORRAR LISTA DE MOVIMIENTOS: MOVDIA Y MOVHISTORICOS
struct Movimientos* borrarlistaMovimientos(struct Movimientos *Movi){ 
	struct Movimientos *aux, *bor;
	
	while(Movi != NULL){
		aux = Movi;
		Movi = Movi->sgte;
		aux->sgte = NULL;
		free(aux);
	}
	return NULL;
}

//FUNCION QUE INICIA EL CONTADOR DE MOV DIA
void inicioNroControl(){
	FILE *puntero;
	int num;
	if((puntero = fopen("NroControl.b","wb")) != NULL){
		num = 1;
		fwrite(&num,sizeof(num),1,puntero);
		fclose(puntero);
	}
}

//FUNCION PARA OBTENER EL ULTIMO NUMERO DE CONTROL DE LA LISTA MOV DIA
int generarNroControl(){
	FILE *puntero;
	int num, aux;
	if((puntero = fopen("NroControl.b","rb")) != NULL){
		fread(&num,sizeof(num),1,puntero);
		aux = num;
		fclose(puntero);
	}
	return(aux);
}

//FUNCION PARA GUARDAR EL NUMERO DE CONTROL
void guardaNroControl(int cont){
	FILE *puntero;
	int num;
	if((puntero = fopen("NroControl.b","wb")) != NULL){
		num = cont + 1;
		fwrite(&num,sizeof(num),1,puntero);
		fclose(puntero);
	}
}

//FUNCION PARA INICIAR ESTACIONAMIENTO
struct Movimientos* iniciarEstacionamiento(struct usuarios *L1, struct Movimientos *MvDia){//arreglar

	
	struct Movimientos *ndoaux=NULL;
	
	int band = 0, aux,aux2, op;
	char patent[10];   
	 
	
	printf("Ingrese su patente\n"); 
	getchar();
	fgets(patent,9,stdin);
	
	
	while((L1 != NULL) && (band == 0)){ 
		if(strcmp(L1->patente,patent) == 0){ //busca si existe la patente o no //aca esta el error
			if(L1->saldo >= -12){//verifica si el saldo es mayor o igual al limite
				ndoaux = (struct Movimientos *) malloc(sizeof(struct Movimientos));
				if(ndoaux != NULL){
					aux2 = generarNroControl();
					printf("\nNRO DE CONTROL: %d\n",aux2);
				    ndoaux->NroControl = aux2; //guarda el nro de control actualizado en el nod
					strcpy(ndoaux->patente,L1->patente);
					strcpy(ndoaux->Nrocuenta,L1->nroCuenta);	
					cargafecha(&ndoaux->fech.dia,&ndoaux->fech.mes,&ndoaux->fech.anio);
				   printf("Ingrese la hora de inicio del estacionamiento:\n");
					cargahora(&ndoaux->tempini.hora,&ndoaux->tempini.min);
					ndoaux->hraini = ndoaux->tempini.hora;
					ndoaux->saldoprev = L1->saldo;

					ndoaux->sgte = NULL;
					insertarMovimientos(&ndoaux, &MvDia);
					guardaNroControl(aux2);//aca 
					band = 1;
					L1 = NULL;
			    }else{
					printf("No hay espacio disponible\n");
			    }
			}else{
				band = 1;
				aux = 1;
				L1 = NULL;
			}
		}else{
		 
			L1 = L1->sgte;
		}
	}
	
	if(aux == 1){
		printf("Saldo Insuficiente\n");
	}

    if(band == 0){
    	printf("La patente ingresada no esta registrada\n");
	}
	
	

	return MvDia;
}

//FUNCION PARA IMPRIMIR EL CONTENIDO DE MOV.DIA
void imprimirMovDia(struct Movimientos *Mv){ //ARREGLAR
	struct Movimientos *dia=NULL;
	
	dia = Mv;
		
	if(dia == NULL){
		printf("No existen estacionamientos iniciados en el dia de hoy\n");
	}
	if(dia != NULL){
		printf("----------------------------\n");
		printf("ESTACIONAMIENTOS INICIADOS: \n");
		printf("----------------------------\n");
	}
	while(dia != NULL){
		printf("Numero de control: %d\n",dia->NroControl);
		printf("Numero de cuenta: %s\n",dia->Nrocuenta);
		printf("Patente: %s\n",dia->patente);
		printf("Saldo: %.2f\n",dia->saldoprev);
		printf("Fecha: %d/%d/%d\n",dia->fech.dia,dia->fech.mes,dia->fech.anio);
		printf("Hora de inicio: %d:%d\n",dia->tempini.hora,dia->tempini.min);
		printf("\n");
		dia = dia->sgte;
	}
	Mv = dia;
	dia = NULL;
}

struct Movimientos* buscarnodo(int dato, struct Movimientos *ini){
	int band = 0;
	
struct Movimientos	*ante = NULL;
	
	while((ini != NULL) && (band == 0)){
		
		if(ini->NroControl == dato){
			
			band = 1;
			ini = NULL;
		}else{
			
			ante = ini;
			ini = ini->sgte;
		}
	}
		
	
	return ante;
}

//FUNCION PARA FINALIZAR EL ESTACIONAMIENTO
struct Movimientos* finalizarEstacionamiento(struct usuarios *L3, struct Movimientos *Mdia){
	
	struct Movimientos *Movd=NULL, *L4=NULL, *ant=NULL;

	
	char patente[10];
	long int temptotal, aux2;
	int band=0;
	
	
	printf("Ingrese su patente para finalizar el estacionamiento: ");
	getchar();
	fgets(patente,9,stdin);
	
	Movd = Mdia;
	
	while((Movd != NULL) && (band == 0)){
		if(strcmp(Movd->patente,patente) == 0 ){
			printf("-----------------------\n");
			printf("DATOS DE LA OPERACION: \n");
			printf("-----------------------\n");
			
			printf("Numero de control: %d\n",Movd->NroControl);
			printf("Numero de cuenta: %s\n",Movd->Nrocuenta);
			printf("Patente: %s\n",Movd->patente);
			printf("Saldo: %.2f\n",	Movd->saldoprev);
			printf("Fecha: %d/%d/%d\n",Movd->fech.dia,Movd->fech.mes,Movd->fech.anio);
			printf("Hora de inicio: %d:%d\n",Movd->tempini.hora,Movd->tempini.min);
			
			printf("\nIngrese la hora de finalizacion del estacionamiento\n");
			
			cargahora(&Movd->tempfin.hora,&Movd->tempfin.min);
			
			Movd->hrafinal = Movd->tempfin.hora;
			
			while(Movd->hrafinal < Movd->hraini){
				printf("\nLa hora ingresada no es correcta. Por favor ingrese de vuelta\n");
				cargahora(&Movd->tempfin.hora,&Movd->tempfin.min);
				Movd->hrafinal = Movd->tempfin.hora;
			}
		
			temptotal = Movd->hrafinal- Movd->hraini; 
	
			if(temptotal < 1){
				Movd->monto = 12;
			}else{
				if(temptotal >= 1){
					Movd->monto = temptotal*12;
				}
			}	
			
			printf("\nEl monto total a pagar es : %.f \n",Movd->monto);
			printf("Hora de finalizacion: %d:%d\n",Movd->tempfin.hora,Movd->tempfin.min);
				
		   
			
		    ant = buscarnodo(Movd->NroControl, Mdia); //SACA EL NODO A INSERTAR A LA LISTA DE MOV HISTORICO DEL USUARIO	
		
			if(ant == NULL){
				Mdia = Movd->sgte;
				Movd->sgte = NULL;
			}else{	
				ant->sgte = Movd->sgte;
				Movd->sgte = NULL;
			}
			
			
			while(L3 != NULL){//busca el usuario por la patente y obtiene su puntero Mov.Historicos
				if(strcmp(L3->patente,patente) == 0){
					archivoMovHisto(Movd);
					L3->saldo = L3->saldo - Movd->monto;
					insertarMovimientos(&Movd,&L3->MovHistoricos);
					L3 = NULL;
				}else{
					L3 = L3->sgte;
				}
			}
			 
			band = 1;
			Movd = NULL;
			printf("\nESTACIONAMIENTO FINALIZADO\n\n");
		}else{
			
			band = 0;
	    	Movd = Movd->sgte;
		}
	}
	
	 
	if(band == 0){
		printf("No se ha encontrado su patente\n");
	}
	
 return Mdia;
		
}

//FUNCION QUE GUARDA EL NODO DE MOV.HISTORICO A UN ARCHIVO
void archivoMovHisto(struct Movimientos *Li){
	
	struct ArchMovimientos histo;
	FILE *arch;

	if((arch = fopen("MovHistoricos.b","ab")) != NULL ){
		
		histo.fech.anio = Li->fech.anio;
		histo.fech.mes = Li->fech.mes;
		histo.fech.dia = Li->fech.dia; 
		histo.fecha = Li->fecha;
		histo.tempini.hora = Li->tempini.hora;
		histo.tempini.min = Li->tempini.min;
		histo.hraini = Li->hraini;
		histo.NroControl = Li->NroControl;
		strcpy(histo.Nrocuenta,Li->Nrocuenta);
		strcpy(histo.patente,Li->patente);
		histo.saldoprev = Li->saldoprev;
		histo.monto = Li->monto;
		histo.tempfin.hora = Li->tempfin.hora;  //se agrego los campos faltantes
		histo.tempfin.min = Li->tempfin.min; 
		fwrite(&histo,sizeof(histo),1,arch);
		fclose(arch);
	}
		
	
}

//FUNCION QUE RECARGA LAS LISTAS DE MOV. HISTORICOS
void RecargaListMovHistorico(struct usuarios *Ls){
	struct usuarios *L=NULL;
	struct Movimientos *nodo=NULL;
	struct ArchMovimientos mv;
	FILE *arch;
	
	L = Ls;
	
	while(L != NULL){
	
		if ((arch = fopen("MovHistoricos.b","rb")) != NULL){
			fread (&mv, sizeof (mv), 1, arch);
			while (!feof (arch)){
				nodo = (struct Movimientos *) malloc (sizeof (struct Movimientos));	
				if(nodo != NULL){	
					if(strcmp(mv.Nrocuenta,L->nroCuenta) == 0){
					
						nodo->fech.anio = mv.fech.anio;
						nodo->fech.mes = mv.fech.mes;
						nodo->fech.dia = mv.fech.dia; 
						nodo->fecha = mv.fecha;
						nodo->tempini.hora = mv.tempini.hora;
						nodo->tempini.min = mv.tempini.min;
						nodo->hraini = mv.hraini;
						nodo->NroControl = mv.NroControl;
						strcpy(nodo->Nrocuenta,mv.Nrocuenta);
						strcpy(nodo->patente,mv.patente);
						nodo->saldoprev = mv.saldoprev;
						nodo->monto = mv.monto;
						nodo->tempfin.hora = mv.tempfin.hora;  //se agrego los campos faltantes
						nodo->tempfin.min = mv.tempfin.min; 
						nodo->sgte = NULL;
						insertarMovimientos(&nodo, &L->MovHistoricos); 
					}
				}else{			
					printf ("Espacio no disponible\n");
			 	}
			 	
			    fread (&mv, sizeof (mv), 1, arch);
			}
			
		 fclose (arch); 	
		}
		L = L->sgte;
    }
    
  
   
}


//FUNCION QUE IMPRIME LOS MOVIMIENTOS HISTORICOS DE UN USUARIO EN ESPECIFICO
void VerHistoricos(struct usuarios *Lu){
	struct usuarios *usu = NULL;
	struct Movimientos *his = NULL, *bor = NULL;
	
	char cuenta[11];
	int band = 0;
		
	usu = Lu;

	printf("Ingrese su numero de cuenta\n");
	getchar();
	gets(cuenta);
	
	
	while(usu != NULL){
		
		if(strcmp(usu->nroCuenta,cuenta) == 0){
			
			his = usu->MovHistoricos;
			if(his == NULL){
				printf("El numero de cuenta %s aun no posee movimientos\n",usu->nroCuenta);
			}
			if(his != NULL){
				printf("------------------------------------------------\n");
				printf("Historial de movimientos del usuario %s: \n",usu->nroCuenta);
				printf("------------------------------------------------\n\n");
			}
			while(his != NULL){
		
				printf("Numero de control: %d\n",his->NroControl);
				printf("Patente: %s\n",his->patente);
				printf("Saldo: %.2f\n",his->saldoprev);
				printf("Fecha: %d/%d/%d\n",his->fech.dia,his->fech.mes,his->fech.anio);
				printf("Hora de inicio: %d:%d\n",his->tempini.hora,his->tempini.min);
				printf("Hora de final: %d:%d\n",his->tempfin.hora,his->tempfin.min);
				printf("Monto: %.2f\n",his->monto);
				printf("\n");
				
				his = his->sgte;		
			}
			band = 1;
		}
		usu = usu->sgte;
	}
	
	if(band == 0){
		printf("El numero de cuenta ingresado no se encuentra en nuestra base de datos\n");
	}
}

void imprimirusuarios(struct usuarios *ls){
	struct usuarios *usu;
	
	usu = ls;
  printf("NRO DE CUENTA	|"); printf("SALDO	|") ;printf("PATENTE	\n"); 
	while(usu != NULL){
	
		printf("%s 	",usu->nroCuenta);
		printf("%.2f	",usu->saldo);
		printf("%s	",usu->patente);
		printf("\n");
		usu = usu->sgte;
	}
}

//INFRACCIONES

void INFRACCIONES (){
	printf ("==========================MENU INFRACCIONES==========================\n");
	printf ("Ingrese una de las opciones presente\n");
	printf ("1) Carga de Infracciones\n");
	printf ("2) Consultas de infracciones\n");
	printf ("0) Salir\n\n");
	while (n!= '0'){ 
		fflush(stdin);
		scanf ("%c", &n);
		switch (n){
		case '1': {
				printf ("=================Eligio Cargar infracciones=================\n");
				Cargar ();
			break;
		}
		case '2': {
				printf ("=================Eligio Consultar infracciones=================\n");
				Consultar ();
			break;
		}
		case '0': 
				printf ("Eligio Salir del menu Infracciones\n");
				break;		
		default:{
				printf ("Valor introducido invalido para el menu infracciones\n");
		} 	
        }
   }  
}
	
	
void Cargar (){
struct Inf *nvo, *Infracciones = NULL;
	int nro =1, band=0;
	while (nro != 0){
		nvo= (struct Inf *) malloc (sizeof (struct Inf));	
		if (nvo != NULL){
			printf ("Ingrese 1 para realizar una carga e ingrese 0 para finalizar la carga\n");
			scanf ("%d", &nro);
			if (nro != 0){
					contNroacta(&nvo->numActa);
					getchar();
					printf ("\nIngrese la fecha en tres etapas, primero el dia, luego mes y por ultimo el anio\n");
					while (band==0){
						printf("Ingrese el dia\n");	
						scanf ("%d",&nvo->fecha.dia);
						printf("Ingrese el mes\n");
						fflush(stdin);
						scanf ("%d",&nvo->fecha.mes);
						printf("Ingrese el anio\n");
						fflush(stdin);
						scanf ("%d",&nvo->fecha.anio);
						if (nvo->fecha.dia>=1 && nvo->fecha.dia<=31 && nvo->fecha.mes >=1 && nvo->fecha.mes<=12 && nvo->fecha.anio >=1990 && nvo->fecha.anio<=2050){
							band=1;
						}
						else{
							printf ("Fecha fuera de parametro, intente nuevamente\n\n");
						}
					}
					band=0;
					fflush(stdin);
					printf ("Ingrese la hora, primero los dos digitos de la hora, luego los minutos\n");
					while (band==0){
						printf("Ingrese la hora\n");
						scanf ("%d",&nvo->h.hora);
						printf("Ingrese los minutos\n");
						fflush(stdin);
						scanf ("%d",&nvo->h.min);
						if (nvo->h.hora >00 && nvo->h.hora <= 23 && nvo->h.min >= 00 && nvo->h.min <= 59){
							band=1;	
						}
						else {
							printf ("Hora fuera de rango, ingrese nuevamente valores validos\n");
						}
					}
					printf ("Ingrese la patente sin guion\n");
					getchar();
					fgets (nvo->patente,7,stdin);
					getchar();
					printf ("Ingrese la marca del vehiculo\n");
					fflush(stdin);
					fgets (nvo->marca,20,stdin);
					printf ("Ingrese la modelo del vehiculo\n");
					fflush(stdin);
					fgets (nvo->modelo,20,stdin);
					printf ("Ingrese el tipo del vehiculo\n");
					fgets (nvo->tipoVehiculo,20,stdin);
					printf ("Ingrese el tipo de infraccion\n");
					fgets (nvo->tipoInfraccion,20,stdin);
					fflush(stdin);
					printf ("Ingrese las observaciones\n");
					fgets (nvo->observacion,20,stdin);
					printf ("Ingrese el nombre del agente\n");
					fgets (nvo->nombreAgente,20,stdin);
					printf ("Ingrese el legajo del agente\n");
					scanf ("%ld", &nvo->legajoAgente);
					fflush(stdin);
					nvo->sgte = NULL;
					Infracciones = insertar (nvo, Infracciones); 		//***INSERTA EL NODO EN LA LISTA***
					}
			else {
				printf ("Usted seleccionado finalizar la carga");
				recorrerygrabar(Infracciones);							//***RECORRE LA LISTA Y GUARDA EN UN ARCHIVO***
				printf ("PRESIONE CERO NUEVAMENTE PARA SALIR\n");
			}
		}
		else{
			printf ("No hay espacio disponible\n");		
		}
		} 
	borrarlista (Infracciones);	
}	

	
struct Inf * insertar (struct Inf *nn, struct Inf *In){  //***INSERTA EL NODO EN LA LISTA***
	if ((In) != NULL){
		(nn)->sgte = (In);
		(In) = (nn);
		(nn) = NULL;
	}
	else
		In = nn;
	return (In);
}
void insertar2 (struct Inf **nn, struct Inf **In){
	if ((*In) != NULL){
		(*nn)->sgte = (*In);
		}
		(*In) = (*nn);
		(*nn) = NULL;
}

struct Inf* insertar3 (struct Inf *ii, struct Inf *l){  // recursiva que ordena de menor a mayor
	if (l!= NULL){
		l->sgte = insertar (ii, l->sgte);
	}
	else 
		l=ii;
	return (l);	
	}
	
void borrarlista (struct Inf *In){ //***BORRA LA LISTA***
	struct Inf *aux;
	while ((In)!= NULL){
		aux=(In);
		(In)=(In)->sgte;
		free (aux);	
	}
}
void recorrerygrabar (struct Inf *i){  //***RECORRE LA LISTA CARGADA Y LO VA GUARDANDO AL ARCHIVO***
	struct Inf archivoinf; 
	FILE *puntinf=NULL;					 		
	while (i != NULL){		
		if ((puntinf=fopen("INFRACCIONES.b","a+b"))!=NULL){
			archivoinf.numActa = i->numActa;
			archivoinf.fecha = i->fecha;
			archivoinf.h = i->h;
			strcpy (archivoinf.patente, i->patente);
			strcpy (archivoinf.marca, i->marca);
			strcpy (archivoinf.modelo, i->modelo);
			strcpy (archivoinf.tipoVehiculo, i->tipoVehiculo);
			strcpy (archivoinf.tipoInfraccion, i->tipoInfraccion);
			strcpy (archivoinf.observacion, i->observacion);
			strcpy (archivoinf.nombreAgente, i->nombreAgente);
			archivoinf.legajoAgente = i->legajoAgente;
			fwrite(&archivoinf,sizeof(archivoinf),1,puntinf);	//En este punto guarda lo que copio de la lista en un archivo.
			printf ("\nGuardo exitosamente\n\n");
			fclose(puntinf);
			(i) = (i)->sgte;
		}
		else 
			printf ("No se abrio el archivo");
	}
}

void Consultar (){
	struct arbol *arb=NULL, *aux=NULL;
	struct Inf *PL=NULL;
	int num= 1, band=0, band2=0;
	struct Fecha fecha1, fecha2;
	while (num != 0){
		printf ("Ingrese 1 para realizar una consulta e ingrese 0 para  salir menu consulta\n");
		scanf ("%d", &num);
		if (num != 0){
			PL = recorrerysubir(PL);
			Buscarmedio (PL, &aux); 			//ACA MANDO A LA FUNCION QUE LEE LA LISTA Y ARMA EL ARBOL.
			printf ("Debera ingresar 2 fechas para conocer la lista de los infraccionados./n");
			printf ("\nIngrese la fecha en tres etapas, primero el dia, luego mes y por ultimo el anio\n");
			while (band2==0){
				while (band==0){
					printf("Ingrese el dia\n");	
					getchar();
					scanf ("%d",&fecha1.dia);
					printf("Ingrese el mes\n");
					fflush(stdin);
					scanf ("%d",&fecha1.mes);
					printf("Ingrese el anio\n");
					fflush(stdin);
					scanf ("%d",&fecha1.anio);
					if (fecha1.dia>=1 && fecha1.dia<=31 && fecha1.mes>=1 && fecha1.mes<=12 && fecha1.anio>=1990 && fecha1.anio<=2050){
						band=1;
					}
					else{
						printf ("Fecha fuera de parametro, intente nuevamente\n\n");
					}				
				}
				band=0;				
				printf("Ingres la 2da fecha\n\n");
				while (band==0){
					fflush(stdin);			
					printf("Ingrese el dia\n");	
					fflush(stdin);
					scanf ("%d",&fecha2.dia);
					printf("Ingrese el mes\n");
					fflush(stdin);
					scanf ("%d",&fecha2.mes);
					printf("Ingrese el anio entre 1990 y 2050\n");
					fflush(stdin);
					scanf ("%d",&fecha2.anio);
					fflush(stdin);
					if (fecha2.dia>=1 && fecha2.dia<=31 && fecha2.mes>=1 && fecha2.mes<=12 && fecha2.anio>=1990 && fecha2.anio<=2050){
							band=1;
						}
						else{
						printf ("Fecha fuera de parametro, intente nuevamente\n\n");
					}
				}
				if (fecha1.dia <= fecha2.dia && fecha1.mes <= fecha2.mes && fecha1.anio <= fecha2.anio){
				band2=1;	
				}
				else {
					printf ("La 1er fecha debe ser menor a las 2da fecha, vuelva a ingresar ambas fechas.\n\n");
					band=0;
				}
			}
			printf ("\n=====LISTA DE INFRACTORES ENTRE LAS FECHAS INGRESADAS=====\n");
			arbolinfractores (fecha1, fecha2, aux);  //***ENVIA LAS FECHAS PARA CONSULTAR LISTA INFRACTORES***
			printf("\n");
			if (bandinf==0){
			printf ("No existen vehiculos infraccionados en ese rango de fechas\n");
			printf("\n");
			}
		}
		else 
			printf ("Usted selecciono salir del menu consulta, presione 0\n");
		}
	borrarlista (PL);
	borrararbol (arb); 
}

	
struct Inf * recorrerysubir (struct Inf *pl){  	 // *** FUNCION ABRE Y RECORRE EL ARCHIVO Y LO PASA A LISTA ***
	struct Inf archivo, *y;
	FILE *puntero = NULL;
	if ((puntero=fopen("INFRACCIONES.b","r+b"))!=NULL){
		fread (&archivo, sizeof (archivo), 1, puntero);
		while (!feof (puntero)){
			y= (struct Inf *) malloc (sizeof (struct Inf));	
			if(y!= NULL){
			 	y->numActa = archivo.numActa;
				y->fecha= archivo.fecha;
				y->h = archivo.h;				
				strcpy (y->patente, archivo.patente);
				strcpy (y->marca, archivo.marca);
				strcpy (y->modelo, archivo.modelo);
				strcpy (y->tipoVehiculo, archivo.tipoVehiculo);
				strcpy (y->tipoInfraccion, archivo.tipoInfraccion);
				strcpy (y->observacion, archivo.observacion);
				strcpy (y->nombreAgente, archivo.nombreAgente);
				y->legajoAgente = archivo.legajoAgente;	
				y->sgte=NULL;
				pl = insertar (y, pl);
			}
			else
				printf ("No tiene espacio");
		fread (&archivo, sizeof (archivo), 1, puntero);			
		}
	fclose (puntero);	
	}
	else
		printf ("El archivo INFRACCIONES no abre");	
	return (pl);
}
	
void contNroacta (long *acta){ 						//***PARA ASIGNAR UN NRO DE ACTA DE INFRACCION DE MANERA CORRELATIVA***	
	struct contadoractainf conta;
	FILE  *puntero;
	int i=-1;
	if((puntero=fopen("NROACTAINF.b","r+b"))!=NULL){
		fread(&conta,sizeof(conta),1,puntero); 				
		conta.nroActa++; 								
		*acta= conta.nroActa;
		fseek(puntero,sizeof(conta)*i,SEEK_CUR); 
		fwrite(&conta,sizeof(conta),1,puntero);
		fclose(puntero);
	}
	else
		printf("Error de apertura de archivo \n");
}	

void Buscarmedio (struct Inf *pl, struct arbol **aa){ 				//***LEE LA LISTA, GUARDA LA MITAD, Y ENVIA PARA CREAR EL  ARBOL***
	struct arbol *arb = NULL, *aux2=NULL, *aux;
	struct Inf *aux1 = NULL;
	int contador = 0, band=0;
	int mitad=0;
	(aux1) = (pl);
	while (aux1 != NULL){ 				//RECORRE LA LISTA Y PASA A UN AUX ARBOL LOS DATOS.
		contador= contador+1; 
		aux1 = aux1->sgte;	
	}		
	
	if ((contador/2)% 2==0){
		mitad=(contador/2);
	
	}
	else{
		mitad=((contador/2)+(0.5));
	}
	(aux1) = (pl); 
	while ( pl != NULL){ 
		if (pl->numActa == mitad){
			aux = (struct arbol *) malloc (sizeof (struct arbol));
         		if(aux != NULL){
					aux->numActa = (pl)->numActa;
					aux->fecha= (pl)->fecha;
					aux->h= (pl)->h;
					strcpy (aux->patente,(pl)->patente);
					strcpy (aux->marca, (pl)->marca);
					strcpy (aux->modelo, (pl)->modelo);
					strcpy (aux->tipoVehiculo, (pl)->tipoVehiculo);
					strcpy (aux->tipoInfraccion, (pl)->tipoInfraccion);
					strcpy (aux->observacion, (pl)->observacion);
					strcpy (aux->nombreAgente, (pl)->nombreAgente);
					aux->legajoAgente = (pl)->legajoAgente;
					aux->derecha = NULL;
					aux->izquierda = NULL;	
				}
		}
		pl = (pl)->sgte;
	}     
	(arb)= (aux);
	(pl)= (aux1);
	while ( pl != NULL){
	aux = (struct arbol *) malloc (sizeof (struct arbol));
         		if(aux != NULL){
         				aux->numActa = (pl)->numActa;
						aux->fecha = (pl)->fecha;
						aux->h= (pl)->h;
						strcpy (aux->patente,(pl)->patente);
						strcpy (aux->marca, (pl)->marca);
						strcpy (aux->modelo, (pl)->modelo);
						strcpy (aux->tipoVehiculo, (pl)->tipoVehiculo);
						strcpy (aux->tipoInfraccion, (pl)->tipoInfraccion);
						strcpy (aux->observacion, (pl)->observacion);
						strcpy (aux->nombreAgente, (pl)->nombreAgente);
						aux->legajoAgente = (pl)->legajoAgente;
						aux->derecha = NULL;
						aux->izquierda = NULL;
						arb = insertararb (aux, arb);
						pl = pl->sgte;
					}
					else
					printf ("nodo sin espacio\n");
			}
	aux2 = arb;	
	(*aa) = arb;
	printf ("=====LISTA DE INFRACTORES DE LA BASE DE DATOS=====\n");	
	recorrerIRD(aux2);
	printf ("==================================================\n");
}	
		     			
void recorrerIRD (struct arbol *a){
     if(a != NULL) {
             recorrerIRD(a->izquierda);
             printf("Fecha infraccion: %d/%d/%d - Patente: %s\n", a->fecha.dia, a->fecha.mes, a->fecha.anio, a->patente);
			 recorrerIRD(a->derecha);
     }
}
struct arbol *insertararb (struct arbol *auxx, struct arbol *ar){
	if( ar!= NULL){
		    if( auxx->numActa == ar->numActa){
             }  
			 else {
                    if(auxx->numActa > ar->numActa) {
                       (ar)->izquierda = insertararb (auxx, ar->izquierda);
					} else {
						ar->derecha = insertararb (auxx, ar->derecha);
                    }
             }
    } else {
               ar= auxx;
    }
       return (ar);
}
		

void borrararbol (struct arbol *arbolcortar){ //***FUNCION BORRAR ARBOL (RECORRE Y ELIMINA LOS NODOS)***
	if (arbolcortar != NULL){
		borrararbol(arbolcortar->izquierda);
		free (arbolcortar);
		borrararbol(arbolcortar->derecha);
}
}

void arbolinfractores (struct Fecha F1, struct Fecha F2, struct arbol *pa){ //***RECORRE EL ARBOL ENTRE LAS FECHAS
	//printf ("Entro a arbolinfractores, el valor de bandinf: %d", bandinf);
	if ( pa != NULL){
	arbolinfractores (F1, F2, pa->izquierda);
		if (pa !=NULL) {
		if ( pa->fecha.dia >= F1.dia && pa->fecha.mes >= F1.mes && pa->fecha.anio >= F1.anio && pa->fecha.dia <= F2.dia && pa->fecha.mes <= F2.mes && pa->fecha.anio <= F2.anio){
			printf("Fecha infraccion: %d/%d/%d - Patente: %s\n", pa->fecha.dia, pa->fecha.mes, pa->fecha.anio, pa->patente);
		bandinf=1;			
		}
		else {

		}
		arbolinfractores (F1, F2, pa->derecha);
		}
	}
}

