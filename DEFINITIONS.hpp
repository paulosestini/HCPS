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
#define GRAVITY_FORCE MathUtils::Vector{0.0, 9.80} // Gravity vector

/* --- Space-Time constants --- */
#define UPDATE_DT 1e-3 // Simulation's time step (change to alter simulation precision)
#define CLOCK_DT UPDATE_DT/900000 // Display clock dt (change ONLY for calibration purposes)
#define SPATIAL_SCALE 100.f // Pixels per meter (change to zoom in or out)
// TASK: CALIBRATE THIS NUMBERS

#define CENTER_BOT MathUtils::Vector{BOUND_BOX_POS_X+BOUND_BOX_WIDTH/2-width/2, BOUND_BOX_POS_Y+BOUND_BOX_HEIGHT-height} // Place system centered horizontally and at the bottom of the screen
#define CENTER_TOP MathUtils::Vector{BOUND_BOX_POS_X+BOUND_BOX_WIDTH/2-width/2, 0.0} // Place system centered horizontally and at the top of the screen

