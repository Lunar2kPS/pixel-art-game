package net.cometpeakgames.javapixelartgame.assets;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

public class JsonTesting {
    public static void Test() {
        ObjectMapper mapper = new ObjectMapper();
        String json = "{\"name\":\"Carlos\"}";

        ExampleClass obj = null;
        try {
            obj = mapper.readValue(json, ExampleClass.class);
        } catch (JsonMappingException e) {
            e.printStackTrace();
            return;
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return;
        }
        System.out.println(obj.name + ", " + obj.hp);

        try {
            System.out.println(mapper.writerWithDefaultPrettyPrinter().writeValueAsString(obj));
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return;
        }
    }
}
