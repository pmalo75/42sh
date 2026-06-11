/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** An integrated videoplayer.
** This requires the libav* libraries.
*/

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/error.h>

#include "global.h"
#include "mediaplayer.h"
#include "my_sh_def.h"

static void display_help(void)
{
    printf("\t\t\t\tMEDIAPLAYER - 42sh\n");
    printf("\n\n\n");
    printf("Read your media files in the");
    printf(" terminal with this built-in command.\n");
    printf("Usage:\n");
    printf("mediaplayer [-c colorEnabled] mediafile");
    printf("\tARGS");
    printf("\t\t-c: enables the color output (disables the ANSI charset)\n");
}

static int run_player(mediaplayer_t *player, char **cmd)
{
    if (!mpl_setup(player, cmd[1])) {
        free(player);
        return ERROR;
    }
    mpl_print_info(player);
    mpl_play(player);
    mpl_teardown(player);
    free(player);
    return SUCCESS;
}

int mediaplayer(env_t *env, char **cmd)
{
    mediaplayer_t *player;

    (void) env;
    if (cmd[1] == NULL) {
        display_help();
        return SUCCESS;
    }
    player = calloc(1, sizeof(mediaplayer_t));
    if (player == NULL) {
        display_text("ERROR", 1, "You should buy more ram...");
        return ERROR;
    }
    return run_player(player, cmd);
}
