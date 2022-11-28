package net.cometpeakgames.javapixelartgame.assets;

import java.util.HashMap;

import net.cometpeakgames.javapixelartgame.serialization.ITextSerializer;
import net.cometpeakgames.javapixelartgame.serialization.JsonSerializer;
import net.cometpeakgames.javapixelartgame.serialization.SerializationException;

public class JsonTesting {
    public static void Test() {
        String json = "{\"name\":\"Carlos\"}";
        ITextSerializer serializer = new JsonSerializer();
        ExampleClass obj = new ExampleClass();
        
        try {
            obj = serializer.<ExampleClass>deserialize(json, ExampleClass.class);
        } catch (SerializationException e) {
            e.printStackTrace();
            return;
        }
        obj.exampleArray = new int[] {
            3, 5, 7
        };
        obj.exampleMap = new HashMap<String, String>();
        obj.exampleMap.put("key1", "value1");
        obj.exampleMap.put("key2", "value2");
        obj.exampleMap.put("key3", "value3");
        obj.exampleMap.put("key0", "value0");

        try {
            System.out.println(serializer.serialize(obj));
        } catch (SerializationException e) {
            e.printStackTrace();
            return;
        }
    }
}
