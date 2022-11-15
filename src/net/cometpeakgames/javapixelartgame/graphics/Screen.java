package net.cometpeakgames.javapixelartgame.graphics;

import java.awt.Color;
import java.util.Random;

//NOTE: Top-left corner is (0, 0)
public class Screen {
    private int width;
    private int height;
    private int[] pixels;
    private int[] tiles;

    private final int tileSize = 16;
    private final int tileCountX = 8;
    private final int tileCountY = 8;
    private int xOffset;
    private int yOffset;

    public Screen(int width, int height) {
        this.width = width;
        this.height = height;
        pixels = new int[width * height];

        Random r = new Random();
        tiles = new int[tileCountX * tileCountY];
        for (int t = 0; t < tiles.length; t++)
            tiles[t] = 0xFF000000 + r.nextInt(0x00FFFFFF);
    }

    public void clear() {
        for (int i = 0; i < pixels.length; i++)
            pixels[i] = 0x00000000;
    }

    public void update() {
        xOffset++;
        if (xOffset % 10 == 0)
            yOffset++;
    }

    public void render() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int i = x + y * width;
                // pixels[i] = new Color((float) x / width, 1 - (float) y / height, 0, 1).getRGB();
                int tileIndex = (((x + xOffset) / tileSize) % tileCountX) + (((y + yOffset) / tileSize) % tileCountY) * tileCountX;
                pixels[i] = tiles[tileIndex];
            }
        }
    }

    //TODO: Argument validation
    public void CopyPixelsInto(int[] targetPixels) {
        for (int i = 0; i < targetPixels.length; i++)
            targetPixels[i] = pixels[i];
    }
}
