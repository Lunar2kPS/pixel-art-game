package net.cometpeakgames.javapixelartgame.serialization;

import java.io.IOException;

import com.fasterxml.jackson.core.JsonGenerator;
import com.fasterxml.jackson.core.util.MinimalPrettyPrinter;

class StandardJSONPrettyPrinter extends MinimalPrettyPrinter {
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
}
