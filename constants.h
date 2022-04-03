#ifndef CONSTANTS_H_SENTRY
#define CONSTANTS_H_SENTRY
#include <FL/Fl.H>

enum obj_types {OBJ_EMPTY, OBJ_BALLOON, OBJ_BUBBLE};
enum directions {TOP_LEFT, TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT, LEFT};
enum moving_states {MOVING_DELETED = -2, MOVING_OK};
enum sizes {S_STRIDE = 20, S_BUTTON_W = 30, S_BUTTON_H = 30};
enum colors {CLR_WIN_BACKGROUND = FL_GRAY, CLR_BTN_EMPTY = FL_CYAN, CLR2_BTN_EMPTY = FL_BLUE};
enum controls_sizes {RB_W = 180, RB_H = 40};
const char* const RB_NAMES[4] = {"Create Bubble", "Create Balloon", "Destroy Bubble", "Destroy Balloon"}; 
enum controls_states {CTRL_CREATE_BUBBLE, CTRL_CREATE_BALLOON, CTRL_DESTROY_BUBBLE, CTRL_DESTROY_BALLOON};

#endif
