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

void add(char sensors[BUFSZ], char equip[BUFSZ], char aux[BUFSZ], equipment *equipments, unsigned int n);
void _remove(char sensors[BUFSZ], char equip[BUFSZ], char aux[BUFSZ], equipment *equipments, unsigned int n);
void list(char equip[BUFSZ], char aux[BUFSZ], equipment *equipments, unsigned int n);

void handle_add(char aux[BUFSZ], equipment *equipments, unsigned int n);
void handle_remove(char aux[BUFSZ], equipment *equipments, unsigned int n);
void handle_list(char aux[BUFSZ], equipment *equipments, unsigned int n);
void handle_buffer(char buf[BUFSZ], equipment *equipment, unsigned int n);