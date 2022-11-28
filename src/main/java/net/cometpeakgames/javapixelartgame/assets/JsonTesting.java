package net.cometpeakgames.javapixelartgame.assets;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.fasterxml.jackson.annotation.JsonInclude.Include;
import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.core.util.DefaultPrettyPrinter;
import com.fasterxml.jackson.core.util.MinimalPrettyPrinter;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;

public class JsonTesting {
    public static void Test() {
        ObjectMapper mapper = new ObjectMapper();
        mapper.setSerializationInclusion(Include.NON_NULL);
        mapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
        // mapper.enable(SerializationFeature.)
        // mapper.configure
        // mapper.configure(SerializationFeature.INDENT_OUTPUT, true);

        DefaultPrettyPrinter pp = new DefaultPrettyPrinter()
            .withoutSpacesInObjectEntries()
            // .withArrayIndenter(new DefaultPrettyPrinter.NopIndenter())
            ;

        // ObjectWriter w = new ObjectMapper()
        //     .writer()
        //     .with(pp);
        mapper.writer(pp);

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

        obj.exampleArray = new int[] {
            3, 5, 7
        };
        obj.exampleMap = new HashMap<String, String>();
        obj.exampleMap.put("key1", "value1");
        obj.exampleMap.put("key2", "value2");
        obj.exampleMap.put("key3", "value3");
        obj.exampleMap.put("key0", "value0");

        mapper.configure(SerializationFeature.ORDER_MAP_ENTRIES_BY_KEYS, true);
        try {
            // System.out.println(mapper.writer(pp).writeValueAsString(obj));

            System.out.println(mapper.writer(new MinimalPrettyPrinter() {
                private final int tabSize = 2;
                private int indentLevel = 0;
                
                @Override
                public void writeStartObject(JsonGenerator generator) throws IOException {
                    indentLevel++;
                    generator.writeRaw('{');
                    generator.writeRaw('\n');
                }

                @Override
                public void writeEndObject(JsonGenerator generator, int valueCount) throws IOException {
                    indentLevel--;
                    generator.writeRaw('\n');
                    writeIndentSpace(generator);
                    generator.writeRaw('}');
                }

                @Override
                public void writeStartArray(JsonGenerator generator) throws IOException {
                    indentLevel++;
                    generator.writeRaw('[');
                    generator.writeRaw('\n');
                    writeIndentSpace(generator);
                }

                @Override
                public void writeEndArray(JsonGenerator generator, int valueCount) throws IOException {
                    indentLevel--;
                    generator.writeRaw('\n');
                    writeIndentSpace(generator);
                    generator.writeRaw(']');
                }
                
                @Override
                public void writeObjectEntrySeparator(JsonGenerator generator) throws IOException {
                    generator.writeRaw(',');
                    generator.writeRaw('\n');
                    writeIndentSpace(generator);
                }

                @Override
                public void writeArrayValueSeparator(JsonGenerator generator) throws IOException {
                    generator.writeRaw(',');
                    generator.writeRaw('\n');
                    writeIndentSpace(generator);
                }

                @Override
                public void writeObjectFieldValueSeparator(JsonGenerator generator) throws IOException {
                    generator.writeRaw(':');
                    generator.writeRaw(' ');
                }

                @Override
                public void beforeObjectEntries(JsonGenerator generator) throws IOException {
                    writeIndentSpace(generator);
                }

                private void writeIndentSpace(JsonGenerator generator) throws IOException {
                    for (int i = 0; i < indentLevel; i++) {
                        for (int j = 0; j < tabSize; j++) {
                            generator.writeRaw(' ');
                        }
                    }
                }
            }).writeValueAsString(obj));
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            return;
        }
    }
}
