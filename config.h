/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005faf";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance    title       tags mask     isfloating   monitor */
	{ "Gimp",        NULL,       NULL,       0,            1,           -1 },
	{ "kcalc",       NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",     NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Caprine",     NULL,       NULL,       1 << 7,       0,           -1 },
	{ "Thunderbird", NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Slack",       NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },    /* first entry is default */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[] = { "st", NULL };
static const char *browser[] = { "firefox", NULL };
static const char *filemng[] = { "pcmanfm", NULL };
static const char *incbckl[] = { "xbacklight", "+10", "-time", "1", "-steps", "100", NULL };
static const char *decbckl[] = { "xbacklight", "-10", "-time", "1", "-steps", "100", NULL };
static const char *mute[]    = { "amixer", "-q", "-D", "pulse", "sset", "Master", "toggle", NULL };
static const char *incvol[]  = { "amixer", "sset", "Master", "3%+", NULL };
static const char *decvol[]  = { "amixer", "sset", "Master", "3%-", NULL };
static const char *capare[]  = { "capare", NULL };
static const char *capscr[]  = { "capscr", NULL };
static const char *lock[]    = { "xtrlock", NULL };
static const char *calc[]    = { "kcalc", NULL };
static const char *plpause[] = { "playerctl", "play-pause", NULL };
static const char *plnext[]  = { "playerctl", "next", NULL };
static const char *plprev[]  = { "playerctl", "previous", NULL };

static Key keys[] = {
	/* modifier           key                      function        argument */
	{ MODKEY,             XK_r,                    spawn,          {.v = dmenucmd } },
	{ MODKEY,             XK_Return,               spawn,          {.v = termcmd } },
	{ MODKEY,             XK_grave,                spawn,          {.v = browser } },
	{ 0,                  XK_Pause,                spawn,          {.v = filemng } },
	{ MODKEY,             XK_b,                    togglebar,      {0} },
	{ MODKEY,             XK_j,                    focusstackvis,  {.i = +1 } },
	{ MODKEY,             XK_k,                    focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_j,                    focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_k,                    focusstackhid,  {.i = -1 } },
	{ MODKEY,             XK_i,                    incnmaster,     {.i = +1 } },
	{ MODKEY,             XK_d,                    incnmaster,     {.i = -1 } },
	{ MODKEY,             XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY,             XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,   XK_Return,               zoom,           {0} },
	{ MODKEY,             XK_Tab,                  view,           {0} },
	{ MODKEY|ShiftMask,   XK_c,                    killclient,     {0} },
	{ MODKEY,             XK_t,                    setlayout,      {.v = &layouts[1]} },
	{ MODKEY,             XK_f,                    setlayout,      {.v = &layouts[2]} },
	{ MODKEY,             XK_m,                    setlayout,      {.v = &layouts[0]} },
	{ MODKEY,             XK_space,                setlayout,      {0} },
	{ MODKEY|ShiftMask,   XK_space,                togglefloating, {0} },
	{ MODKEY,             XK_0,                    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,   XK_0,                    tag,            {.ui = ~0 } },
	{ MODKEY,             XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,             XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,   XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,   XK_period,               tagmon,         {.i = +1 } },
	{ 0,                  XF86XK_MonBrightnessUp,  spawn,          {.v = incbckl } },
	{ 0,                  XF86XK_MonBrightnessDown,spawn,          {.v = decbckl } },
	{ 0,                  XF86XK_AudioMute,        spawn,          {.v = mute } },
	{ 0,                  XF86XK_AudioRaiseVolume, spawn,          {.v = incvol } },
	{ 0,                  XF86XK_AudioLowerVolume, spawn,          {.v = decvol } },
	{ 0,                  XF86XK_Calculator,       spawn,          {.v = calc } },
	{ 0,                  XF86XK_AudioPause,       spawn,          {.v = plpause } },
	{ 0,                  XF86XK_AudioPlay,        spawn,          {.v = plpause } },
	{ 0,                  XF86XK_AudioPrev,        spawn,          {.v = plprev } },
	{ 0,                  XF86XK_AudioNext,        spawn,          {.v = plnext } },
	{ 0,                  XK_Print,                spawn,          {.v = capscr } },
	{ ShiftMask,          XK_Print,                spawn,          {.v = capare } },
	{ MODKEY|ShiftMask,   XK_t,                    spawn,          {.v = lock } },
	TAGKEYS(              XK_1,                                    0)
	TAGKEYS(              XK_2,                                    1)
	TAGKEYS(              XK_3,                                    2)
	TAGKEYS(              XK_4,                                    3)
	TAGKEYS(              XK_5,                                    4)
	TAGKEYS(              XK_6,                                    5)
	TAGKEYS(              XK_7,                                    6)
	TAGKEYS(              XK_8,                                    7)
	TAGKEYS(              XK_9,                                    8)
	{ MODKEY|ShiftMask,   XK_q,                    quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        killclient,     {0} },
	{ ClkWinTitle,          0,              Button3,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

