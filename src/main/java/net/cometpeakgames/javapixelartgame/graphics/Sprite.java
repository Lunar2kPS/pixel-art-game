package net.cometpeakgames.javapixelartgame.graphics;

public class Sprite {
    /** The sprite sheet that contains the pixels of this sprite. */
    public final SpriteSheet sheet;

    /** The horizontal width of this sprite, measured in pixels. */
    public final int width;

    /** The vertical height of this sprite, measured in pixels. */
    public final int height;

    /** The first x pixel coordinate of this sprite. */
    public final int x;

    /** The first y pixel coordinate of this sprite. */
    public final int y;

    public Sprite(SpriteSheet sheet, int x, int y, int width, int height) {
        if (sheet == null)
            throw new IllegalArgumentException("The sprite sheet cannot be null!");
        if (x < 0 || x >= sheet.width)
            throw new IllegalArgumentException("The x pixel coordinate must be in range [0, " + sheet.width + ")");
        if (y < 0 || y >= sheet.height)
            throw new IllegalArgumentException("The y pixel coordinate must be in range [0, " + sheet.height + ")");
        if (width < 1 || (x + width) >= sheet.width)
            throw new IllegalArgumentException("Invalid width value! It must be positive, and not point to a pixel that's greater than the sheet's width of " + sheet.width + ".");
        if (height < 1 || (y + height) >= sheet.height)
            throw new IllegalArgumentException("Invalid height value! It must be positive, and not point to a pixel that's greater than the sheet's height of " + sheet.height + ".");
        
        this.sheet = sheet;
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }
}
