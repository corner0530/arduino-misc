#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(SS);

unsigned long rxId;
byte len;

byte send_data[1] = {0};
byte receive_data[1];

void setup() {
  Serial.begin(115200);

  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
    CAN0.setMode(MCP_NORMAL);
  else
    Serial.println("Error");
}

void loop() {
  send_data[0] += 2;
  //if (CAN0.checkReceive()) {
    CAN0.readMsgBuf(&rxId, &len, receive_data);
    Serial.println(receive_data[0]);
  //}
  //delay(100);
  CAN0.sendMsgBuf(0x101, 0, 1, send_data);
  delay(100);
}
