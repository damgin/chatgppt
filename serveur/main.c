#include "global.h"

int client_fd[8000];
int server_fd;
int client_connecter;
char msg[255];



void* recv_client(void* arg) {
    int client_id = *(int*)arg;
    t_infos msg; /// possible problème d'attribution de struct ?? 
    printf("recv_client\n");

    while (1){

        ///// URGENCE ICI BAS
        printf("recv du client : %d\n",client_id);
        recv(clients_fd[client_id].fd, &msg, sizeof(t_infos), 0);perror("recv");
        printf("message de %s: %s\n",msg.name,msg.message);
        // if (strcmp(msg.message, "create salon") == 0) { 
        //     create_salon(clients_fd[client_id].fd, msg.message + 12);
        
        // }else{
        //     printf("client : %s dans le salon : %s.\n",msg.name, msg.salon);
        broadcast_to_salon(salons,msg);
        // }
       

    }
    close(clients_fd[client_id].fd);
    return NULL;

}

void* accept_client(void*arg){

    while (1) {

        if (compteur_client >= MAX_CLIENTS) {
            printf("Nombre maximum de clients atteint.\n");
            sleep(1); // Évite une boucle infinie trop rapide
            continue;
        }

        printf("En attente de client...\n");

        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);

        int new_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len);

        if (new_fd < 0) {
            perror("accept");
            continue;
        }

        // Trouver un emplacement libre dans le tableau
        int client_id = -1;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients_fd[i].fd == 0) { // 0 signifi emplacement libre
                client_id = i;
                break;
            }
        }
        if (client_id == -1) {
            printf("Aucun espace disponible pour le client.\n");
            close(new_fd);
            continue;
        }
        // Initialiser le client
        clients_fd[client_id].fd = new_fd;
        clients_fd[client_id].salon = 0; // Par défaut, salon public
        
        salons[0].client_count++;
        printf("salon '%s : %d utilisateurs\n",salons[0].name,salons[0].client_count);
        strcpy(clients_fd[client_id].name, "Inconnu");
        printf("Client[%d] accepté, fd = %d\n", client_id, new_fd);
        

        pthread_t thread_client;
        if (pthread_create(&thread_client, NULL, recv_client, &client_id) != 0) {
            perror("pthread_create");
            close(new_fd);
            clients_fd[client_id].fd = 0;
        
            continue;
        }
        
        compteur_client++;
    }

}


int main(int argc, char** argv){
    
    strcpy(salons[0].name,"world");
    salons[0].id = 0;
    int port = SERVER_PORT;

    if(argc > 1){
        port = atoi(argv[1]);
    }
    char user_command[255];
    server_fd = initSocket(port);
    if(server_fd == -1) return EXIT_FAILURE;

   ///apelle du thread

    pthread_t thread_client;
    pthread_create(&thread_client,NULL,accept_client,NULL); // Run thread
    pthread_join(thread_client,0);
    // Prêt à communiquer avec les client
    // ...


    // Broadcasting
  
    close(server_fd);
    return 0;
}






char command[255];
