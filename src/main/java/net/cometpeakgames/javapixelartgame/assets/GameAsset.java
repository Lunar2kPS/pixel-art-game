package net.cometpeakgames.javapixelartgame.assets;

import java.io.Serializable;
import java.util.UUID;

import com.fasterxml.jackson.annotation.JsonProperty;

//TODO: Custom annotations to avoid exposing JSON-specific Jackson annotations:
//https://bsideup.github.io/posts/custom_jackson_annotations/
public abstract class GameAsset implements Serializable {
    @JsonProperty private String className;
    @JsonProperty private String guid;

    public String getGuid() { return guid; }
    
    protected GameAsset() {
        System.out.println("WARNING: GameAsset ctr created className and guid!");
        className = getClass().getTypeName();
        guid = UUID.randomUUID().toString();
    }

    protected static void reate() {
    }
}
