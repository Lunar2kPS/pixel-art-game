package net.cometpeakgames.javapixelartgame.graphics;

import java.awt.Color;
import java.util.Random;

import net.cometpeakgames.javapixelartgame.input.Keyboard;
import net.cometpeakgames.javapixelartgame.util.MathUtility;

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

    private Keyboard keyboard;

    public Screen(int width, int height, Keyboard keyboard) {
        this.width = width;
        this.height = height;
        this.keyboard = keyboard;
        pixels = new int[width * height];

        Random r = new Random();
        tiles = new int[tileCountX * tileCountY];
        for (int t = 0; t < tiles.length; t++) {
            tiles[t] = 0xFF000000 + r.nextInt(0x00FFFFFF);
            // if (t % tileCountX == 0)
            //     tiles[t] = 0xFF000000;
        }
    }

    public void clear() {
        for (int i = 0; i < pixels.length; i++)
            pixels[i] = 0x00000000;
    }

    public void update() {
        if (keyboard.getLeft())
            xOffset--;
        if (keyboard.getRight())
            xOffset++;

        //NOTE: +y is DOWN!
        if (keyboard.getDown())
            yOffset++;
        if (keyboard.getUp())
            yOffset--;
    }

    public void render() {
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int i = x + y * width;
                // pixels[i] = new Color((float) x / width, 1 - (float) y / height, 0, 1).getRGB();

                int adjustedX = x + xOffset;
                int adjustedY = y + yOffset;
                int tileX = MathUtility.euclideanRemainder((adjustedX / tileSize), tileCountX);
                int tileY = MathUtility.euclideanRemainder(adjustedY / tileSize, tileCountY);

                //NOTE: Because [-7, -1] U [0, 7] / 8 = 0, we need to offset one half so the tile at index X = 0 and Y = 0 don't repeat all ugly:
                if (adjustedX < 0) {
                    tileX--;
                    if (tileX < 0)
                        tileX = tileCountX - 1;
                }
                if (adjustedY < 0) {
                    tileY--;
                    if (tileY < 0)
                        tileY = tileCountY - 1;
                }
                

                assert tileX >= 0 && tileX < tileCountX : "tileX must be in range [0, " + tileCountX + "), but was " + tileX + " instead!";
                assert tileY >= 0 && tileY < tileCountY : "tileY must be in range [0, " + tileCountY + "), but was " + tileY + " instead!";
                int tileIndex = tileX + tileY * tileCountX;
                pixels[i] = tiles[tileIndex];

                pixels[i] = 0xFF000000 + ((int) (((float) tileX / (tileCountX - 1)) * 0x000000FF) << 16) + ((int) (((float) tileY / (tileCountY - 1)) * 0x000000FF) << 8);
            }
        }
    }

    //TODO: Argument validation
    public void CopyPixelsInto(int[] targetPixels) {
        for (int i = 0; i < targetPixels.length; i++)
            targetPixels[i] = pixels[i];
    }
}
