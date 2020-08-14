/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";
static const int monitortime = 5;
static const char *message = "Locked";
static const char *text_color = "#eceff4";
static const char *font_name = "6x10";
/* time in seconds to cancel lock with mouse movement */
static const int timetocancel = 4;

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#2e3440",     /* after initialization */
	[INPUT] =  "#81a1c1",   /* during input */
	[FAILED] = "#bf616a",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
