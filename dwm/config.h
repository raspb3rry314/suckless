/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel size of windows */
static const unsigned int gappx     = 5;        /* gaps size between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FontAwesome:size=13" };
static const char dmenufont[]       = "Source Code Pro:size=12";
//background color
static const char col_gray1[]       = "#222222";
//inactive window border color
static const char col_gray2[]       = "#444444";
//font color
static const char col_gray3[]       = "#bbbbbb";
//current tag and current window font color
static const char col_gray4[]       = "#eeeeee";
//Top bar second color (blue) and active window border color
static const char col_cyan[]        = "#0b57a4";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
//tag names (upper left)
static const char *tags[] = { "", "","" ,"", "","", "", "", "" };
#include <X11/XF86keysym.h>
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *filemanager[] = { "
// Custom app shortcuts definitions
static const char *monitor[] = { "/usr/bin/htop", NULL };
static const char *spotify[] = { "spotify", NULL };
static const char *web[] = { "firefox", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *idea[] = { "intellij-iu", NULL };
// Volume controls
//static const char *upvol[]   = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
//static const char *downvol[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
//static const char *mutevol[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
//static const char *volmutecmd[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
//static const char *volupcmd[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
//static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };
  static const char *volupcmd[] = { "/bin/bash", "-c", "amixer -D default sset Master Playback 1%+" };
  static const char *volmaxcmd[] = { "/bin/bash", "-c", "amixer -D default sset Master Playback 100%" };
  static const char *voldowncmd[] = { "/bin/bash", "-c", "amixer -D default sset Master Playback 1%-" };
  static const char *volmutecmd[] = { "/bin/bash", "-c", "amixer -D default sset Master Playback 0%" };
  static const char *medplaypausecmd[] = { "playerctl", "play-pause", NULL };
  static const char *mednextcmd[] = { "playerctl", "next", NULL };
  static const char *medprevcmd[] = { "playerctl", "previous", NULL };

#include "shiftview.c"
static char *endx[] = { "/bin/sh", "-c", "endx", "externalpipe", NULL };
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_w,      spawn,          {.v = web } },
	{ MODKEY,                       XK_p,      spawn,          {.v = idea } },
	{ MODKEY,                       XK_s,      spawn,          {.v = spotify } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,	                    XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_t,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                    XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,              		    XK_Right,      shiftview,  	   { .i = +1 } },
	{ MODKEY,              		    XK_Left,      shiftview,      { .i = -1 } },
	{ MODKEY,			XK_F11,      spawn,          {.v = volupcmd   } },
	{ MODKEY,                       XK_F10,      spawn,          {.v = voldowncmd   } },
	 { MODKEY,                       XK_F9,      spawn,          {.v = voldowncmd   } },
    { 0,                       XF86XK_AudioRaiseVolume,     spawn,          {.v = volupcmd   } },
    { 0,                       XF86XK_AudioLowerVolume,     spawn,          {.v = voldowncmd } },
    { 0,                       XF86XK_AudioMute,     spawn,          {.v = volmutecmd } },
    { 0,			XF86XK_AudioPlay,		spawn, {.v = medplaypausecmd } },
    { 0, 			XF86XK_AudioNext,		spawn, {.v = mednextcmd } },
    { 0, 		 	XF86XK_AudioPrev,		spawn, {.v = medprevcmd } },

	TAGKEYS(                       XK_KP_End,                      0)
	TAGKEYS(                        XK_KP_Down,                      1)
	TAGKEYS(                        XK_KP_Next,                      2)
	TAGKEYS(                        XK_KP_Left,                      3)
	TAGKEYS(                        XK_KP_Begin,                      4)
	TAGKEYS(                        XK_KP_Right,                      5)
	TAGKEYS(                        XK_KP_Home,                      6)
	TAGKEYS(                        XK_KP_Up,                      7)
	TAGKEYS(                        XK_KP_Prior,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
