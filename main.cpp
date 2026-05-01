#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow ana_pencere(sf::VideoMode(600, 400), "flappy bird game");//pencere oluşturduk
    sf::CircleShape bird_shape(50.f);//karakter tanımlaması yaptık burda 50 piksel yarıçaplı bir daire

    bird_shape.setFillColor(sf::Color::Yellow);//nesnenin iç rengi 

    bird_shape.setPosition(250, 150);//nesnenin konumu belirleniyor(x.y)koordinatları

    while (ana_pencere.isOpen()) {//açık olduğu sürece
        sf::Event etkilesim;//işletim sisteminden gelen etkileşimleri algılar
        while (ana_pencere.pollEvent(etkilesim)) {//sırada bekleyen bir etkilesim var mı
            if (etkilesim.type == sf::Event::Closed)
                ana_pencere.close();//pencereyi kapatıp döngüden çıkıyoruz
        }
        ana_pencere.clear();//her karede ekran temizlenir
        ana_pencere.draw(bird_shape);//hazırlanan nesne ekrana çiziliyor
        ana_pencere.display();//ekrana yansıtma
    }
    return 0;
}