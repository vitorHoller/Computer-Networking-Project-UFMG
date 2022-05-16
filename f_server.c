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
#define EQUIP_SIZE 4
#define SENSOR_SIZE 4
#define MAX_SENSOR 15

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

int verify_existing_sensors(equipment *equipments, unsigned int n)
{
    int x = 0;
    for (int i = 0; i < EQUIP_SIZE; i++)
    {
        for (int j = 0; j < SENSOR_SIZE; j++)
        {
            if (equipments[i].sensor_array[j].id != EMPTY_ID)
            {
                x++;
                if (x == MAX_SENSOR)
                {
                    return -1;
                }
            }
        }
    }
    return 0;
}

void add(char sensors[BUFSZ], char equip[BUFSZ], char aux[BUFSZ], equipment *equipments, unsigned int n) // equipments precisa ser passado como referencia
{
    char sensor_buffer[BUFSZ];
    memset(sensor_buffer, 0, BUFSZ);
    char equip_buffer[BUFSZ];
    memset(equip_buffer, 0, BUFSZ);
    char *ptr[BUFSZ];
    *ptr = NULL;
    char ptr_aux[BUFSZ];
    memset(ptr_aux, 0, BUFSZ);
    int sensor_id[4] = {0, 0, 0, 0};
    int equip_id;
    int index;
    int max;
    int int_aux[4] = {0, 0, 0, 0};

    switch (strlen(sensors)) // delimit how many sensors will be added
    {
    case 11: // a string "01 02 03 04" has a length of 11
        max = 3;
        break;
    case 8: // a string "01 02 03" has a length of 8
        max = 2;
        break;
    case 5: // a string "01 02" has a length of 5
        max = 1;
        break;
    case 2: // a string "014" has a length of 2
        max = 0;
        break;
    }

    while (strlen(sensors) <= 11 && strlen(sensors) > 0)
    {
        strcpy(sensor_buffer, strrchr(sensors, '0')); // copy the last two digits of sensors into sensor_buffer
        strcpy(equip_buffer, strrchr(equip, '0'));    // eliminate the substring " " in the first character of equip_buffer
        if (strlen(sensors) == 2)
        {
            strncpy(ptr_aux, sensors, strlen(sensors) - 2); // eliminate the two digits that have been already copied to sensor_buffer
            index = 0;
        }
        else
        {
            strncpy(ptr_aux, sensors, strlen(sensors) - 3); // eliminate the two digits and the backspace that have been already copied to sensor_buffer
            switch (strlen(sensors))                        // order the array position to be added in the database
            {
            case 11: // the last character, "04", of the string with lenght = 11, "01 02 03 04" will be added after "01" "02" "03"
                index = 3;
                break;
            case 8: // the last character, "03", of the string with lenght = 11, "01 02 03" will be added after "01" "02"
                index = 2;
                break;
            case 5: // the last character, "02", of the string with lenght = 11, "01 02" will be added after "01"
                index = 1;
                break;
            }
        }
        strcpy(sensors, ptr_aux); // refresh the string sensor without the characters removed in line 14 lines above
        memset(ptr_aux, 0, BUFSZ);

        sensor_id[index] = strtol(sensor_buffer, ptr, 10); // convert sensor_buffer to integer
        *ptr = NULL;
        equip_id = strtol(equip_buffer, ptr, 10); // convert equip_buffer to integer
        *ptr = NULL;
    }
    for (int i = 0; i <= max; i++)
    {
        switch (sensor_id[i])
        {
        case TEMPERATURA_ID:
            for (int i = 0, j = 0; i < EQUIP_SIZE; i++) // will run all the equipments' array
            {
                if (equipments[equip_id - 1].sensor_array[i].id == EMPTY_ID) // get the first position of equipments' array that is empty
                {
                    int_aux[j] = i; // save the first position
                    j++;
                }
                else if (equipments[equip_id - 1].sensor_array[i].id == TEMPERATURA_ID) // verify if the sensor_id alrealdy exist in the equipments' array
                {
                    sprintf(aux, "sensor 0%d already exists in 0%d", TEMPERATURA_ID, equip_id);
                    return;
                }
            }
            equipments[equip_id - 1].sensor_array[int_aux[0]].id = TEMPERATURA_ID; // save the sensor_id in the first empty position of the array
            break;

        case PRESSAO_ID:
            for (int i = 0, j = 0; i < 4; i++) // will run all the equipments' array
            {
                if (equipments[equip_id - 1].sensor_array[i].id == EMPTY_ID) // get the first position of equipments' array that is empty
                {
                    int_aux[j] = i; // save the first position
                    j++;
                }
                else if (equipments[equip_id - 1].sensor_array[i].id == PRESSAO_ID) // verify if the sensor_id alrealdy exist in the equipments' array
                {
                    sprintf(aux, "sensor 0%d already exists in 0%d", PRESSAO_ID, equip_id);
                    return;
                }
            }
            equipments[equip_id - 1].sensor_array[int_aux[0]].id = PRESSAO_ID; // save the sensor_id in the first empty position of the array
            break;

        case VELOCIDADE_ID:
            for (int i = 0, j = 0; i < 4; i++) // will run all the equipments' array
            {
                if (equipments[equip_id - 1].sensor_array[i].id == EMPTY_ID) // get the first position of equipments' array that is empty
                {
                    int_aux[j] = i; // save the first position
                    j++;
                }
                else if (equipments[equip_id - 1].sensor_array[i].id == VELOCIDADE_ID) // verify if the sensor_id alrealdy exist in the equipments' array
                {
                    sprintf(aux, "sensor 0%d already exists in 0%d", VELOCIDADE_ID, equip_id);
                    return;
                }
            }
            equipments[equip_id - 1].sensor_array[int_aux[0]].id = VELOCIDADE_ID; // save the sensor_id in the first empty position of the array
            break;

        case CORRENTE_ID:
            for (int i = 0, j = 0; i < 4; i++) // will run all the equipments' array
            {
                if (equipments[equip_id - 1].sensor_array[i].id == EMPTY_ID) // get the first position of equipments' array that is empty
                {
                    int_aux[j] = i; // save the first position
                    j++;
                }
                else if (equipments[equip_id - 1].sensor_array[i].id == CORRENTE_ID) // verify if the sensor_id alrealdy exist in the equipments' array
                {
                    sprintf(aux, "sensor 0%d already exists in 0%d", CORRENTE_ID, equip_id);
                    return;
                }
            }
            equipments[equip_id - 1].sensor_array[int_aux[0]].id = CORRENTE_ID; // save the sensor_id in the first empty position of the array
            break;

        default:
            break;
        }
    }

    memset(aux, 0, BUFSZ);

    if (max == 3) // print schema for each number of sensors added (1, 2, 3 or 4)
    {
        sprintf(aux, "sensor 0%d 0%d 0%d 0%d added", sensor_id[0], sensor_id[1], sensor_id[2], sensor_id[3]);
        return;
    }
    else if (max == 2)
    {
        sprintf(aux, "sensor 0%d 0%d 0%d added", sensor_id[0], sensor_id[1], sensor_id[2]);
        return;
    }
    else if (max == 1)
    {
        sprintf(aux, "sensor 0%d 0%d added", sensor_id[0], sensor_id[1]);
        return;
    }
    else if (max == 0)
    {
        sprintf(aux, "sensor 0%d added", sensor_id[0]);
        return;
    }
}

