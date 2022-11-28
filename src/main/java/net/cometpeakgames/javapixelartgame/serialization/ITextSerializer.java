package net.cometpeakgames.javapixelartgame.serialization;

public interface ITextSerializer {
    public String serialize(Object object) throws SerializationException;
    public <T> T deserialize(String json, Class<T> type) throws SerializationException;
}
