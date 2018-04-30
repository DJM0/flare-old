#include <zephyr.h>
#include <bluetooth/gatt.h>
#include <logging/sys_log.h>

#include "lcs.h"

// Lighting control service (8034A02C-93B8-4C87-ADED-A309826E2200)
struct bt_uuid_128 uuid_lcs = BT_UUID_INIT_128(
    0x00, 0x22, 0x6E, 0x82, 0x09, 0xA3, 0xED, 0xAD,
    0x87, 0x4C, 0xB8, 0x93, 0x2C, 0xA0, 0x34, 0x80);

// Power characteristic

// 8034A02C-93B8-4C87-ADED-A309826E2201
static struct bt_uuid_128 uuid_lcs_power = BT_UUID_INIT_128(
    0x01, 0x22, 0x6E, 0x82, 0x09, 0xA3, 0xED, 0xAD,
    0x87, 0x4C, 0xB8, 0x93, 0x2C, 0xA0, 0x34, 0x80);

static u8_t power[1];

static ssize_t read_power(struct bt_conn *conn, const struct bt_gatt_attr *attr,
    void *buf, u16_t len, u16_t offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
        sizeof(power));
}

static ssize_t write_power(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, const void *buf, u16_t len,
    u16_t offset, u8_t flags)
{
    u8_t *value = attr->user_data;

    if (offset + len > sizeof(power)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    memcpy(value + offset, buf, len);

    return len;
}

// Lightness characteristic

// 8034A02C-93B8-4C87-ADED-A309826E2202
static struct bt_uuid_128 uuid_lcs_lightness = BT_UUID_INIT_128(
    0x02, 0x22, 0x6E, 0x82, 0x09, 0xA3, 0xED, 0xAD,
    0x87, 0x4C, 0xB8, 0x93, 0x2C, 0xA0, 0x34, 0x80);

static u16_t lightness[1];

static ssize_t read_lightness(struct bt_conn *conn, const struct bt_gatt_attr *attr,
    void *buf, u16_t len, u16_t offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
        sizeof(lightness));
}

static ssize_t write_lightness(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, const void *buf, u16_t len,
    u16_t offset, u8_t flags)
{
    u8_t *value = attr->user_data;

    if (offset + len > sizeof(lightness)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    memcpy(value + offset, buf, len);

    return len;
}

// Temperature characteristic

// 8034A02C-93B8-4C87-ADED-A309826E2203
static struct bt_uuid_128 uuid_lcs_temperature = BT_UUID_INIT_128(
    0x03, 0x22, 0x6E, 0x82, 0x09, 0xA3, 0xED, 0xAD,
    0x87, 0x4C, 0xB8, 0x93, 0x2C, 0xA0, 0x34, 0x80);

static u16_t temperature[1];

static ssize_t read_temperature(struct bt_conn *conn, const struct bt_gatt_attr *attr,
    void *buf, u16_t len, u16_t offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
        sizeof(temperature));
}

static ssize_t write_temperature(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, const void *buf, u16_t len,
    u16_t offset, u8_t flags)
{
    u8_t *value = attr->user_data;

    if (offset + len > sizeof(temperature)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    memcpy(value + offset, buf, len);

    return len;
}

// Colour characteristic (24-bit RGB)

// 8034A02C-93B8-4C87-ADED-A309826E2204
static struct bt_uuid_128 uuid_lcs_colour = BT_UUID_INIT_128(
    0x04, 0x22, 0x6E, 0x82, 0x09, 0xA3, 0xED, 0xAD,
    0x87, 0x4C, 0xB8, 0x93, 0x2C, 0xA0, 0x34, 0x80);

static u8_t colour[3];

static ssize_t read_colour(struct bt_conn *conn, const struct bt_gatt_attr *attr,
    void *buf, u16_t len, u16_t offset)
{
    const char *value = attr->user_data;
    return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
        sizeof(colour));
}

static ssize_t write_colour(struct bt_conn *conn,
    const struct bt_gatt_attr *attr, const void *buf, u16_t len,
    u16_t offset, u8_t flags)
{
    u8_t *value = attr->user_data;

    if (offset + len > sizeof(colour)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
    }

    memcpy(value + offset, buf, len);

    return len;
}

// Lighting control service

static struct bt_gatt_attr attrs[] = {
    BT_GATT_PRIMARY_SERVICE(&uuid_lcs),
    BT_GATT_CHARACTERISTIC(&uuid_lcs_power.uuid,
        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_WRITE),
    BT_GATT_DESCRIPTOR(&uuid_lcs_power.uuid,
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE, read_power, write_power, power),
    BT_GATT_CHARACTERISTIC(&uuid_lcs_lightness.uuid,
        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_WRITE),
    BT_GATT_DESCRIPTOR(&uuid_lcs_lightness.uuid,
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE, read_lightness, write_lightness, lightness),
    BT_GATT_CHARACTERISTIC(&uuid_lcs_temperature.uuid,
        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_WRITE),
    BT_GATT_DESCRIPTOR(&uuid_lcs_temperature.uuid,
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE, read_temperature, write_temperature, temperature),
    BT_GATT_CHARACTERISTIC(&uuid_lcs_colour.uuid,
        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_WRITE),
    BT_GATT_DESCRIPTOR(&uuid_lcs_colour.uuid,
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE, read_colour, write_colour, colour),
};

static struct bt_gatt_service lcs_svc = BT_GATT_SERVICE(attrs);

void lcs_init(void)
{
    bt_gatt_service_register(&lcs_svc);
}
