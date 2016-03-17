#include "console.h"

int kern_entry()
{
        console_clear();
        console_write_color("Hello, Small OS!\n", rc_black, rc_green);
	return 0;
}
