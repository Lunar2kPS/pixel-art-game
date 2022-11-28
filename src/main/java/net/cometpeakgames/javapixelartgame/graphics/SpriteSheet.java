package net.cometpeakgames.javapixelartgame.graphics;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.URL;
import java.nio.file.Path;

import javax.imageio.ImageIO;

import com.fasterxml.jackson.annotation.JsonCreator;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.databind.annotation.JsonSerialize;

import net.cometpeakgames.javapixelartgame.assets.GameAsset;

@JsonSerialize
public class SpriteSheet extends GameAsset {
    public static final int MAX_SIZE = 4096;

    public final String filePath;
    public final int width;
    public final int height;
    
    private int[] pixels;

    @JsonCreator
    public SpriteSheet(
        @JsonProperty("filePath") String filePath,
        @JsonProperty("width") int width,
        @JsonProperty("height") int height) {
        if (filePath == null || filePath.isBlank())
            throw new IllegalArgumentException("You must provide a non-null and non-blank value for the file path.");
        if (width <= 0 || width >= MAX_SIZE)
            throw new IllegalArgumentException("The " + getClass().getTypeName() + " width must be in range: [1, " + MAX_SIZE + ")");
        if (height <= 0 || height >= MAX_SIZE)
            throw new IllegalArgumentException("The " + getClass().getTypeName() + " height must be in range: [1, " + MAX_SIZE + ")");
        
        this.filePath = filePath;
        this.width = width;
        this.height = height;

        pixels = new int[width * height];
        load();
    }

    private void load() {
        try {
            File file = new File(filePath);
            if (!file.exists())
                throw new FileNotFoundException("Unable to find file at " + filePath + "!");

            BufferedImage image = ImageIO.read(file);
            int w = image.getWidth();
            int h = image.getHeight();
            image.getRGB(0, 0, w, h, pixels, 0, w);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
