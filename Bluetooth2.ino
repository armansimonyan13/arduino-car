char position = 0;

long valueLeft = 0;
long valueRight = 0;

int enLeft = 10;
int enRight = 5;

int outLeft0 = 9;
int outLeft1 = 8;

int outRight0 = 7;
int outRight1 = 6;

enum Side {
	LEFT, RIGHT
};

enum Direction {
	FORWARD, BACKWARD
};

struct Data {
	Side side;
	Direction direction;
	int speed;
};

byte buffer[4];

void setup() {
	Serial.begin(9600);

	pinMode(enLeft, OUTPUT);
	pinMode(enRight, OUTPUT);
	pinMode(outLeft0, OUTPUT);
	pinMode(outLeft1, OUTPUT);
	pinMode(outRight0, OUTPUT);
	pinMode(outRight1, OUTPUT);
}

void loop() {
	if (Serial.available() > 0) {
		Data data = readData();

		if (data.side == LEFT) {
			if (data.speed > 0) {
				if (data.direction == FORWARD) {
					moveLeftForward(255);
				} else if (data.direction == BACKWARD) {
					moveLeftBackward(255);
				}
			} else {
				stopLeft();
			}
		} else if (data.side == RIGHT) {
			if (data.speed > 0) {
				if (data.direction == FORWARD) {
					moveRightForward(255);
				} else if (data.direction == BACKWARD) {
					moveRightBackward(255);
				}
			} else {
				stopRight();
			}
		}
	}
}

Data readData() {
	int readCount = Serial.readBytes(buffer, 4);

	Data data;

	if (buffer[0] == 0) {
		data.side = LEFT;
	} else {
		data.side = RIGHT;
	}

	if (buffer[1] == 0) {
		data.direction = FORWARD;
	} else {
		data.direction = BACKWARD;
	}

	data.speed = 0;
	data.speed |= buffer[2];
	data.speed << 8;
	data.speed |= buffer[3];

	logData(data);

	return data;
}

void logData(Data data) {
	Serial.print("Side: ");
	Serial.print(data.side);
	Serial.print(", Direction: ");
	Serial.print(data.direction);
	Serial.print(", Speed: ");
	Serial.print(data.speed);
	Serial.print("\n");
}

void moveLeftForward(int speed) {
	digitalWrite(outLeft0, HIGH);
	digitalWrite(outLeft1, LOW);
	analogWrite(enLeft, speed);
}

void moveLeftBackward(int speed) {
	digitalWrite(outLeft0, LOW);
	digitalWrite(outLeft1, HIGH);
	analogWrite(enLeft, speed);
}

void stopLeft() {
	digitalWrite(outLeft0, LOW);
	digitalWrite(outLeft1, LOW);
	analogWrite(enLeft, 0);
}

void moveRightForward(int speed) {
	digitalWrite(outRight0, HIGH);
	digitalWrite(outRight1, LOW);
	analogWrite(enRight, speed);
}

void moveRightBackward(int speed) {
	digitalWrite(outRight0, LOW);
	digitalWrite(outRight1, HIGH);
	analogWrite(enRight, speed);
}

void stopRight() {
	digitalWrite(outRight0, LOW);
	digitalWrite(outRight1, LOW);
	analogWrite(enRight, 0);
}
