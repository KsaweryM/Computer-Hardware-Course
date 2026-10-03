// Task 3: who runs loop()?
// Run it and open the Serial Monitor. Which task runs setup()? What is its priority?
// NULL means: the task that is running now.

void setup() {
  Serial.begin(115200);
  Serial.print("Task: ");
  Serial.println(pcTaskGetName(NULL));
  Serial.print("Priority: ");
  Serial.println(uxTaskPriorityGet(NULL));
}

void loop() {
  delay(1000);
}
