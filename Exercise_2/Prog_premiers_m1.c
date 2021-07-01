#include<unistd.h>

#include<stdio.h>

#include<stdlib.h>

#include<sys/wait.h>

#include<string.h>




int premier(int nb) {
    int r = 0;
    for (int i = 1; i <= nb; i++) {
        if (nb % i == 0) r++;
    }
    if (r > 2) return 0; 
    else return 1; // on a seulement 1 et nb comme diviseur donc premier
}

void explorer(int debut, int fin) {
    int etat, pid, pid2;
    pid = fork(); // processus qui exécute la boucle for

    if (pid == 0) { // on est dans le fils

        for (int i = debut; i <= fin; i++) {

            if (premier(i) == 1) { // si l'indice est premier
                
                pid2 = fork(); // creer fils pere
                
                if (pid2 == 0) { // on rentre dans le fils
                    
                    char chaine[500];
                    sprintf(chaine, "echo '%d  est un nombre premier écrit par le processus %d qui a créé le processus sytem et qui a pour parent le processus %d. Le pid du processus qui a écrit le message sur le terminal est '$$>>nbr_premiers.txt", i, getpid(),getppid());
                    // echo $$ affiche le processus du termianl
                    // sprintf stocke la chaîne formatée en mémoire dans un buffer pré-alloué nommée chaine.
                    // echo associé au >> (redirection) va permettre d'ajouter à la fin du fichier nbr_premier.txt la chaine de caractères entre single quote au lieu de l'afficher sur l'écran.
                    system(chaine); // renvoie 0 si tout s'est bien passé, exécute la commande "chaine"
                    // c'est cette instruction qui va permettre l'écriture dans le fichier
                    //printf("\n\nici le fils créateur du processus system, mon pid est %d et le pid de mon pere est %d\n\n", getpid(), getppid()); 

                    sleep(2); // permet d'aller dans le père (l'instruction wait dans le père sera ainsi exécutée qui va entrainer un retour dans le fils)
                    exit(0); // terminaison normale du fils
                } 
                else { // on rentre dans le pere
                    wait(&etat); // on attent le fils
                    // wait enregistre les informations sur l'état/le statut du fils dans l'entier "etat".
                    // instruction 41
                }
            }
        }

        exit(0); // terminaison normale du fils

    } 
    else {
        wait(&etat); // on attent le fils
        // wait enregistre les informations sur l'état/le statut du fils dans l'entier "etat".
        // instruction 46
    } 
}
int main() {
    int grp = 1;
    while (grp <= 11) {
        explorer(grp + 1, grp + 10);
        grp = grp + 10;
    }
}