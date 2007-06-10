#ifndef TV_H
#define TV_H

#ifdef USE_TV
//#include "libao2/afmt.h"
//#include "libmpcodecs/img_format.h"
//#include "mp_msg.h"

extern char *tv_param_freq;
extern char *tv_param_channel;
extern char *tv_param_chanlist;
extern char *tv_param_norm;
extern int tv_param_automute;
#ifdef HAVE_TV_V4L2
extern int tv_param_normid;
#endif
extern char *tv_param_device;
extern char *tv_param_driver;
extern int tv_param_width;
extern int tv_param_height;
extern int tv_param_input;
extern int tv_param_outfmt;
extern float tv_param_fps;
extern char **tv_param_channels;
extern int tv_param_noaudio;
extern int tv_param_immediate;
extern int tv_param_audiorate;
extern int tv_param_audio_id;
#if defined(HAVE_TV_V4L)
extern int tv_param_amode;
extern int tv_param_volume;
extern int tv_param_bass;
extern int tv_param_treble;
extern int tv_param_balance;
extern int tv_param_forcechan;
extern int tv_param_force_audio;
extern int tv_param_buffer_size;
extern int tv_param_mjpeg;
extern int tv_param_decimation;
extern int tv_param_quality;
#if defined(HAVE_ALSA9) || defined(HAVE_ALSA1X)
extern int tv_param_alsa;
#endif
extern char* tv_param_adevice;
#endif
#ifdef HAVE_TV_TELETEXT
extern char* tv_param_tdevice;        ///< teletext vbi device
extern char* tv_param_tformat;        ///< format: text,bw,gray,color
extern int tv_param_tpage;            ///< page number
#endif
extern int tv_param_brightness;
extern int tv_param_contrast;
extern int tv_param_hue;
extern int tv_param_saturation;

typedef struct tvi_info_s
{
    struct tvi_handle_s * (*tvi_init)(char *device,char *adevice);
    const char *name;
    const char *short_name;
    const char *author;
    const char *comment;
} tvi_info_t;

typedef struct tvi_functions_s
{
    int (*init)();
    int (*uninit)();
    int (*control)();
    int (*start)();
    double (*grab_video_frame)();
    int (*get_video_framesize)();
    double (*grab_audio_frame)();
    int (*get_audio_framesize)();
} tvi_functions_t;

typedef struct tvi_handle_s {
    tvi_functions_t	*functions;
    void		*priv;
#ifdef HAVE_TV_TELETEXT
    void                *priv_vbi;
#endif
    int 		seq;

    /* specific */
    int			norm;
    int			chanlist;
    const struct CHANLIST *chanlist_s;
    int			channel;
} tvi_handle_t;

typedef struct tv_channels_s {
    int index;
    char number[5];
    char name[20];
    int   freq;
    struct tv_channels_s *next;
    struct tv_channels_s *prev;
} tv_channels_t;

#ifdef HAVE_TV_TELETEXT
typedef struct tv_teletext_img_s {
    void*    canvas;
    int        tformat;
    int        columns;
    int        rows;
    int        height;
    int        width;
    int        half;
} tv_teletext_img_t;
#endif

extern tv_channels_t *tv_channel_list;
extern tv_channels_t *tv_channel_current, *tv_channel_last;
extern char *tv_channel_last_real;

#define TVI_CONTROL_FALSE		0
#define TVI_CONTROL_TRUE		1
#define TVI_CONTROL_NA			-1
#define TVI_CONTROL_UNKNOWN		-2

/* ======================== CONTROLS =========================== */

/* GENERIC controls */
#define TVI_CONTROL_IS_AUDIO		0x1
#define TVI_CONTROL_IS_VIDEO		0x2
#define TVI_CONTROL_IS_TUNER		0x3
#define TVI_CONTROL_IMMEDIATE           0x4

/* VIDEO controls */
#define TVI_CONTROL_VID_GET_FPS		0x101
#define TVI_CONTROL_VID_GET_PLANES	0x102
#define TVI_CONTROL_VID_GET_BITS	0x103
#define TVI_CONTROL_VID_CHK_BITS	0x104
#define TVI_CONTROL_VID_SET_BITS	0x105
#define TVI_CONTROL_VID_GET_FORMAT	0x106
#define TVI_CONTROL_VID_CHK_FORMAT	0x107
#define TVI_CONTROL_VID_SET_FORMAT	0x108
#define TVI_CONTROL_VID_GET_WIDTH	0x109
#define TVI_CONTROL_VID_CHK_WIDTH	0x110
#define TVI_CONTROL_VID_SET_WIDTH	0x111
#define TVI_CONTROL_VID_GET_HEIGHT	0x112
#define TVI_CONTROL_VID_CHK_HEIGHT	0x113
#define TVI_CONTROL_VID_SET_HEIGHT	0x114
#define TVI_CONTROL_VID_GET_BRIGHTNESS	0x115
#define TVI_CONTROL_VID_SET_BRIGHTNESS	0x116
#define TVI_CONTROL_VID_GET_HUE		0x117
#define TVI_CONTROL_VID_SET_HUE		0x118
#define TVI_CONTROL_VID_GET_SATURATION	0x119
#define TVI_CONTROL_VID_SET_SATURATION	0x11a
#define TVI_CONTROL_VID_GET_CONTRAST	0x11b
#define TVI_CONTROL_VID_SET_CONTRAST	0x11c
#define TVI_CONTROL_VID_GET_PICTURE	0x11d
#define TVI_CONTROL_VID_SET_PICTURE	0x11e

