#if !defined(__PATH_FINDING_H__)
#define __PATH_FINDING_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAB_HEIGHT 20
#define TAB_WIDTH 20

typedef enum{
    none,
    start = 11,
    end = 22,
    way = 33,
}tileState_t;

typedef struct{
    int x;
    int y;
}TilePos_t;

typedef struct{
    tileState_t state;

    bool loaded;

    // Distance from start node minus
    // distance from end node
    int f_cost;

    // Previous tile
    TilePos_t previous;
}tile_t;



void initTab(tile_t ***tab);
void printTab(tile_t **tab);
void findExit(tile_t **tab);
void discoverTile(tile_t **tab, TilePos_t position, TilePos_t caller);
void discoverTiles(tile_t **tab, TilePos_t tile);
int distanceBetweenTwoPoint(TilePos_t start, TilePos_t end);
#endif // __PATH_FINDING_H__
