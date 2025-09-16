# Java Projects ☕🚀

This directory contains complete Java projects and applications that demonstrate practical implementations of algorithms, data structures, and software engineering principles using Java's enterprise features.

## 📂 Directory Structure

```
projects/
├── games/               # Interactive games and entertainment
└── utilities/           # Practical utility applications
```

## 🎮 Games

Located in `games/`

### Current Implementations

#### 🎯 **Guess The Number Game** (`GuessTheNumber.java`)
A classic number guessing game that demonstrates:
- Random number generation using `java.util.Random`
- User input handling with `Scanner`
- Game loop implementation
- Conditional logic and user feedback

```java
import java.util.*;

public class GuessTheNumber {
    private static final Random random = new Random();
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.println("Welcome to Guess The Number Game!");
        playGame();
    }

    private static void playGame() {
        int numberToGuess = random.nextInt(100) + 1;
        int attempts = 0;
        int maxAttempts = 7;

        System.out.println("I've picked a number between 1 and 100.");
        System.out.println("You have " + maxAttempts + " attempts to guess it!");

        while (attempts < maxAttempts) {
            System.out.print("Enter your guess: ");
            int guess = scanner.nextInt();
            attempts++;

            if (guess == numberToGuess) {
                System.out.println("Congratulations! You guessed it in "
                    + attempts + " attempts!");
                return;
            } else if (guess < numberToGuess) {
                System.out.println("Too low! Try again.");
            } else {
                System.out.println("Too high! Try again.");
            }

            System.out.println("Attempts remaining: "
                + (maxAttempts - attempts));
        }

        System.out.println("Game over! The number was: " + numberToGuess);
    }
}
```

### Game Development Concepts

#### Object-Oriented Game Design
```java
// Game engine architecture
public abstract class Game {
    protected boolean isRunning;
    protected Scanner input;

    public Game() {
        isRunning = false;
        input = new Scanner(System.in);
    }

    public abstract void initialize();
    public abstract void gameLoop();
    public abstract void cleanup();

    public final void start() {
        initialize();
        isRunning = true;
        gameLoop();
        cleanup();
    }
}

// Specific game implementation
public class NumberGuessingGame extends Game {
    private int targetNumber;
    private int attempts;
    private final int maxAttempts;

    public NumberGuessingGame(int maxAttempts) {
        super();
        this.maxAttempts = maxAttempts;
    }

    @Override
    public void initialize() {
        targetNumber = new Random().nextInt(100) + 1;
        attempts = 0;
        System.out.println("Game initialized! Number chosen.");
    }

    @Override
    public void gameLoop() {
        while (isRunning && attempts < maxAttempts) {
            processUserInput();
            updateGameState();
            render();
        }
    }

    // Game-specific methods...
}
```

#### Game State Management
```java
public enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    WIN
}

public class GameManager {
    private GameState currentState;
    private Map<GameState, GameStateHandler> stateHandlers;

    public GameManager() {
        currentState = GameState.MENU;
        initializeStateHandlers();
    }

    private void initializeStateHandlers() {
        stateHandlers = new HashMap<>();
        stateHandlers.put(GameState.MENU, new MenuHandler());
        stateHandlers.put(GameState.PLAYING, new PlayingHandler());
        stateHandlers.put(GameState.PAUSED, new PausedHandler());
        stateHandlers.put(GameState.GAME_OVER, new GameOverHandler());
    }

    public void update() {
        GameStateHandler handler = stateHandlers.get(currentState);
        if (handler != null) {
            handler.handle(this);
        }
    }

    public void changeState(GameState newState) {
        System.out.println("Changing state from " + currentState
            + " to " + newState);
        currentState = newState;
    }
}
```

### Potential Game Extensions

#### 🎲 **Advanced Number Games**
- [ ] **Mathematical Puzzle Game** - Arithmetic challenges
- [ ] **Memory Number Game** - Remember number sequences
- [ ] **Number Pattern Game** - Identify mathematical patterns

#### 🃏 **Card Games**
- [ ] **Blackjack** - Classic card game with strategy
- [ ] **Poker** - Texas Hold'em implementation
- [ ] **Solitaire** - Single-player card game

#### 🧩 **Puzzle Games**
- [ ] **Sudoku Solver** - Generate and solve Sudoku puzzles
- [ ] **Word Puzzle** - Anagram and word search games
- [ ] **Maze Generator** - Create and solve mazes

