void SendMail() {
  
  EMailSender emailSend(String(SMTPmail).c_str(), String(SMTPassword).c_str());
 // EMailSender(String(SMTPmail).c_str(), String(SMTPassword).c_str(), String(SMTmail).c_str(), "server", 587, true);
  EMailSender::EMailMessage message;
  message.subject = String(subject);
  message.message = String(messaggio);

  EMailSender::Response resp = emailSend.send(String(email).c_str(), message);

}


void ConfMail() {
  Main = SPIFFS.open("/email/smtp_user", "r");

  while (Main.available()) {

    SMTPmail += char(Main.read());
  }
  Main.close();
  Serial.println(SMTPmail);
  Main = SPIFFS.open("/email/smtp_password", "r");

  while (Main.available()) {

    SMTPassword += char(Main.read());
  }
  Main.close();
  Serial.println(SMTPassword);
  Main = SPIFFS.open("/email/email", "r");

  while (Main.available()) {

    email += char(Main.read());
  }
  Main.close();
Serial.println(email);
  Main = SPIFFS.open("/email/subject", "r");

  while (Main.available()) {

    subject += char(Main.read());
  }
  Main.close();
  Serial.println(subject);
    Main = SPIFFS.open("/email/message", "r");

  while (Main.available()) {

    messaggio += char(Main.read());
  }
  Main.close();

  Serial.println(messaggio);
}
