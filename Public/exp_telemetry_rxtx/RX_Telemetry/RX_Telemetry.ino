// Receive Telemetry Data to Uart2 Port.
// This Sample Code is compatible with any arduino board taht have at leat two UART port. eg Arduino mega2560
// The Transfer packet data format is as below:
// uint8_t data[13] = {STX,LEN,SEQ,ID,PAYLOAD[0],PAYLOAD[1],PAYLOAD[2],PAYLOAD[3],PAYLOAD[4],PAYLOAD[5],PAYLOAD[6],PAYLOAD[7], CHECKSUM};
// PAYLOAD[0] to PAYLOAD [3] are for one int32_t data.
// PAYLOAD[4] to PAYLOAD [7] are for one float data.

union union_data{

  int32_t int32_data;       // 4 byte
  float   float_data;       // 4 byte
  uint8_t byteVec_data[4];
    
}u_data;

uint8_t STX=0xFE;   // Packet start marker
uint8_t LEN = 8;    // Payload length: 4 byte float + 4 byte int32_t
uint8_t SEQ = 0;    // Packet sequence number. Used to detect packet loss. Components increment value for each message sent.
uint8_t ID = 12;    // ID of message type in payload. Used to decode data back into message object.
uint8_t PAYLOAD[8]; // Message data. Content depends on message type (i.e. Message ID).
uint8_t CHECKSUM;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int32_t a;     // 4 byte 
  float b;       // 4 byte

  uint8_t data[13];
  
  if(Serial2.available() >= 13){

    data[0]=Serial2.read();

    if((data[0]== STX)){
      
      data[1]=Serial2.read();
      data[2]=Serial2.read();
      data[3]=Serial2.read();

      CHECKSUM = data[1] + data[3];
    
      for(int i=0; i<data[1]; i++)
      {  
        data[i+4]=Serial2.read();
        CHECKSUM = CHECKSUM + data[i+4];
      }

      data[12] = Serial2.read();    // CHECKSUM data

      if(data[12] == CHECKSUM)
      {
        for(int i=0; i<4; i++)
        u_data.byteVec_data[i] = data[i+4];
        
        a = u_data.int32_data;

        for(int i=0; i<4; i++)
        u_data.byteVec_data[i] = data[i+8];
        
        b = u_data.float_data;
      }
    }
    Serial.print("a = ");
    Serial.print(a);
    Serial.print(" b = ");
    Serial.println(b,3);
  }
  
  delay(100);
}
