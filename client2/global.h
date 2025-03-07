#pragma once

#define CLIENT_PORT 2450
#define SERVER_PORT 7777

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

#include "fonctions.c"