# EE 5450 M1A1: Superloop Combination Lock

In this homework, you will create a "combination lock" using the four buttons 
and LEDs on your nRF52dk board.  Your program should be able to track
button presses and turn on the "correct" or "incorrect" LED based on
what was entered.

Use the following setup for your hardware (Zephyr names in parentheticals):
- BUTTON1 (`sw0`) through BUTTON3 (`sw2`) inclusive: Potential "combo" buttons.
- BUTTON4 (`sw3`): "Enter" button (doubles as the "clear" button).
- LED1 (`led0`): flash when a key is pressed
- LED2 (`led1`): flash rapidly when an incorrect "combo" has been pressed after pressing "Enter".
- LED4 (`led3`): stays on for 3 seconds when the correct" combo has been pressed after pressing "Enter".

Provide the following behavior:
- Only use the most recent six keypresses. If the user enters presses more 
than six "combo" buttons, only take the most recent six.
- The "Enter" button should always run a check, even if the user did not 
press "combo" buttons six times.
- Once the correct combo and the "Enter" button has been pressed, turn
on LED4 for 3 seconds (do not respond to any button presses during this period).
- If an incorrect combo has been entered and the "Enter" button has been pressed,
flash LED2 rapidly (200 ms on time, 200 ms off time) for 3 seconds (do not respond to
any button presses during this period).
- For flexibility, define the number of keypresses as a macro.  Your code should be
flexible to allow for future lengthening or shortening of the number of keypresses required.