void _remove(char sensors[BUFSZ], char equip[BUFSZ], char aux[BUFSZ], equipment *equipments, unsigned int n)
{
    char sensor_buffer[BUFSZ];
    memset(sensor_buffer, 0, BUFSZ);
    char equip_buffer[BUFSZ];
    memset(equip_buffer, 0, BUFSZ);
    char *ptr[BUFSZ];
    *ptr = NULL;
    int sensor_id;
    int equip_id;

    strcpy(sensor_buffer, strrchr(sensors, '0')); // copy the last two digits of sensors into sensor_buffer
    strcpy(equip_buffer, strrchr(equip, '0'));    // eliminate the substring " " in the first character of equip_buffer

    sensor_id = strtol(sensor_buffer, ptr, 10); // convert sensor_buffer to integer
    *ptr = NULL;
    equip_id = strtol(equip_buffer, ptr, 10); // convert equip_buffer to integer
    *ptr = NULL;

    for (int i = 0; i < SENSOR_SIZE; i++) // run all the array and verifies if there is any sensor in the respective equipment
    {
        if (equipments[equip_id - 1].sensor_array[i].id == sensor_id) // if there is, the sensor will be removed from the database
        {
            equipments[equip_id - 1].sensor_array[i].id = EMPTY_ID;
            memset(aux, 0, BUFSZ);
            sprintf(aux, "sensor 0%d removed", sensor_id);
            return;
        }
        memset(aux, 0, BUFSZ);
        sprintf(aux, "sensor 0%d does not exist in 0%d", sensor_id, equip_id); // if there isn't, this message will appear
        return;
    }
}

