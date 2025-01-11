import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC

from .. import CONF_SOUNDSEND_ID, SoundSendComponent, soundsend_ns

QueryButton = soundsend_ns.class_("QueryButton", button.Button)

CONF_QUERY = "query"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_SOUNDSEND_ID): cv.use_id(SoundSendComponent),
        cv.Optional(CONF_QUERY): button.button_schema(
            QueryButton,
            entity_category=ENTITY_CATEGORY_DIAGNOSTIC,
            icon="mdi:heart-search",
        ),
    }
)


async def to_code(config):
    soundsend_component = await cg.get_variable(config[CONF_SOUNDSEND_ID])

    if query_config := config.get(CONF_QUERY):
        var = await button.new_button(query_config)
        await cg.register_parented(var, soundsend_component)
        cg.add(soundsend_component.set_query_button(var))
