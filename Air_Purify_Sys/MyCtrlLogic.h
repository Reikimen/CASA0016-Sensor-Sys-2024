// Including Encoder and Home Button display reading and judgement, and programmed stabilisation.
// And the relationship of device mode to Encoder Rotate, Encoder Pressed, Home Button Pressed - ‘modeLogic’.

// Function for the Logic of DISPLAYMODE which is also represent the way machine working
void modeLogic(){
  switch (DISPLAYMODE){
    case 0:
      if (EncoderRotate == 0) DISPLAYMODE = 1;
      else if (EncoderRotate == 1) DISPLAYMODE = 1;
      if (buttonPressed) DISPLAYMODE = 1;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 1:
      if (EncoderRotate == 0) DISPLAYMODE = 2;
      else if (EncoderRotate == 1) DISPLAYMODE = 1;
      if (buttonPressed) DISPLAYMODE = 13;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 2:
      if (EncoderRotate == 0) DISPLAYMODE = 3;
      else if (EncoderRotate == 1) DISPLAYMODE = 1;
      if (buttonPressed) DISPLAYMODE = 14;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 3:
      if (EncoderRotate == 0) DISPLAYMODE = 6;
      else if (EncoderRotate == 1) DISPLAYMODE = 2;
      if (buttonPressed) DISPLAYMODE = 15;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 4:
      if (EncoderRotate == 0) DISPLAYMODE = 5;
      else if (EncoderRotate == 1) DISPLAYMODE = 1;
      if (buttonPressed) DISPLAYMODE = 14;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 5:
      if (EncoderRotate == 0) DISPLAYMODE = 6;
      else if (EncoderRotate == 1) DISPLAYMODE = 4;
      if (buttonPressed) DISPLAYMODE = 15;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 6:
      if (EncoderRotate == 0) DISPLAYMODE = 9;
      else if (EncoderRotate == 1) DISPLAYMODE = 5;
      if (buttonPressed) DISPLAYMODE = 16;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 7:
      if (EncoderRotate == 0) DISPLAYMODE = 8;
      else if (EncoderRotate == 1) DISPLAYMODE = 4;
      if (buttonPressed) DISPLAYMODE = 15;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 8:
      if (EncoderRotate == 0) DISPLAYMODE = 9;
      else if (EncoderRotate == 1) DISPLAYMODE = 7;
      if (buttonPressed) DISPLAYMODE = 16;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 9:
      if (EncoderRotate == 0) DISPLAYMODE = 9;
      else if (EncoderRotate == 1) DISPLAYMODE = 8;
      if (buttonPressed) DISPLAYMODE = 10;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 10:
      if (EncoderRotate == 0) DISPLAYMODE = 11;
      else if (EncoderRotate == 1) DISPLAYMODE = 10;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 11:
      if (EncoderRotate == 0) DISPLAYMODE = 12;
      else if (EncoderRotate == 1) DISPLAYMODE = 10;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 12:
      if (EncoderRotate == 0) DISPLAYMODE = 12;
      else if (EncoderRotate == 1) DISPLAYMODE = 11;
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 13:
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 14:
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 15:
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    case 16:
      if (homebuttonPressed) DISPLAYMODE = 1;
      break;
    default:
      break;
  }
}

// This thread has an execution period of 1ms, so you can't assign computation tasks to this function.
void encoderThread() {
  int currentStateA = digitalRead(encoderPinA);
  int currentStateB = digitalRead(encoderPinB);

  // Detect rotation, Serial back, change LCD mode
  if (lastEncoderStateA == LOW && currentStateA == HIGH) {
    if (currentStateB == LOW) {// turn left
      encoderPosition--;
      // EncoderRotate = 1;
      // Serial.println("Rotated Left");
    } 
    else {// turn right
      encoderPosition++;
      // EncoderRotate = 0;
      // Serial.println("Rotated Right");
    }
    //modeLogic(); // Change the LCD mode according to the direction of rotation information obtained.
  }

  // refresh the state
  lastEncoderStateA = currentStateA;
  lastEncoderStateB = currentStateB;
  
}

// Accumulate the encoder readings over a period of 10ms to get the result of a left or right turn, and perform the calculation task ‘modeLogic()’.
void CheckEncoderThread(){
  encodercount--;
  if (encodercount<=0){
    encodercount = CONSTENCODERCOUNT;
    if (encoderPosition < 0){
      EncoderRotate = 1;
      Serial.println("Rotated Left");
      modeLogic();
    }
    if (encoderPosition > 0){
      EncoderRotate = 0;
      Serial.println("Rotated Right");
      modeLogic();
    }

    // Renormalise encoderPosition to 0
    encoderPosition = 0;
    // Eliminate direction-of-rotation judgements
    EncoderRotate = 11451;
  }
}

void buttonThread() {
  int currentButtonState = digitalRead(encoderPinBtn);

  // De-jittering detection
  if (currentButtonState != lastButtonState) {
    ButtonlastDebounceTime = millis();
  }

  if ((millis() - ButtonlastDebounceTime) > DEBOUNCE_TIME) {
    // Button state change detection
    if (currentButtonState == LOW && !buttonPressed) {
      buttonPressed = true;
      Serial.println("Button Pressed");
      modeLogic();
    } 
    else if (currentButtonState == HIGH && buttonPressed) {
      buttonPressed = false;
      Serial.println("Button Released");
    }
  }

  // Update button status
  lastButtonState = currentButtonState;
}

void homeBtnThread() {
  int currentHomeBtnState = digitalRead(homeBtnPin);

  // De-jittering detection
  if (currentHomeBtnState != homelastButtonState) {
    homeBtnlastDebounceTime = millis();
  }

  if ((millis() - homeBtnlastDebounceTime) > DEBOUNCE_TIME) {
    // Button state change detection
    if (currentHomeBtnState == HIGH && !homebuttonPressed) {
      homebuttonPressed = true;
      Serial.println("Home Button Pressed");
      modeLogic();
    } 
    else if (currentHomeBtnState == LOW && homebuttonPressed) {
      homebuttonPressed = false;
      Serial.println("Home Button Released");
    }
  }

  // Update button status
  homelastButtonState = currentHomeBtnState;
}