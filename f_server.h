#pragma once

#include <stdlib.h>

#define BUFSZ 500 // buffer length 
typedef struct sensor
{
    int id;
} sensor;

typedef struct equipment
{
    int id;
    sensor sensor_array[4];
} equipment;

void add(char sensors[BUFSZ], char equip[BUFSZ], char aux[BUFSZ], equipment equipments[4]);

void handle_add(char buf[BUFSZ]);
void handle_buffer(char buf[BUFSZ], equipment *equipment, unsigned int n);