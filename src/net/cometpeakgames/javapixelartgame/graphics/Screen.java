package net.cometpeakgames.javapixelartgame.graphics;

import java.awt.Color;

//NOTE: Top-left corner is (0, 0)
public class Screen {
    private int width;
    private int height;
    private int[] pixels;

    public Screen(int width, int height) {
        this.width = width;
        this.height = height;
        pixels = new int[width * height];
    }

    public void clear() {
        for (int i = 0; i < pixels.length; i++)
            pixels[i] = 0x00000000;
    }

    public void render() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int i = x + y * width;
                // pixels[i] = new Color((float) x / width, 1 - (float) y / height, 0, 1).getRGB();
                pixels[i] = 0xFF000000;
            }
        }
    }

    //TODO: Argument validation
    public void CopyPixelsInto(int[] targetPixels) {
        for (int i = 0; i < targetPixels.length; i++)
            targetPixels[i] = pixels[i];
    }
}
