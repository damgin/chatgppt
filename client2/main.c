#include "global.h"


int main(){
    int client_fd = initSocketClient();

    // SOCKET CLIENT PRET A COMMUNIQUER !

    printf("###################### TCHAT ###################\n\n");
    printf("- list users: Lister les utilisateurs connectés\n");
    printf("- list salons: Lister les salons de discution disponible\n\n");
    printf("- join salon *salon_id* : rejoindre un salon de discussion\n");
    printf("- join user *user_id* : rejoindre un joueur dans un salon privé\n");
    printf("- join world\n\n");
    printf("- exit : Se déconnecter ou revenir en arrière\n");
    printf("################################################\n");
    




    char buf[255];memset(buf,0,255);
    char msg[255];memset(msg,0,255); // message recus depuis le serveur
    char user[255];memset(user,0,255); ///stock temporerement les noms des utilisateurs
    printf("entrée votre nom:\n");
    fgets(user,sizeof(user),stdin);
    user[strcspn(user, "\n")] = 0;
    printf("bienvenue dans le salon 'world'\n");


    while(1) {


        fgets(buf,sizeof(buf),stdin);
        int error = send(client_fd, buf, sizeof(buf), 0); perror("send");
        if(error == -1) return EXIT_FAILURE;
        
        error = recv(client_fd, msg, sizeof(msg), 0);perror("recv");
        if(error == -1) return EXIT_FAILURE;
        
        printf("%s: %s",user,msg);
        
    }




    return 0;
}
    