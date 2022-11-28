package net.cometpeakgames.javapixelartgame;

import java.nio.file.Paths;

public final class Application {
    private static String projectPath;

    public static String getProjectPath() { return projectPath; }
    
    private Application() { }

    static void Initialize() {
        projectPath = Paths.get(".").normalize().toAbsolutePath().toString().replace('\\', '/');
    }
}
