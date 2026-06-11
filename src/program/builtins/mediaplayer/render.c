/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** An integrated videoplayer.
** This requires the libav* libraries.
*/

#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>

#include "mediaplayer.h"

static void mpl_term_size(int *cols, int *rows)
{
    struct winsize ws;

    *cols = 80;
    *rows = 24;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0) {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
    }
}

static void mpl_compute_dims(mediaplayer_t *p)
{
    int src_w = p->codec_ctx->width;
    int src_h = p->codec_ctx->height;
    int cols;
    int rows;
    int max_w;
    int max_h;
    double scale;

    mpl_term_size(&cols, &rows);
    mpl_cells_to_pixels(cols, rows, &max_w, &max_h);
    scale = mpl_fit_scale(src_w, src_h, max_w, max_h);
    p->out_w = mpl_even_length(src_w * scale);
    p->out_h = mpl_even_length(src_h * scale);
}

static void mpl_put_cell(const uint8_t *top, const uint8_t *bot)
{
    printf("\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm\xe2\x96\x80",
        top[0], top[1], top[2], bot[0], bot[1], bot[2]);
}

bool mpl_init_scaler(mediaplayer_t *p)
{
    mpl_compute_dims(p);
    p->delay_us = mpl_frame_delay_us(&p->stream->avg_frame_rate);
    p->sws = sws_getContext(p->codec_ctx->width, p->codec_ctx->height,
        p->codec_ctx->pix_fmt, p->out_w, p->out_h, AV_PIX_FMT_RGB24,
        SWS_BILINEAR, NULL, NULL, NULL);
    p->rgb_frame = av_frame_alloc();
    if (p->sws == NULL || p->rgb_frame == NULL)
        return false;
    p->rgb_frame->format = AV_PIX_FMT_RGB24;
    p->rgb_frame->width = p->out_w;
    p->rgb_frame->height = p->out_h;
    if (av_frame_get_buffer(p->rgb_frame, 0) < 0)
        return false;
    return true;
}

void mpl_render_frame(mediaplayer_t *p)
{
    uint8_t *d = p->rgb_frame->data[0];
    int ls = p->rgb_frame->linesize[0];
    int x;
    int y;

    sws_scale(p->sws, (const uint8_t *const *)p->frame->data,
        p->frame->linesize, 0, p->codec_ctx->height,
        p->rgb_frame->data, p->rgb_frame->linesize);
    printf("\x1b[H");
    for (y = 0; y + 1 < p->out_h; y += 2) {
        for (x = 0; x < p->out_w; x++)
            mpl_put_cell(d + y * ls + x * 3, d + (y + 1) * ls + x * 3);
        printf("\x1b[0m\n");
    }
    fflush(stdout);
    if (mpl_should_stop())
        p->stop = true;
    if (p->delay_us > 0)
        usleep(p->delay_us);
}
