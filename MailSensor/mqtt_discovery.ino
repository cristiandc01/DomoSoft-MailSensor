void discover() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["name"] = devname;
  json["state_topic"] = sensor_status_topic;
  json["payload_on"] = "1";
  json["expire_after"] = "5";

  String topic = hassio_prefix + "/binary_sensor/domosoft/" + ESP.getFlashChipId()  + "/config";
  char JSONmessageBuffer[512];
  json.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));



  client.publish(topic.c_str(), JSONmessageBuffer, true);
  discovered = 1;
  EEPROM.write(201, discovered);
  EEPROM.commit();
}




void deleteConfig() {
  String topic = hassio_prefix + "/binary_sensor/domosoft/" + ESP.getFlashChipId()   + "/config";
  client.publish(topic.c_str(), "", true);

  discovered = 0;
  EEPROM.write(201, discovered);
  EEPROM.commit();
}
