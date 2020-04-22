void bootConfig() {
  wifi_ok = 1;

  Main = SPIFFS.open("/device_name", "r");

  while (Main.available()) {

    devname += char(Main.read());
  }
  Main.close();
  devname2 = "Sensor " + devname;
  WiFi.hostname(devname2);
  ConfMail();
  if (mqtt_conf) {


    discovered = EEPROM.read(201);
    hassio_prefix = "";
    Main = SPIFFS.open("/discovery/prefix", "r");

    while (Main.available()) {

      hassio_prefix += char(Main.read());
    }
    Main.close();

    sensor_status_topic = "sensor/button/trig_" + devname;
    vdd_status_topic = "sensor/battery/voltage_" + devname;
    perc_status_topic = "sensor/battery/perc_" + devname;
    mqtt_server = "";
    for (int i = 108; i < 123; ++i)
    {
      mqtt_server += char(EEPROM.read(i));
    }

    mqtt_user = "";
    for (int i = 124; i < 144; ++i)
    {
      mqtt_user += char(EEPROM.read(i));
    }

    mqtt_password = "";
    for (int i = 145; i < 165; ++i)
    {
      mqtt_password  += char(EEPROM.read(i));
    }


    client.setServer(mqtt_server.c_str(), 1883);

    lastReconnectAttempt = 0;
    if (mqtt_conn()) { //tento la prima connessione
      lastReconnectAttempt = 0;
      E_MQ = 0;
    }
  }
  digitalWrite(LED_BUILTIN, HIGH);
}
