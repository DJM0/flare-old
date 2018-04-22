#include <zephyr.h>
#include <logging/sys_log.h>

#if defined(CONFIG_FLARE_STATUS)
#include "status.h"
#endif

#if defined(CONFIG_FLARE_BLE_GATT)
#include "ble/gatt/gatt.h"
#endif

void main(void)
{

    SYS_LOG_INF("Flare 🔥");

    #if defined(CONFIG_FLARE_STATUS)
    status_init();
    #endif

    #if defined(CONFIG_FLARE_BLE_GATT)
    ble_gatt_init();
    #endif

}
