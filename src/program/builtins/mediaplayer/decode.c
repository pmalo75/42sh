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

#include "mediaplayer.h"

static void mpl_handle_frame(mediaplayer_t *p)
{
    p->frame_count++;
    mpl_render_frame(p);
}

static bool mpl_drain_decoder(mediaplayer_t *p, AVPacket *pkt)
{
    int ret;

    if (avcodec_send_packet(p->codec_ctx, pkt) < 0)
        return false;
    while (true) {
        ret = avcodec_receive_frame(p->codec_ctx, p->frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return true;
        if (ret < 0)
            return false;
        mpl_handle_frame(p);
        av_frame_unref(p->frame);
    }
    return true;
}

static bool mpl_read_loop(mediaplayer_t *p)
{
    bool ok = true;

    while (!p->stop && av_read_frame(p->ctx, p->packet) >= 0) {
        if (p->packet->stream_index == p->video_idx)
            ok = mpl_drain_decoder(p, p->packet);
        av_packet_unref(p->packet);
        if (!ok)
            return false;
    }
    return true;
}

bool mpl_play(mediaplayer_t *p)
{
    struct termios saved;
    bool ok;

    if (!mpl_init_scaler(p))
        return false;
    mpl_input_begin(&saved);
    printf("\x1b[?1049h\x1b[2J\x1b[?25l");
    ok = mpl_read_loop(p) && (p->stop || mpl_drain_decoder(p, NULL));
    printf("\x1b[0m\x1b[?25h\x1b[?1049l");
    fflush(stdout);
    mpl_input_end(&saved);
    return ok;
}
