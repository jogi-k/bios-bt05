
#define KEY_SHIFT  KEY_LEFT_SHIFT

/* do it only once */
int done = 0;

void setup()
{
  Keyboard.begin();
}

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
        usb_keyboard_press( KEY_RIGHT , 0  );
        _delay_ms(500);
        // Go down to USB-Boot
        for ( i = 0; i < 8; ++i )
        {
            usb_keyboard_press( KEY_DOWN, 0 );
            _delay_ms(500);
        }
        // and enable USB-Boot
        usb_keyboard_press( KEY_ENTER , 0 );
        _delay_ms(500);
        usb_keyboard_press( KEY_PAGE_DOWN , 0 );
        _delay_ms(500);
        usb_keyboard_press( KEY_ENTER , 0 );
        _delay_ms(500);
        usb_keyboard_press( KEY_PAGE_DOWN , 0 );
        _delay_ms(500);
        usb_keyboard_press( KEY_ENTER , 0 );
        _delay_ms(500);

        // return from submenu
        usb_keyboard_press( KEY_ESC , 0 );
        _delay_ms(500);

        // go to boot-order-menu
        for( i = 0; i < 3; ++i )
        {
            usb_keyboard_press( KEY_RIGHT , 0);
            _delay_ms(500);
        }

        // go down to to first entry
        for( i = 0; i < 3; ++i )
        {
            usb_keyboard_press( KEY_DOWN , 0);
        _delay_ms(500);
        }
        // Enter to select this entry
        usb_keyboard_press( KEY_ENTER , 0 );
        _delay_ms(500);

        // Page up is upper value = uefi menu
        usb_keyboard_press( KEY_PAGE_UP , 0 );
        _delay_ms(500);

        // and enter
        usb_keyboard_press( KEY_ENTER , 0 );
        _delay_ms(500);

        // F4 = Save and exit
        usb_keyboard_press( KEY_F4 , 0 );
        _delay_ms(500);

        // Yes, I really want to save and exit
        usb_keyboard_press( KEY_ENTER , 0 );
        _delay_ms(500);

        // Yes, I really want to save and exit
        usb_keyboard_press( KEY_ENTER , 0 );
        _delay_ms(500);

        /* now we are in the UEFI-shell */
        // go to fs0:
        usb_keyboard_press( KEY_F, 0 );
        _delay_ms(100);
        usb_keyboard_press( KEY_S, 0 );
        _delay_ms(100);
        usb_keyboard_press( KEY_0, 0 );
        _delay_ms(100);
        usb_keyboard_press( KEY_SEMICOLON, KEY_SHIFT );
        _delay_ms(100);
        usb_keyboard_press( KEY_ENTER, 0 );
        _delay_ms(1000 );

        /* now we are on the USB-Stick */
        // and now run "go_x64"
        usb_keyboard_press( KEY_G, 0 );
        _delay_ms(100);
        usb_keyboard_press( KEY_O , 0);
        _delay_ms(100);
        usb_keyboard_press( KEY_MINUS, KEY_SHIFT );
        _delay_ms(100);
        usb_keyboard_press( KEY_X, 0 );
        _delay_ms(100);
        usb_keyboard_press( KEY_6, 0 );
        _delay_ms(100);
        usb_keyboard_press( KEY_4, 0 );

        // last chance to escape via removing power from IPC
        _delay_ms(4000);

        usb_keyboard_press( KEY_ENTER, 0 );
        _delay_ms(100);




        // END copy between teensy and sketchbook
        done = 1;
    }
    delay(1000);
}

