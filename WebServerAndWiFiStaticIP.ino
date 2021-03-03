#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#define MY_SSID         "CMC"         //默认WIFI名称
#define MY_SSID_PW      "CJW88rfessd" //默认WIFI密码
const char* ssid = MY_SSID;
const char* password = MY_SSID_PW;
const int led = 4;
//静态地址、网关、子网掩码
IPAddress local_IP(192, 168, 1, 47);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WebServer server(80);
//**********************

//首页
void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/html", "<h1>Home</h1>");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

//**********************
void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
//设置
WiFi.config(local_IP, gateway, subnet);//设置静态IP
  Serial.print("\r\nConnected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
