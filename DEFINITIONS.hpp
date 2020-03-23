#include "Examples/STRUCTURES_DLC.hpp"

/* --- Screen --- */
#define SCREEN_WIDTH 800/SPATIAL_SCALE
#define SCREEN_HEIGHT 800/SPATIAL_SCALE

/* --- Boundary box --- */
#define BOUND_BOX_WIDTH SCREEN_WIDTH*0.5
#define BOUND_BOX_HEIGHT SCREEN_HEIGHT*0.95
#define BOUND_BOX_POS_X (SCREEN_WIDTH - BOUND_BOX_WIDTH)/2.0
#define BOUND_BOX_POS_Y 0
#define WALL_REFLECTION 0.9 // 0->full absortion, 1->full reflection

/* --- Nodes shapes and colors --- */
#define NODE_SHAPE_RADIUS 1.0
#define NODE_SELECTION_RADIUS 3.0/SPATIAL_SCALE
#define FREE_NODE_COLOR sf::Color::White
#define SLCT_NODE_COLOR sf::Color::Yellow
#define FIXD_NODE_COLOR sf::Color::Red

/* --- External forces constants --- */
#define FIELD_DISSIPATION 0.0 // Absolute velocity dissipation factor
#define GRAVITY_FORCE MathUtils::Vector{0.0, 9.80*TIME_SCALE*TIME_SCALE} // Gravity vector

/* --- Space-Time constants --- */
#define UPDATE_DT 5e-16 // Simulation's time step (change to alter simulation precision)
#define CLOCK_DT TIME_SCALE*UPDATE_DT/1000000 // Display clock dt (change ONLY for calibration purposes)
#define TIME_SCALE 0.0020/UPDATE_DT // Simulation's speed (change to speed up/down the simulation)
#define SPATIAL_SCALE 100.f // Pixels per meter (change to zoom in or out)
// TASK: CALIBRATE THIS NUMBERS



