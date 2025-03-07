#include "global.h"


void* recv_client(void* arg){

    int client_fd = *(int*)arg;
    t_infos user;
    
    while (1) {
        ssize_t data = recv(client_fd, &user, sizeof(user), 0);
        if (data <= 0) {
            perror("recv");
            break; // Arrête le thread en cas de déconnexion
        }
        printf("%s : %s\n", user.name, user.message);
    }


}

int main(int argc, char** argv){
    int port = atoi(argv[1]);
    int port_serv = atoi(argv[2]);
    int client_fd = initSocketClient(port,port_serv);
    // SOCKET CLIENT PRET A COMMUNIQUER !

    
    char msg[255];memset(msg,0,255); // message recus depuis le serveur
    char user_name[255];memset(user_name,0,255); ///stock temporerement les noms des utilisateurs
    char buf_message[255];memset(buf_message,0,255);
    printf("entrée votre nom:\n");
    fgets(user_name,sizeof(user_name),stdin);
    user_name[strcspn(user_name, "\n")] = 0;

    t_infos user_infos;
    strcpy(user_infos.name,user_name);
    printf("bienvenue '%s'\n",user_infos.name);
 
    printf("connection au salon\n");
    pthread_t my_thread;
    pthread_create(&my_thread,NULL,recv_client,&client_fd);

    while(1) {
                                                                                                                                                                                                                                         
        fgets(user_infos.message,sizeof(user_infos.message),stdin);
        send(client_fd,&user_infos, sizeof(user_infos),0);perror("send");
        printf("msg : %s\n",user_infos.message);
        
    }




    return 0;
}
    