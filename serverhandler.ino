/********* Add Listeners For Server HTTP Requests ***********/
void addServerHandlers()
{
    /*************** Redirect to correct domain *****************/
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->redirect("http://meter.local/view");
    });
    server.on("/view", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
    });
    /************************************************************/

    /*************** GET requests to send data ******************/
    server.on("/voltage", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(voltage, 3).c_str());
    });
    server.on("/current", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(current, 1).c_str());
    });
    server.on("/power", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(power).c_str());
    });
    server.on("/check", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "ACK");
    });
    /************************************************************/

    /********* GET requests to set INA219 Calibration ***********/
    server.on("/setcalc", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
        INA219.setCalibration_32V_2A();
    });
    server.on("/setcalb", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
        INA219.setCalibration_32V_1A();
    });
    server.on("/setcala", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
        INA219.setCalibration_16V_400mA();
    });
    /************************************************************/

    /********* GET requests to send files from SPIFFS ***********/
    server.on("/index.html", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html");
    });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/style.css", "text/css");
    });
    server.on("/datahandler.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/datahandler.js", "text/javascript");
    });
    server.on("/graph.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/graph.js", "text/javascript");
    });
    server.on("/theme.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/theme.js", "text/javascript");
    });
    server.on("/service-worker.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/service-worker.js", "text/javascript");
    });
    server.on("/manifest.json", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/manifest.json", "application/json");
    });
    server.on("/meter.png", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/meter.png", "image/png");
    });
    server.on("/meter-large.png", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/meter-large.png", "image/png");
    });
    server.on("/git.png", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/git.png");
    });
    /************************************************************/
}
/************************************************************/
