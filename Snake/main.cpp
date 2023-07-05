#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <chrono>

int snake[12][12]; int begin[2] = { 0, 0 }; int end[2] = { 0, 1 }; 
int apple[2] = { 0, 0 }; int dapple[2] = { 0, 0 };  int cd = 3; int ch = 0; int t = 600;

void Field(sf::RenderWindow& window, sf::Image& img) {
	for (int i = 1; i < 12; ++i) {
		for (int j = 1; j < 600; ++j) {
			img.setPixel(i * 50, j, sf::Color::Black);
			img.setPixel(j, i * 50, sf::Color::Black);
		}
	}
}

void DrawSquare(int a, int b, sf::RenderWindow& window, sf::Image& img) {
	sf::ConvexShape square(4);
	square.setPoint(0, sf::Vector2f(b * 50, a * 50));
	square.setPoint(1, sf::Vector2f(b * 50 + 50, a * 50));
	square.setPoint(2, sf::Vector2f(b * 50 + 50, a * 50 + 50));
	square.setPoint(3, sf::Vector2f(b * 50, a * 50 + 50));
	square.setFillColor(sf::Color::Blue);
	window.draw(square);
}

void DrawApple(sf::RenderWindow& window, sf::Image& img) {
	sf::ConvexShape square(4);
	square.setPoint(0, sf::Vector2f(apple[1] * 50, apple[0] * 50));
	square.setPoint(1, sf::Vector2f(apple[1] * 50 + 50, apple[0] * 50));
	square.setPoint(2, sf::Vector2f(apple[1] * 50 + 50, apple[0] * 50 + 50));
	square.setPoint(3, sf::Vector2f(apple[1] * 50, apple[0] * 50 + 50));
	square.setFillColor(sf::Color::Red);
	window.draw(square);
}

void FindApple(sf::RenderWindow& window, sf::Image& img) {
	int i = rand() % 12;
	int j = rand() % 12;
	if (snake[i][j] != 0 || (i == begin[0] && j == begin[1])) FindApple(window, img);
	else { apple[0] = i; apple[1] = j; }
}

void DrawDeathApple(sf::RenderWindow& window, sf::Image& img) {
	sf::ConvexShape square(4);
	square.setPoint(0, sf::Vector2f(dapple[1] * 50, dapple[0] * 50));
	square.setPoint(1, sf::Vector2f(dapple[1] * 50 + 50, dapple[0] * 50));
	square.setPoint(2, sf::Vector2f(dapple[1] * 50 + 50, dapple[0] * 50 + 50));
	square.setPoint(3, sf::Vector2f(dapple[1] * 50, dapple[0] * 50 + 50));
	square.setFillColor(sf::Color::Black);
	window.draw(square);
}

void FindDeathApple(sf::RenderWindow& window, sf::Image& img) {
	int i = rand() % 12;
	int j = rand() % 12;
	if (snake[i][j] != 0 || (i == begin[0] && j == begin[1])) FindDeathApple(window, img);
	else { dapple[0] = i; dapple[1] = j; }
}

void MovementHead(sf::RenderWindow& window, sf::Image& img) {
	if (cd == 1) {snake[begin[0]][begin[1]] = 1; --begin[0]; ++ch; }
	else if (cd == 2) { snake[begin[0]][begin[1]] = 2; ++begin[1]; ++ch; }
	else if (cd == 3) { snake[begin[0]][begin[1]] = 3; ++begin[0]; ++ch; }
	else if (cd == 4) { snake[begin[0]][begin[1]] = 4; --begin[1]; ++ch; }
}

void Movement(sf::RenderWindow& window, sf::Image& img) {
	if (snake[begin[0]][begin[1]] != 0) window.close();
	if (begin[0] == dapple[0] && begin[1] == dapple[1]) { t += 20; FindDeathApple(window, img); }
	if (begin[0] < 0 || begin[0] > 11 || begin[1] < 0 || begin[1] > 11) {
		window.close();
		if (begin[0] < 0) begin[0] = 11;
		else if(begin[0] > 11) begin[0] = 0;
		else if (begin[1] < 0) begin[1] = 11;
		else if (begin[1] > 11) begin[1] = 0;
	}
	DrawSquare(begin[0], begin[1], window, img);
	if (snake[apple[0]][apple[1]] != 0 || (apple[0] == begin[0] && apple[1] == begin[1])) {
		--ch;  FindApple(window, img); }
	if (ch == 1) {
		if (snake[end[0]][end[1]] == 1) snake[end[0]--][end[1]] = 0;
		else if (snake[end[0]][end[1]] == 2) snake[end[0]][end[1]++] = 0;
		else if (snake[end[0]][end[1]] == 3) snake[end[0]++][end[1]] = 0;
		else if (snake[end[0]][end[1]] == 4) snake[end[0]][end[1]--] = 0;
		--ch;}
	for (int i = 0; i < 144; ++i) if (snake[i / 12][i % 12] != 0) DrawSquare(i / 12, i % 12, window, img);
	DrawApple(window, img);
}

void Event(sf::RenderWindow& window, sf::Image& img) {
	auto begin1 = std::chrono::high_resolution_clock::now();
	auto end1 = std::chrono::high_resolution_clock::now();
	auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1);
	auto begin2 = std::chrono::high_resolution_clock::now();
	auto end2 = std::chrono::high_resolution_clock::now();
	auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2);
	sf::Font font;
	if (!font.loadFromFile("D:/Proga/Calender/Raleway-Regular.ttf"));
	sf::Texture texture;
	texture.loadFromImage(img);
	sf::Sprite sprite;
	sprite.setTexture(texture, true);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left) { }
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) cd = 1;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) cd = 2;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) cd = 3;
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) cd = 4;
			else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift)) {
				//if (t == 300) t = 600; else t = 300;
			}
		}
		window.clear();
		window.draw(sprite);
		if (time1.count() > t) {
			MovementHead(window, img); t -= 3;
			begin1 = std::chrono::high_resolution_clock::now();
		}
		end1 = std::chrono::high_resolution_clock::now();
		time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - begin1);
		if (time2.count() > 5000) {
			FindDeathApple(window, img); 
			begin2 = std::chrono::high_resolution_clock::now();
		}
		DrawDeathApple(window, img);
		end2 = std::chrono::high_resolution_clock::now();
		time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2);
		Movement(window, img);
		window.display();
	}
}

int main() 
{
	for (int i = 0; i < 144; ++i) snake[i / 12][i % 12] = 0;
	snake[0][1] = 4;

	sf::RenderWindow window(sf::VideoMode(600, 600), "!");
	sf::Image img;
	img.create(600, 600, sf::Color::White);
	Field(window, img);
	FindApple(window, img);
	Event(window, img);
	
	return 0;
}