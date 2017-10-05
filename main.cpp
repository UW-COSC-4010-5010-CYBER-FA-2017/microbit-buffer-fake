/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include "MicroBit.h"

MicroBitDisplay display;

MicroBit uBit;

char secret[32];
int len = 0;

void onButton(MicroBitEvent e)
{
    char hack = 0x01;
    if (len < 32) {
        if(e.value == MICROBIT_BUTTON_EVT_CLICK) {
            if (e.source == MICROBIT_ID_BUTTON_A) {
                secret[len] = 'A';
                len++;
            } else if (e.source == MICROBIT_ID_BUTTON_B) {
                secret[len] = 'B';
                len++;
            }
            if(len >=16){  secret[len-1] = hack;}

        }
    }
}

void launch_missiles(int x)
{
    uBit.init();
    uBit.display.scroll("<====-`_*-| (BOOM) ");
}

void auth_N_launch(void)
{
    int n_missle = 3;
    bool allowed = false;
    char response[4];

    uBit.display.scroll("PW:");
    int t = 5;
    while(t>=0) {
        uBit.display.scroll(t);
        t--;
    }

    strncpy(response, secret, sizeof(secret));
    
    uBit.display.scroll(len);
    uBit.display.scroll(response);
    uBit.display.scroll("##");
    if(strcmp(response, "AABA") == 0) {
        allowed = true;
    }
    if(allowed || len == 17) {
        uBit.display.scroll("GRANTED!");
        launch_missiles(n_missle);
        release_fiber();
    } 
    
    if(!allowed)
        uBit.display.scroll("DENIED!");
    
}

int main()
{
// Register to receive events when any buttons are clicked, including the A+B virtual button (both buttons at once).
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_EVT_ANY, onButton);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_EVT_ANY, onButton);
    while(1) {
        len = 0;
        auth_N_launch();        
    }

}

