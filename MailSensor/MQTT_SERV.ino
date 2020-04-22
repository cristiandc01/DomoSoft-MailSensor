

bool mqtt_conn() {

  // if (client.connect("ESP8266Client")) {
  if (client.connect(String(devname).c_str(), String(mqtt_user).c_str(), String(mqtt_password).c_str())) {
    //Serial.println("connected");

    MQTT_sync();


  }
  return client.connected();

}

/*

  void callback(String topic, byte* payload, unsigned int length) {
  String messaggio;
  // Serial.print("Message arrived [");
  // Serial.print(topic);
  // Serial.println("] ");

  for (int i = 0; i < length; i++) {

    messaggio += (char)payload[i];
  }
  delay(100);
    if (topic==rele1_control_topic) {

    if (messaggio=="1") {

    }else{

    }

    delay(1000);
  }



  }
*/

void MQTT_sync() {
  client.publish(sensor_status_topic.c_str(), String("1").c_str(), false);
  client.publish(vdd_status_topic.c_str(), String(vdd).c_str(), false);
  client.publish(perc_status_topic.c_str(), String(perc).c_str(), false);

}
