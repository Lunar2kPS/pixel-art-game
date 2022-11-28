package net.cometpeakgames.javapixelartgame.input;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Keyboard implements KeyListener {
    private boolean[] keys = new boolean[120];

    public boolean getKey(int keyCode) { return keys[keyCode]; }
    public boolean getUp() { return getKey(KeyEvent.VK_UP) || getKey(KeyEvent.VK_W); }
    public boolean getDown() { return getKey(KeyEvent.VK_DOWN) || getKey(KeyEvent.VK_S); }
    public boolean getLeft() { return getKey(KeyEvent.VK_LEFT) || getKey(KeyEvent.VK_A); }
    public boolean getRight() { return getKey(KeyEvent.VK_RIGHT) || getKey(KeyEvent.VK_D); }
    
    public void keyTyped(KeyEvent e) { }
    public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();
        resizeIfNeeded(keyCode);
        keys[keyCode] = true;
    }
    public void keyReleased(KeyEvent e) {
        int keyCode = e.getKeyCode();
        resizeIfNeeded(keyCode);
        keys[keyCode] = false;
    }
    
    private boolean resizeIfNeeded(int keyCode) {
        if (keyCode >= keys.length) {
            int newLength = keyCode + 1;
            System.out.println("WARNING: The keys array was not large enough for key code " + keyCode + "! Resizing from " + keys.length + " to " + newLength + "!");

            boolean[] newArray = new boolean[newLength];
            for (int i = 0; i < keys.length; i++)
                newArray[i] = keys[i];
            keys = newArray;
            return true;

        }
        return false;
    }
}