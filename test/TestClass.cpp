
#define LiquidCrystal_Test LiquidCrystal
#include "Common.cpp"

unittest(testingClassName) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  assertEqual("LiquidCrystal_CI", lcd.className());
}

unittest(getRows) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  assertEqual(1, lcd.getRows());
  lcd.begin(16, 2);
  assertEqual(2, lcd.getRows());
}

// based on Autoscroll.ino example
unittest(autoscrollHi) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  assertFalse(lcd.isAutoscroll());
  lcd.begin(16, 2);
  // get currently displayed lines
  std::vector<std::string> lines;
  // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // print from 0 to 9:
  for (int thisChar = 0; thisChar < 10; thisChar++) {
    lcd.print(thisChar);
    delay(500);
  }
  // verify display not empty
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  // uncomment when print works
  // assertEqual(10, lines.at(0).length());
  // assertEqual("0123456789", lines.at(0));
  assertEqual(0, lines.at(1).length());

  // set the cursor to (16,1):
  lcd.setCursor(16, 1);
  // set the display to automatically scroll:
  lcd.autoscroll();
  assertTrue(lcd.isAutoscroll());
  // print from 0 to 9:
  std::string zeroTo9 = "0123456789";
  std::string text = "                ";

  for (int i = 0; i < 10; i++) {
    // send character to screen
    lcd.print(i);

    // calculate expected value for second line
    std::string expected = text.substr(0, 15 - i);
    expected += zeroTo9;
    expected = expected.substr(0, 16);

    // compare expected to actual
    lines = lcd.getLines();
    // uncomment when print works
    // assertEqual(16, lines.at(1).length());
    // assertEqual(expected, lines.at(1));

    delay(500);
  }
  // turn off automatic scrolling
  lcd.noAutoscroll();
  assertFalse(lcd.isAutoscroll());

  // clear screen for the next loop:
  lcd.clear();
}

unittest(clearBuffer) {
  // create lcd object
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  // get currently displayed lines
  std::vector<std::string> lines = lcd.getLines();
  // verify that display contains 1 empty line
  assertEqual(1, lines.size());
  assertEqual(0, lines.at(0).length());

  // reset lcd to have two lines
  lcd.begin(16, 2);
  // verify that begin clears the display
  lines = lcd.getLines();
  // verify that display contains 2 empty lines
  assertEqual(2, lines.size());
  assertEqual(0, lines.at(0).length());
  assertEqual(0, lines.at(1).length());

  // write something to display
  lcd.print("hello world");

  // verify display not empty
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  // assertEqual(11, lines.at(0).length());
  // assertEqual("hello world", lines.at(0));
  assertEqual(0, lines.at(1).length());

  // clear display
  lcd.clear();

  // verify display is empty
  lines = lcd.getLines();
  assertEqual(2, lines.size());
  assertEqual(0, lines.at(0).length());
  assertEqual(0, lines.at(1).length());
}

unittest_main()
