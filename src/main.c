#include <zephyr.h>
#include <logging/sys_log.h>

#if defined(CONFIG_FLARE_STATUS)
#include "status.h"
#endif

void main(void)
{

    SYS_LOG_INF("Flare 🔥");

    #if defined(CONFIG_FLARE_STATUS)
    status_init();
    #endif

}
