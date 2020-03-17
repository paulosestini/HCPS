/* --- Screen --- */

#define SCREEN_WIDTH 800/SPATIAL_SCALE
#define SCREEN_HEIGHT 800/SPATIAL_SCALE

/* --- Boundary box --- */

#define BOUND_BOX_POS_WIDTH SCREEN_WIDTH*0.9
#define BOUND_BOX_POS_HEIGHT SCREEN_HEIGHT*0.95
#define BOUND_BOX_POS_POS_X (SCREEN_WIDTH - BOUND_BOX_POS_WIDTH)/2.0
#define BOUND_BOX_POS_POS_Y 0
#define WALL_VALUE 1.0 // 1->wall absorbs impact, 2->wall reflects impact

/* --- Nodes shapes and colors --- */

#define NODE_SHAPE_RADIUS 1.0
#define NODE_SELECTION_RADIUS 3.0/SPATIAL_SCALE
#define FREE_NODE_COLOR sf::Color::White
#define SLCT_NODE_COLOR sf::Color::Yellow
#define FIXD_NODE_COLOR sf::Color::Red

/* --- Structure constants --- */

#define PARTICLES_Y 20 // How many particles of height the tower will have
#define PARTICLES_X 20 // How many particles of width the tower will have
#define Y_SPACING 10.0/PARTICLES_Y // Vertical spacing between particles in the tower
#define X_SPACING 10.0/PARTICLES_X // Horizontal spacing between particles in the tower
#define FIELD_DISSIPATION 0.0 // Absolute velocity dissipation factor
#define GRAVITY_FORCE MathUtils::Vector{0.0, 9.80*TIME_SCALE*TIME_SCALE} // Gravity vector

/* --- Global physical constants --- */

#define UPDATE_DT 0.0000000000000005f // Simulation's time step (change to alter simulation precision)
#define CLOCK_DT TIME_SCALE*UPDATE_DT/1000000 // Display clock dt (change ONLY for calibration purposes)
#define TIME_SCALE 0.0020/UPDATE_DT // Simulation's speed (change to speed up/down the simulation)
#define SPATIAL_SCALE 50.f // Pixels per meter
// TASK: CALIBRATE THIS NUMBERS

/* --- Structures physical constants --- */

#define BLOCK_DENSITY 100
#define FLUID_DENSITY 100
#define BLOCK_HARDNESS 40
#define BLOCK_INT_FRICCTION 20
#define BLOCK_MAX_DIST_FACTOR_CONSTANT 10 // Structure's factor that multiplies the eqDists and so defines the bond's breaking distance

#define COLLISION_K_CONSTANT 1000*PARTICLES_Y*PARTICLES_Y*TIME_SCALE*TIME_SCALE // Particles collision softness
#define COLLISION_C_CONSTANT 0.01*PARTICLES_Y*TIME_SCALE // Viscosity

#define STRUCTURE_K_CONSTANT ((BLOCK_HARDNESS*BLOCK_DENSITY)*PARTICLES_Y*PARTICLES_Y*TIME_SCALE*TIME_SCALE) // Particles bonding softness
#define STRUCTURE_C_CONSTANT (BLOCK_INT_FRICCTION*PARTICLES_Y*TIME_SCALE) // Structure's internal friction
#define NODE_COLLISION_RADIUS (10.0*NODE_SHAPE_RADIUS/SPATIAL_SCALE)

/* --- Building the structures -- */

#define BUILD_BOX structure.build_RectShape_XGrid(BLOCK_DENSITY, PARTICLES_Y, PARTICLES_X, Y_SPACING, X_SPACING, NODE_COLLISION_RADIUS);
#define BUILD_STRUCTURES BUILD_BOX

// TIP: since this example don't care mush for the particles collision, you can comment particlesCollision(graphics); out in StructureElement.cpp/update