#include "vex.h"

using namespace vex;

// Robot configuration code.
brain Brain;

//There's so many motors :,)

motor DrivetrainLeft1 = motor(PORT8, ratio18_1, false);
motor DrivetrainLeft2 = motor(PORT9, ratio18_1, false);
motor DrivetrainLeft3 = motor(PORT10, ratio18_1, false);
motor DrivetrainRight1 = motor(PORT1, ratio18_1, false);
motor DrivetrainRight2 = motor(PORT2, ratio18_1, false);
motor DrivetrainRight3 = motor(PORT3, ratio18_1, false);
motor_group DrivetrainLeft = motor_group(DrivetrainLeft1, DrivetrainLeft2, DrivetrainLeft3);
motor_group DrivetrainRight = motor_group(DrivetrainRight1, DrivetrainRight2, DrivetrainRight3);

motor IntakeMotor = motor(PORT20, ratio18_1, false);

controller Controller1 = controller(primary);

void controller_R1_Pressed() {
  IntakeMotor.spin(forward);
  while (Controller1.ButtonR1.pressing()) {
    wait(5, msec);
  }
  IntakeMotor.stop();
}

void controller_R2_Pressed() {
  IntakeMotor.spin(reverse);
  while (Controller1.ButtonR2.pressing()) {
    wait(5, msec);
  }
  IntakeMotor.stop();
}

int main() {
  Controller1.ButtonR1.pressed(controller_R1_Pressed);
  Controller1.ButtonR2.pressed(controller_R2_Pressed);
  wait(5, msec);
  
  IntakeMotor.setStopping(hold);
  IntakeMotor.setVelocity(100, percent);

  // Main Controller loop to set motors to controller axis postiions
  while(true){

    DrivetrainLeft.setVelocity(
      Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent), 
      percent
    );
    DrivetrainRight.setVelocity(
      Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent), 
      percent
    );

    DrivetrainLeft.spin(reverse);
    DrivetrainRight.spin(forward);

    wait(5, msec);
  }
}
