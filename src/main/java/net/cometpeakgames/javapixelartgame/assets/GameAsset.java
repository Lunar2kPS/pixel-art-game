package net.cometpeakgames.javapixelartgame.assets;

import java.io.Serializable;
import java.util.UUID;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;

public class GameAsset implements Serializable {
    @JsonProperty private String guid;

    public GameAsset() {
        guid = UUID.randomUUID().toString();

    }
}
