import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_CONFIG, UNIT_MILLISECOND, UNIT_PERCENT

from .. import CONF_SOUNDSEND_ID, SoundSendComponent, soundsend_ns

VolumeNumber = soundsend_ns.class_("VolumeNumber", number.Number)
LipSyncNumber = soundsend_ns.class_("LipSyncNumber", number.Number)
EqHighNumber = soundsend_ns.class_("EqHighNumber", number.Number)
EqMidRangeNumber = soundsend_ns.class_("EqMidRangeNumber", number.Number)
EqVoiceNumber = soundsend_ns.class_("EqVoiceNumber", number.Number)
EqMidBassNumber = soundsend_ns.class_("EqMidBassNumber", number.Number)
EqSubNumber = soundsend_ns.class_("EqSubNumber", number.Number)

TrimFrontLeftNumber = soundsend_ns.class_("TrimFrontLeftNumber", number.Number)
TrimFrontRightNumber = soundsend_ns.class_("TrimFrontRightNumber", number.Number)
TrimCenterNumber = soundsend_ns.class_("TrimCenterNumber", number.Number)
TrimSubwooferNumber = soundsend_ns.class_("TrimSubwooferNumber", number.Number)
TrimSurroundLeftNumber = soundsend_ns.class_("TrimSurroundLeftNumber", number.Number)
TrimSurroundRightNumber = soundsend_ns.class_("TrimSurroundRightNumber", number.Number)

CONF_VOLUME = "volume"
CONF_LIP_SYNC = "lip_sync"
CONF_EQ_HIGH = "eq_high"
CONF_EQ_MID_RANGE = "eq_mid_range"
CONF_EQ_VOICE = "eq_voice"
CONF_EQ_MID_BASS = "eq_mid_bass"
CONF_EQ_SUB = "eq_sub"

CONF_TRIM_FRONT_LEFT = "trim_front_left"
CONF_TRIM_FRONT_RIGHT = "trim_front_right"
CONF_TRIM_CENTER = "trim_center"
CONF_TRIM_SUBWOOFER = "trim_subwoofer"
CONF_TRIM_SURROUND_LEFT = "trim_surround_left"
CONF_TRIM_SURROUND_RIGHT = "trim_surround_right"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_SOUNDSEND_ID): cv.use_id(SoundSendComponent),
        cv.Optional(CONF_VOLUME): number.number_schema(
            VolumeNumber,
            unit_of_measurement=UNIT_PERCENT,
            icon="mdi:volume-high",
        ),
        cv.Optional(CONF_LIP_SYNC): number.number_schema(
            LipSyncNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            unit_of_measurement=UNIT_MILLISECOND,
            icon="mdi:timer-music",
        ),
        cv.Optional(CONF_EQ_HIGH): number.number_schema(
            EqHighNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:cosine-wave",
        ),
        cv.Optional(CONF_EQ_MID_RANGE): number.number_schema(
            EqMidRangeNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:cosine-wave",
        ),
        cv.Optional(CONF_EQ_VOICE): number.number_schema(
            EqVoiceNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:cosine-wave",
        ),
        cv.Optional(CONF_EQ_MID_BASS): number.number_schema(
            EqMidBassNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:cosine-wave",
        ),
        cv.Optional(CONF_EQ_SUB): number.number_schema(
            EqSubNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:cosine-wave",
        ),
        cv.Optional(CONF_TRIM_FRONT_LEFT): number.number_schema(
            TrimFrontLeftNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:knob",
        ),
        cv.Optional(CONF_TRIM_FRONT_RIGHT): number.number_schema(
            TrimFrontRightNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:knob",
        ),
        cv.Optional(CONF_TRIM_CENTER): number.number_schema(
            TrimCenterNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:knob",
        ),
        cv.Optional(CONF_TRIM_SUBWOOFER): number.number_schema(
            TrimSubwooferNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:knob",
        ),
        cv.Optional(CONF_TRIM_SURROUND_LEFT): number.number_schema(
            TrimSurroundLeftNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:knob",
        ),
        cv.Optional(CONF_TRIM_SURROUND_RIGHT): number.number_schema(
            TrimSurroundRightNumber,
            entity_category=ENTITY_CATEGORY_CONFIG,
            icon="mdi:knob",
        ),
    }
)


async def to_code(config):
    soundsend_component = await cg.get_variable(config[CONF_SOUNDSEND_ID])

    if volume_config := config.get(CONF_VOLUME):
        var = await number.new_number(
            volume_config,
            min_value=0,
            max_value=100,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_volume_number(var))

    if lip_sync_config := config.get(CONF_LIP_SYNC):
        var = await number.new_number(
            lip_sync_config,
            min_value=0,
            max_value=200,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_lip_sync_number(var))

    if eq_high_config := config.get(CONF_EQ_HIGH):
        var = await number.new_number(
            eq_high_config,
            min_value=-6,
            max_value=6,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_eq_high_number(var))

    if eq_mid_range_config := config.get(CONF_EQ_MID_RANGE):
        var = await number.new_number(
            eq_mid_range_config,
            min_value=-6,
            max_value=6,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_eq_mid_range_number(var))

    if eq_voice_config := config.get(CONF_EQ_VOICE):
        var = await number.new_number(
            eq_voice_config,
            min_value=-6,
            max_value=6,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_eq_voice_number(var))

    if eq_mid_bass_config := config.get(CONF_EQ_MID_BASS):
        var = await number.new_number(
            eq_mid_bass_config,
            min_value=-6,
            max_value=6,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_eq_mid_bass_number(var))

    if eq_sub_config := config.get(CONF_EQ_SUB):
        var = await number.new_number(
            eq_sub_config,
            min_value=-6,
            max_value=6,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_eq_sub_number(var))

    if trim_front_left_config := config.get(CONF_TRIM_FRONT_LEFT):
        var = await number.new_number(
            trim_front_left_config,
            min_value=-12,
            max_value=5,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_trim_front_left_number(var))

    if trim_front_right_config := config.get(CONF_TRIM_FRONT_RIGHT):
        var = await number.new_number(
            trim_front_right_config,
            min_value=-12,
            max_value=5,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_trim_front_right_number(var))

    if trim_center_config := config.get(CONF_TRIM_CENTER):
        var = await number.new_number(
            trim_center_config,
            min_value=-12,
            max_value=5,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_trim_center_number(var))

    if trim_subwoofer_config := config.get(CONF_TRIM_SUBWOOFER):
        var = await number.new_number(
            trim_subwoofer_config,
            min_value=-12,
            max_value=5,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_trim_subwoofer_number(var))

    if trim_surround_left_config := config.get(CONF_TRIM_SURROUND_LEFT):
        var = await number.new_number(
            trim_surround_left_config,
            min_value=-12,
            max_value=5,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_trim_surround_left_number(var))

    if trim_surround_right_config := config.get(CONF_TRIM_SURROUND_RIGHT):
        var = await number.new_number(
            trim_surround_right_config,
            min_value=-12,
            max_value=5,
            step=1,
        )
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_trim_surround_right_number(var))
