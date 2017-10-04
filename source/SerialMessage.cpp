#include "SerialMessage.h"

void SerialMessage::clearMessage()
{
  cur_id_data = 0;
  cur_pos_data = 0;

  message_id = 0;
  message = 0;
}

void SerialMessage::nextPartMessage()
{
  cur_id_data++;
  cur_pos_data = 0;
}

void SerialMessage::sendMessage(long message_id, long message)
{
  for (int i = 3; i >=0; i--)
  {
    Serial.print(char((message_id >> (i * 8)) & 255));
  }
  
  for (int i = 3; i >=0; i--)
  {
    Serial.print(char((message >> (i * 8)) & 255));
  }
}

void SerialMessage::init()
{
  Serial.begin(115200);
  Serial.setTimeout(20);

  clearMessage();

  onGetMessage = NULL;
  start = true;
}

bool SerialMessage::checkMessage()
{
  if (start)
  {
    Serial.print('g');
    start = false;
    return false;
  }
  
  if (Serial.available() <= 0)
  {
    return false;
  }
      

  char data = Serial.read();


  cur_pos_data++;

  switch (cur_id_data)
  {
    case 0:
      message_id = (message_id << 8) | (data & 255);

      if (cur_pos_data >= 4)
        nextPartMessage();
    
      break;

    case 1:
      message_name[cur_pos_data - 1] = data;

      if (cur_pos_data >= 20)
        nextPartMessage();
    
      break;

    case 2:
      message = (message << 8) | (data & 255);

      if (cur_pos_data >= 4)
      {
        if (onGetMessage != NULL)
          message_name[20] = 0;
          String message_name_temp = String(message_name);

          if (message_name_temp == "hello" && message == -38098347)
          {
            sendMessage(message_id, -74389083); // Hello, world!
          }
          else
            sendMessage(message_id, onGetMessage(message_name_temp, message));

        clearMessage();
      }
    
      break;
  }

  return true;
}

void SerialMessage::setOnGetMessage(long (*onGetMessage)(String, long))
{
  this->onGetMessage = onGetMessage;
}