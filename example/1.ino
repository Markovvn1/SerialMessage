#include <SerialMessage.h> // Подключение библиотеки для обработки сообщений с СОМ-порта

SerialMessage serialMessage;

// Обработчик собитий
long onGetMessage(String message_name, long message)
{
  if (message_name == "get8")
    return 8;

  if (message_name == "get7")
    return 7;

  if (message_name == "mult2")
    return message * 2;

  return 0;
}

void setup()
{
  serialMessage.init(); // Инициализация
  serialMessage.setOnGetMessage(onGetMessage); // Установка обработчика собития получения сообщения
}


void loop()
{  
  serialMessage.checkMessage(); // Проверка наличия сообщения
}

