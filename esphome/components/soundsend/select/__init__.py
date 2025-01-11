import esphome.codegen as cg
from esphome.components import select
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_CONFIG

from .. import CONF_SOUNDSEND_ID, SoundSendComponent, soundsend_ns

AudioSourceSelect = soundsend_ns.enum("AudioSourceSelect", select.Select)
AudioModeSelect = soundsend_ns.enum("AudioModeSelect", select.Select)

CONF_AUDIO_SOURCE = "audio_source"
CONF_AUDIO_MODE = "audio_mode"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_SOUNDSEND_ID): cv.use_id(SoundSendComponent),
        cv.Optional(CONF_AUDIO_SOURCE): select.select_schema(
            AudioSourceSelect,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:audio-input-stereo-minijack",
        ),
        cv.Optional(CONF_AUDIO_MODE): select.select_schema(
            AudioModeSelect,
            icon="mdi:waveform",
        ),
    }
)


async def to_code(config):
    soundsend_component = await cg.get_variable(config[CONF_SOUNDSEND_ID])

    if audio_source_config := config.get(CONF_AUDIO_SOURCE):
        var = await select.new_select(
            audio_source_config,
            options=["HDMI ARC/eARC", "Optical"],
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_audio_source_select(var))

    if audio_mode_config := config.get(CONF_AUDIO_MODE):
        var = await select.new_select(
            audio_mode_config,
            options=["Direct", "Movie", "Music", "Night"],
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_audio_mode_select(var))
