int arr[3] = {1, 2, 3};
void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i=0;i<=2;i++){
    Serial.write(arr[i]);}
  delay(1000);

}
