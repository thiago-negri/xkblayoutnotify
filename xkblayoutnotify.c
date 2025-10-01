#include <X11/XKBlib.h>
#include <stdio.h>

#define XKB_ANY_EVENT 85

static int xkb_group;

void
emit_event()
{
	fprintf(stdout, "xkb_layout\t%d\n", xkb_group);
	fflush(stdout);
}

void
handle_xkb_event(XEvent *event)
{
	XkbAnyEvent *xkb_event;
	XkbStateNotifyEvent *xkb_state_notify_event;

	if (event->type != XKB_ANY_EVENT)
		return;

	xkb_event = (XkbAnyEvent *)event;
	if (xkb_event->xkb_type != XkbStateNotify)
		return;

	xkb_state_notify_event = (XkbStateNotifyEvent *)xkb_event;
	if (xkb_group == xkb_state_notify_event->group)
		return;

	xkb_group = xkb_state_notify_event->group;
	emit_event();
}

int
main(int argc, char *argv[])
{
	Display *display;
	XkbStateRec state;
	XEvent event;

	(void)argc;
	(void)argv;

	display = XOpenDisplay(NULL);
	if (display == NULL)
	{
		fprintf(stderr, "XOpenDisplay(NULL) = NULL\n");
		return -1;
	}

	if (!XkbSelectEvents(display, XkbUseCoreKbd, XkbStateNotifyMask, XkbStateNotifyMask))
	{
		fprintf(stderr, "!XkbSelectEvents(...)\n");
		XCloseDisplay(display);
		return -2;
	}

	if (XkbGetState(display, XkbUseCoreKbd, &state) != 0)
	{
		fprintf(stderr, "XkbGetState(...) != 0\n");
		XCloseDisplay(display);
		return -3;
	}
	xkb_group = state.group;
	emit_event();

	for (;;)
	{
		XNextEvent(display, &event);
		handle_xkb_event(&event);
	}

	XCloseDisplay(display);
	return 0;
}
