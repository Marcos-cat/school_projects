#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class Vec2 {
  public:
    double x, y;

    Vec2() : x(0), y(0) {}
    Vec2(double x, double y) : x(x), y(y) {}

    static const Vec2 RIGHT;
    static const Vec2 UP;
    static const Vec2 DOWN;
    static const Vec2 LEFT;

    Vec2 operator+(Vec2 other) { return Vec2(other.x + x, other.y + y); }
    void operator+=(Vec2 other) {
        x += other.x;
        y += other.y;
    }
    Vec2 operator-() { return Vec2(-x, -y); }
    Vec2 operator*(double k) { return Vec2(x * k, y * k); }
};

const Vec2 Vec2::RIGHT(1, 0);
const Vec2 Vec2::LEFT(-1, 0);
const Vec2 Vec2::UP(0, -1);
const Vec2 Vec2::DOWN(0, 1);

#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif

class Sprite {
  public:
    Vec2 pos;
    std::vector<std::string> image;

    Sprite(std::string image_file, Vec2 pos = {0, 0}) : pos(pos) {
        std::ifstream file(image_file);
        std::vector<std::string> lines;

        if (!file) {
            std::cerr << "Error opening file" << std::endl;
            return; // Return an error code
        }

        std::string line;
        while (std::getline(file, line)) { image.push_back(line); }

        file.close();
    }
};

class Game {
  public:
    const int height, width;
    Game(int height, int width) : height(height), width(width) {
#ifdef __linux__
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
#endif

        input_thread = std::thread([this]() { read_input(); });
    }

    ~Game() { input_thread.join(); }

    void frame() {
        for (auto sprite : sprites) {
            sprite->pos.x = std::clamp<double>(sprite->pos.x, 0, width);
            sprite->pos.y = std::clamp<double>(sprite->pos.y, 0, height);
        }
        draw();
    }

    void add_sprite(Sprite* sprite) { sprites.push_back(sprite); }

    char get_key() {
        char key = key_press;
        key_press = 0;
        return key;
    }

    bool running() { return is_running; }

  private:
    std::vector<Sprite*> sprites;
    std::atomic<char> key_press;
    std::thread input_thread;
    std::atomic<bool> is_running = true;

    void print_sprite(Sprite sprite) {
        for (int row = 0; row < sprite.image.size(); row++) {
            gotoXY(sprite.pos + Vec2(0, row));
            printf("%s", sprite.image[row].c_str());
        }
    }

    void draw() {
        clear_screen();
        for (auto sprite : sprites) { print_sprite(*sprite); }
        fflush(stdout);
    }

    void gotoXY(Vec2 pos) {
        printf(
            "\033[%d;%dH", static_cast<int>(pos.y + 1),
            static_cast<int>(pos.x + 1)
        );
    }

    void clear_screen() {
        for (int line = 0; line < height; line++) {
            gotoXY(Vec2(0, line));
            for (int column = 0; column < width; column++) {
                putc(' ', stdout);
            }
        }
    }

    void read_input() {
        while (is_running) {
#ifdef _WIN32
            if (_kbhit()) { key_press = _getch(); }
#else
            char c = getch();
            if (c != ERR) { key_press = c; }
#endif

            if (key_press == 'q') is_running = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};

int main() {
    Game game(24, 80);
    Sprite x("./sprite.txt");
    game.add_sprite(&x);

    Vec2 velocity;

    while (game.running()) {
        game.frame();

        char key;
        if ((key = game.get_key())) {

            switch (key) {
            case 'w': velocity = Vec2::UP; break;
            case 'a': velocity = Vec2::LEFT; break;
            case 's': velocity = Vec2::DOWN; break;
            case 'd': velocity = Vec2::RIGHT; break;
            }
        }

        // Move X
        x.pos += velocity;

        // Delay to control speed
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
