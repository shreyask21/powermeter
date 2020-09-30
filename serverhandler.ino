/********* Add Listeners For Server HTTP Requests ***********/
void addServerHandlers()
{
  /*************** Redirect to correct domain *****************/
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->redirect("http://meter.local/view");
  });
  server.on("/view", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.html.gz", "text/html");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  /************************************************************/

  /*************** GET requests to send data ******************/
  server.on("/readings", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", data_string.c_str());
  });
  server.on("/check", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "ACK");
  });
  /************************************************************/

  /********* GET requests to set INA219 Calibration ***********/
  server.on("/setcalc", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(204);
    INA219.setCalibration_32V_2A();
  });
  server.on("/setcalb", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(204);
    INA219.setCalibration_32V_1A();
  });
  server.on("/setcala", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(204);
    INA219.setCalibration_16V_400mA();
  });
  /************************************************************/

  /********* GET requests to send HTML from SPIFFS ***********/
  server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.html.gz", "text/html");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/manifest.json", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/manifest.json", "application/json");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  server.on("/meter-large.png", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/meter-large.png", "image/png");
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });
  /************************************************************/
}
/************************************************************/
