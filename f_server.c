#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSZ 500
#define EMPTY_ID 0
#define ESTEIRA_ID 01
#define GUINDASTE_ID 02
#define PONTE_ROLANTE_ID 03
#define EMPILHADEIRA_ID 04
#define TEMPERATURA_ID 01
#define PRESSAO_ID 02
#define VELOCIDADE_ID 03
#define CORRENTE_ID 04

typedef struct sensor
{
    int id;
} sensor;

typedef struct equipment
{
    int id;
    sensor sensor_array[4];
} equipment;

// equipament esteira;
// equipament guindaste;
// equipament ponte_rolante;
// equipament empilhadeira;

// sensor temperatura;
// sensor pressao;
// sensor velocidade;
// sensor corrente;

// esteira.id = ESTEIRA_ID;
// guindaste.id = GUINDASTE_ID;
// ponte_rolante.id = PONTE_ROLANTE_ID;
// empilhadeira.id = EMPILHADEIRA_ID;
// temperatura.id = TEMPERATURA_ID;
// pressao.id = PRESSAO_ID;
// velocidade.id = VELOCIDADE_ID;
// corrente.id = CORRENTE_ID;
// for (int i = 0; i < 4; i++)
// {
//     esteira.sensor_array[i].id = 00;
//     guindaste.sensor_array[i].id = 00;
//     ponte_rolante.sensor_array[i].id = 00;
//     empilhadeira.sensor_array[i].id = 00;
// }

int verify_existing_sensors(equipment equipments[4])
{
    return 0;
}
void add_handle(char aux[BUFSZ], equipment equipments[4])
{
    char buffer[BUFSZ];
    char buf[BUFSZ];
    char sensors[BUFSZ];
    char equip[BUFSZ];

    if (verify_existing_sensors(equipments) == 0)
    {                                                                                // if the sum of sensors in each equipment is more than 15, the server returns "limit excedeed" to the client
        strcpy(buffer, strrchr(aux, 'r'));                                           // eliminate the substring "add sensor" and then copies the rest of string into buffer
        strcpy(buffer, strchr(buffer, '0'));                                         // eliminate the substring " " in the first character of buffer
        strncpy(sensors, buffer, strlen(buffer) - strlen(strrchr(buffer, 'i')) - 1); // sensors id that the client want to be added
        strcpy(equip, strrchr(buffer, '0'));                                         // equipments id that the client want to be added
        // add(sensors, equip, aux, equipments);
    }
}

// void add(char sensors[BUFSZ], char equip[BUFSZ], char aux[BUFSZ], equipment equipments[4])
// {
//     char sensor_buffer[BUFSZ];
//     char equip_buffer[BUFSZ];
//     char *ptr;
//     int sensor_id;
//     int equip_id;

//     while (strlen(sensors) <= 6 && strlen(sensors) > 0)
//     {
//         strcpy(sensor_buffer, strrchr(sensors, '0'));
//         strcpy(equip_buffer, strrchr(equip, '0'));
//         strncpy(sensors, sensors, strlen(sensors) - 2);
//         sensor_id = strtol(sensor_buffer, ptr, 10);
//         equip_id = strtol(equip_buffer, ptr, 10);
//         switch (sensor_id)
//         {
//         case 01:
//             if (equipments[equip_id].sensor_array[0].id != TEMPERATURA_ID){
//                 equipments[equip_id].sensor_array[0].id = TEMPERATURA_ID;
//                 break;
//             } else {
//                 sprintf(aux, "sensor %d already exists in %d", TEMPERATURA_ID, equip_id);
//                 return;
//             }
//         case 02:
//             if (equipments[equip_id].sensor_array[0].id != TEMPERATURA_ID)
//                 break;
//         case 03:
//             if (equipments[equip_id].sensor_array[0].id != TEMPERATURA_ID)
//                 break;
//         case 04:
//             if (equipments[equip_id].sensor_array[0].id != TEMPERATURA_ID)
//                 break;
//         default:
//             break;
//         }
//     }
// }

void handle_buffer(char buf[BUFSZ])
{
    equipment equipments[4];
    equipments[0].id = ESTEIRA_ID;
    equipments[1].id = GUINDASTE_ID;
    equipments[2].id = PONTE_ROLANTE_ID;
    equipments[3].id = EMPILHADEIRA_ID;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            equipments[i].sensor_array[j].id = EMPTY_ID;
        }
    }

    char aux[BUFSZ];
    memset(aux, 0, BUFSZ);
    strncpy(aux, buf, strlen(buf));

    if (strncmp("add", buf, 3) == 0)
    {                                // if buf has a substring "add" in its first 3 characters
        add_handle(aux, equipments); // pass a _copy_ of buf to the function
        strncpy(buf, aux, strlen(aux));
    }
    else if (strncmp("remove", buf, 6) == 0)
    { // if buf has a substring "remove" in its first 6 characters
        // remove(aux); // pass a _copy_ of buf to the function
        strncpy(buf, aux, strlen(aux));
    }
    else if (strncmp("list", buf, 4) == 0)
    { // if buf has a substring "list" in its first 3 characters
        // list(aux); // pass a _copy_ of buf to the function
        strncpy(buf, aux, strlen(aux));
    }
    else if (strncmp("read", buf, 4) == 0)
    { // if buf has a substring "read" in its first 3 characters
        // read(aux); // pass a _copy_ of buf to the function
        strncpy(buf, aux, strlen(aux));
    }
    else
    {
        memset(buf, 0, BUFSZ);
        strncpy(buf, "kill", 4); // close the communication, it will call kill function in server.c and in client.c
    }
}