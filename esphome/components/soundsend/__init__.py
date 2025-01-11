import esphome.codegen as cg
from esphome.components import ble_client
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@masonmilby"]
DEPENDENCIES = ["ble_client"]
MULTI_CONF = True

soundsend_ns = cg.esphome_ns.namespace("soundsend")
SoundSendComponent = soundsend_ns.class_(
    "SoundSendComponent", cg.Component, ble_client.BLEClientNode
)

CONF_SOUNDSEND_ID = "soundsend_id"

CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(SoundSendComponent),
    }
).extend(ble_client.BLE_CLIENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await ble_client.register_ble_node(var, config)
