
//ESTRUCTURAS DE SEM
struct Fecha{
	int dia;
	int mes;
	int anio;
};

struct hora{
	int hora;
	int min;
};
struct Movimientos{
	char Nrocuenta[11];
	struct Fecha fech;
	long int fecha;
	int NroControl;
	char patente[10];
	float saldoprev;
	int estado;
	struct hora tempini;
	struct hora tempfin;
	long int hraini;
	long int hrafinal;
	float monto;
	struct Movimientos *sgte;
};
struct ArchMovimientos{
	char Nrocuenta[11];
	struct Fecha fech;
	long int fecha;
	int NroControl;
	int estado;
	char patente[10];
	float saldoprev;
	struct hora tempini;
	struct hora tempfin;
	long int hraini;
	long int hrafinal;
	float monto;
	
};
struct recargas{
	long nroControl;
	char nroCuenta[11];
	float monto;
	float saldoPrevio;
	struct Fecha fecha;
	struct hora horarc;
	struct recargas *sgte;
};
struct archirec{
	long nroControl;
	char nroCuenta[11];
	float monto;
	float saldoPrevio;
	struct Fecha fecha;
	struct hora horarc;
};
struct usuarios{
	char nroCuenta[11];	
	char patente[10];
	float saldo;
	struct Movimientos *MovHistoricos;
	struct recargas *recUsu;
	struct usuarios *sgte;
};
struct archiusu{
	char nroCuenta[11];
	char patente[10];
	float saldo;
};
struct contadorcontrol{
	long nroControl;
};

struct Inf {
	long	numActa;
	struct  Fecha fecha;
	struct	hora h;
	char 	patente [7];
	char    marca [10];
	char	modelo [10];
	char 	tipoVehiculo [10];
	char	tipoInfraccion [20];	
	char	observacion [100];
	char	nombreAgente [20];
	long  	legajoAgente;
	struct Inf *sgte;	
};

struct arbol {
	long	numActa;
	struct  Fecha fecha;
	struct	hora h;
	char 	patente [7];
	char    marca [10];
	char	modelo [10];
	char 	tipoVehiculo [10];
	char	tipoInfraccion [20];	
	char	observacion [100];
	char	nombreAgente [20];
	long  	legajoAgente;
	struct arbol *derecha; 
	struct arbol *izquierda;
};

struct contadoractainf{
	long nroActa;
};
