#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <thread>
#include <vector>

#include "LEDPlayer.h"
#include "OFPlayer.h"
#include "player.h"
#include "utils.h"
#include "StateMachine.h"
#include "FSM_Common.h"

#define MAXLEN 100

//enum CMD { C_PLAY, C_PAUSE, C_STOP, C_RESUME };
extern const std::string cmds[10];
extern std::thread led_loop, of_loop;
extern Player player;
extern LEDPlayer led_player;
extern OFPlayer of_player;
extern int dancer_fd;
extern string path;
extern const char *rd_fifo;
extern const char *wr_fifo;


int main(int argc, char *argv[]){
    // create player_to_cmd
    if (mkfifo(wr_fifo, 0666) == -1) {
        if (errno != EEXIST) {
            fprintf(stderr, "[LOOP] Cannot create %s\n", wr_fifo);
        } else {
            fprintf(stderr, "[LOOP] %s already exists\n", wr_fifo);
        }
    } else
        fprintf(stderr, "[LOOP] %s created\n", wr_fifo);
    int rd_fd, n;
    if (mkfifo(rd_fifo, 0666) == -1) {
        if (errno != EEXIST) {
            fprintf(stderr, "[LOOP] Cannot create %s\n", rd_fifo);
        } else {
            fprintf(stderr, "[LOOP] %s already exists\n", rd_fifo);
        }
    } else
        fprintf(stderr, "[LOOP] %s created\n", rd_fifo);
    rd_fd = open(rd_fifo, O_RDONLY | O_NONBLOCK);
    if (rd_fd == -1) perror("open");
    char cmd_buf[MAXLEN];

    StateMachine* playingState=new StateMachine();

    while (1) {
        //read and parse command       
        n = read(rd_fd, cmd_buf, MAXLEN);
        std::string cmd_str = cmd_buf;
        if (n > 0) {
            fprintf(stderr,"[LOOP] parsing command\n");
	    int cmd = parse_command(playingState,cmd_buf);
            fprintf(stderr, "[LOOP] cmd_buf: %s, cmd: %d\n", cmd_buf, cmd);
            playingState->transition(cmd);         
        }
        else{
           playingState->stating(playingState->getCurrentState());      //as no cmd, keep stating
        }
    }
    close(rd_fd);
    return 0;
}
