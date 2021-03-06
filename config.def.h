/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Fira Sans:size=12", "NotoColorEmoji", "feather:size=15" };
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { "#ebdbb2", "#1d2021", "#1d2021" },
    [SchemeSel]  = { "#ebdbb2", "#454545", "#454545" },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    //{ "Gigswifi",               NULL,       NULL,        0,             1,         0 },
    //{ "Godot",                  "Godot_ProjectList",       NULL,          0,             1,         0 },
    { "jetbrains-studio",       "sun-awt-X11-XWindowPeer",       NULL,          0,             1,         0 },
    { "jetbrains-studio",       "sun-awt-X11-XFramePeer",       NULL,          0,             1,         0 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run" };
static const char *termcmd[]  = { "st", NULL };
static const char *firefoxcmd[]  = { "firefox", NULL };
//static const char *musiccmd[] = {"st", "-c", "cmus", "-e", "cmus", NULL};
static const char *shotcmd[] = {"shot", NULL};
static const char *emojicmd[] = {"dmenu_emoji", NULL};
static const char *brtupcmd[]  = { "sudo", "brightness", "inc", "10", NULL };
static const char *brtdowncmd[]  = { "sudo", "brightness", "dec", "10", NULL };
//static const char *musictogglecmd[]  = { "cmus-remote", "-u", NULL };
//static const char *musicnextcmd[]  = { "cmus-remote", "-n", NULL };
//static const char *musicprevcmd[]  = { "cmus-remote", "-r", NULL };
//static const char *musicstopcmd[]  = { "cmus-remote", "-s", NULL };
static const char *volupcmd[] = {"amixer", "set", "Master", "5%+", NULL};
static const char *voldowncmd[] = {"amixer", "set", "Master", "5%-", NULL};
static const char *mutecmd[] = {"amixer", "set", "Master", "toggle", NULL};
//static const char *wificmd[] = {"wifi", NULL};
//static const char *wificmd[] = {"wpa_gui", NULL};

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
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
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    //{ MODKEY|ControlMask,           XK_m,      spawn,          {.v = musiccmd } },
        { MODKEY|ControlMask,           XK_f,      spawn,          {.v = firefoxcmd } },
        { 0,                            XK_Print,  spawn,          {.v = shotcmd} },
        { ShiftMask|ControlMask,        XK_e,      spawn,          {.v = emojicmd} },
        { 0,                        0x1008ff02,      spawn,    {.v = brtupcmd } },
        { 0,                        0x1008ff03,      spawn,    {.v = brtdowncmd } },
        //{ 0,                        0x1008ff14,      spawn,    {.v = musictogglecmd } },
        //{ 0,                        0x1008ff17,      spawn,    {.v = musicnextcmd } },
        //{ 0,                        0x1008ff16,      spawn,    {.v = musicprevcmd } },
        //{ 0,                        0x1008ff15,      spawn,    {.v = musicstopcmd } },
        { 0,                            0x1008ff13,      spawn,    {.v = volupcmd} },
        { 0,                            0x1008ff11,      spawn,    {.v = voldowncmd} },
        { 0,                            0x1008ff12,      spawn,    {.v = mutecmd} },
        //{ ShiftMask|ControlMask,        XK_w,            spawn,    {.v = wificmd} },
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

