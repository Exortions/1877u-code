#include "main.h"

const int LEFT_FRONT_MOTOR_PORT = 1;
const int LEFT_MIDDLE_MOTOR_PORT = 2;
const int LEFT_BACK_MOTOR_PORT = 3;
const int RIGHT_FRONT_MOTOR_PORT = 4;
const int RIGHT_MIDDLE_MOTOR_PORT = 5;
const int RIGHT_BACK_MOTOR_PORT = 6;
const int INDEXER_PORT = 'A';
const int SHOOTER_PORT = 7;
const int INTAKE_PORT = 8;
const int IMU_PORT = 9;

int shooterSpeed = 100;
int intakeSpeed = 100;

Controller controller;

ControllerButton runAutonomousButton(ControllerDigital::Y);
ControllerButton intakeOutButton(ControllerDigital::L2);
ControllerButton intakeInButton(ControllerDigital::L1);
ControllerButton flywheelButton(ControllerDigital::R1);
ControllerButton shooterButton(ControllerDigital::R2);

Motor leftFrontMotor(LEFT_FRONT_MOTOR_PORT);
Motor leftMiddleMotor(LEFT_MIDDLE_MOTOR_PORT);
Motor leftBackMotor(LEFT_BACK_MOTOR_PORT);
Motor rightFrontMotor(RIGHT_FRONT_MOTOR_PORT);
Motor rightMiddleMotor(RIGHT_MIDDLE_MOTOR_PORT);
Motor rightBackMotor(RIGHT_BACK_MOTOR_PORT);
Motor shooterMotor(SHOOTER_PORT);
Motor intakeMotor(INTAKE_PORT);

pros::ADIDigitalOut indexer(INDEXER_PORT);

std::map<std::string, Motor> MOTORS {
	{"leftFront", leftFrontMotor},
	{"leftMiddle", leftMiddleMotor},
	{"leftBack", leftBackMotor},
	{"rightFront", rightFrontMotor},
	{"rightMiddle", rightMiddleMotor},
	{"rightBack", rightBackMotor},
	{"shooter", shooterMotor},
	{"intake", intakeMotor}
};

auto drive = ChassisControllerBuilder()
	.withMotors({MOTORS["leftFront"], MOTORS["leftMiddle"], MOTORS["leftBack"]}, {MOTORS["rightFront"], MOTORS["rightMiddle"], MOTORS["rightBack"]})
	.withGains(
		{0.002, 0, 0.0001}, // Distance controller gains
		{0.002, 0, 0.0001}, // Turn controller gains
		{0.002, 0, 0.0001}  // Angle controller gains (helps drive straight)
	)
	.withDimensions(AbstractMotor::gearset::green, {{4_in, 12.5_in}, imev5GreenTPR})
	.build();

pros::Imu imu(IMU_PORT);

auto intakeController = AsyncVelControllerBuilder()
	.withMotor(MOTORS["intake"])
	.build();

auto shooterController = AsyncVelControllerBuilder()
	.withMotor(MOTORS["shooter"])
	.build();

auto slowDrive = AsyncMotionProfileControllerBuilder()
	.withLimits({
		0.1, // Maximum linear velocity of the Chassis in m/s
		0.3, // Maximum linear acceleration of the Chassis in m/s/s
		5.0 // Maximum linear jerk of the Chassis in m/s/s/s
	})
	.withOutput(drive)
	.buildMotionProfileController();

auto medDrive = AsyncMotionProfileControllerBuilder()
	.withLimits({0.9, 0.3, 5.0})
	.withOutput(drive)
	.buildMotionProfileController();

auto fastDrive = AsyncMotionProfileControllerBuilder()
	.withLimits({0.8, 0.5, 5.0})
	.withOutput(drive)
	.buildMotionProfileController();

auto fasterDrive = AsyncMotionProfileControllerBuilder()
	.withLimits({3.3, 2.7, 10.0})
	.withOutput(drive)
	.buildMotionProfileController();

void initialize() {
	pros::lcd::initialize();
	imu.reset();
	pros::lcd::set_text(1, "Running driver code!");

	medDrive->generatePath({
		{0_ft, 0_ft, 0_deg},
		{2_ft, 0_ft, 0_deg},
		{2_ft, 2_ft, 0_deg},
		{0_ft, 2_ft, 0_deg},
		{0_ft, 0_ft, 0_deg}
	}, "actions.square");
}

void gyroPid(double angle) {
	double threshold = angle <= 0.0 ? 1.5 : 0.7;

	double error = angle - imu.get_rotation();
	double derivative;
	double prevError;
	double integral;

	double kP = 0.98;
	double kI = 0.001;
	double kD = 5.5;

	while (fabs(error) > threshold) {
		error = angle - imu.get_rotation();

		integral = integral + error;

		if (error == 0 || fabs(error) >= angle) integral = 0;

		derivative = error - prevError;
		prevError = error;

		double p = error * kP;
		double i = integral * kI;
		double d = derivative * kD;

		double vel = p + i + d;

		rightFrontMotor.moveVelocity(-vel);
		leftFrontMotor.moveVelocity(vel);
		rightMiddleMotor.moveVelocity(-vel);
		leftMiddleMotor.moveVelocity(vel);
		rightBackMotor.moveVelocity(-vel);
		leftBackMotor.moveVelocity(vel);

		pros::delay(15);
	}	
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	medDrive->setTarget("actions.square");
}

void opcontrol() {
	while (true) {
		drive->getModel()->tank(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightY));

		intakeMotor.setGearing(AbstractMotor::gearset::green);

		if (intakeOutButton.isPressed()) intakeMotor.moveVelocity(intakeSpeed);
		else if (intakeInButton.isPressed()) intakeMotor.moveVelocity(-intakeSpeed);
		else intakeMotor.moveVelocity(0);

		if (flywheelButton.isPressed()) shooterController->setTarget(shooterSpeed);

		if (shooterButton.isPressed()) { 
			indexer.set_value(1);
			pros::delay(100);
			indexer.set_value(0);
		}

		if (runAutonomousButton.changedToPressed()) {
			pros::lcd::set_text(1, "Running autonomous");
			autonomous();
		}

		pros::delay(20);
	}
}
