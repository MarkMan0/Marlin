#include "../../../inc/MarlinConfig.h"

#if HAS_TRINAMIC_CONFIG && ENABLED(TMC_Z_CALIBRATION)

#include "../../gcode.h"
#include "../../../feature/tmc_util.h"
#include "../../../module/stepper/indirection.h"

void GcodeSuite::M915() {

  home_all_axes();
  constexpr uint16_t def_current = TMC_Z_CURRENT;
  constexpr uint16_t def_extra = TMC_Z_EXTRA_HEIGHT;
  constexpr xyz_pos_t pos = TMC_Z_POS;
  constexpr xy_pos_t xyPos = {pos.x, pos.y};
  constexpr float spd_fast = TMC_Z_SPD_MOVE, spd_slow = TMC_Z_SPD_SLOW;
  constexpr float z_after = 20;
  constexpr float spd_raise = 10;

  const uint16_t current = parser.ushortval('S', def_current);
  const uint16_t extra = parser.ushortval('Z', def_extra);

  const uint16_t old_current = stepperZ.rms_current();
  soft_endstops_enabled = false;
  const float cal_point = pos[Z_AXIS] - extra;

  do_blocking_move_to_xy_z(xyPos, pos.z, spd_fast);
  stepperZ.rms_current(current);
  do_blocking_move_to_z(cal_point, spd_slow);
  planner.synchronize();
  stepperZ.rms_current(old_current);
  do_blocking_move_to_z(z_after, spd_raise);


  soft_endstops_enabled = true;
  process_subcommands_now_P(PSTR("G28 Z"));


}

#endif
