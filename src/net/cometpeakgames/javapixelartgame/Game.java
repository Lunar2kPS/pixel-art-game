package net.cometpeakgames.javapixelartgame;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferStrategy;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;

import javax.swing.JFrame;

import net.cometpeakgames.javapixelartgame.graphics.Screen;

public class Game extends Canvas implements Runnable {
    private static int width = 400;
    private static int height = 225;
    private static int scale = 3;
    private static String title = "Java Pixel Art Game";

    //NOTE: This thread is NOT the same thread as the one that starts our main program!
    private Thread gameThread;
    private boolean isRunning = false;

    private JFrame frame;
    private Screen screen;

    private BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
    private int[] pixels = ((DataBufferInt) image.getRaster().getDataBuffer()).getData();

    public int getScreenWidth() { return width * scale; }
    public int getScreenHeight() { return height * scale; }
    public Screen getScreen() { return screen;}

    public Game() { }

    public synchronized void start() {
        isRunning = true;
        screen = new Screen(width, height);
        frame = CreateFrame();
        
        gameThread = new Thread(this, "Game");
        gameThread.start();
    }

    public synchronized void stop() {
        isRunning = false;
        try {
            gameThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void run() {
        long prevTime = System.nanoTime();
        int maxFramerate = 60;
        final double minNanoFrametime = (double) 1000000000 / maxFramerate;
        long nanoTimeElapsed = 0;

        int updatesPassed = 0;
        int framesPassed = 0;
        long lastSecondMs = System.currentTimeMillis();

        while (isRunning) {
            long now = System.nanoTime();
            long dtLong = now - prevTime;
            nanoTimeElapsed += dtLong;
            prevTime = now;
            
            int updateCountNeeded = (int) (nanoTimeElapsed / minNanoFrametime);
            if (updateCountNeeded > 0) {
                float dt = (float) ((double) nanoTimeElapsed / 1000000000 / updateCountNeeded);
                System.out.println("dt = " + String.format("%.3f", dt));
                
                for (int i = 0; i < updateCountNeeded; i++) {
                    update();
                    updatesPassed++;
                }
                nanoTimeElapsed -= updateCountNeeded * minNanoFrametime;
            }
            
            render();
            framesPassed++;

            if (System.currentTimeMillis() - lastSecondMs >= 1000) {
                lastSecondMs += 1000;
                frame.setTitle(title + "    |    " + updatesPassed + " updates, " + framesPassed + " FPS");
                updatesPassed = 0;
                framesPassed = 0;
            }
        }
        stop();
    }

    private void update() {

    }

    private void render() {
        BufferStrategy bs = getBufferStrategy();
        if (bs == null) {
            createBufferStrategy(3);
            return;
        }

        screen.clear();
        screen.render();
        screen.CopyPixelsInto(pixels);

        Graphics g = bs.getDrawGraphics();
        
        int uiWidth = getWidth();
        int uiHeight = getHeight();
        g.drawImage(image, 0, 0, uiWidth, uiHeight, null);
        g.dispose();
        bs.show();
    }

    private JFrame CreateFrame() {
        JFrame frame = new JFrame();
        Dimension size = new Dimension(getScreenWidth(), getScreenHeight());
        setPreferredSize(size);

        frame.setResizable(false);
        frame.setTitle("Java Pixel Art Game");
        frame.add(this);
        frame.pack();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        return frame;
    }

    public static void main(String[] args) {
        Game game = new Game();
        game.start();
    }
}
