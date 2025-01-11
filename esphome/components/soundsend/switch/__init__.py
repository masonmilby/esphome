import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_CONFIG, ENTITY_CATEGORY_DIAGNOSTIC

from .. import CONF_SOUNDSEND_ID, SoundSendComponent, soundsend_ns

MuteSwitch = soundsend_ns.class_("MuteSwitch", switch.Switch)
PowerSwitch = soundsend_ns.class_("PowerSwitch", switch.Switch)
VirtualDolbySwitch = soundsend_ns.class_("VirtualDolbySwitch", switch.Switch)
BassManagementSwitch = soundsend_ns.class_("BassManagementSwitch", switch.Switch)

CONF_MUTE = "mute"
CONF_POWER = "power"
CONF_VIRTUAL_DOLBY = "virtual_dolby"
CONF_BASS_MANAGEMENT = "bass_management"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_SOUNDSEND_ID): cv.use_id(SoundSendComponent),
        cv.Optional(CONF_MUTE): switch.switch_schema(
            MuteSwitch,
            block_inverted=True,
            icon="mdi:volume-mute",
        ),
        cv.Optional(CONF_POWER): switch.switch_schema(
            PowerSwitch,
            block_inverted=True,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            icon="mdi:power",
        ),
        cv.Optional(CONF_VIRTUAL_DOLBY): switch.switch_schema(
            VirtualDolbySwitch,
            block_inverted=True,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:surround-sound",
        ),
        cv.Optional(CONF_BASS_MANAGEMENT): switch.switch_schema(
            BassManagementSwitch,
            block_inverted=True,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:volume-vibrate",
        ),
    }
)


async def to_code(config):
    soundsend_component = await cg.get_variable(config[CONF_SOUNDSEND_ID])

    if mute_config := config.get(CONF_MUTE):
        var = await switch.new_switch(mute_config)
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_mute_switch(var))

    if power_config := config.get(CONF_POWER):
        var = await switch.new_switch(power_config)
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_power_switch(var))

    if virtual_dolby_config := config.get(CONF_VIRTUAL_DOLBY):
        var = await switch.new_switch(virtual_dolby_config)
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_virtual_dolby_switch(var))

    if bass_management_config := config.get(CONF_BASS_MANAGEMENT):
        var = await switch.new_switch(bass_management_config)
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_bass_management_switch(var))
