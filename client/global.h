#pragma once

#define CLIENT_PORT 2450
#define SERVER_PORT 3002

#include <dirent.h> // Pour lister les fichiers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>  // Pour manipuler les fichiers
#include <sys/stat.h> // Pour les fichiers
#include <pthread.h> // pr le multithread



typedef struct infos_client{
    int id;
    int destinataire;
    char name[255];
    char message[255];
    int salon;
    
} t_infos;

/// anciennement tab_client

t_infos clients_fd[1000];





#include "fonctions.c"