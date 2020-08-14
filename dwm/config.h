/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int showsystray        = 1;        /* 0 means no systray */
static const int systrayspacing     = 10;
static const int systraypinning     = 1;
static const int systraypinningfailfirst     = 0;
static const unsigned int gappx     = 10;        /* gap pixel between windows */
static const char *fonts[]          = { "Victor Mono:pixelsize=16:antialias=true:autohint=true" };
static const char dmenufont[]       = "Victor Mono:size=13";
/*static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";*/
static const char col_gray1[]       = "#2e3440";
static const char col_gray2[]       = "#2e3440";
static const char col_gray3[]       = "#eceff4";
static const char col_gray4[]       = "#e5e9f0";
static const char col_cyan[]        = "#81a1c1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_cyan,  col_cyan  },
};


/* tagging */
static const char *tags[] = { "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	/*{ "Gimp",     NULL,       NULL,       0,            1,           -1 },*/
	{ "Firefox",  NULL,       NULL,       0,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "🤖",      tile },    /* first entry is default */
	{ "🐠",      NULL },    /* no layout function means floating behavior */
	{ "🔎",      monocle },
	{ "🧭",      centeredfloatingmaster },
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
/*static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };*/
static const char *dmenucmd[] = { "rofi", "-show", "drun", "-show-icons", "-config", "/home/maximilien/.config/rofi/themes/launchpad.rasi", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *lockcmd[] = { "slock", "-m", "$(fortune)", NULL };
static const char *clipboardcmd[] = { "greenclip", "print", "|", "sed", "'/^$/d'", "|", "dmenu", "-l", "10", "-p", "clipboard", "|", "xargs", "-r", "-d'\n'", "-I", "'{}'", "greenclip", "print", "'{}'", NULL };
static const char *screenshotcmd[] = { "maim", "-s", "|", "xclip", "-selection", "clipboard", "-t", "image/png", "&&", "notify-send", "'Screenshot'", "'Capture dans le presse papier'", NULL };
static const char *mutecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };

static const char *const autostart[] = {
	"nitrogen", "--restore", NULL,
	"slstatus", NULL,
	"/home/maximilien/.screenlayout/office.sh", NULL,
	"synclient", "VertScrollDelta=-27", "HorScrollDelta=-27", NULL,
	"numlockx", NULL,
	"unclutter", NULL,
	"flashfocus", NULL,
	"xautolock", "-locker", "slock", "-m", "$(fortune)", NULL,
	"greenclip", "daemon", NULL,
	"compton", NULL,
	/*"sh", "-c", "while :; do dwmstatus.sh -; sleep 60; done", NULL,*/
	"dunst", NULL,
	NULL
};

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = screenshotcmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = clipboardcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       0xe0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             0xe0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Prior,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Next, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Prior,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Next, tagmon,         {.i = +1 } },
	TAGKEYS(                        0x26,                      0)
	TAGKEYS(                        0xe9,                      1)
	TAGKEYS(                        0x22,                      2)
	TAGKEYS(                        0x27,                      3)
	TAGKEYS(                        0x28,                      4)
	TAGKEYS(                        0x2d,                      5)
	TAGKEYS(                        0xe8,                      6)
	TAGKEYS(                        0x5f,                      7)
	TAGKEYS(                        0xe7,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0, XF86XK_AudioMute, spawn, {.v = mutecmd } },
	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
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

