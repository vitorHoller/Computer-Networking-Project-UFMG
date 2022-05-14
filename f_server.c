#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFSZ 500

void handle_buffer(char buf[BUFSZ]){
    char aux[BUFSZ];
    memset(buf, 0, BUFSZ);
    strncpy(aux, buf, strlen(buf)); 
    if(strncmp("add", buf, 3)){ //if buf has a substring "add" in its first 3 characters
        add(aux); // pass a _copy_ of buf to the function
        strncpy(buf, aux, strlen(aux));

    } else if(strncmp("remove", buf, 6)){ //if buf has a substring "remove" in its first 6 characters
        remove(aux); // pass a _copy_ of buf to the function
        strncpy(buf, aux, strlen(aux));
    } 
    else if(strncmp("list", buf, 4)){ //if buf has a substring "list" in its first 3 characters
        list(aux); // pass a _copy_ of buf to the function
        strncpy(buf, aux, strlen(aux));
    } 
    else if(strncmp("read", buf, 4)){ //if buf has a substring "read" in its first 3 characters
        read(aux); // pass a _copy_ of buf to the function
        strncpy(buf, aux, strlen(aux));
    } 
    else{
        strncpy(buf, "kill", 4); // close the communication, it will call kill function in server.c and in client.c
}