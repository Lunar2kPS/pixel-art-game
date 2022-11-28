package net.cometpeakgames.javapixelartgame.assets;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashMap;

import net.cometpeakgames.javapixelartgame.serialization.ITextSerializer;
import net.cometpeakgames.javapixelartgame.serialization.JsonSerializer;
import net.cometpeakgames.javapixelartgame.serialization.SerializationException;

public class JsonTesting {
    public static void Test() {
        System.out.println("\n\n--- --- JSON TESTING --- ---\n\n");
        ITextSerializer serializer = new JsonSerializer();

        // try {
        //     GameAsset test = new GameAsset();
        //     System.out.println(serializer.serialize(test));
        // } catch (SerializationException e) {
        //     e.printStackTrace();
        // }

        try {
            Class c = Class.forName("net.cometpeakgames.javapixelartgame.assets.GameAsset");
            System.out.println(c.getName());
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }

        
        try {
            String jsonTest = Files.readString(Paths.get("./resources/spritesheets/Terrain Tiles.json"));
            System.out.println(jsonTest);
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        String json = "{\"name\":\"Carlos\"}";
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
