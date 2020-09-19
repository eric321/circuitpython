#include "py/obj.h"

#include "shared-bindings/io_alarm/__init__.h"
#include "shared-bindings/microcontroller/Pin.h"

//| Set Timer Wakeup 
//|
STATIC mp_obj_t io_alarm_pin_state(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args) {  
    enum { ARG_level, ARG_pull };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_level, MP_ARG_INT | MP_ARG_KW_ONLY | MP_ARG_REQUIRED },
        { MP_QSTR_pull, MP_ARG_INT | MP_ARG_KW_ONLY, {.u_bool = false} },
    }; 

    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all(n_args - 1, pos_args + 1, kw_args, MP_ARRAY_SIZE(allowed_args), allowed_args, args);  

    mcu_pin_obj_t *pin = validate_obj_is_pin(pos_args[0]);
    common_hal_io_alarm_pin_state(pin->number, args[ARG_level].u_int, args[ARG_pull].u_bool);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_KW(io_alarm_pin_state_obj, 1, io_alarm_pin_state);

STATIC const mp_rom_map_elem_t io_alarm_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_io_alarm) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_PinState), MP_ROM_PTR(&io_alarm_pin_state_obj) },
};
STATIC MP_DEFINE_CONST_DICT(io_alarm_module_globals, io_alarm_module_globals_table);

const mp_obj_module_t io_alarm_module = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&io_alarm_module_globals,
};
