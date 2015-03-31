/* Update BIOS of BT-05 automatically with a Teensy-Stick, programmed with Teensy-Duino */

#define DEFAULT_DELAY 200 // 200 ms between keypresses

/* do it only once */
int done = 0;

void setup()
{
  Keyboard.begin();
}

/* Compatibility to plain C-Teensy programming , Start */

#define KEY_SHIFT  KEY_LEFT_SHIFT

void usb_keyboard_press( int character, int special )
{
   if (special != 0 )
   {
      Keyboard.press( special);
      delay( 10 );
   }
   Keyboard.press( character );
   delay( 50 );
   Keyboard.releaseAll();
}

void _delay_ms( int wait )
{
   delay( wait );
}

/* Compatibility to plain C-Teensy programming , End */


void usb_keyboard_press_and_delay( int character, int special )
{
    usb_keyboard_press( character, special );
    _delay_ms( DEFAULT_DELAY );
}

void loop()
{
    int i;
    if ( ! done )
    {
        // START copy between teensy and sketchbook

        // Enter BIOS via pressing 10 times DELETE
            for ( i = 0; i < 10; ++i )
        {
            usb_keyboard_press( KEY_DELETE, 0 );
            _delay_ms(1000);
        }

        // Go right into the menu
        usb_keyboard_press_and_delay( KEY_RIGHT , 0  );
        // Go down to USB-Boot
        for ( i = 0; i < 8; ++i )
        {
            usb_keyboard_press_and_delay( KEY_DOWN, 0 );
        }
        // and enable USB-Boot
        usb_keyboard_press_and_delay( KEY_ENTER , 0 );
        usb_keyboard_press_and_delay( KEY_PAGE_DOWN , 0 );
        usb_keyboard_press_and_delay( KEY_ENTER , 0 );
        usb_keyboard_press_and_delay( KEY_PAGE_DOWN , 0 );
        usb_keyboard_press_and_delay( KEY_ENTER , 0 );

        // return from submenu
        usb_keyboard_press_and_delay( KEY_ESC , 0 );

        // go to boot-order-menu
        for( i = 0; i < 3; ++i )
        {
            usb_keyboard_press_and_delay( KEY_RIGHT , 0);
        }

        // go down to to first entry (depends on the connected drives, this one works with connected mSATA)
        for( i = 0; i < 2; ++i )
        {
            usb_keyboard_press_and_delay( KEY_DOWN , 0);
        }
        // Enter to select this entry
        usb_keyboard_press_and_delay( KEY_ENTER , 0 );

        // Page up is upper value = uefi menu
        usb_keyboard_press_and_delay( KEY_PAGE_UP , 0 );

        // and enter
        usb_keyboard_press_and_delay( KEY_ENTER , 0 );

        // F4 = Save and exit
        usb_keyboard_press_and_delay( KEY_F4 , 0 );

        // Yes, I really want to save and exit
        usb_keyboard_press_and_delay( KEY_ENTER , 0 );

        // Yes, I really want to save and exit
        usb_keyboard_press_and_delay( KEY_ENTER , 0 );

        /* now we are in the UEFI-shell */
        // go to fs0:
        usb_keyboard_press_and_delay( KEY_F, 0 );
        usb_keyboard_press_and_delay( KEY_S, 0 );
        usb_keyboard_press_and_delay( KEY_0, 0 );
        usb_keyboard_press_and_delay( KEY_SEMICOLON, KEY_SHIFT );
        usb_keyboard_press_and_delay( KEY_ENTER, 0 );
        _delay_ms(1000 );

        /* now we are on the USB-Stick */
        // and now run "go_x64"
        usb_keyboard_press_and_delay( KEY_G, 0 );
        usb_keyboard_press_and_delay( KEY_O , 0);
        usb_keyboard_press_and_delay( KEY_MINUS, KEY_SHIFT );
        usb_keyboard_press_and_delay( KEY_X, 0 );
        usb_keyboard_press_and_delay( KEY_6, 0 );
        usb_keyboard_press_and_delay( KEY_4, 0 );

        // last chance to escape via removing power from IPC
        _delay_ms(4000);

        usb_keyboard_press_and_delay( KEY_ENTER, 0 );




        // END copy between teensy and sketchbook
        done = 1;
    }
    delay(1000);
}

