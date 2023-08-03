#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void printStatusWin(WINDOW *local_win);
void printTCBWin(WINDOW *local_win);
void printBitMapWin(WINDOW *local_win);
void printReadyLine(WINDOW *local_win);

int main(int argc, char *arv[]) {
    int startx = 0;
    int starty = 0;
    int ch;

    initscr();	
    cbreak();		    	
    keypad(stdscr, TRUE);
    noecho();
    curs_set(false);

    while(true){
        
        WINDOW *status_win = create_newwin(10, 20, 0, 0);
        WINDOW *tcb_win = create_newwin(10, 20, 0, 25);
        WINDOW *bitMap_win = create_newwin(10, 30, 0, 50);
        WINDOW *readyLine_win = create_newwin(30, 80, 10, 0);

        printStatusWin(status_win);
        printTCBWin(tcb_win);
        printBitMapWin(bitMap_win);
        printReadyLine(readyLine_win);

        sleep(1);

        delwin(status_win);
        delwin(tcb_win);
        delwin(bitMap_win);
        delwin(readyLine_win);
    }

    endwin();

    return 0;
}

void printStatusWin(WINDOW *local_win) {
    wprintw(local_win, "STATUS\n\n");

    // for(int i = 0; i < process.instructions.size(); i++){
    //     wprintw(local_win, "%s ", process.instructions[i]);

    //     if(process.pc == i)
    //         wprintw(local_win, "<----");
        
    //     wprintw(local_win, "\n");
    // }

    // TODO: substituir mock
    wprintw(local_win, "MOV AX, 10\n");
    wprintw(local_win, "MOV BX, AX <---\n");
    wprintw(local_win, "JMP\n");
    wprintw(local_win, "HTL\n");

    wrefresh(local_win);
}

void printTCBWin(WINDOW *local_win) {
    wprintw(local_win, "TCB\n\n");

    // wprintw(local_win, "PID: %d\n", process.getID());
    // for(int i = 0; i < process.registerList.size(); i++)
    //     wprintw(local_win, "REG %s:\n", process.registerList[i]);          
    // wprintw(local_win, "PC: &d\n", tcb.pc) 
    // wprintw(local_win, "........\n");    

    // TODO: substituir mock
    wprintw(local_win, "PID: 3\n");
    wprintw(local_win, "REG AX:\n");
    wprintw(local_win, "REG BX:\n");
    wprintw(local_win, "PC: 1\n");
    wprintw(local_win, "........\n");

    wrefresh(local_win);
}

void printBitMapWin(WINDOW *local_win) {
    wprintw(local_win, "MAPA DE BITS\n\n");

    // for(int i = 0; i < MAX_MEMORY_SIZE; i++){
    //     wprintw(local_win, "%d ", Memory.bitMap[i]);
    //     if(i % 4 == 0)
    //         wprintw(local_win, "\n");
    // }
    //

    for(int i = 0; i < 20; i++) {
        if(i % 5 == 0 && i != 0)
            wprintw(local_win, "\n");

        int n = (int) rand() % 2;
        wprintw(local_win, "%d ", n);
    }

    wrefresh(local_win);
}

void printReadyLine(WINDOW *local_win) {
    wprintw(local_win, "FILA DE PRONTOS\n\n");

    // TODO: substituir mock
    wprintw(local_win, "PID 10 | PID 9 | kill | PID 7 | create\n");

    wrefresh(local_win);
}

WINDOW *create_newwin(int height, int width, int starty, int startx){
  WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);
  //box(local_win, 0 , 0);		/* 0, 0 dá caracteres padrão para as linhas verticais and horizontais	*/
  //wrefresh(local_win);		/* Mostra aquela caixa 	*/

  return local_win;
}