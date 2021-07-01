#include <sys/types.h> /* Types pid_t... */ 
#include <unistd.h> /* fork()... */ 
#include <stdio.h> /* printf... */
#include <stdlib.h> /* EXIT_FAILURE... */
#include <sys/wait.h>


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  pfeuille
 *  Description: fonction qui gére les noeuds feuilles (sans fils)

 * =====================================================================================
 */
void pfeuille(int cle) {
 
    if (fork()==0) {
        printf("le processus fils %d a un pid de %d et un ppid de %d\n", cle, getpid(), getppid());
        } 
    else {
            wait(0);    
        }
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  p6
 *  Description: gestion du noeud numéro 6 qui a 2 fils (12 et 13) et gestion des descendants

 * =====================================================================================
 */
void p6() {
 
    
    for (int i=11; i<13; i++) {
        if (fork()==0) {
            printf("le processus fils %d a un pid de %d et un ppid de %d\n", i+1, getpid(), getppid());
            switch (i+1)
            {
            case 12:
                pfeuille(16); // fils unique du noeud 12
                break;
            
            default:
                break;
            }
            break;
        } else {
            /*if (i==11) {
                printf("le processus parent a un pid de %d \n", getpid());
            }*/
            wait(0);    
        }
    }
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  p2
 *  Description: gestion du noeud numéro 2 qui a 3 fils (6,7,8) et gestion des descendants

 * =====================================================================================
 */
void p2() {
 
    for (int i=5; i<8; i++) {
        if (fork()==0) {
            printf("le processus fils %d a un pid de %d et un ppid de %d\n", i+1, getpid(), getppid());
            switch (i+1)
            {
            case 6:
                p6(); // gestion des fils du noeud 6
                break;
            case 7:
                pfeuille(14); // fils unique du noeud 7
            
            default:
                break;
            }
            break; // on sort de la boucle for
        } else {
            /*if (i==5) {
                printf("le processus parent a un pid de %d \n", getpid());
            }*/
            wait(0); // on attend le retour du fils   
        }
    }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  p3
 *  Description: gestion du noeud numéro 3 qui a 2 fils (9,10) et gestion des descendants

 * =====================================================================================
 */
void p3() {
 
    
    for (int i=8; i<10; i++) {
        if (fork()==0) {
            printf("le processus fils %d a un pid de %d et un ppid de %d\n", i+1, getpid(), getppid());
            switch (i+1)
            {
            case 9:
                pfeuille(15); // fils unique du noeud 9
                break;
            
            default:
                break;
            }
            break;
            
        } else {
            /*if (i==8) {
                printf("le processus parent a un pid de %d \n", getpid());
            }*/
            wait(0);    
        }
    }
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description: gestion du noeud numéro 1 qui a 4 fils (2,3,4,5) et gestion des descendants

 * =====================================================================================
 */

int main()
{
    for (int i=1; i<5; i++) {
        if (fork()==0) {
            printf("le processus fils %d a un pid de %d et un ppid de %d\n", i+1, getpid(), getppid());
            switch (i+1)
            {
            case 2:
                p2(); // gestion des fils du noeud 2
                break;
            case 3:
                p3(); // gestion des fils du noeud 3
                break;
            case 4:
                pfeuille(11);  // fils unique du noeud 4
                break;
            default:
                break; // on sort du switch
            }

            break; // on sort de la boucle for
        } else {
            /*if (i==1) {
                printf("le processus parent a un pid de %d \n", getpid());
            }*/
            wait(0);  // on attend le retour du fils   
        }
    }
    return 0;
}





