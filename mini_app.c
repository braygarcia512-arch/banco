#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct usuario
{
    char nombre[20];
    char apellido_paterno[20];
    char apellido_materno[20];
    int dia;
    int mes;
    int anio;
    char curp[25];
    char contrasena[21];
    int saldo;
}usuario;



int u;
int op;
int inicio;
char ID[30];
char llave[21];
int deposito_inicial;

void crear_cuenta(struct usuario e[], int n)
{
    printf("\nCual es tu nombre\n");
    scanf("%s", e[n].nombre);
    printf("\nCual es apellido paterno\n");
    scanf("%s", e[n].apellido_paterno);
    printf("\nCual es tu apellido materno\n");
    scanf("%s", e[n].apellido_materno);
    printf("\nDia de nacimiento(Con dos digitos. Ejem: 03)\n");
    scanf("%d", &e[n].dia);
    printf("\nMes de nacimiento(Con dos digitos. Ejem: 03)\n");
    scanf("%d", &e[n].mes);
    printf("\nAño de nacimiento\n");
    scanf("%d", &e[n].anio);
    printf("\nIngresa una contraseña(maximo 20 digitos o letras) \n");
    scanf("%s", e[n].contrasena);

    
}

char obtener_vocal(char palabra[])
{
    for(int i = 1; i < strlen(palabra); i++)
    {
        char letra = tolower(palabra[i]);

        if(letra == 'a' ||
           letra == 'e' ||
           letra == 'i' ||
           letra == 'o' ||
           letra == 'u')
        {
            return toupper(letra);
        }
    }

    return 'X';
}

void crear_curp(struct usuario e[], int n)
{

    sprintf(
        e[n].curp,
        "%c%c%c%c%02d%02d%02d",

        toupper(e[n].apellido_paterno[0]),

        obtener_vocal(e[n].apellido_paterno),

        toupper(e[n].apellido_materno[0]),

        toupper(e[n].nombre[0]),

        e[n].anio % 100,
        e[n].mes,
        e[n].dia
    );

}

void iniciar_sesion(struct usuario e[], int n)
{
    
    
    printf("\nMete tu usuario generado\n");
    scanf("%s", ID);
    printf("\nMete tu contraseña\n");
    scanf("%s", llave);

    int i = 0;

    FILE * ar = fopen(ID,"r");

    if (ar == NULL)
    {
        printf("\nError al solicitar la informacion de tu cuenta");
    }
    
    while (fscanf(ar,
                "%19s %19s %19s %d %d %d %24s %20s %d",
                e[i].nombre,
                e[i].apellido_paterno,
                e[i].apellido_materno,
                e[i].dia,
                e[i].mes,
                e[i].anio,
                e[i].curp,
                e[i].contrasena,
                e[i].saldo) == 8)
    {
        i++;
    }



    if (strcmp(e[n].curp,ID) && strcmp(e[n].contrasena,llave) == 0)
    {
        printf("acceso concedido");
    }
    else
    {
    printf("Acceso denegado");
    }    
}

void depositar()
{

    printf("Cuanto quieres depositarte?");
    scanf("%d", &deposito_inicial);

}




int main()
{

    usuario e[10];

    printf("\nbienvenido a tu aplicacion de vacaciones");
    printf("\nQue desea hacer?");
    printf("\n1.- Crear cuenta");
    printf("\n2.- Iniciar sesion\n");
    scanf("%d", &inicio);
    
    if (inicio == 1)
    {
        crear_cuenta(e,u);
        crear_curp(e,u);
        
        FILE * ar = fopen(e[u].curp,"a");
        
        if (ar == NULL)
        {
            perror("\nHubo un error de creacion de usuario");
        }

        fprintf(ar, "%s %s %s\n" "%d %d %d\n" "%s\n" "%s\n" "%d\n",
            e[u].nombre,
            e[u].apellido_paterno,
            e[u].apellido_materno,
            e[u].dia,
            e[u].mes,
            e[u].anio,
            e[u].curp,
            e[u].contrasena,
            e[u].saldo);

        fclose(ar);
        printf("\ncreacion de cuenta exitosa");

            

    }
    else if (inicio == 2)
    {
        iniciar_sesion(e,u);


        printf("\n¿Que deseas hacer?");
        printf("\n1.- Checar saldo");
        printf("\n2.- Retirar saldo");
        printf("\n3.- Hacer transferencia");
        printf("\n4.- Depositar");
        printf("\n5.- Checar tu informacion personal\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:

            printf("este es tu saldo");    

            break;
        
        case 2:
            
            printf("¿Cuanto deseas retirar");    

            break;
        
        case 3:

            printf("¿A quien deseas tranferir");

            break;

        case 4:

            printf("¿Cuanto quieres depositar");

            break;

        case 5:

            printf("Aqui esta tu informacion personal");
            printf("\nnombre: %s", e[u].nombre);
            printf("\napellido paterno: %s", e[u].apellido_paterno);
            printf("\napellido materno: %s", e[u].apellido_materno);
            printf("\ndia de nacimiento: %d", e[u].dia);
            printf("\nmes de nacimiento: %d", e[u].mes);
            printf("\naño de nacimiento: %d", e[u].anio);
            printf("\ncontraseña: %s", e[u].contrasena);
            printf("\nID: %s", e[u].curp);

            break;

        default:
            break;
        }

    }
    else
    {
        printf("\ntu opcion no es valida");
    }
    



    printf("\n"); system("pause");
    return 0;
}