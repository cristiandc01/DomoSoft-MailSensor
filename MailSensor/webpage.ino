void homeweb() {
  if (E_MQ == 1) {
    Main = SPIFFS.open("/home_mqtt.html", "r");
    String ciaoF;
    while (Main.available()) {
      ciaoF += char(Main.read());
    }
    Main.close();
    server.send(200, "text/html", ciaoF);
    ciaoF = "";
  } else {
    Main = SPIFFS.open("/home.html", "r");
    String ciaoF;
    while (Main.available()) {
      ciaoF += char(Main.read());
    }
    Main.close();
    server.send(200, "text/html", ciaoF);
    ciaoF = "";
  }
}


void cloudweb(String add) {
  Main = SPIFFS.open("/cloud.html", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();

  server.send(200, "text/html", ciaoF + add);
  ciaoF = "";
}


void netweb(String add) {
  Main = SPIFFS.open("/net.html", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();

  server.send(200, "text/html", ciaoF + add);
  ciaoF = "";
}



void infoweb(String add) {
  Main = SPIFFS.open("/inf.html", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();

  server.send(200, "text/html", ciaoF + version + add);
  ciaoF = "";
}


void setweb(String add) {
  Main = SPIFFS.open("/set.html", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();

  server.send(200, "text/html", ciaoF + version + add);
  ciaoF = "";
}



void mailweb(String add) {
  Main = SPIFFS.open("/mail.html", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();
  server.send(200, "text/html", ciaoF + add);
  ciaoF = "";
}

void mqttweb(String add) {
  Main = SPIFFS.open("/mq.html", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();

  server.send(200, "text/html", ciaoF + add);
  ciaoF = "";
}

void secweb(String add) {
  Main = SPIFFS.open("/sec.html", "r");
  String ciaoF;
  while (Main.available()) {
    ciaoF += char(Main.read());
  }
  Main.close();
  server.send(200, "text/html", ciaoF + add);
  ciaoF = "";
}
