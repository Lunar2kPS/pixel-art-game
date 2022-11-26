package net.cometpeakgames.javapixelartgame.graphics;

import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;

import javax.imageio.ImageIO;

public class SpriteSheet {
    public static final int MAX_SIZE = 4096;

    public final String filePath;
    public final int width;
    public final int height;
    
    private int[] pixels;

    public SpriteSheet(String filePath, int width, int height) {
        if (filePath == null || filePath.isBlank())
            throw new IllegalArgumentException("You must provide a non-null and non-blank value for the file path.");
        if (width <= 0 || width >= MAX_SIZE)
            throw new IllegalArgumentException("The " + getClass().getTypeName() + " width must be in range: [1, " + MAX_SIZE + ")");
        if (height <= 0 || height >= MAX_SIZE)
            throw new IllegalArgumentException("The " + getClass().getTypeName() + " height must be in range: [1, " + MAX_SIZE + ")");
        
        this.filePath = filePath;
        this.width = width;
        this.height = height;
        System.out.println(getClass().getTypeName() + " created!");

        pixels = new int[width * height];
        load();
    }

    private void load() {
        try {
            URL resourcePath = SpriteSheet.class.getResource(filePath);
            System.out.println(resourcePath);
            
            BufferedImage image = ImageIO.read(resourcePath);
            int w = image.getWidth();
            int h = image.getHeight();
            image.getRGB(0, 0, w, h, pixels, 0, w);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
