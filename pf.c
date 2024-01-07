#include "pf.h"

const TilePos_t startPosition = {3, 18};
const TilePos_t endPosition = {10, 8};

void initTab(tile_t ***tab){
    if (*tab != NULL){
        fprintf(stderr, "tab est déja initialisé !\n");
        return;
    }
    
    *tab = (tile_t**)malloc(TAB_HEIGHT * sizeof(tile_t*));
    for (int i = 0; i < TAB_HEIGHT; i++) {
        (*tab)[i] = (tile_t*)malloc(TAB_WIDTH * sizeof(tile_t));

        if ((*tab)[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation de mémoire pour la ligne %d du tableau.\n", i);
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < TAB_WIDTH; j++){
            (*(*tab+i)+j)->state = none;
            (*(*tab+i)+j)->f_cost = -1;
            (*(*tab+i)+j)->loaded = 0;
            (*(*tab+i)+j)->previous = (TilePos_t){0,0};
        }
    }
}

int distanceBetweenTwoPoint(TilePos_t start, TilePos_t end) {
    int dx = abs(end.x - start.x); // 5
    int dy = abs(end.y - start.y); // 2
    
    int diagonal = dx < dy ? dx : dy;
    int straight = abs(dx - dy);

    return (diagonal * 14) + (straight * 10);
}

void printTab(tile_t **tab){

    if (tab == NULL){
        fprintf(stderr, "Le tableau ne peut pas être afficher car il est vide !\n");
        return;
    }

    printf("Tableau :\n\n");
    for (int i = 0; i < TAB_HEIGHT; i++)
    {
        for (int j = 0; j < TAB_WIDTH; j++)
        {
            if (tab[i][j].state != none){
                printf("    ■", tab[i][j].state);
            }else{
                printf("%5.d", tab[i][j].f_cost);
            }
            
        }
        printf("\n");
    }
    printf("\n");;
}

void discoverTile(tile_t **tab, TilePos_t position, TilePos_t caller){
    if (position.x < 0 || position.x >= TAB_WIDTH)
        return;
    if (position.y < 0 || position.y >= TAB_HEIGHT)
        return;

    tile_t *tile = &tab[position.y][position.x];

    if (tile->loaded){ // || wall
        return;
    }else {
        if (tile->f_cost == -1){
            tile->f_cost = distanceBetweenTwoPoint(position, endPosition);
            //tile->f_cost += distanceBetweenTwoPoint(position, startPosition);
        }
        tile->previous = caller;
    }
        
}

void discoverTiles(tile_t **tab, TilePos_t tile){
    if (tab[tile.y][tile.x].loaded){
        return;
    }
    tab[tile.y][tile.x].loaded = true;
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (i == 0 && j == 0){
                continue;
            }
            discoverTile(tab, (TilePos_t){tile.x+i , tile.y+j}, tile);
        }
    }
}