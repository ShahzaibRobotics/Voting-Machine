#include <LiquidCrystal.h>
#include <Keypad.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6, 5, 4, 3};
byte colPins[COLS] = {2, A0, A1, A2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Voting Pins
#define showResultPin A4
#define clearResultPin A3

// Passwords
String userPasswords[] = {"123456", "654321", "222222", "444444", "666666", "888888", "000000"};
String adminPasswords[] = {"989898"};
int userCount = sizeof(userPasswords) / sizeof(userPasswords[0]);

// Vote counters: votes[0] = A, [1] = B, [2] = C, [3] = D
int votes[4] = {0, 0, 0, 0};

void setup() {
  lcd.begin(16, 2);
  pinMode(showResultPin, INPUT_PULLUP);
  pinMode(clearResultPin, INPUT_PULLUP);
  lcd.clear();
  lcd.print(" Voting Machine ");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Press Any Button");
  lcd.setCursor(0, 1);
  lcd.print("     To Vote    ");

  // Admin: Show Result
  if (digitalRead(showResultPin) == LOW) {
    handleAdminAccess(true);
    return;
  }

  // Admin: Clear Result
  if (digitalRead(clearResultPin) == LOW) {
    handleAdminAccess(false);
    return;
  }

  // Keypad Vote
  char key = keypad.getKey();
  if (key == 'A' || key == 'B' || key == 'C' || key == 'D') {
    int teamIndex = key - 'A';  // 'A'=0, 'B'=1, etc.

    lcd.clear();
    lcd.print("You voted ");
    lcd.setCursor(0, 1);
    lcd.print("Team ");
    lcd.print(key);
    delay(2000);

    if (verifyUserPassword()) {
      votes[teamIndex]++;
      lcd.clear();
      lcd.print("Vote Recorded");
    } else {
      lcd.clear();
      lcd.print("Wrong Password");
    }

    delay(2000);
    lcd.clear();
  }
}

// Password input (auto-completes after 6 digits)
String getPassword(int digits = 6) {
  String input = "";
  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);

  while (input.length() < digits) {
    char key = keypad.getKey();
    if (key >= '0' && key <= '9') {
      input += key;
      lcd.print("*");
    } else if (key == '*') {
      if (input.length() > 0) {
        input.remove(input.length() - 1);
        lcd.setCursor(input.length(), 1);
        lcd.print(" ");
        lcd.setCursor(input.length(), 1);
      }
    }
  }
  return input;
}

// Verify user password and remove it after use
bool verifyUserPassword() {
  String entered = getPassword(6);
  for (int i = 0; i < userCount; i++) {
    if (entered == userPasswords[i]) {
      // Remove the used password by shifting elements
      for (int j = i; j < userCount - 1; j++) {
        userPasswords[j] = userPasswords[j + 1];
      }
      userCount--; // Reduce the count
      return true;
    }
  }
  return false;
}

// Verify admin password
bool verifyAdminPassword() {
  String entered = getPassword(6);
  for (String pass : adminPasswords) {
    if (entered == pass) return true;
  }
  return false;
}

// Handle showing or clearing result
void handleAdminAccess(bool show) {
  lcd.clear();
  lcd.print(show ? "Show Results" : "Clear Results");
  delay(1000);

  if (verifyAdminPassword()) {
    if (show) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("A=");
      lcd.print(votes[0]);
      lcd.print("  B=");
      lcd.print(votes[1]);
      lcd.setCursor(0, 1);
      lcd.print("C=");
      lcd.print(votes[2]);
      lcd.print("  D=");
      lcd.print(votes[3]);
      delay(10000);
    } else {
      for (int i = 0; i < 4; i++) votes[i] = 0;
      lcd.clear();
      lcd.print("Results Cleared");
      delay(10000);
    }
  } else {
    lcd.clear();
    lcd.print("Access Denied");
    delay(2000);
  }
  lcd.clear();
}