/* TUNER controls */
#define TVI_CONTROL_TUN_GET_FREQ	0x201
#define TVI_CONTROL_TUN_SET_FREQ	0x202
#define TVI_CONTROL_TUN_GET_TUNER	0x203	/* update priv->tuner struct for used input */
#define TVI_CONTROL_TUN_SET_TUNER	0x204	/* update priv->tuner struct for used input */
#define TVI_CONTROL_TUN_GET_NORM	0x205
#define TVI_CONTROL_TUN_SET_NORM	0x206

/* AUDIO controls */
#define TVI_CONTROL_AUD_GET_FORMAT	0x301
#define TVI_CONTROL_AUD_GET_SAMPLERATE	0x302
#define TVI_CONTROL_AUD_GET_SAMPLESIZE	0x303
#define TVI_CONTROL_AUD_GET_CHANNELS	0x304
#define TVI_CONTROL_AUD_SET_SAMPLERATE	0x305

/* SPECIFIC controls */
#define TVI_CONTROL_SPC_GET_INPUT	0x401	/* set input channel (tv,s-video,composite..) */
#define TVI_CONTROL_SPC_SET_INPUT	0x402	/* set input channel (tv,s-video,composite..) */
#define TVI_CONTROL_SPC_GET_NORMID	0x403	/* get normid from norm name */

/* TELETEXT controls */
#define TVI_CONTROL_VBI_SET_MODE        0x501   ///< on/off grab teletext
#define TVI_CONTROL_VBI_GET_MODE        0x502   ///< get current mode teletext
#define TVI_CONTROL_VBI_STEP_MODE       0x503  ///< step teletext mode

#define TVI_CONTROL_VBI_SET_PAGE        0x504   ///< set grab teletext page number
#define TVI_CONTROL_VBI_STEP_PAGE       0x505   ///< step grab teletext page number
#define TVI_CONTROL_VBI_GET_PAGE        0x506   ///< get grabbed teletext page

#define TVI_CONTROL_VBI_SET_FORMAT      0x507   ///< set teletext format
#define TVI_CONTROL_VBI_STEP_FORMAT     0x508   ///< step teletext format
#define TVI_CONTROL_VBI_GET_FORMAT      0x509   ///< get eletext format

#define TVI_CONTROL_VBI_GET_HALF_PAGE   0x50a   ///< get current half page
#define TVI_CONTROL_VBI_STEP_HALF_PAGE  0x50b   ///< switch half page
#define TVI_CONTROL_VBI_SET_HALF_PAGE   0x50c   ///< switch half page

#define TVI_CONTROL_VBI_ADD_DEC         0x50d   ///< add page number with dec
#define TVI_CONTROL_VBI_GO_LINK         0x50e   ///< go link (1..6)
#define TVI_CONTROL_VBI_GET_TXTPAGE     0x50f   ///< get grabbed text teletext page
#define TVI_CONTROL_VBI_GET_IMGPAGE     0x510   ///< get grabbed image teletext page
#define TVI_CONTROL_VBI_GET_VBIPAGE     0x511   ///< get vbi_image for grabbed teletext page
#define TVI_CONTROL_VBI_RESET           0x512   ///< vbi reset
#define TVI_CONTROL_VBI_START           0x513   ///< vbi start

extern tvi_handle_t *tv_begin(void);
extern int tv_init(tvi_handle_t *tvh);
extern int tv_uninit(tvi_handle_t *tvh);

int tv_set_color_options(tvi_handle_t *tvh, int opt, int val);
int tv_get_color_options(tvi_handle_t *tvh, int opt, int* val);
#define TV_COLOR_BRIGHTNESS	1
#define TV_COLOR_HUE		2
#define TV_COLOR_SATURATION	3
#define TV_COLOR_CONTRAST	4

int tv_step_channel_real(tvi_handle_t *tvh, int direction);
int tv_step_channel(tvi_handle_t *tvh, int direction);
#define TV_CHANNEL_LOWER	1
#define TV_CHANNEL_HIGHER	2

int tv_last_channel(tvi_handle_t *tvh);

int tv_set_channel_real(tvi_handle_t *tvh, char *channel);
int tv_set_channel(tvi_handle_t *tvh, char *channel);

int tv_step_norm(tvi_handle_t *tvh);
int tv_step_chanlist(tvi_handle_t *tvh);

int tv_set_freq(tvi_handle_t *tvh, unsigned long freq);
int tv_get_freq(tvi_handle_t *tvh, unsigned long *freq);
int tv_step_freq(tvi_handle_t *tvh, float step_interval);

int tv_set_norm(tvi_handle_t *tvh, char* norm);

#ifdef HAVE_TV_TELETEXT
int tv_teletext_control(tvi_handle_t* tvh, int control,void* arg);
/// add dec to pageno
int tv_teletext_add_dec(tvi_handle_t *tvh, char *dec);
/// go link
int tv_teletext_go_link(tvi_handle_t *tvh, int linkno);
/// get current vbi_page
void* tv_get_teletext_vbipage(tvi_handle_t *tvh);
/// get current page text
char* tv_get_teletext_txtpage(tvi_handle_t *tvh);
/// get current page image (RGB32_LB format)
tv_teletext_img_t* tv_get_teletext_imgpage(tvi_handle_t *tvh);
#endif

#define TV_NORM_PAL		1
#define TV_NORM_NTSC		2
#define TV_NORM_SECAM		3
#define TV_NORM_PALNC		4
#define TV_NORM_PALM		5
#define TV_NORM_PALN		6
#define TV_NORM_NTSCJP		7

#endif /* USE_TV */

#endif /* TV_H */
