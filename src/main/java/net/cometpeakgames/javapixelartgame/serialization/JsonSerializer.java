package net.cometpeakgames.javapixelartgame.serialization;

import com.fasterxml.jackson.annotation.JsonInclude.Include;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.ObjectWriter;
import com.fasterxml.jackson.databind.SerializationFeature;

//NOTE: Custom deserializers on a per-type basis: https://andrewtarry.com/posts/deserialising-an-interface-with-jackson/
public class JsonSerializer implements ITextSerializer {
    private ObjectMapper objectMapper;
    private ObjectWriter objectWriter;
    
    @Override
    public String serialize(Object object) throws SerializationException {
        createMapperIfNeeded();
        createWriterIfNeeded();

        try {
            return objectWriter.writeValueAsString(object);
        } catch (JsonProcessingException e) {
            e.printStackTrace();
            throw new SerializationException();
        }
    }

    @Override
    public <T> T deserialize(String json, Class<T> type) throws SerializationException {
        createMapperIfNeeded();
        try {
            return (T) objectMapper.readValue(json, type);
        } catch (JsonProcessingException e) {
            throw new SerializationException();
        }
    }
    
    private boolean createMapperIfNeeded() {
        if (objectMapper == null) {
            objectMapper = new ObjectMapper();
            objectMapper.setSerializationInclusion(Include.NON_NULL);
            objectMapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
            objectMapper.configure(SerializationFeature.ORDER_MAP_ENTRIES_BY_KEYS, true);
    
            return true;
        }
        return false;
    }

    private boolean createWriterIfNeeded() {
        if (objectWriter == null) {
            objectWriter = objectMapper.writer(new StandardJSONPrettyPrinter());
            return true;
        }
        return false;
    }
}
