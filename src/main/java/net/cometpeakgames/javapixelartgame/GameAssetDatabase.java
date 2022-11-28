package net.cometpeakgames.javapixelartgame;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import net.cometpeakgames.javapixelartgame.assets.GameAsset;
import net.cometpeakgames.javapixelartgame.serialization.ITextSerializer;
import net.cometpeakgames.javapixelartgame.serialization.JsonSerializer;
import net.cometpeakgames.javapixelartgame.serialization.SerializationException;

public final class GameAssetDatabase {
    private static HashMap<String, GameAsset> allAssets;

    private GameAssetDatabase() { }

    static void Initialize() {
        allAssets = new HashMap<>();
        try (Stream<Path> stream = Files.walk(Paths.get("./resources"))) {
            // stream.filter(Files::isRegularFile)
            //       .forEach(System.out::println);

            List<Path> filePaths = stream
                .map(p -> p.toFile())
                .filter(f -> f.isFile())
                .map(f -> f.toString().replace('\\', '/'))
                .map(f -> Paths.get(f))
                .collect(Collectors.toList());

            ITextSerializer serializer = new JsonSerializer();
            for (Path filePath : filePaths) {
                if (filePath.toString().endsWith(".json")) {
                    String json = Files.readString(filePath);
                    try {
                        String className = serializer.getClassName(json);
                        GameAsset asset = (GameAsset) serializer.deserialize(json, Class.forName(className));
                        allAssets.put(asset.getGuid(), asset);
                    } catch (SerializationException|ClassNotFoundException e) {
                        e.printStackTrace();
                        continue;
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
