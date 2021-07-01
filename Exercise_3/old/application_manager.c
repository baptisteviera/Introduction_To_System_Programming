/*
 * =====================================================================================
 *
 *       Filename:  ApplicationManager.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  17/12/2020 18:10:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonathan Legrand 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  wait_process
 *  Description:  
 * =====================================================================================
 */
    void
wait_process ( char* process_name, pid_t pid )
{
    int status;
    waitpid(pid,&status,0);
    if(WIFEXITED(status)){
        printf("Terminaison normale de %s avec le code %d\n",process_name,WEXITSTATUS(status));
    } 
    if(WIFSIGNALED(status)){
        printf("Le processus %s a été terminé par le signal %d\n",process_name,WTERMSIG(status));
    }


}		/* -----  end of function process_result  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  launch_application
 *  Description:  
 * =====================================================================================
 */
    void
launch_application ( char *path, char **arg )
{
    if(execv(path,arg)== -1){
        perror("execv");
            exit(EXIT_FAILURE);
    }
}		/* -----  end of function launch_network_manager  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  case_get_time
 *  Description:  
 * =====================================================================================
 */
    void
case_get_time (pid_t get_time_id)
{
    int *pid_son;
    char *arg_get_time[] = {"get_time", NULL};
    switch(get_time_id){
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;

        case 0:
            *pid_son = getpid();
            printf("pid get_time = %d\n",*pid_son);
            launch_application("./bin/get_time",arg_get_time);

            break;

        default:
            wait_process("get_time",*pid_son);
            break;
    }

}		/* -----  end of function case_get_time  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  case_network_manager
 *  Description:  
 * =====================================================================================
 */
    void
case_network_manager (pid_t network_manager_id)
{
    int *pid_son;
    int pid;
    int fd[2];
    pipe(fd);
    char *arg_network_manager[] = {"network_manager", NULL};
    switch(network_manager_id){
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
            break;

        case 0:
            *pid_son = getpid();
            close(fd[READ]);
            if ((write(fd[WRITE],pid_son,sizeof(pid_son))) == -1){
                fprintf(stderr,"Erreur lors de l'écriture dans le pipe\n");
            }
            close(fd[WRITE]);
            printf("pid network_manager = %d\n",*pid_son);
            launch_application("./bin/network_manager",arg_network_manager);

            break;

        default:
            
            close(fd[WRITE]);
            read(fd[READ],&pid,sizeof(pid_son));
            printf("Reçu par le pipe : %d\n",pid);
            wait_process("network_manager",*pid_son);
            break;
    }

}		/* -----  end of function case_network_id  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  application manager
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )

{


    pid_t network_manager_id = -1;
    pid_t get_time_id = fork();
    if (get_time_id != 0){
        network_manager_id = fork();
        case_network_manager(network_manager_id);
    }
#if 0
    /*On s'assure que le processus qui rentre dans case_network_manager
     * est soit le père, soit le processus network_manager*/
    if(network_manager_id != -1 || get_time_id != 0 ){
        printf("pid avant le case network %d\n",getpid());
        case_network_manager(network_manager_id);
        return EXIT_SUCCESS;
    } 
#endif
    case_get_time(get_time_id);


    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */

