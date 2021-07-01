
#include "my_system.h"

int my_system(char* chaine)
{
    char *argv[] = { "sh", "-c", chaine, NULL };
    pid_t pid_fils;
    int stat_fils;
    switch (pid_fils = fork())
    {
    case (pid_t)-1:
        perror("my_system/fork"); 
        return EXIT_FAILURE;  
        //break;

    case (pid_t)0:
        if (execv("/bin/sh", argv) == -1)
        {
           perror("my_system/execv");
           return(EXIT_FAILURE);
        }
        
        return EXIT_SUCCESS;  
        //break;
    
    default:
        wait(&stat_fils);
        if(WIFEXITED(stat_fils) != 0 ){ 
            printf("Fils:fin normale,code retour %d\n",WEXITSTATUS(stat_fils));
        }
        break;
    }

}