#### 🎯 **Strategy Games**
- [ ] **Tic-Tac-Toe** - With AI opponent
- [ ] **Connect Four** - Drop-token strategy game
- [ ] **Chess** - Complete chess game with rules engine

## 🛠️ Utilities

Located in `utilities/`

### Utility Categories and Ideas

#### 📊 **Data Processing Tools**
```java
// CSV processor example
public class CSVProcessor {
    public static List<Map<String, String>> readCSV(String filename) {
        List<Map<String, String>> data = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String headerLine = br.readLine();
            String[] headers = headerLine.split(",");

            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(",");
                Map<String, String> row = new HashMap<>();

                for (int i = 0; i < headers.length && i < values.length; i++) {
                    row.put(headers[i].trim(), values[i].trim());
                }
                data.add(row);
            }
        } catch (IOException e) {
            System.err.println("Error reading CSV file: " + e.getMessage());
        }
        return data;
    }

    public static void writeCSV(String filename,
                               List<Map<String, String>> data) {
        if (data.isEmpty()) return;

        Set<String> headers = data.get(0).keySet();
        try (PrintWriter writer = new PrintWriter(new FileWriter(filename))) {
            // Write headers
            writer.println(String.join(",", headers));

            // Write data rows
            for (Map<String, String> row : data) {
                List<String> values = new ArrayList<>();
                for (String header : headers) {
                    values.add(row.getOrDefault(header, ""));
                }
                writer.println(String.join(",", values));
            }
        } catch (IOException e) {
            System.err.println("Error writing CSV file: " + e.getMessage());
        }
    }
}
```

#### 🔐 **Security and Cryptography Tools**
```java
// Password generator and validator
public class PasswordUtils {
    private static final String UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private static final String LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
    private static final String DIGITS = "0123456789";
    private static final String SYMBOLS = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    public static String generatePassword(int length,
                                        boolean includeUppercase,
                                        boolean includeLowercase,
                                        boolean includeDigits,
                                        boolean includeSymbols) {
        StringBuilder characterSet = new StringBuilder();
        if (includeUppercase) characterSet.append(UPPERCASE);
        if (includeLowercase) characterSet.append(LOWERCASE);
        if (includeDigits) characterSet.append(DIGITS);
        if (includeSymbols) characterSet.append(SYMBOLS);

        if (characterSet.length() == 0) {
            throw new IllegalArgumentException("At least one character type must be included");
        }

        Random random = new Random();
        StringBuilder password = new StringBuilder();

        for (int i = 0; i < length; i++) {
            int randomIndex = random.nextInt(characterSet.length());
            password.append(characterSet.charAt(randomIndex));
        }

        return password.toString();
    }

    public static PasswordStrength checkPasswordStrength(String password) {
        int score = 0;
        if (password.length() >= 8) score++;
        if (password.length() >= 12) score++;
        if (password.matches(".*[A-Z].*")) score++;
        if (password.matches(".*[a-z].*")) score++;
        if (password.matches(".*\\d.*")) score++;
        if (password.matches(".*[!@#$%^&*()].*")) score++;

        if (score <= 2) return PasswordStrength.WEAK;
        if (score <= 4) return PasswordStrength.MEDIUM;
        return PasswordStrength.STRONG;
    }

    public enum PasswordStrength {
        WEAK, MEDIUM, STRONG
    }
}
```

#### 🌐 **Network and Web Tools**
```java
// HTTP client utility
public class HTTPClient {
    public static String sendGET(String url) throws IOException {
        HttpURLConnection connection = (HttpURLConnection) new URL(url).openConnection();
        connection.setRequestMethod("GET");
        connection.setConnectTimeout(5000);
        connection.setReadTimeout(5000);

        int responseCode = connection.getResponseCode();
        if (responseCode == HttpURLConnection.HTTP_OK) {
            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(connection.getInputStream()))) {
                StringBuilder response = new StringBuilder();
                String line;
                while ((line = reader.readLine()) != null) {
                    response.append(line).append("\n");
                }
                return response.toString();
            }
        } else {
            throw new IOException("HTTP request failed with response code: " + responseCode);
        }
    }

    public static String sendPOST(String url, String jsonBody) throws IOException {
        HttpURLConnection connection = (HttpURLConnection) new URL(url).openConnection();
        connection.setRequestMethod("POST");
        connection.setRequestProperty("Content-Type", "application/json");
        connection.setDoOutput(true);

        try (OutputStream outputStream = connection.getOutputStream()) {
            byte[] input = jsonBody.getBytes(StandardCharsets.UTF_8);
            outputStream.write(input, 0, input.length);
        }

        // Read response...
        return readResponse(connection);
    }
}
```

