/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** An integrated videoplayer.
** This requires the libav* libraries.
*/

#include <libavformat/avformat.h>
#include <libavutil/pixdesc.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/error.h>

#include "mediaplayer.h"


void mpl_print_info(const mediaplayer_t *p)
{
    printf("\tcodec : %s\n", p->codec_ctx->codec->name);
    printf("\tsize  : %dx%d\n", p->codec_ctx->width, p->codec_ctx->height);
    printf("\tpixfmt: %s\n", av_get_pix_fmt_name(p->codec_ctx->pix_fmt));
    printf("\tduration : %.1fs\n", (double)p->ctx->duration / AV_TIME_BASE);
}

static bool mpl_open_container(mediaplayer_t *p, const char *path)
{
    if (avformat_open_input(&p->ctx, path, NULL, NULL) < 0)
        return false;
    if (avformat_find_stream_info(p->ctx, NULL) < 0)
        return false;
    return true;
}

static bool mpl_select_video_stream(mediaplayer_t *p, const AVCodec **codec)
{
    int idx = av_find_best_stream(p->ctx, AVMEDIA_TYPE_VIDEO, -1, -1, codec, 0);

    if (idx < 0)
        return false;
    p->video_idx = idx;
    p->stream = p->ctx->streams[idx];
    return true;
}

static bool mpl_open_decoder(mediaplayer_t *p, const AVCodec *codec)
{
    p->codec_ctx = avcodec_alloc_context3(codec);
    if (p->codec_ctx == NULL)
        return false;
    if (avcodec_parameters_to_context(p->codec_ctx, p->stream->codecpar) < 0)
        return false;
    if (avcodec_open2(p->codec_ctx, codec, NULL) < 0)
        return false;
    return true;
}

static bool mpl_alloc_buffers(mediaplayer_t *p)
{
    p->packet = av_packet_alloc();
    p->frame = av_frame_alloc();
    return p->packet != NULL && p->frame != NULL;
}

bool mpl_setup(mediaplayer_t *p, const char *path)
{
    const AVCodec *codec = NULL;

    if (!mpl_open_container(p, path)
        || !mpl_select_video_stream(p, &codec)
        || !mpl_open_decoder(p, codec)
        || !mpl_alloc_buffers(p)) {
        mpl_teardown(p);
        return false;
    }
    return true;
}

bool mpl_teardown(mediaplayer_t *p)
{
    sws_freeContext(p->sws);
    av_frame_free(&p->rgb_frame);
    av_frame_free(&p->frame);
    av_packet_free(&p->packet);
    avcodec_free_context(&p->codec_ctx);
    avformat_close_input(&p->ctx);
    return false;
}
