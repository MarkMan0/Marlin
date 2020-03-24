#include "../../../inc/MarlinConfig.h"

#if HAS_TRINAMIC_CONFIG

#include "../../gcode.h"
#include "../../../feature/tmc_util.h"
#include "../../../module/stepper/indirection.h"

void GcodeSuite::M915() {

  home_all_axes();
  soft_endstops_enabled = false;

  constexpr float spd_fast = 10, spd_slow = 1;
  constexpr float z_max = Z_MAX_POS, z_extra = Z_MAX_POS + 10;
  do_blocking_move_to_z(z_max, spd_fast);
  do_blocking_move_to_z(z_extra, spd_slow);
  do_blocking_move_to_z(z_max, spd_fast);

  soft_endstops_enabled = true;
  home_all_axes();

}

#endif
