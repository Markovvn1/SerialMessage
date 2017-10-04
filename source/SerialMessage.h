#include "Arduino.h"

#ifndef LIB_SERIAL_MESSAGE
#define LIB_SERIAL_MESSAGE

class SerialMessage
{
  private:
    int cur_id_data;
    int cur_pos_data;

    long message_id;
    char message_name[21];
    long message;
    bool start;

    long (*onGetMessage)(String, long);

    void clearMessage();
    void nextPartMessage();
    void sendMessage(long message_id, long message);
    
  public:
    void init();
    bool checkMessage();
    void setOnGetMessage(long (*onGetMessage)(String, long));
};

#endif