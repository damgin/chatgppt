#pragma once
#include "global.h"

int initSocket(int port) {

 int server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    // Si la création échoue je ferme mon programme
    if(server_fd == -1) return EXIT_FAILURE;

    /**
    * BIND
    * Je relie le socket à un port et une ip avec la fonction bind()
    */
    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(port)
    };
    int error = bind(server_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("bind");
    if(error == -1) { close(server_fd); return EXIT_FAILURE; }

    /**
     * LISTEN obligatoire pr le serveur
     */
    error = listen(server_fd,BUFSIZ);perror("listen");
    if(error == -1) { close(server_fd); return EXIT_FAILURE; }

    printf("Server listen on port : %d\n",port);

    return server_fd;
}

void create_salon( int client_id, char* salon_name) {
  // Bloquer l'accès aux salons avce mutex :
  // mutex(wip)

    // Vérifier si le nombre de salons est atteint
    if (salon_count >= MAX_SALONS) {
        char* error_msg = "❌ Erreur : Trop de salons existants. Impossible d'en créer un nouveau.\n";
        send(clients_fd[client_id].fd, error_msg, strlen(error_msg), 0);
        ///fermer le mutex ici !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        return;
    }

    // Créer un nouveau salon
    salons[salon_count].id = salon_count + 1;  // Identifiant unique du salon
    strncpy(salons[salon_count].name, salon_name, sizeof(salons[salon_count].name) - 1);
    //salons[salon_count].clients[0] = client_id;  // Ajouter le créateur au salon
    salons[salon_count].client_count = 1;

    // Mettre à jour le salon actuel du client
    clients_fd[client_id].salon = salons[salon_count].id;

    // Préparer le message de confirmation
    char success_msg[555];
    snprintf(success_msg, sizeof(success_msg), "✅ Salon '%s' créé avec succès ! (ID: %d)\n",salon_name, salons[salon_count].id);

    // Envoyer le message de confirmation au créateur du salon
    send(clients_fd[client_id].fd, success_msg, strlen(success_msg), 0);

    // Notifier les autres clients qu'un nouveau salon est disponible
    char broadcast_msg[555];
    snprintf(broadcast_msg, sizeof(broadcast_msg), "📢 Nouveau salon disponible : '%s' (ID: %d)\n",salon_name, salons[salon_count].id);

    for (int i = 0; i < MAX_CLIENTS; i++) {
          // crée un code pour Envoyer à tous sauf au createur
            send(clients_fd[i].fd, broadcast_msg, strlen(broadcast_msg), 0);
        
    }
    ///fermer le mutex ici !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // voir quoi ajouter demain(ajourd'hui)
    salon_count++;
}

// void list_salons(int client_id) {

//     for (int i = 0; i < salon_count; i++) {
//         char buffer[555];
//         snprintf(buffer, sizeof(buffer), "Salon [%d] : %s (%d membres)\n",salons[i].id, salons[i].name, salons[i].client_count);
//         send(clients_fd[client_id].fd, buffer, strlen(buffer), 0);
//     }

// }

// void join_salon(int salon_id, int client_id) {
// ////vérifier la syntaxe plusieur fois ici
//     for (int i = 0; i < salon_count; i++) {
//         if (salons[i].id == salon_id) {
//             salons[i].clients[salons[i].client_count++] = client_id;
//             clients_fd[client_id].salon = salon_id;

//             char buffer[255];
//             snprintf(buffer, sizeof(buffer), "Vous avez rejoint le salon : %s\n", salons[i].name);
//             send(clients_fd[client_id].fd, buffer, strlen(buffer), 0);
//             ///fermer le mutex ici !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//             return;
//         }
//     }

//     char* msg = "Salon introuvable.\n";
//     send(clients_fd[client_id].fd, msg, strlen(msg), 0);
//     ///fermer le mutex ici !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// }

void broadcast_to_salon(t_salon* salons,t_infos msg) {
    printf("fonction : boadcast_to_salon\n");
    int salon_id = msg.salon;

    // je parcourt les user du salon i
    // POur chaque client contenu dans le salon : salon_id
        printf("compteur client = %d\n",compteur_client);

        // Si le client possède le meme id
        for( int i = 0; i < MAX_CLIENTS+5; i++ ){

            if(clients_fd[i].salon == msg.salon){
                printf("envoie du message '%s' au client:%s\n",msg.message,msg.name);
                send(clients_fd[i].fd ,&msg, sizeof(t_infos),0);
                
            }
        }

        ///fermer le mutex ici !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

// void handle_command(char* command, int client_id) {
//     if (strncmp(command, "create salon", 12) == 0) {
//         char salon_name[255];
//         sscanf(command + 13, "%s", salon_name);
//         create_salon(salon_name, client_id);
//     }
//     else if (strncmp(command, "list salons", 11) == 0) {
//         list_salons(client_id);
//     }
//     else if (strncmp(command, "join salon", 10) == 0) {
//         int salon_id;
//         sscanf(command + 11, "%d", &salon_id);
//         join_salon(salon_id, client_id);
//     }
//     else if (strncmp(command, "join world", 10) == 0) {
//         join_salon(1, client_id); // Salon global
//     }
//     else if (strncmp(command, "exit", 4) == 0) {
//         close(clients_fd[client_id].fd);
//     }
// }
