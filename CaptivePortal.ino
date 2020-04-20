/*
   Captive Portal by: M. Ray Burnette 20150831
   See Notes tab for original code references and compile requirements
   Sketch uses 300,640 bytes (69%) of program storage space. Maximum is 434,160 bytes.
   Global variables use 50,732 bytes (61%) of dynamic memory, leaving 31,336 bytes for local variables. Maximum is 81,920 bytes.
*/

/*
 * This is fox #01
 * Question:
 * Anwser:
 * 
*/

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const byte        DNS_PORT = 53;          // Capture DNS requests on port 53
IPAddress         apIP(10, 10, 10, 1);    // Private network for server
DNSServer         dnsServer;              // Create the DNS object
ESP8266WebServer  webServer(80);          // HTTP server

String responseHTML = ""
                      "<!DOCTYPE html><html><head><title>WiFi Foxhunt #10</title>"
                      "<script>function validateForm() {var x = document.forms['answerForm']['answer'].value;if (x == '10') {alert('Yes!'); return false;} else { alert('Wrong!!'); return false; }}</script>"
                      "</head><body>"
                      "<h1>FOX #10</h1><p>This is FOX  #10<br>"
                      "QUESTION: Why are trains yellow?</p>"
                      "<!--<p><form name=\"answerForm\" onsubmit=\"return validateForm()\">Answer: <input type=\"text\" name=\"answer\"><input type=\"submit\" value=\"GO!!\"></form></p>-->"
                      "<p></p></body></html>";


void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("FOX #10");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
