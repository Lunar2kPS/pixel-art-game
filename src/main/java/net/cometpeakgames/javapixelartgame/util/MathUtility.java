package net.cometpeakgames.javapixelartgame.util;

public class MathUtility {
    //WARNING: There's no Math.floor(float) overload?

    public static int euclideanRemainder(int x, int n) {
        int absN = Math.abs(n);
        return x - absN * (int) Math.floor((float) x / absN);
    }
}
