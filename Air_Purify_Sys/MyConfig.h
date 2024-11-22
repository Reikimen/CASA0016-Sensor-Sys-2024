 /////////////////////////////////////////////////////// LCD 2004 ///////////////////////////////////////////////////////
LiquidCrystal_I2C lcd(0x27, 20, 4);

int DISPLAYMODE = 0;

char buffer[4][21]; // 4 lines of up to 20 characters each for storage of the current display
int LCDcount = 50;

/////////////////////////////////////////////////////// Mode IO ////////////////////////////////////////////////////////
#define encoderPinA     12    // D6
#define encoderPinB     13    // D7
#define encoderPinBtn   14    // D5
#define homeBtnPin      0     // D3

// De-jitter time
#define DEBOUNCE_TIME 30  // Used for both encoderBtn (Simplified as 'Button') and homeBtn
unsigned long ButtonlastDebounceTime = 0;
unsigned long homeBtnlastDebounceTime = 0;

// Save rotation count, button press state
volatile int encoderPosition = 0;
volatile bool buttonPressed = false;
volatile bool homebuttonPressed = false;

// The state of encoder pins, use HIGH to avoid the first detceting turn
int lastEncoderStateA = HIGH;
int lastEncoderStateB = HIGH;

// Counterclockwise (left) is 1, Clockwise (right) is 0, default is 11451
int EncoderRotate = 11451;

// Button status, default null pin high
int lastButtonState = HIGH;
int homelastButtonState = HIGH;

// Used to increase the period for detecting the rotary encoder to enable runtime support for modeLogic
int encodercount = 10;

/////////////////////////////////////////////////////// Sensors ////////////////////////////////////////////////////////