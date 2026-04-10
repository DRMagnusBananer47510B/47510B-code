#pragma once

#include "autons.hpp"

void auton_selector_initialize();
void auton_selector_show();
void auton_selector_run_selected();
const AutonEntry& auton_selector_selected();
bool auton_selector_is_active();
