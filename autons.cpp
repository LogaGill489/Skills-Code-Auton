#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



//runs first offical skills test code
void skills_test() 
{
//speed of how long we spin each roller for
int rollerTime = 400;

//resets catapult position
//runs cata
catapult = 110;

//waits for limit switch to be pressed
while (limitSwitch.get_value() >= 4095) {
  pros::delay(2);
}

//stops cata
catapult = 0;

//drives into motor
chassis.set_drive_pid(-4, DRIVE_SPEED, true);
chassis.wait_drive();

//spins roller
intake = 127;
pros::delay(rollerTime);
intake = 0;

//drives away from motor
chassis.set_drive_pid(12, DRIVE_SPEED, true);
chassis.wait_drive();

//rotates to be in line with disk
chassis.set_turn_pid(130, TURN_SPEED);
chassis.wait_drive();

//starts intake
intake = 127;

//drives forward, picking up disk
chassis.set_drive_pid(-16, DRIVE_SPEED, true);
chassis.wait_drive();

//stops intake after disk has been secured
intake = 0;

//alligns with second roller
chassis.set_turn_pid(90, TURN_SPEED);
chassis.wait_drive();

//drives at second roller
chassis.set_drive_pid(-10, DRIVE_SPEED, true);
chassis.wait_drive();

//spins roller
intake = 127;
pros::delay(rollerTime);
intake = 0;

//backs away from second roller
chassis.set_drive_pid(10, DRIVE_SPEED, true);
chassis.wait_drive();

//alligns with goal
chassis.set_turn_pid(0, TURN_SPEED);
chassis.wait_drive();

//drives to goal
chassis.set_drive_pid(50, DRIVE_SPEED, true);
chassis.wait_drive();

//shoots and resets catapult position
//runs cata
catapult = 110;
pros::delay(10);

//waits for limit switch to be pressed
while (limitSwitch.get_value() >= 4095) {
  pros::delay(2);
}

//stops cata
catapult = 0;

//drives backwards
chassis.set_drive_pid(-4, DRIVE_SPEED, true);
chassis.wait_drive();

//resets shot position
chassis.set_turn_pid(-40, TURN_SPEED);
chassis.wait_drive();

//turns on intake
intake = 127;

//drives backwards
chassis.set_drive_pid(-26, DRIVE_SPEED, true);
chassis.wait_drive();

//turns off intake
intake = 0;

//resets position to be in line with disks
chassis.set_turn_pid(-135, TURN_SPEED);
chassis.wait_drive();

//turns on intake
intake = 127;

//drives at disks
chassis.set_drive_pid(-34, DRIVE_SPEED, true);
chassis.wait_drive();

//turns off intake
intake = 0;

//aligns for shot position
chassis.set_turn_pid(315, TURN_SPEED);
chassis.wait_drive();

//drives to corner of scoring box for shot
chassis.set_drive_pid(12, DRIVE_SPEED, true);
chassis.wait_drive();

//shoots and resets catapult position
//runs cata
catapult = 110;
pros::delay(10);

//waits for limit switch to be pressed
while (limitSwitch.get_value() >= 4095) {
  pros::delay(2);
}

//stops cata
catapult = 0;

//drives back to line
chassis.set_drive_pid(-12, DRIVE_SPEED, true);
chassis.wait_drive();

//resets position to be in line with disks
chassis.set_turn_pid(-135, TURN_SPEED);
chassis.wait_drive();

//drives at 3 stack
chassis.set_drive_pid(-20, DRIVE_SPEED, true);
chassis.wait_drive();

//turn on intake and slow bot
intake = 127;
DRIVE_SPEED = 90;

//collect 3 stack
chassis.set_drive_pid(-10, DRIVE_SPEED, true);
chassis.wait_drive();

//turn off intake and reset bot speed
intake = 0;
DRIVE_SPEED = 110;

//resets position to be in line with wall
chassis.set_turn_pid(0, TURN_SPEED);
chassis.wait_drive();

//drive to just before wall
chassis.set_drive_pid(5, DRIVE_SPEED, true);
chassis.wait_drive();

//align to shoot at net
chassis.set_turn_pid(-270, TURN_SPEED);
chassis.wait_drive();

//drive to net
chassis.set_drive_pid(45, DRIVE_SPEED, true);
chassis.wait_drive();

//align to shoot at net
chassis.set_turn_pid(-265, TURN_SPEED);
chassis.wait_drive();

//shoots and resets catapult position
//runs cata
catapult = 110;
pros::delay(10);

//waits for limit switch to be pressed
while (limitSwitch.get_value() >= 4095) {
  pros::delay(2);
}

//align for backwards drive
chassis.set_turn_pid(-270, TURN_SPEED);
chassis.wait_drive();

//stops cata
catapult = 0;

//drive to align with roller
chassis.set_drive_pid(-50, DRIVE_SPEED, true);
chassis.wait_drive();

//align with roller
chassis.set_turn_pid(180, TURN_SPEED);
chassis.wait_drive();

//drive to roller
chassis.set_drive_pid(-10, DRIVE_SPEED, true);
chassis.wait_drive();

//spins roller
intake = 127;
pros::delay(rollerTime);
intake = 0;

//drive slightly back from roller
chassis.set_drive_pid(4, DRIVE_SPEED, true);
chassis.wait_drive();

//adjust to drive up to three stack
chassis.set_turn_pid(-200, TURN_SPEED);
chassis.wait_drive();

//drive slightly up to aling with three stack
chassis.set_drive_pid(6, DRIVE_SPEED, true);
chassis.wait_drive();

//adjust to drive up to three stack
chassis.set_turn_pid(0, TURN_SPEED);
chassis.wait_drive();

//drive slightly up to aling with three stack
chassis.set_drive_pid(-16, DRIVE_SPEED, true);
chassis.wait_drive();

//turn on intake and slow bot
intake = 127;
DRIVE_SPEED = 90;

//collect 3 stack
chassis.set_drive_pid(-10, DRIVE_SPEED, true);
chassis.wait_drive();

//turn off intake and reset bot speed
intake = 0;
DRIVE_SPEED = 110;

//back up to be in line with 4th roller
chassis.set_drive_pid(16, DRIVE_SPEED, true);
chassis.wait_drive();

//adjust to drive up to three stack
chassis.set_turn_pid(-270, TURN_SPEED);
chassis.wait_drive();

//drive to 4th roller
chassis.set_drive_pid(-16, DRIVE_SPEED, true);
chassis.wait_drive();

//spins roller
intake = 127;
pros::delay(rollerTime);
intake = 0;


//PART B
//REPEAT OF PART A MOSTLY BUT IN REVERSE


//backs away from second roller
chassis.set_drive_pid(10, DRIVE_SPEED, true);
chassis.wait_drive();

//alligns with goal
chassis.set_turn_pid(180, TURN_SPEED);
chassis.wait_drive();

//drives to goal
chassis.set_drive_pid(50, DRIVE_SPEED, true);
chassis.wait_drive();

//shoots and resets catapult position
//runs cata
catapult = 110;
pros::delay(10);

//waits for limit switch to be pressed
while (limitSwitch.get_value() >= 4095) {
  pros::delay(2);
}

//stops cata
catapult = 0;

//drives backwards
chassis.set_drive_pid(-4, DRIVE_SPEED, true);
chassis.wait_drive();

//resets shot position
chassis.set_turn_pid(130, TURN_SPEED);
chassis.wait_drive();

//turns on intake
intake = 127;

//drives backwards
chassis.set_drive_pid(-26, DRIVE_SPEED, true);
chassis.wait_drive();

//turns off intake
intake = 0;

//resets position to be in line with disks
chassis.set_turn_pid(45, TURN_SPEED);
chassis.wait_drive();

//turns on intake
intake = 127;

//drives at disks
chassis.set_drive_pid(-34, DRIVE_SPEED, true);
chassis.wait_drive();

//turns off intake
intake = 0;

//aligns for shot position
chassis.set_turn_pid(135, TURN_SPEED);
chassis.wait_drive();

//drives to corner of scoring box for shot
chassis.set_drive_pid(12, DRIVE_SPEED, true);
chassis.wait_drive();

//shoots and resets catapult position
//runs cata
catapult = 110;
pros::delay(10);

//waits for limit switch to be pressed
while (limitSwitch.get_value() >= 4095) {
  pros::delay(2);
}

//stops cata
catapult = 0;

//drives back to line
chassis.set_drive_pid(-12, DRIVE_SPEED, true);
chassis.wait_drive();

//resets position to be in line with disks
chassis.set_turn_pid(45, TURN_SPEED);
chassis.wait_drive();

//drives at 3 stack
chassis.set_drive_pid(-20, DRIVE_SPEED, true);
chassis.wait_drive();

//turn on intake and slow bot
intake = 127;
DRIVE_SPEED = 90;

//collect 3 stack
chassis.set_drive_pid(-10, DRIVE_SPEED, true);
chassis.wait_drive();

//turn off intake and reset bot speed
intake = 0;
DRIVE_SPEED = 110;

//resets position to be in line with wall
chassis.set_turn_pid(0, TURN_SPEED);
chassis.wait_drive();

//drive to just before wall
chassis.set_drive_pid(5, DRIVE_SPEED, true);
chassis.wait_drive();

//align to shoot at net
chassis.set_turn_pid(90, TURN_SPEED);
chassis.wait_drive();

//drive to net
chassis.set_drive_pid(45, DRIVE_SPEED, true);
chassis.wait_drive();

//align to shoot at net
chassis.set_turn_pid(86, TURN_SPEED);
chassis.wait_drive();

//shoots and resets catapult position
//runs cata
catapult = 110;
pros::delay(10);

//waits for limit switch to be pressed
while (limitSwitch.get_value() >= 4095) {
  pros::delay(2);
}

//align for backwards drive
chassis.set_turn_pid(90, TURN_SPEED);
chassis.wait_drive();

//stops cata
catapult = 0;

//drive to first roller
chassis.set_drive_pid(-55, DRIVE_SPEED, true);
chassis.wait_drive();

//rotates to adjust line
chassis.set_turn_pid(130, TURN_SPEED);
chassis.wait_drive();

//drives to pneumatic launch location
chassis.set_drive_pid(8, DRIVE_SPEED, true);
chassis.wait_drive();

//rotates to launch
chassis.set_turn_pid(45, TURN_SPEED);
chassis.wait_drive();

//launches endgame
endgameLeft.set_value(true);
endgameRight.set_value(true);

//sticks auton in while loop as long as skills is still running as to not repeat
while (true) {
  pros::delay(20);
}
}


//for Nate & Derick
//add ingame auton into here and adjust it to this auton function on the brain screen by pressing the left and right squares
//uses the skills auton as a template, and work with Aubrey (or just leave it and I'll make later idrc)
void ingame_auton() {

}