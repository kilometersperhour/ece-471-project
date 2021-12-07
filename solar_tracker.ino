char inputString[10]; // Should only ever be 5 characters: [0-9ucd] [0-9lcr] [0-9] [0-9] [0-9] \n
int8_t unitDirectionVector = {0, 0}; 
/* This code should run on the Raspberry Pi
// For more on spherical coordinates, see https://en.wikipedia.org/wiki/Spherical_coordinate_system
uint16_t topLeft[2]; // 
uint16_t topCenter[2];
uint16_t topRight[2];
uint16_t midLeft[2];
uint16_t midCenter[2];
uint16_t midRight[2];
uint16_t botLeft[2];
uint16_t botCenter[2];
uint16_t botRight[2];

int positionPointers[9] = {midCenter, midRight, topRight, topCenter, topLeft, midLeft, bottomLeft, bottomCenter, bottomRight}; // photoresistor 0 and photoresistor 1 inputs
*/
/* Reads the sensor data acquired by the 
 * Raspberry Pi (done with SPI) over serial.
 * Returns a pointer to a string 
 * containing a string of format
 * "[ucd][lcr]" (that's a PCRE)
 * for up/center/down left/center/right.
 */
int8_t receiveDirection(); 

/* function that will 
 * take two letter string as input 
 * and determine if movement dir is 
 * up or down, left or right 
 * ("[ucd][lcr]"), and return 
 * a corresponding vector for mvmt
 */ 
void moveDirection(char*, int); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial connection initialized.");
}

void loop() {
  // put your main code here, to run repeatedly:
  /* 
   *  Serial interface over bluetooth?
   *  Rotate slightly 
   *	  acquire neighboring readings 
   *  Poll photoresistors
   *    ioctl adc channel 0 annd 1 over adc
   *    capture sensor readings
   *    compare sensor readings
   *  Compare sensor readings 
   *  Move to position of nearest sensor reading
   *  
   *  if lastMovement is opposite of firstMovement
   *    Reduce movement distance
   *    re-enter data_acquisition loop
   *      returns highest value
   */ 
}

int8_t receiveDirection() {
  inputString = Serial.readStringUntil('\n');
  // Must input as an ordered pair! (In order, anyway.
  // 
  if (inputString[0] == 'u') { // Determine theta
    unitDirectionVector[0] = 1; // Setup to move in positive "u(p)"/+theta direction
  } else if (inputString[0] == 'd' || inputString[0] == 'D') {
    unitDirectionVector[0] = -1; // Setup to move in negative "d(own)"/-theta direction
  } else if (inputString[0] == 'c' || inputString[0] == 'C') {
    unitDirectionVector[0] = 0; // Setup to NOT move in any up/down direction; "c(enter)"
  } else {
    unitDirectionVector[0] = 0; // Setup to NOT move in any up/down direction; "c(enter)"
    Serial.println("ERROR: First character sent was invalid. Valid inputs are of format [udcUDC]. Will not move up/down.");
    Serial.print("Invalid character sent has binary equivalent ");
    Serial.println(inputString[0],BIN)
  } 
  if (inputString[1] == 'r' || inputString[1] == 'R') { // Determine phi
    unitDirectionVector[1] = 1; // Setup to move in positive "r(ight)"/+phi direction
  } else if (inputString[1] == 'l' || inputString[1] == 'L') {
    unitDirectionVector[1] = -1; // Setup to move in negative "l(eft)"/-phi direction
  } else if (inputString[1] == 'c' || inputString[1] == 'C') {
    unitDirectionVector[1] = 0; // Setup to NOT move in any right/left direction; "c(enter)"
  } else {
    unitDirectionVector[1] = 0; // Setup to NOT move in any right/left direction; "c(enter)"
    Serial.println("ERROR: Second character sent was invalid. Valid inputs are of format [rlcRLC]. Will not move right/left.");
    Serial.print("Invalid character sent has binary equivalent ");
    Serial.println(inputString[1],BIN)
  } 
  return unitDirectionVector;
}
