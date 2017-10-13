String myName;  // Declare the string variable to hold name
int age;        // Declare the int variable to hold age
float height;   // Declare the float variable to hold height
float weight;   // Declare the float variable to hold weight

// get weight, claculate in ounces, grams, carats

void setup() {
  Serial.begin(9600); // Turning on Serial port at 9600 baud

}

void loop() {
  Serial.println("Please enter your name"); // Prompt the user for name
  while(Serial.available()==0) {};          // Waiting for user input
  myName = Serial.readString();             // Read the String
  
  Serial.println("How old are you?");       // Prompt the user for age
  while(Serial.available()==0) {};          // Waiting for user input
  age = Serial.parseInt();                  // Read the Int

  Serial.println("How tall are you?");      // Prompt the user for height
  while(Serial.available()==0) {};          // Waiting for user input
  height = Serial.parseFloat();             // Read the Float

  Serial.println("How much do you weigh?"); // Prompt the user for weight
  while(Serial.available()==0) {};          // Waiting for user input
  weight = Serial.parseFloat();             // Read the Float
  
  Serial.println("");

  Serial.print("Hello ");
  Serial.print(myName);
  Serial.print(", you are ");
  Serial.print(age);
  Serial.println(" years old,");
  Serial.print("and you are ");
  Serial.print(height);
  Serial.println(" feet tall.");

  // Weight in pounds
  Serial.print("You weigh ");
  Serial.print(weight);
  Serial.println(" pounds.");

  // Weight in ounces
  Serial.print("You weigh ");
  Serial.print(weight * 16);
  Serial.println(" ounces.");

  // Weight in grams
  Serial.print("You weigh ");
  Serial.print(weight * 453.592);
  Serial.println(" grams.");

  // Weight in carats
  Serial.print("You weigh ");
  Serial.print(weight * 2267.96);
  Serial.println(" carats.");
  Serial.println("");
}
