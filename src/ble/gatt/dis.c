#include <zephyr.h>
#include <bluetooth/gatt.h>

#include "dis.h"

static const char *dis_software_revision = GIT_COMMIT_HASH " - " GIT_BRANCH;
static const char *dis_hardware_revision = CONFIG_SOC;

static ssize_t read_software_revision(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, void *buf, u16_t len, u16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
        dis_software_revision, strlen(dis_software_revision));
}

static ssize_t read_hardware_revision(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, void *buf, u16_t len, u16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
        dis_hardware_revision, strlen(dis_hardware_revision));
}

// Service declaration

static struct bt_gatt_attr attrs[] = {
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DIS),
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_HARDWARE_REVISION, BT_GATT_CHRC_READ),
    BT_GATT_DESCRIPTOR(BT_UUID_DIS_HARDWARE_REVISION, BT_GATT_PERM_READ,
        read_hardware_revision, NULL, NULL),
    BT_GATT_CHARACTERISTIC(BT_UUID_DIS_SOFTWARE_REVISION, BT_GATT_CHRC_READ),
    BT_GATT_DESCRIPTOR(BT_UUID_DIS_SOFTWARE_REVISION, BT_GATT_PERM_READ,
        read_software_revision, NULL, NULL),
};

static struct bt_gatt_service dis_svc = BT_GATT_SERVICE(attrs);

void dis_init(void)
{
    bt_gatt_service_register(&dis_svc);
}