#### 📁 **File Management Tools**
```java
// File organizer utility
public class FileOrganizer {
    public static void organizeByExtension(Path sourceDir, Path targetDir) {
        try {
            Files.walk(sourceDir)
                .filter(Files::isRegularFile)
                .forEach(file -> {
                    String extension = getFileExtension(file.getFileName().toString());
                    Path extensionDir = targetDir.resolve(extension);

                    try {
                        Files.createDirectories(extensionDir);
                        Files.move(file, extensionDir.resolve(file.getFileName()),
                                 StandardCopyOption.REPLACE_EXISTING);
                    } catch (IOException e) {
                        System.err.println("Failed to move file: " + file);
                    }
                });
        } catch (IOException e) {
            System.err.println("Error organizing files: " + e.getMessage());
        }
    }

    private static String getFileExtension(String filename) {
        int lastDotIndex = filename.lastIndexOf('.');
        if (lastDotIndex == -1) return "no_extension";
        return filename.substring(lastDotIndex + 1).toLowerCase();
    }

    public static void cleanupOldFiles(Path directory, int daysOld) {
        long cutoffTime = System.currentTimeMillis() - (daysOld * 24L * 60L * 60L * 1000L);

        try {
            Files.walk(directory)
                .filter(Files::isRegularFile)
                .filter(file -> {
                    try {
                        return Files.getLastModifiedTime(file).toMillis() < cutoffTime;
                    } catch (IOException e) {
                        return false;
                    }
                })
                .forEach(file -> {
                    try {
                        Files.delete(file);
                        System.out.println("Deleted old file: " + file);
                    } catch (IOException e) {
                        System.err.println("Failed to delete: " + file);
                    }
                });
        } catch (IOException e) {
            System.err.println("Error cleaning up files: " + e.getMessage());
        }
    }
}
```

## 🏗️ Project Architecture Patterns

### MVC (Model-View-Controller)
```java
// Model
public class GameModel {
    private int score;
    private int level;
    private boolean gameOver;

    // Getters, setters, and business logic
}

// View
public class GameView {
    public void displayScore(int score) {
        System.out.println("Score: " + score);
    }

    public void displayGameOver() {
        System.out.println("Game Over!");
    }

    public String getUserInput() {
        return new Scanner(System.in).nextLine();
    }
}

// Controller
public class GameController {
    private GameModel model;
    private GameView view;

    public GameController(GameModel model, GameView view) {
        this.model = model;
        this.view = view;
    }

    public void updateGame() {
        String input = view.getUserInput();
        // Process input and update model
        view.displayScore(model.getScore());
    }
}
```

### Observer Pattern
```java
// Observable game events
public class GameEventManager {
    private Map<String, List<GameEventListener>> listeners;

    public GameEventManager() {
        listeners = new HashMap<>();
    }

    public void subscribe(String eventType, GameEventListener listener) {
        listeners.computeIfAbsent(eventType, k -> new ArrayList<>()).add(listener);
    }

    public void notify(String eventType, Object data) {
        List<GameEventListener> eventListeners = listeners.get(eventType);
        if (eventListeners != null) {
            for (GameEventListener listener : eventListeners) {
                listener.onEvent(eventType, data);
            }
        }
    }
}

// Event listener interface
@FunctionalInterface
public interface GameEventListener {
    void onEvent(String eventType, Object data);
}
```

### Factory Pattern
```java
// Game factory for different game types
public abstract class GameFactory {
    public static Game createGame(String gameType) {
        switch (gameType.toLowerCase()) {
            case "guessing":
                return new NumberGuessingGame();
            case "memory":
                return new MemoryGame();
            case "puzzle":
                return new PuzzleGame();
            default:
                throw new IllegalArgumentException("Unknown game type: " + gameType);
        }
    }
}

// Usage
Game game = GameFactory.createGame("guessing");
game.start();
```

## 📚 Advanced Java Features

### Streams and Lambda Expressions
```java
// Data processing with streams
public class DataAnalyzer {
    public static Map<String, Double> analyzeScores(List<Player> players) {
        return players.stream()
            .collect(Collectors.groupingBy(
                Player::getCategory,
                Collectors.averagingDouble(Player::getScore)
            ));
    }

    public static List<Player> getTopPlayers(List<Player> players, int count) {
        return players.stream()
            .sorted(Comparator.comparing(Player::getScore).reversed())
            .limit(count)
            .collect(Collectors.toList());
    }
}
```

