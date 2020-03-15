/* --- Screen --- */

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

/* --- Boundary box --- */

#define BOUND_BOX_POS_WIDTH SCREEN_WIDTH*0.9
#define BOUND_BOX_POS_HEIGHT SCREEN_HEIGHT*0.95
#define BOUND_BOX_POS_POS_X (SCREEN_WIDTH - BOUND_BOX_POS_WIDTH)/2.f
#define BOUND_BOX_POS_POS_Y 0

/* --- Nodes shapes and colors --- */

#define NODE_RADIUS 3
#define FREE_NODE_COLOR sf::Color::White
#define SLCT_NODE_COLOR sf::Color::Yellow
#define FIXD_NODE_COLOR sf::Color::Red

/* --- Force line shape and color --- */

#define EXTERNAL_FORCE_LINE_SIZE sf::Vector2f(100, 5)
#define EXTERNAL_FORCE_LINE_COLOR sf::Color::White

/* --- Structure constants --- */

#define PARTICLES_Y 20 // How many particles of height the tower will have
#define PARTICLES_X 20
#define Y_SPACING 10.f/PARTICLES_Y // Vertical spacing between particles in the tower
#define X_SPACING 10.f/PARTICLES_X
#define FIELD_DISSIPATION 0.f
#define GRAVITY_FORCE MathUtils::Vector{0.f, 9.8f*TIME_SCALE*TIME_SCALE}

/* --- Phisical constants --- */

#define SPATIAL_SCALE 50.f // Pixels per meter
#define UPDATE_DT 0.0000000000000005f // Simulation's time step (change to alter simulation precision)
#define TIME_SCALE 0.002f/UPDATE_DT // Simulation's speed (change to speed up/down the simulation)
#define CLOCK_DT TIME_SCALE*UPDATE_DT/1000000 // Display clock dt (change ONLY for calibration purposes)
// OBSERVATION: THIS NUMBERS WERE DETERMINED BY EXPERIMENTATION
// TASK: DETERMINE THIS NUMBERS WITH A BETTER METHOD