/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Mediaplayer Header file
*/
#include <termios.h>
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/error.h>

#include <stdbool.h>

#ifndef MEDIAPLAYER_H_
    #define MEDIAPLAYER_H_

typedef struct mediaplayer_s {
    AVFormatContext *ctx;
    AVCodecContext *codec_ctx;
    AVStream *stream;
    int video_idx;
    AVPacket *packet;
    AVFrame *frame;
    int frame_count;
    struct SwsContext *sws;
    AVFrame *rgb_frame;
    int out_w;
    int out_h;
    long delay_us;
    bool stop;
} mediaplayer_t;

/*--Helpers--*/

void display_text(char *level, int nb, ...);
bool mpl_setup(mediaplayer_t *p, const char *path);
bool mpl_teardown(mediaplayer_t *p);
void mpl_print_info(const mediaplayer_t *p);
bool mpl_play(mediaplayer_t *p);
bool mpl_init_scaler(mediaplayer_t *p);
void mpl_render_frame(mediaplayer_t *p);
void mpl_input_begin(struct termios *saved);
void mpl_input_end(const struct termios *saved);
bool mpl_should_stop(void);
void mpl_cells_to_pixels(int cols, int rows, int *max_w, int *max_h);
double mpl_fit_scale(int src_w, int src_h, int max_w, int max_h);
long mpl_frame_delay_us(const AVRational *fps);
int mpl_even_length(double scaled);
#endif /* !MEDIAPLAYER_H_ */