### Concurrent Programming
```java
// Multi-threaded game server
public class GameServer {
    private final ExecutorService threadPool;
    private final ConcurrentHashMap<String, GameSession> activeSessions;

    public GameServer(int threadCount) {
        threadPool = Executors.newFixedThreadPool(threadCount);
        activeSessions = new ConcurrentHashMap<>();
    }

    public void handleClient(Socket clientSocket) {
        threadPool.submit(() -> {
            String sessionId = UUID.randomUUID().toString();
            GameSession session = new GameSession(sessionId, clientSocket);
            activeSessions.put(sessionId, session);

            try {
                session.handleGame();
            } finally {
                activeSessions.remove(sessionId);
            }
        });
    }

    public void shutdown() {
        threadPool.shutdown();
        try {
            if (!threadPool.awaitTermination(60, TimeUnit.SECONDS)) {
                threadPool.shutdownNow();
            }
        } catch (InterruptedException e) {
            threadPool.shutdownNow();
        }
    }
}
```

## 🎯 Project Development Guidelines

### Documentation Standards
```java
/**
 * A comprehensive number guessing game implementation.
 *
 * <p>This game generates a random number within a specified range
 * and challenges the player to guess it within a limited number of attempts.
 *
 * <p>Features:
 * <ul>
 *   <li>Configurable difficulty levels</li>
 *   <li>Score tracking and statistics</li>
 *   <li>Hint system for beginners</li>
 *   <li>Replay functionality</li>
 * </ul>
 *
 * @author Your Name
 * @version 2.0
 * @since 1.0
 */
public class NumberGuessingGame implements Game {
    // Implementation...
}
```

### Testing Strategy
```java
// JUnit test example for game logic
public class NumberGuessingGameTest {
    private NumberGuessingGame game;

    @BeforeEach
    void setUp() {
        game = new NumberGuessingGame(1, 100, 7);
    }

    @Test
    void testValidGuess() {
        GuessResult result = game.makeGuess(50);
        assertThat(result.getType()).isIn(GuessType.TOO_HIGH, GuessType.TOO_LOW, GuessType.CORRECT);
    }

    @Test
    void testInvalidGuess() {
        assertThrows(IllegalArgumentException.class, () -> {
            game.makeGuess(150); // Outside valid range
        });
    }

    @Test
    void testGameOver() {
        // Make maximum number of wrong guesses
        for (int i = 0; i < game.getMaxAttempts(); i++) {
            game.makeGuess(-1); // Guaranteed wrong guess
        }
        assertTrue(game.isGameOver());
    }
}
```

### Configuration Management
```java
// Properties-based configuration
public class GameConfig {
    private static final Properties properties = new Properties();

    static {
        try (InputStream input = GameConfig.class.getResourceAsStream("/game.properties")) {
            properties.load(input);
        } catch (IOException e) {
            System.err.println("Failed to load configuration: " + e.getMessage());
        }
    }

    public static int getMaxAttempts() {
        return Integer.parseInt(properties.getProperty("game.max.attempts", "7"));
    }

    public static int getMinNumber() {
        return Integer.parseInt(properties.getProperty("game.min.number", "1"));
    }

    public static int getMaxNumber() {
        return Integer.parseInt(properties.getProperty("game.max.number", "100"));
    }
}
```

## 🏆 Best Practices for Java Projects

### Code Organization
1. **Package Structure**: Use meaningful package names
2. **Single Responsibility**: Each class should have one purpose
3. **Dependency Injection**: Use frameworks like Spring for large projects
4. **Error Handling**: Comprehensive exception handling
5. **Logging**: Use logging frameworks (SLF4J, Logback)

### Performance Optimization
1. **Object Pooling**: Reuse expensive objects
2. **Lazy Initialization**: Initialize objects when needed
3. **Caching**: Cache frequently accessed data
4. **Profiling**: Use tools like JProfiler or VisualVM

### Security Considerations
1. **Input Validation**: Validate all user inputs
2. **Secure Coding**: Follow OWASP guidelines
3. **Dependency Management**: Keep libraries updated
4. **Data Encryption**: Encrypt sensitive data

Happy Java Project Development! ☕💡🚀