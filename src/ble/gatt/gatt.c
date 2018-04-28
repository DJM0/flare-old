#include <zephyr.h>
#include <bluetooth/conn.h>
#include <logging/sys_log.h>

#include "gatt.h"
#include "dis.h"
#include "lcs.h"

#define DEVICE_NAME_LEN	(sizeof(CONFIG_BT_DEVICE_NAME) - 1)

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0x0A, 0x18), // Device Information
    BT_DATA_BYTES(BT_DATA_UUID128_ALL,
        0x00, 0x22, 0x6E, 0x82, 0x09, 0xA3, 0xED, 0xAD,
        0x87, 0x4C, 0xB8, 0x93, 0x2C, 0xA0, 0x34, 0x80), // Light Control Service
};

static const struct bt_data sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, DEVICE_NAME_LEN),
};

static void connected(struct bt_conn *conn, u8_t err)
{

    if (err) {
        SYS_LOG_INF("BLE Connection failed (error %u)", err);
    } else {
        SYS_LOG_INF("BLE Connected");
    }

}

static void disconnected(struct bt_conn *conn, u8_t reason)
{
    SYS_LOG_INF("BLE Disconnected (reason %u)", reason);
}

static struct bt_conn_cb conn_callbacks = {
    .connected = connected,
    .disconnected = disconnected,
};

void ble_gatt_init(void)
{

    int err;

    err = bt_enable(NULL);

    if (err) {
        SYS_LOG_INF("BLE Init failed (error %d)", err);
        return;
    }

    dis_init();

    lcs_init();

    bt_conn_cb_register(&conn_callbacks);

    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad),
        sd, ARRAY_SIZE(sd));

    if (err) {
        SYS_LOG_INF("Advertising failed to start (error %d)", err);
        return;
    }

    SYS_LOG_INF("Advertising started");

}
