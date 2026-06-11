/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** An integrated videoplayer.
** This requires the libav* libraries.
*/

#include <libavutil/rational.h>

#include "mediaplayer.h"

/* Terminal col is 2 pixels (sof) */
void mpl_cells_to_pixels(int cols, int rows, int *max_w, int *max_h)
{
    *max_w = cols;
    *max_h = rows * 2;
}

double mpl_fit_scale(int src_w, int src_h, int max_w, int max_h)
{
    double scale_x = (double)max_w / src_w;
    double scale_y = (double)max_h / src_h;

    return scale_x < scale_y ? scale_x : scale_y;
}

long mpl_frame_delay_us(const AVRational *fps)
{
    if (fps->num <= 0)
        return 0;
    return (long)(1000000.0 * fps->den / fps->num);
}

int mpl_even_length(double scaled)
{
    int length = (int)scaled & ~1;

    if (length < 2)
        length = 2;
    return length;
}
