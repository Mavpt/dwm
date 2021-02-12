/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=11" };
static const char dmenufont[]       =   "monospace:size=11"  ;

static const char NormColorFG[]     = "#D8DEE9"; /* Font color */
static const char NormColorBG[]     = "#2E3440"; /* Background color */
static const char NormColorBorder[] = "#4C566A"; /* Inactive window border color */
static const char SelColorFG[]      = "#ECEFF4"; /* Current tag and window font color */
static const char SelColorBG[]      = "#4C566A"; /* Top bar second color */
static const char SelColorBorder[]  = "#88C0D0"; /* Active window border color */

static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { NormColorFG, NormColorBG, NormColorBorder },
	[SchemeSel]  = { SelColorFG , SelColorBG , SelColorBorder  },
};

static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;

static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "6", "7", "8", "9" };

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class                instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
        { "Alacritty",          NULL,     NULL,           0,         0,          1,           0,        -1 },
        { NULL,                 NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */

        { "Brave-browser",      NULL,     NULL,           1<<0,      0,          1,           0,         0 },
        { "discord",            NULL,     NULL,           1<<0,      0,          1,           0,         0 },
        { "zoom",               NULL,     NULL,           1<<0,      0,          1,           0,         1 },
        { "Jami-gnome",         NULL,     NULL,           1<<0,      0,          1,           0,         1 },
        { "Chromium",           NULL,     NULL,           1<<1,      0,          1,           0,        -1 },
        { NULL,                 NULL,     "RSS",          1<<4,      0,          1,          -1,        -1 },
        { "LibreWolf",          NULL,     NULL,           1<<5,      0,          1,           0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5;    /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;       /* number of clients in master area */
static const int resizehints = 0;       /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
// Include Fn keys
#include <X11/XF86keysym.h>

// Helper to run shell commands
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// Useful functions
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]   = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", NormColorBG, "-nf", NormColorFG, "-sb", SelColorBorder, "-sf", SelColorFG, NULL };

static Key keys[] = {
	/* modifier                     key             function        argument */
        /* DWM */
	{ MODKEY|ShiftMask,             XK_q,                   quit,           {0} },

	{ MODKEY,                       XK_b,                   togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_c,                   killclient,     {0} },

        /* Monitors */
	{ MODKEY,                       XK_KP_Delete,           focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_m,                   focusmon,       {.i = +1 } },
	//{ MODKEY,                     XK_comma,               focusmon,       {.i = -1 } },
	//{ MODKEY,                     XK_period,              focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_KP_Delete,           tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_m,                   tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_comma,               tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_period,              tagmon,         {.i = +1 } },

        /* Tags */
	{ ALTKEY,                       XK_Tab,                 view,           {0} },

        // Keypad without numlock
	TAGKEYS(                        XK_KP_Insert,           0)
	TAGKEYS(                        XK_asterisk,            0)
	TAGKEYS(                        XK_KP_End,              1)
	TAGKEYS(                        XK_parenleft,           1)
	TAGKEYS(                        XK_KP_Down,             2)
	TAGKEYS(                        XK_parenright,          2)
	TAGKEYS(                        XK_KP_Next,             3)
	TAGKEYS(                        XK_braceright,          3)
	TAGKEYS(                        XK_KP_Left,             4)
	TAGKEYS(                        XK_plus,                4)
	TAGKEYS(                        XK_KP_Begin,            5)
	TAGKEYS(                        XK_braceleft,           5)
	TAGKEYS(                        XK_KP_Right,            6)
	TAGKEYS(                        XK_bracketright,        6)
	TAGKEYS(                        XK_KP_Home,             7)
	TAGKEYS(                        XK_bracketleft,         7)
	TAGKEYS(                        XK_KP_Up,               8)
	TAGKEYS(                        XK_exclam,              8)
	TAGKEYS(                        XK_equal,               9)
	TAGKEYS(                        XK_KP_Prior,            9)

	{ MODKEY,                       XK_0,                   view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                   tag,            {.ui = ~0 } },

	/* Layout */
        // Change layout
	{ MODKEY|ControlMask,           XK_t,                   setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_f,                   setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_m,                   setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_space,               setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,               togglefloating, {0} },

        { MODKEY,                       XK_minus,               setgaps,        {.i = -1 } },
        { MODKEY,                       XK_plus,                setgaps,        {.i = +1 } },
        { MODKEY,                       XK_equal,               setgaps,        {.i = 0  } },

        // Change master window size
	{ MODKEY,                       XK_j,                   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_k,                   setmfact,       {.f = +0.05} },

        // Move windows from slave to master and vice versa
	{ MODKEY,                       XK_i,                   incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                   incnmaster,     {.i = -1 } },

        /* Windows */
        // Changed focused window
        { MODKEY,                       XK_l,                   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,                   focusstack,     {.i = -1 } },

        // Move focused window to/from master
	{ MODKEY|ShiftMask,             XK_Return,              zoom,           {0} },

        /* Programs */
	{ MODKEY,                       XK_space,               spawn,                  {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,              spawn,                  SHCMD("$TERMINAL") },
        { MODKEY,                       XK_w,                   spawn,                  SHCMD("$BROWSER") },
        { MODKEY,                       XK_p,                   spawn,                  SHCMD("$PBROWSER") },
        { MODKEY,                       XK_c,                   spawn,                  SHCMD("$WBROWSER") },
        { MODKEY,                       XK_s,                   spawn,                  SHCMD("$TERMINAL -e $PLAYER") },
        { MODKEY,                       XK_r,                   spawn,                  SHCMD("$TERMINAL -t RSS -e $RSSREADER") },
        { MODKEY,                       XK_x,                   spawn,                  SHCMD("$TERMINAL -e $FM") },

        /* Fn Keys */
        { 0,                            XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t") },
	{ 0,                            XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer -i 3") },
	{ 0,                            XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer -d 3") },
        { 0,                            XF86XK_Calculator,		spawn,		SHCMD("$TERMINAL -e python") },

	{ 0,                            XF86XK_AudioPlay,		spawn,		SHCMD("mpc toggle") },
	{ 0,                            XF86XK_AudioStop,		spawn,		SHCMD("mpc stop") },
        { 0,                            XF86XK_AudioPrev,		spawn,		SHCMD("mpc prev") },
	{ 0,                            XF86XK_AudioNext,		spawn,		SHCMD("mpc next") },

        { 0,                            XF86XK_Explorer,                spawn,          SHCMD("$TERMINAL -e $FM") },
       	{ 0,                            XF86XK_HomePage,                spawn,		SHCMD("$BROWSER") },

        /* Other */
        { 0,                            XK_Print,                       spawn,          SHCMD("flameshot gui") },
        { MODKEY,			XK_Scroll_Lock,	                spawn,		SHCMD("killall screenkey || screenkey &") },
        { MODKEY|ShiftMask,             XK_a,                           spawn,          SHCMD("remaps") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          SHCMD("$TERMINAL") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
