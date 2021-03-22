/*
 * Image size: 0x10 x 0x70
 * Number of tiles (total - unique): 0x1C - 0x1C
 */

#define NBSFRAMES 0x02 /* Nb frames for the sprite */
#define WINSZX 0x80    /* Size of the picture in the window */
#define WINSZY 0x50
#define MINWINX (MAXWNDPOSX - WINSZX + 1) /* Bounds of the window origin */
#define MINWINY (MAXWNDPOSY - WINSZY + 1)
#define MAXWINX MAXWNDPOSX
#define MAXWINY MAXWNDPOSY