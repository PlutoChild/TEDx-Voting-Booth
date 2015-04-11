/*
  SendDataToGoogleSpreadsheet

  Demonstrates appending a row of data to a Google spreadsheet from the Arduino Yun 
  using the Temboo Arduino Yun SDK.  

  This example code is in the public domain.

*/

#include <Bridge.h>
#include <Temboo.h>

#include "TembooAccount.h" // contains Temboo account information

/*** SUBSTITUTE YOUR VALUES BELOW: ***/

// Note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.

const String GOOGLE_USERNAME = "email@email";
const String GOOGLE_PASSWORD = "password";

// the title of the spreadsheet you want to send data to
// (Note that this must actually be the title of a Google spreadsheet
// that exists in your Google Drive/Docs account, and is configured
// as described above.)
const String SPREADSHEET_TITLE = "filetitle";

const unsigned long RUN_INTERVAL_MILLIS = 10000; // how often to run the Choreo (in milliseconds)
int pot1Pin = 1;
int pot2Pin = 2; 
int pot3Pin = 3;// select the input pin for the potentiometer

int val1 = 0; 
int val2 = 0;
int val3 = 0;

int output1Value = 0;
int output2Value = 0;
int output3Value = 0;


// the last time we ran the Choreo 
// (initialized to 60 seconds ago so the
// Choreo is run immediately when we start up)
unsigned long lastRun = (unsigned long)-10000;

void setup() {
  
  // for debugging, wait until a serial console is connected
  Bridge.begin();
  Console.begin();
  delay(1000);
  while(!Console);
 

  Console.print("Initializing the bridge...");
  
  Console.println("Done");
  
 
}

void loop()
{
  // get the number of milliseconds this sketch has been running
  val1 = analogRead(pot1Pin);
  val2 = analogRead(pot2Pin);
  val3 = analogRead(pot3Pin);
  
  output1Value = map(val1, 0, 1023, 0, 255);
  output2Value = map(val2, 0, 1023, 0, 255);
  output3Value = map(val3, 0, 1023, 0, 255);
    // variables to hold the pushbutton states


  

  // run again if it's been 60 seconds since we last ran
  

    // remember 'now' as the last time we ran the choreo
   
    
    Console.println("Getting sensor value...");

    // get the value we want to append to our spreadsheet
   Console.write(output1Value);
   Console.write(output2Value);
   Console.write(output3Value);
   

    Console.println("Appending value to spreadsheet...");

    // we need a Process object to send a Choreo request to Temboo
    TembooChoreo AppendRowChoreo;

    // invoke the Temboo client
    // NOTE that the client must be reinvoked and repopulated with
    // appropriate arguments each time its run() method is called.
    AppendRowChoreo.begin();
    
    // set Temboo account credentials
    AppendRowChoreo.setAccountName(TEMBOO_ACCOUNT);
    AppendRowChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    AppendRowChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // identify the Temboo Library choreo to run (Google > Spreadsheets > AppendRow)
    AppendRowChoreo.setChoreo("/Library/Google/Spreadsheets/AppendRow");
    
    // set the required Choreo inputs
    // see https://www.temboo.com/library/Library/Google/Spreadsheets/AppendRow/ 
    // for complete details about the inputs for this Choreo
    
    // your Google username (usually your email address)
    AppendRowChoreo.addInput("Username", GOOGLE_USERNAME);

    // your Google account password
    AppendRowChoreo.addInput("Password", GOOGLE_PASSWORD);

    // the title of the spreadsheet you want to append to
    AppendRowChoreo.addInput("SpreadsheetTitle", SPREADSHEET_TITLE);

    // convert the time and sensor values to a comma separated string
    String rowData(output1Value);
    rowData += ",";
   
    rowData += output2Value;
    rowData += ",";
    rowData += output3Value;

    // add the RowData input item
    AppendRowChoreo.addInput("RowData", rowData);
    AppendRowChoreo.addInput("RowData", rowData);
    AppendRowChoreo.addInput("RowData", rowData);

    // run the Choreo and wait for the results
    // The return code (returnCode) will indicate success or failure 
    unsigned int returnCode = AppendRowChoreo.run();

    // return code of zero (0) means success
    if (returnCode == 0) {
      Console.println("Success! Appended " + rowData);
      Console.println("");
    } else {
      // return code of anything other than zero means failure  
      // read and display any error messages
      while (AppendRowChoreo.available()) {
        char c = AppendRowChoreo.read();
        Console.print(c);
      }
    }

    AppendRowChoreo.close();
  }




// this function simulates reading the value of a sensor 
unsigned long getSensorValue() {
 
  
  
  return analogRead(A0);
}
