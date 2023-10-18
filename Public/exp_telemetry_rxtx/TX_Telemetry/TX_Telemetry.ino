// Transfer Telemetry Data to Uart Port.
// This Sample Code is compatible with any arduino board.
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
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int32_t a=12;     // 4 byte 
  float b=126.654;  // 4 byte
  
  u_data.int32_data = a;
  PAYLOAD[0]=u_data.byteVec_data[0];
  PAYLOAD[1]=u_data.byteVec_data[1];
  PAYLOAD[2]=u_data.byteVec_data[2];
  PAYLOAD[3]=u_data.byteVec_data[3];

  u_data.float_data = b;
  PAYLOAD[4]=u_data.byteVec_data[0];
  PAYLOAD[5]=u_data.byteVec_data[1];
  PAYLOAD[6]=u_data.byteVec_data[2];
  PAYLOAD[7]=u_data.byteVec_data[3];
  
  SEQ++;
  
  CHECKSUM = LEN + ID;
  for(int i=0; i<sizeof(PAYLOAD); i++)
  CHECKSUM = CHECKSUM + PAYLOAD[i];
  
  uint8_t data[13] = {STX,LEN,SEQ,ID,PAYLOAD[0],PAYLOAD[1],PAYLOAD[2],PAYLOAD[3],PAYLOAD[4],PAYLOAD[5],PAYLOAD[6],PAYLOAD[7], CHECKSUM};
  
  Serial.write(data,sizeof(data));
  delay(1000);
  
}
