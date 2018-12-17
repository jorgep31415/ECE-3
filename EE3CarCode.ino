#define RED 2
#define GREEN 4
#define BLUE 6
#define RIGHT_MOTOR 9
#define LEFT_MOTOR 11
#define LEFT_IN A3
#define MIDDLE_IN A5
#define RIGHT_IN A7

#define THRESHOLD 650
#define BASE_LEFT 160
#define BASE_RIGHT 180

#define PREV_LEFT 1
#define PREV_RIGHT 2

int svR = 0, svM = 0, svL = 0;
bool TURN_LEFT = false;
bool TURN_RIGHT = false;
bool STRAIGHT = true;
bool STOP = false;
int last = 0;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(LEFT_MOTOR, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  svR = analogRead(RIGHT_IN);
  svM = analogRead(MIDDLE_IN);
  svL = analogRead(LEFT_IN);

  /* for debugging */
  Serial.print("\nright = ");
  Serial.print(svR);
  delay(2);
  Serial.print("\nmiddle = ");
  Serial.print(svM);
  delay(2);    
  Serial.print("\nleft = ");
  Serial.print(svL);
  delay(2);  


  if (svM > THRESHOLD)
  {
    STRAIGHT = true;
    TURN_LEFT = false;
    TURN_RIGHT = false;
  }

  else if (svR > THRESHOLD)
  {
    STRAIGHT = false;
    TURN_LEFT = false;
    TURN_RIGHT = true;
  }

  else if (svL > THRESHOLD)
  {
    STRAIGHT = false;
    TURN_LEFT = true;
    TURN_RIGHT = false;
  }

  if (STOP)
  {
    STOP = true;
  }
  
  else if (svR > THRESHOLD && svL > THRESHOLD) //finish line
  {
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, HIGH);
    digitalWrite(GREEN, LOW);
    analogWrite(RIGHT_MOTOR, 0);
    analogWrite(LEFT_MOTOR, 0);
    STOP = true;
  }

  else if (TURN_RIGHT) //shifting left, turn right
  {
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    analogWrite(RIGHT_MOTOR, 0);
    analogWrite(LEFT_MOTOR, BASE_LEFT - 43);
    last = PREV_RIGHT;
  }

  else if (TURN_LEFT) //shifting right, turn left
  {
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    analogWrite(RIGHT_MOTOR, BASE_RIGHT - 50);
    analogWrite(LEFT_MOTOR, 0);
    last = PREV_LEFT;
  }

  else if (STRAIGHT && last == 0)   //straight, keep straight
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
    analogWrite(RIGHT_MOTOR, BASE_RIGHT);
    analogWrite(LEFT_MOTOR, BASE_LEFT);
  }

  else if (STRAIGHT && last == PREV_LEFT)
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
    analogWrite(RIGHT_MOTOR, BASE_RIGHT - 20);
    analogWrite(LEFT_MOTOR, BASE_LEFT);
  }

  else if (STRAIGHT && last == PREV_RIGHT)
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
    analogWrite(RIGHT_MOTOR, BASE_RIGHT);
    analogWrite(LEFT_MOTOR, BASE_LEFT - 16);
  }
}
