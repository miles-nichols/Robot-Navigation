double move_forward(oi_t * sensor, double millimeters);

void turn_clockwise(oi_t * sensor, double degrees);

void turn_counterclockwise(oi_t * sensor, double degrees);

void move_backward(oi_t * sensor, double millimeters);

void handleCollisionLeft(oi_t * sensor);

void handleCollisionRight(oi_t * sensor);

void travel(oi_t * sensor, double millimeters);

void putty(char * pointer);