void handle_add(char aux[BUFSZ], equipment *equipments, unsigned int n)
{
    char buffer[BUFSZ];
    char sensors[BUFSZ];
    char equip[BUFSZ];
    memset(buffer, 0, BUFSZ);
    memset(sensors, 0, BUFSZ);
    memset(equip, 0, BUFSZ);

    if (verify_existing_sensors(equipments, EQUIP_SIZE) == 0) // if the sum of sensors in each equipment is more than 15, the server returns "limit excedeed" to the client
    {

        strcpy(buffer, strrchr(aux, 'r'));                                           // eliminate the substring "add sensor" and then copies the rest of string into buffer
        strcpy(buffer, strchr(buffer, '0'));                                         // eliminate the substring " " in the first character of buffer
        strncpy(sensors, buffer, strlen(buffer) - strlen(strrchr(buffer, 'i') - 1)); // sensors id that the client want to add
        strcpy(equip, strrchr(buffer, '0'));                                         // equipments id that the client want to add
        add(sensors, equip, aux, equipments, EQUIP_SIZE);                            // will add the sensors in its respectives equipments
    }
    else
    {
        sprintf(aux, "limit exceeded");
    }
}

void handle_remove(char aux[BUFSZ], equipment *equipments, unsigned int n)
{
    char buffer[BUFSZ];
    char sensors[BUFSZ];
    char equip[BUFSZ];
    memset(buffer, 0, BUFSZ);
    memset(sensors, 0, BUFSZ);
    memset(equip, 0, BUFSZ);

    strcpy(buffer, strrchr(aux, 'r'));                                           // eliminate the substring "remove sensor" and then copies the rest of string into buffer
    strcpy(buffer, strchr(buffer, '0'));                                         // eliminate the substring " " in the first character of buffer
    strncpy(sensors, buffer, strlen(buffer) - strlen(strrchr(buffer, 'i') - 1)); // sensor id that the client want to remove
    strcpy(equip, strrchr(buffer, '0'));                                         // equipments id that the client want to remove
    _remove(sensors, equip, aux, equipments, EQUIP_SIZE);                        // will add the sensors in its respectives equipments
}


void handle_buffer(char buf[BUFSZ], equipment *equipments, unsigned int n)
{
    char aux[BUFSZ];
    memset(aux, 0, BUFSZ);
    strncpy(aux, buf, strlen(buf));

    if (strncmp("add", buf, 3) == 0)
    {                                            // if buf has a substring "add" in its first 3 characters
        handle_add(aux, equipments, EQUIP_SIZE); // pass a _copy_ of buf to the function
        memset(buf, 0, BUFSZ);
        strncpy(buf, aux, strlen(aux));
    }
    else if (strncmp("remove", buf, 6) == 0)
    {                                               // if buf has a substring "remove" in its first 6 characters
        handle_remove(aux, equipments, EQUIP_SIZE); // pass a _copy_ of buf to the function
        memset(buf, 0, BUFSZ);
        strncpy(buf, aux, strlen(aux));
    }
    else if (strncmp("list", buf, 4) == 0)
    {                                             // if buf has a substring "list" in its first 3 characters
       // handle_list(aux, equipments, EQUIP_SIZE); // pass a _copy_ of buf to the function
        memset(buf, 0, BUFSZ);
        strncpy(buf, aux, strlen(aux));
    }
    else if (strncmp("read", buf, 4) == 0)
    { // if buf has a substring "read" in its first 3 characters
        // read(aux); // pass a _copy_ of buf to the function
        memset(buf, 0, BUFSZ);
        strncpy(buf, aux, strlen(aux));
    }
    else
    {
        memset(buf, 0, BUFSZ);
        strncpy(buf, "kill", 4); // close the communication, it will call kill function in server.c and in client.c
    }
}