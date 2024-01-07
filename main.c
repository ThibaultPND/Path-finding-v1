#include "pf.h"

int main(int argc, char* argv[]){
    (void)argc;
    (void)argv;

    tile_t **tab = NULL;

    initTab(&tab);
    if (tab == NULL){
        fprintf(stderr, "Erreur lors de l'initialisation de tab !\n");
        exit(EXIT_FAILURE);
    }

    tab[18][3].state = start;
    tab[8][10].state = end;

    printTab(tab);

    
    TilePos_t index = {3,18};
    while (distanceBetweenTwoPoint(index, (TilePos_t){10,8}) != 0){
        discoverTiles(tab, index);
        TilePos_t minimumPos = {0,0};
        int minimum = INT_MAX;
        for (int i = 0; i < TAB_HEIGHT; i++)
            for (int j = 0; j < TAB_WIDTH; j++)
                if (tab[i][j].f_cost != -1 && tab[i][j].f_cost < minimum)
                {
                    minimum = tab[i][j].f_cost;
                    minimumPos = (TilePos_t){j,i};
                }
        index = minimumPos;
    }
    tile_t index2 = tab[index.y][index.x];

    while (index2.state != start) {
        tab[index2.previous.y][index2.previous.x].state = way;
        index2 = tab[index2.previous.y][index2.previous.x];

        printf("%d : %d\n",index2.previous.y,index2.previous.x );
        printTab(tab);
    }

    printTab(tab);
    

    // cleanup:
    for (int i = 0; i < TAB_HEIGHT; i++)
        free(tab[i]);

    free(tab);


    printf("Le programme s'est fermé normalement.\n");
    return EXIT_SUCCESS;
}