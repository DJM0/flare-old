#include <zephyr.h>
#include <logging/sys_log.h>

#include "status.h"

void main(void)
{

    SYS_LOG_INF("Flare 🔥");

    status_init();

}
