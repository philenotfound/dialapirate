/* 
 * The MIT License (MIT)
 * 
 * Copyright (c) 2021 phil@zankapfel.net
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* Dial-a-pirate keyboard */

#include <Bounce2.h> /* https://github.com/thomasfredericks/Bounce2 */
#include <Keyboard.h>

Button dial = Button();
Button pulse = Button();

void setup() {
  dial.attach( 4, INPUT_PULLUP );
  dial.interval(5 /*ms*/);
  dial.setPressedState(LOW);
  
  pulse.attach( 5, INPUT_PULLUP );
  pulse.interval(5 /*ms*/);
  pulse.setPressedState(LOW); 
    
  Keyboard.begin();
}

int Dialing = 0;
int Count = 0;

void loop() {
  dial.update();
  pulse.update();
  
  if(dial.fell())
     Dialing = 1;
  else if (dial.rose())
  {
     if (Count)
        /* 10 pulses means 0 was dialed */
        /* otherwise number of pulses */
        Keyboard.write('0'+Count%10);
     else
        /* A not fully dialed '1' is interpreted as Enter */
        Keyboard.write(KEY_RETURN);
     Dialing = Count = 0;
  }
  
  if (Dialing && pulse.fell())
  {
    Count++;
  }
}
