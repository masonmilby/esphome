import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC

from . import CONF_SOUNDSEND_ID, SoundSendComponent

CONF_MODULE_VERSIONS = "module_versions"
CONF_AUDIO_FORMAT = "audio_format"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_SOUNDSEND_ID): cv.use_id(SoundSendComponent),
        cv.Optional(CONF_MODULE_VERSIONS): text_sensor.text_sensor_schema(
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            icon="mdi:source-branch",
        ),
        cv.Optional(CONF_AUDIO_FORMAT): text_sensor.text_sensor_schema(
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            icon="mdi:audio-video",
        ),
    }
)


async def to_code(config):
    soundsend_component = await cg.get_variable(config[CONF_SOUNDSEND_ID])

    if module_versions_config := config.get(CONF_MODULE_VERSIONS):
        var = await text_sensor.new_text_sensor(module_versions_config)
        cg.add(soundsend_component.set_module_versions_text_sensor(var))

    if audio_format_config := config.get(CONF_AUDIO_FORMAT):
        var = await text_sensor.new_text_sensor(audio_format_config)
        cg.add(soundsend_component.set_audio_format_text_sensor(var))
