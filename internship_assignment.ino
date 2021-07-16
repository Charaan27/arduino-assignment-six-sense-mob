/*
 * Six Sense Mobility - assignment solution sketch
 * NAME : CHARAAN S
 * COLLEGE : MADRAS INSTITUTE OF TECHNOLOGY, ANNA UNIVERSITY
 * In this sketch the following tasks are performed:
 * 1. A .csv file was created with multiple rows and colums, and was filled with random data
 * 2. The file was pre-processed and parsed, and the last line of the file was printed at the Serial Monitor
 * 3. Finally the last line was deleted.
 */

// Required Header Files
#include <SD.h>
#include <SPI.h>

// On the Ethernet Shield, PIN 4 is the CSPIN, and is set as an output by default.
const int CSpin = 4;

void setup() {
  // Standard baud rate
  Serial.begin(9600);
  Serial.print("Initializing SD Card....");

  if (!SD.begin(CSpin)) {
    Serial.println("ERROR: Failed to load Card or Card is not present.");
    return;
  }
  Serial.println("Initialization successful!");

  
  // A text file is created from which .csv file is processed out.
  File readTable = SD.open("readsheet.txt", FILE_WRITE);
  
  // Table is of 5X5 Dimension.
  if (readTable) {
    readTable.print("3001");
    readTable.print(",");
    readTable.print("501");
    readTable.print(",");
    readTable.print("98");
    readTable.print(",");
    readTable.print("90");
    readTable.print(",");
    readTable.print("85\n");
    readTable.print("3002");
    readTable.print(",");
    readTable.print("561");
    readTable.print(",");
    readTable.print("90");
    readTable.print(",");
    readTable.print("84");
    readTable.print(",");
    readTable.print("70\n");
    readTable.print("3003");
    readTable.print(",");
    readTable.print("578");
    readTable.print(",");
    readTable.print("100");
    readTable.print(",");
    readTable.print("95");
    readTable.print(",");
    readTable.print("98\n");
    readTable.print("3004");
    readTable.print(",");
    readTable.print("558");
    readTable.print(",");
    readTable.print("70");
    readTable.print(",");
    readTable.print("75");
    readTable.print(",");
    readTable.print("65\n");
    readTable.print("3005");
    readTable.print(",");
    readTable.print("543");
    readTable.print(",");
    readTable.print("87");
    readTable.print(",");
    readTable.print("93");
    readTable.print(",");
    readTable.print("96\n");
    readTable.close();
  }

  else {
    Serial.println("Error while opening file");
    return;
  }
  
  // Creating two copies of required table files
  File origTable = SD.open("origsheet.csv", FILE_WRITE);
  File dupTable = SD.open("dupsheet.csv", FILE_WRITE);
  
  String l_line;
  l_line.reserve(128);
  
  while (readTable.available()) {
    l_line = readTable.readStringUntil('\n');
    l_line.trim();
    if (l_line != "") {
      int l_start_posn = 0;
      while (l_start_posn != -1) 
      {
        origTable.println(ENDF2(l_line,l_start_posn,',').toInt()); // ENDF2 function is defined below after a few lines of code
        dupTable.println(ENDF2(l_line,l_start_posn,',').toInt());
      }
    }
    readTable.close();
    dupTable.close();
  }

  // To print the last line of the csv file
  if (origTable) {
    // a variable to store a line of the csv file(size can be adjusted based on the need)
    char line[128];
    // a variable to count the no of lines in the csv file
    int lineCounter = 0;

    // read each line of the csv file sequentially
    while (origTable.available()) {
      //reset the prev value of line to NULL
      memset(line, '\0', sizeof(line));
      origTable.readBytesUntil('\n', line, sizeof(line) - 1);
      // increment the line counter now
      lineCounter ++;
    }

    // Once all the available data in origTable is read, we display only the last line of the csv file
    // The last line is the recently updated value of 'line'
    Serial.println(line);

    // To delete the last line
    /* To delete the last line, we can go for two methods:
    * Method 1: We copy all the values prior to the last line, and we save it under a new .csv file.  
    * Method 2: We set the value of the last line as NULL.
    * We will go for method 2, since it consumes less memory.
    */

    memset(line, '\0', sizeof(line));
    origTable.close();
  }
  
}

// ENDF2(Extract Next Delimited Field) Function:
String ENDF2(const String &parse_line, int &parse_start, char parse_delimiter) {
// Fields are extracted one at a time from a line, based on a delimiter.
// parse_start would normally start as 0 and incremetns as we move along the line.
// parse_start = -1 is returned with the last field

  //If we have already parsed the whole line then return null
  if (parse_start == -1) {
    return "";
  }

  int l_start = parse_start;
  int l_index = parse_line.indexOf(parse_delimiter,l_start);
  if (l_index == -1) { //last field of the data line
    parse_start = l_index;
    return parse_line.substring(l_start);
  }
  else { //take the next field off the data line
    parse_start = l_index + 1;
    return parse_line.substring(l_start,l_index);
  }
} 


void loop() {
  // No instructions are required to be given under void loop()  
}
