
/*
https://www.jetsonhacks.com/nvidia-jetson-nano-j41-header-pinout/
https://automaticaddison.com/how-to-blink-an-led-using-nvidia-jetson-nano/
https://github.com/pjueon/JetsonGPIO

altro:
https://www.jetsonhacks.com/2019/06/07/jetson-nano-gpio/
https://maker.pro/nvidia-jetson/tutorial/how-to-use-gpio-pins-on-jetson-nano-developer-kit


*/
// Handles input and output
#include <iostream>

#include <string>
 
// For delay function
#include <chrono> 
 
// Handles threads of program execution
#include <thread>
 
// Signal handling
#include <signal.h>
 
#include <JetsonGPIO.h>

using namespace std;
 
// Pin Definitions
int led_pin_green = 7;
int led_pin_yellow = 19;
int led_pin_blue = 21;
int led_pin_red = 23;

string s;
char led;
char command;

bool green = true;
bool yellow = false;
 
// Flag to determine when user wants to end program
bool done = false;
 
// Function called by Interrupt
void signalHandler (int s){
  done = true;
}
 
int main() {
 
  // When CTRL+C pressed, signalHandler will be called
  // to interrupt the programs execution
  signal(SIGINT, signalHandler);
 
  // Pin Definitions 
  GPIO::setmode(GPIO::BOARD);
 std::cout << "TEST AVVIO :" << std::endl;
  // LED pin gets set to high initially
  GPIO::setup(led_pin_green, GPIO::OUT, GPIO::HIGH);
  GPIO::setup(led_pin_yellow, GPIO::OUT,  GPIO::HIGH);
  GPIO::setup(led_pin_blue, GPIO::OUT, GPIO::HIGH);
  GPIO::setup(led_pin_red, GPIO::OUT, GPIO::HIGH);

  std::cout << "......" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
 
    GPIO::output(led_pin_green,  GPIO::LOW);
    GPIO::output(led_pin_yellow, GPIO::LOW);
    GPIO::output(led_pin_blue, GPIO::LOW);
    GPIO::output(led_pin_red, GPIO::LOW);
 
    std::cout << "TEST AVVIO COMPLETATO!!" << std::endl;


   std::cout << "Press CTRL+C to stop the LED" << std::endl;
 
  int curr_value = GPIO::HIGH;
 
  // Blink LED every 0.5 seconds
  while(!done) {
 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
 
    curr_value = GPIO::HIGH;
 
    GPIO::output(led_pin_green, curr_value);
 
    std::cout << "LED is ON" << std::endl;

	getline(cin, s);

	cout << "OK " << s << "\r\n";

	led = s.at(0);
	command = s.at(1);
	
	cout << "led " << led << " eseguo " << command << "\r\n";

	if (led == 'Y'){
		if (command == '+'){
			cout << "OK, ACCENDO LED YELLOW" << "\r\n";
			GPIO::output(led_pin_yellow, GPIO::HIGH); 
    			std::cout << "LED YELLOW is ON" << std::endl;

		}else if (command == '-'){
			cout << "OK, SPENGO LED YELLOW" << "\r\n";
			GPIO::output(led_pin_yellow, GPIO::LOW); 
    			std::cout << "LED YELLOW is OFF" << std::endl;

		} else {
			cout << "SORRY, NON HO CAPITO!!!!" << "\r\n";
		}
	} else if (led == 'B'){
		if (command == '+'){
			cout << "OK, ACCENDO LED BLUE" << "\r\n";
			GPIO::output(led_pin_blue, GPIO::HIGH); 
    			std::cout << "LED BLUE is ON" << std::endl;

		}else if (command == '-'){
			cout << "OK, SPENGO LED BLUE" << "\r\n";
			GPIO::output(led_pin_blue, GPIO::LOW); 
    			std::cout << "LED BLUE is OFF" << std::endl;

		} else {
			cout << "SORRY, NON HO CAPITO!!!!" << "\r\n";
		}
	}else if (led == 'R'){
		if (command == '+'){
			cout << "OK, ACCENDO LED RED" << "\r\n";
			GPIO::output(led_pin_red, GPIO::HIGH); 
    			std::cout << "LED RED is ON" << std::endl;

		}else if (command == '-'){
			cout << "OK, SPENGO LED RED" << "\r\n";
			GPIO::output(led_pin_red, GPIO::LOW); 
    			std::cout << "LED RED is OFF" << std::endl;

		} else {
			cout << "SORRY, NON HO CAPITO!!!!" << "\r\n";
		}
	}


	else {
		cout << "SORRY, NON HO CAPITO!!!!" << "\r\n";
	}
	
 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
 
    curr_value = GPIO::LOW;
 
    GPIO::output(led_pin_green, curr_value);
 
    std::cout << "LED is OFF" << std::endl;




  }
 
  GPIO::cleanup();
 
  return 0;
}

