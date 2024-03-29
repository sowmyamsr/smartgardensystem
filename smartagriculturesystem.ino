#define BLYNK_PRINT Serial
#define BLYNK_MAX_SENDBYTES 256
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
int moisture_level;
// You should get Auth Token in the Blynk App.
char auth[] = "2f0b1ea923a643158a61118703fe89ec";
char ssid[] = "SSID";
char pass[] = "PASSWORD";
int temperature;
int value;
void setup()
{
	Serial.begin(115200);
	pinMode(A0, INPUT);
	pinMode(D2, INPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	//pinMode(D7,OUTPUT);
	// analogWrite(D5,0);
	//  analogWrite(D6,0);
	Blynk.begin(auth, ssid, pass);
}
BLYNK_WRITE(V2)
{
	value = param.asInt();
	Serial.print(value);
}
void loop()
{
	digitalWrite(D5, LOW);
	moisture_level = analogRead(A0);
	temperature = analogRead(D2);
	//Serial.println(moisture_level);
	Blynk.virtualWrite(V9, moisture_level);
	Blynk.virtualWrite(V5, temperature);
	WidgetLCD lcd(V7);
	Blynk.email("reg farm", "Please water me boss");
	digitalWrite(D6, value);
//	BLYNK_WRITE(V3)
//	{
		//int buttonState = param.asInt();
	//}
	//digitalWrite(D7,buttonState);
	if (moisture_level>450)
	{
		lcd.print(0, 0, "Iam Thristy");
		lcd.print(0, 1, "water me");
		Blynk.notify("Hey master , Im thristy");
	}
	else
	{
		lcd.print(0, 0, "Iam okay");
		lcd.print(0, 1, "thank you");
		Blynk.email("reg farm", "happy day");
	}
	int pinData = BLYNK_WRITE(V2);
	digitalWrite(D6, pinData);
	Blynk.run();
}