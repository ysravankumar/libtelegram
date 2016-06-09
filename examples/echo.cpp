/// This example demonstrates a minimal bot that just echoes back what it reads.

#include "libtelegram/libtelegram.h"

auto main()->int {
  std::string const token("bot123456:ABC-DEF1234ghIkl-zyx57W2v1u123ew11");      // in practice you would probably read this from config file or database
  telegram::listener listener;                                                  // create a listener which will process incoming requests
  telegram::sender sender(token);                                               // create a sender with our token for outgoing messages
  listener.set_callback_message([&](telegram::types::message const &message){   // we set a callback for receiving messages in native format, using a lambda for convenience
    std::string const message_from(message.from ? message.from->first_name : "Unknown sender"); // some fields, such as message.from, are optional
    std::string const reply(message_from + " sent \"" + message.text + "\" to chat id " + std::to_string(message.chat.id)); // each element is a native type - the chat id is an integer
    sender.send_message(message.chat.id, reply);                                // send our reply from within the callback
  });
  listener.run();                                                               // launch the listener - this call blocks until the fastcgi server drops us
  return EXIT_SUCCESS;
};
