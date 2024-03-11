// #include "Random.h"
// #include "ManualRandom.h"
#include "RandomForestGec.h"
#include <WiFi.h>

Eloquent::ML::Port::RandomForest classifier;

const int MAX_NETWORKS = 4;  // Maximum number of networks to store

String knownSSIDs[MAX_NETWORKS];
float rssiFeatures[MAX_NETWORKS];

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();  // Disconnect from any previous WiFi connection
  knownSSIDs[0]="Redmi 8";
  // knownSSIDs[1]="Galaxy M012162";
  knownSSIDs[1]="Redmi 9A";
  // knownSSIDs[2]="DIRECT-N3-BRAVIA";
  // knownSSIDs[2]="IIT-goa";
  knownSSIDs[2]="Pixel_5556";
  // Serial.println("%%%%%%%%%%%%%%%%%%%%%%%%%%%NEW%%%%%%%%%%%%%%%%%%%%%%%%%5");
}

void loop() {

  scanAndAssignNetworks();
  convertToFeaturesVector();
  printFeaturesVector();
  classify();
  delay(500);  // Scan every 5 seconds
}

void scanAndAssignNetworks() {
  // int numNetworks = WiFi.scanNetworks();

  // // Clear previous data
  // for (int i = 0; i < MAX_NETWORKS; i++) {
  //   knownSSIDs[i] = "";
  //   rssiFeatures[i] = 0;
  // }
  // Clear previous rssi values
  //   for (int i = 0; i < MAX_NETWORKS; i++) {
  //   // knownSSIDs[i] = "";
  //   rssiFeatures[i] = 0;
  // }

  // Assign each SSID to a fixed index
  // for (int i = 0; i < min(numNetworks, MAX_NETWORKS); i++) {
  //   knownSSIDs[i] = WiFi.SSID(i);
  // }
}

void convertToFeaturesVector() {
  int numNetworks = WiFi.scanNetworks();

  // Clear previous RSSI feature values
  for (int i = 0; i < MAX_NETWORKS; i++) {
    rssiFeatures[i] = 0;
  }

  // Convert scan results to features vector
  // for (int i = 0; i < min(numNetworks, MAX_NETWORKS); i++) {
  //   int index = indexOf(knownSSIDs, MAX_NETWORKS, WiFi.SSID(i));
  //   if (index != -1) {
  //     rssiFeatures[index] = WiFi.RSSI(i);
  //   }
  // }
    for (int i = 0; i < min(numNetworks, MAX_NETWORKS); i++) {
    int index = indexOf(knownSSIDs, MAX_NETWORKS, WiFi.SSID(i));
    if (index != -1) {
      if(WiFi.RSSI(i)==0){
        rssiFeatures[index]=0;
      }else
      rssiFeatures[index] = 100 - abs(WiFi.RSSI(i));
    }
  }
}

void printFeaturesVector() {
  Serial.println("Features Vector:");

  for (int i = 0; i < MAX_NETWORKS && !knownSSIDs[i].isEmpty(); i++) {
    Serial.print("SSID: ");
    Serial.print(knownSSIDs[i]);
    Serial.print(", RSSI: ");
    Serial.println(rssiFeatures[i]);
  }
    // Serial.println("##########################################");

  Serial.println();
}

int indexOf(String arr[], int size, String target) {
  for (int i = 0; i < size; i++) {
    if (arr[i] == target) {
      return i;  // Return the index if the target is found
    }
  }
  return -1;  // Return -1 if the target is not found in the array
}

void classify() {

    Serial.print("You are in CT");
    // Serial.println(classIdxToName(predict(features)));
    // Serial.println(classifier.predict());
        // float dummyRssiFeatures[3] = {0, 31, 0};

    // Serial.print("Predicted label (you should see '2': ");
    // Serial.println(classifier.predict(dummyRssiFeatures));
    int className = classifier.predict(rssiFeatures) + 1;
    // int className = classifier.predict(dummyRssiFeatures) + 1;
    Serial.println(className);
    // Serial.println(classifier.predict(rssiFeatures));
    delay(500);
}

