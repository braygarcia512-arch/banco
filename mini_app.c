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

int op;
int inicio;
char ID[30];
char llave[21];

void actualizar_usuario(usuario e[], int n)
{
    FILE *ar = fopen(e[n].curp, "w");

    if(ar == NULL)
    {
        printf("Error al guardar usuario\n");
        return;
    }

    fprintf(ar,"%s %s %s\n""%d %d %d\n""%s\n""%s\n""%d\n",
            e[n].nombre,
            e[n].apellido_paterno,
            e[n].apellido_materno,
            e[n].dia,
            e[n].mes,
            e[n].anio,
            e[n].curp,
            e[n].contrasena,
            e[n].saldo);
        fclose(ar);
}

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
    e[n].saldo = 0;

    
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
    printf("\nMete tu clave\n");
    scanf("%s", llave);

    int i = 0;

    FILE * ar = fopen(ID,"r");

    if (ar == NULL)
    {
        printf("\nError al solicitar la informacion de tu cuenta");
        return;
    }
    
    while (fscanf(ar,
                "%19s %19s %19s %d %d %d %24s %20s %d",
                e[i].nombre,
                e[i].apellido_paterno,
                e[i].apellido_materno,
                &e[i].dia,
                &e[i].mes,
                &e[i].anio,
                e[i].curp,
                e[i].contrasena,
                &e[i].saldo) == 9)
    {
        i++;
        fclose(ar);
    }



    if (strcmp(e[0].curp,ID) == 0 && strcmp(e[0].contrasena,llave) == 0)
    {
        printf("acceso concedido");
    }
    else
    {
        printf("Acceso denegado");
        return;
    }    
}

void depositar(struct usuario e[], int n)
{
    int deposito;

    printf("Cuanto quieres depositarte?: ");
    scanf("%d", &deposito);

    e[n].saldo += deposito;

    actualizar_usuario(e,n);

    printf("\nDeposito hecho con exito");
    printf("\ntu saldo actual es de %d pesos",e[n].saldo);
    
}

void retirar(struct usuario e[],int n)
{
    int retiro;

    printf("\nCuanto deseas retirar: ");
    scanf("%d", &retiro);

    if (retiro > e[n].saldo)
    {
        printf("\nTienes menos dinero y no puedes retirar lo solicitado");
        return;
    }
    
    e[n].saldo -= retiro;

    actualizar_usuario(e,n);

    printf("\nTu saldo actual es de %d pesos", e[n].saldo);

}

void deposito(struct usuario e[],int n)
{
    char depositante[20];
    int deposito;
    int i = 1;

    printf("\nA quien le quieres depositar?");
    scanf("%s", depositante);

    FILE * er = fopen(depositante,"r+");

    if (er == NULL)
    {
        printf("A la persona que le quieres depositar no existe en el sistema");
        return;
    }

    fscanf(er,
                "%19s %19s %19s %d %d %d %24s %20s %d",
                e[i].nombre,
                e[i].apellido_paterno,
                e[i].apellido_materno,
                &e[i].dia,
                &e[i].mes,
                &e[i].anio,
                e[i].curp,
                e[i].contrasena,
                &e[i].saldo);


    fclose(er);

    printf("\nCuando deseas depositar");
    scanf("%d", &deposito);

    if (deposito > e[n].saldo)
    {
        printf("\nNo tienes suficiente dinero para hacer el deposito");
        return;
    }
    
    e[1].saldo += deposito;
    e[n].saldo -= deposito;

    actualizar_usuario(e,1);
    actualizar_usuario(e,0);

    printf("\nTu deposito fue exitoso");

}


int main()
{

    usuario e[10];

    printf("\nbienvenido a tu aplicacion de banco");
    printf("\nQue desea hacer?");
    printf("\n1.- Crear cuenta");
    printf("\n2.- Iniciar sesion\n");
    scanf("%d", &inicio);
    
    if (inicio == 1)
    {
        crear_cuenta(e,0);
        crear_curp(e,0);
        
        FILE * ar = fopen(e[0].curp,"a");
        
        if (ar == NULL)
        {
            perror("\nHubo un error de creacion de usuario");
            return 0;
        }

        fprintf(ar,"%s %s %s\n""%d %d %d\n""%s\n""%s\n""%d\n",
        e[0].nombre,
        e[0].apellido_paterno,
        e[0].apellido_materno,
        e[0].dia,
        e[0].mes,
        e[0].anio,
        e[0].curp,
        e[0].contrasena,
        e[0].saldo);

        fclose(ar);
        printf("\ncreacion de cuenta exitosa");

            

    }
    else if (inicio == 2)
    {
    
        iniciar_sesion(e,0);

        while (op != 6)
        {
            printf("\n*********************************************************");
            printf("\n¿Que deseas hacer?");
            printf("\n1.- Checar saldo");
            printf("\n2.- Retirar saldo");
            printf("\n3.- Hacer transferencia");
            printf("\n4.- Depositar");
            printf("\n5.- Checar tu informacion personal");
            printf("\n6.- cerrar el programa\n");
            scanf("%d", &op);

            switch (op)
            {
            case 1:

                printf("este es tu saldo");
                printf("\nSaldo %d", e[0].saldo);  

                break;
            
            case 2:
                
                retirar(e,0); 

                break;
            
            case 3:

                deposito(e,0);

                break;

            case 4:

                depositar(e,0);

                break;

            case 5:
                printf("*********************************************************");
                printf("\nAqui esta tu informacion personal");
                printf("\nnombre: %s", e[0].nombre);
                printf("\napellido paterno: %s", e[0].apellido_paterno);
                printf("\napellido materno: %s", e[0].apellido_materno);
                printf("\ndia de nacimiento: %d", e[0].dia);
                printf("\nmes de nacimiento: %d", e[0].mes);
                printf("\naño de nacimiento: %d", e[0].anio);
                printf("\ncontraseña: %s", e[0].contrasena);
                printf("\nID: %s", e[0].curp);
                printf("\n*********************************************************");

                break;

            default:
                break;
            }
            
        }
    }
    else
    {
        printf("\n tu opcion no es valida");
    }
        

    printf("\n"); system("pause");
    return 0;
}