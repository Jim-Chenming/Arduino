# Arduino

#include <WiFi.h>
//静态地址、网关、子网掩码
IPAddress local_IP(192, 168, 1, 47);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
//设置（要在WiFi连接之后才调用config）
WiFi.config(local_IP, gateway, subnet);//设置静态IP
