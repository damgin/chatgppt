#pragma once

#define SERVER_PORT 7744
#define MAX_CLIENTS 1000
#define MAX_SALONS 100

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


typedef struct infos_client {
    int id;                 // Identifiant unique du client
    int destinataire;       // Pour un salon privé (0 = public)
    char name[255];         // Nom de l'utilisateur
    char message[255];      // Message envoyé
    int salon;              // ID du salon où se trouve le client
} t_infos;
// Tableau des clients connectés
t_infos clients_fd[MAX_CLIENTS];

// Structure pour un salon de discussion
typedef struct salon {
    int id;               
    char name[255];       
    int clients[MAX_CLIENTS]; 
    int client_count;
} t_salon;


// Tableaux des salons existants
t_salon salons[MAX_SALONS];

// Nombre de salons créés
int salon_count = 1;


// vérifie a chaque passage qu'ill ne manque rien

//céréalisation
#include "fonctions.c"
