HTTPClient http;



void normalset () {





  server.on("/", []() {
    if (username == "") {
      homeweb();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      homeweb();
    }
  });


  server.on("/macadd", []() {
    if (username == "") {
      server.send(200, "text/html", String(WiFi.macAddress()));
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      server.send(200, "text/html", String(WiFi.macAddress()));
    }
  });


  server.on("/settings", []() {
    if (username == "") {
      setweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      setweb("");
    }
  });

  server.on("/info", []() {
    if (username == "") {
      infoweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      infoweb("");
    }
  });

  server.on("/network", []() {

    if (username == "") {
      netweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      netweb("");
    }

  });


  server.on("/test", []() {

    if (username == "") {
      testSys(); 
      server.send(200, "text/html", "OK");


    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      testSys();
      server.send(200, "text/html", "OK");


    }

  });


  server.on("/setwifi", []() {
    if (username == "") {
      String qsid = server.arg("ssid");
      String qpass = server.arg("password");

      if (qsid.length() > 0 && qpass.length() > 0) {
        netweb("Ok, rete cambiata!<br>Mi connetto alla nuova rete...");
        delay(1000);
        WiFi.disconnect();
        WiFi.begin(qsid, qpass);




      } else {
        netweb("Errore, il nome rete non può essere vuoto");
      }
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String qsid = server.arg("ssid");
      String qpass = server.arg("password");

      if (qsid.length() > 0 && qpass.length() > 0) {
        netweb("Ok, rete cambiata!<br>Mi connetto alla nuova rete...");
        delay(1000);
        WiFi.disconnect();
        WiFi.begin(qsid, qpass);



      } else {
        netweb("Errore, il nome rete non può essere vuoto");
      }
    }
  });



  server.on("/reset", []() {      //reset the system
    if (username == "") {
      server.send(200, "text/html", "<h2>Ripristino compleatato! Riavvio in corso...</h2>");

      for (int i = 0; i < 360; ++i) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
      delay(1000);
      ESP.restart();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);
      server.send(200, "text/html", "<h2>Ripristino compleatato! Riavvio in corso...</h2>");

      for (int i = 0; i < 360; ++i) {
        EEPROM.write(i, 0);
      }
      EEPROM.commit();
      delay(1000);
      ESP.restart();
    }
  });


  server.on("/mailconf", []() {

    if (username == "") {
      mailweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      mailweb("");
    }

  });

  server.on("/mailstat", []() {

    if (username == "") {


      String aroma = server.arg("q");

      if (aroma == "on") {

        mail_conf = 1;
        EEPROM.write(204, mail_conf);
        EEPROM.commit();
      } else {

        mail_conf = 0;
        EEPROM.write(202, mail_conf);
        EEPROM.commit();




      }
      mailweb("<h3>Salvataggio avvenuto</h3>");



    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String aroma = server.arg("q");

      if (aroma == "on") {

        mail_conf = 1;
        EEPROM.write(204, mail_conf);
        EEPROM.commit();
      } else {

        mail_conf = 0;
        EEPROM.write(202, mail_conf);
        EEPROM.commit();




      }
      mailweb("<h3>Salvataggio avvenuto</h3>");


    }

  });

  server.on("/mail/status", []() {

    if (username == "") {
      server.send(200, "text/html", String(mail_conf));
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      server.send(200, "text/html", String(mail_conf));
    }

  });


  server.on("/mailSet", []() {       //this part set a password to system http

    if (username == "") {

      SMTPmail = server.arg("email");
      SMTPassword = server.arg("pwd");

      Main = SPIFFS.open("/email/smtp_user", "w");
      Main.print(SMTPmail);
      Main.close();

      Main = SPIFFS.open("/email/smtp_password", "w");
      Main.print(SMTPassword);
      Main.close();
      mailweb("<h3>Salvataggio avvenuto<br></h3>");





    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);


      SMTPmail = server.arg("email");
      SMTPassword = server.arg("pwd");

      Main = SPIFFS.open("/email/smtp_user", "w");
      Main.print(SMTPmail);
      Main.close();

      Main = SPIFFS.open("/email/smtp_password", "w");
      Main.print(SMTPassword);
      Main.close();
      mailweb("<h3>Salvataggio avvenuto<br></h3>");



    }

  });

  server.on("/mailTo", []() {       //this part set a password to system http

    if (username == "") {

      email = server.arg("to");
      Main = SPIFFS.open("/email/email", "w");
      Main.print(email);
      Main.close();
      mailweb("<h3>Salvataggio avvenuto<br></h3>");

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);

      email = server.arg("to");
      Main = SPIFFS.open("/email/email", "w");
      Main.print(email);
      Main.close();
      mailweb("<h3>Salvataggio avvenuto<br></h3>");
    }

  });


  server.on("/mailText", []() {       //this part set a password to system http

    if (username == "") {

      subject = server.arg("subject");
      messaggio = server.arg("messaggio");
      Main = SPIFFS.open("/email/subject", "w");
      Main.print(subject);
      Main.close();
      Main = SPIFFS.open("/email/message", "w");
      Main.print(messaggio);
      Main.close();
      mailweb("<h3>Salvataggio avvenuto<br></h3>");

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);

      subject = server.arg("subject");
      messaggio = server.arg("messaggio");
      Main = SPIFFS.open("/email/subject", "w");
      Main.print(subject);
      Main.close();
      Main = SPIFFS.open("/email/message", "w");
      Main.print(messaggio);
      Main.close();
      mailweb("<h3>Salvataggio avvenuto<br></h3>");

    }

  });


  server.on("/mqttconf", []() {

    if (username == "") {
      mqttweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      mqttweb("");
    }

  });


  server.on("/mqttconf/status", []() {
    if (username == "") {
      if (!mqtt_conf) {
        server.send(200, "text/html", "0");
      } else {
        if (client.connected()) {
          server.send(200, "text/html", "1");
        } else {
          server.send(200, "text/html", "2");
        }
      }
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      if (!mqtt_conf) {
        server.send(200, "text/html", "0"  );
      } else {
        if (client.connected()) {
          server.send(200, "text/html", "1"  );
        } else {
          server.send(200, "text/html", "2" );
        }
      }
    }
  });

  server.on("/discovery", []() {
    if (username == "") {
      String prefix = server.arg("prefix");

      if (prefix == "") {
      } else {
        hassio_prefix = prefix;

        Main = SPIFFS.open("/discovery/prefix", "r");
        Main.print(prefix);
        Main.close();
      }

      discover();

      mqttweb("<h3>Comando inviato!</h3>");

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      String prefix = server.arg("prefix");
      if (prefix == "") {
      } else {
        hassio_prefix = prefix;

        Main = SPIFFS.open("/discovery/prefix", "r");
        Main.print(prefix);
        Main.close();
      }
      discover();

      mqttweb("<h3>Comando inviato!</h3>");

    }
  });


  server.on("/discovery/delete", []() {
    if (username == "") {
      String prefix = server.arg("prefix");
      if (prefix == "") {
      } else {
        hassio_prefix = prefix;
      }
      deleteConfig();
      mqttweb("<h3>Comando inviato!</h3>");

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      String prefix = server.arg("prefix");
      if (prefix == "") {
      } else {
        hassio_prefix = prefix;
      }
      deleteConfig();
      mqttweb("<h3>Comando inviato!</h3>");

    }
  });

  server.on("/info/devname", []() {
    if (username == "") {

      server.send(200, "text/html", devname);


    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);


      server.send(200, "text/html", devname );

    }


  });


  server.on("/MQhost", []() {

    if (username == "") {
      mqtt_server = server.arg("iphost");

      if (mqtt_server.length() >= 16) {
        mqttweb("<h3>Errore!<br>Indirizzo troppo lungo</h3>");
      } else {
        for (int i = 108; i < 123; ++i) {
          EEPROM.write(i, 0);
        }
        for (int i = 0; i < mqtt_server.length(); ++i)
        {
          EEPROM.write(108 + i, mqtt_server[i]);
          //Serial.print("Wrote: ");
          //Serial.println(mqtt_server[i]);
        }

        EEPROM.commit();
        mqttweb("<h3>Salvataggio avvenuto</h3>");
      }
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      mqtt_server = server.arg("iphost");

      if (mqtt_server.length() >= 16) {
        mqttweb("<h3>Errore!<br>Indirizzo troppo lungo</h3>");
      } else {
        for (int i = 108; i < 123; ++i) {
          EEPROM.write(i, 0);
        }
        for (int i = 0; i < mqtt_server.length(); ++i)
        {
          EEPROM.write(108 + i, mqtt_server[i]);
          //Serial.print("Wrote: ");
          //Serial.println(mqtt_server[i]);
        }

        EEPROM.commit();
        mqttweb("<h3>Salvataggio avvenuto</h3>");
      }
    }

  });

  server.on("/mqttstat", []() {

    if (username == "") {
      String aroma = server.arg("q");

      if (aroma == "on") {

        mqtt_conf = 1;
        EEPROM.write(202, mqtt_conf);
        EEPROM.commit();
      } else {

        mqtt_conf = 0;
        EEPROM.write(202, mqtt_conf);
        EEPROM.commit();




      }
      mqttweb("<h3>Salvataggio avvenuto, <br>Riavvio in corso...</h3>");
      delay(800);

      ESP.restart();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String aroma = server.arg("q");

      if (aroma == "on") {

        mqtt_conf = 1;
        EEPROM.write(202, mqtt_conf);
        EEPROM.commit();
      } else {

        mqtt_conf = 0;
        EEPROM.write(202, mqtt_conf);
        EEPROM.commit();




      }
      mqttweb("<h3>Salvataggio avvenuto, <br>Riavvio in corso...</h3>");
      delay(800);


      ESP.restart();
    }

  });



  server.on("/mqttreboot", []() {
    if (username == "") {
      mqtt_conf = 1;
      E_MQ = 0;
      homeweb();
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      mqtt_conf = 1;
      E_MQ = 0;
      homeweb();
    }
  });



  server.on("/MQuser", []() {        //set the mqtt user and password

    if (username == "") {
      mqtt_user = server.arg("username");
      mqtt_password = server.arg("pwd");

      if (mqtt_user.length() >= 21) {
        mqttweb("<h3>Errore!<br>nome utente troppo lungo (Max 20 caratteri)</h3>");
      } else {

        if (mqtt_password.length() >= 21) {
          mqttweb("<h3>Errore!<br>password troppo lunga (Max 20 caratteri)</h3>");
        } else {
          for (int i = 124; i < 144; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < mqtt_user.length(); ++i)
          {
            EEPROM.write(124 + i, mqtt_user[i]);
            //Serial.print("Wrote: ");
            //  Serial.println(mqtt_user[i]);
          }
          for (int i = 145; i < 165; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < mqtt_password.length(); ++i)
          {
            EEPROM.write(145 + i, mqtt_password[i]);
            //Serial.print("Wrote: ");
            //Serial.println(mqtt_password[i]);
          }

          EEPROM.commit();
          mqttweb("<h3>Salvataggio avvenuto..</h3>");
        }
      }
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);
      mqtt_user = server.arg("username");
      mqtt_password = server.arg("pwd");

      if (mqtt_user.length() >= 21) {
        mqttweb("<h3>Errore!<br>nome utente troppo lungo (Max 20 caratteri)</h3>");
      } else {

        if (mqtt_password.length() >= 21) {
          mqttweb("<h3>Errore!<br>password troppo lunga (Max 20 caratteri)</h3>");
        } else {
          for (int i = 124; i < 144; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < mqtt_user.length(); ++i)
          {
            EEPROM.write(124 + i, mqtt_user[i]);
            //Serial.print("Wrote: ");
            //  Serial.println(mqtt_user[i]);
          }
          for (int i = 145; i < 165; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < mqtt_password.length(); ++i)
          {
            EEPROM.write(145 + i, mqtt_password[i]);
            //Serial.print("Wrote: ");
            //Serial.println(mqtt_password[i]);
          }

          EEPROM.commit();
          mqttweb("<h3>Salvataggio avvenuto..</h3>");
        }
      }
    }

  });






  server.on("/security", []() {      //print the security page
    if (username == "") {
      secweb("");
    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);
      secweb("");
    }
  });


  server.on("/protect", []() {       //this part set a password to system http

    if (username == "") {
      username = "";
      password = "";
      username = server.arg("username");
      password = server.arg("password");
      if (username.length() >= 14) {
        secweb("<h3>Errore!<br>Username troppo lungo max 14</h3>");
      } else {
        if (password.length() >= 18) {
          secweb("<h3>Errore!<br>Password troppo lunga max 18</h3>");
        } else {
          for (int i = 166; i < 180; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < username.length(); ++i)
          {
            EEPROM.write(166 + i, username[i]);
          }

          for (int i = 181; i < 199; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < password.length(); ++i)
          {
            EEPROM.write(181 + i, password[i]);
          }

          EEPROM.commit();
          secweb("<h3>Salvataggio avvenuto<br></h3>");

        }
      }



    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(DIGEST_AUTH, realm);
      username = "";
      password = "";
      username = server.arg("username");
      password = server.arg("password");
      if (username.length() >= 14) {
        secweb("<h3>Errore!<br>Username troppo lungo max 14</h3>");
      } else {
        if (password.length() >= 18) {
          secweb("<h3>Errore!<br>Password troppo lunga max 18</h3>");
        } else {
          for (int i = 166; i < 180; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < username.length(); ++i)
          {
            EEPROM.write(166 + i, username[i]);
          }

          for (int i = 181; i < 199; ++i) {
            EEPROM.write(i, 0);
          }
          for (int i = 0; i < password.length(); ++i)
          {
            EEPROM.write(181 + i, password[i]);
          }

          EEPROM.commit();
          secweb("<h3>Salvataggio avvenuto<br></h3>");

        }
      }
    }

  });

  server.on("/setName", []() {

    if (username == "") {
      String nome = server.arg("name");




      Main = SPIFFS.open("/device_name", "w");
      Main.print(nome);
      Main.close();

      setweb("<h3>Salvataggio avvenuto!</h3>");
      delay(800);
      ESP.restart();

    } else {
      if (!server.authenticate(username.c_str(), password.c_str()))
        return server.requestAuthentication(BASIC_AUTH, realm);

      String nome = server.arg("name");




      Main = SPIFFS.open("/device_name", "w");
      Main.print(nome);
      Main.close();

      setweb("<h3>Salvataggio avvenuto!</h3>");
      delay(800);
      ESP.restart();
    }

  });

  httpUpdater.setup(&server, update_path);
  server.begin();
  //Serial.println("HTTP server started");

}
