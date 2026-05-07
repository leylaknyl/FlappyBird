#pragma once// dosyanın program içinde 1 kez yüklenmesini sağlar

#include <SFML/Graphics.hpp>// sfml kütüphanesi

class Pipe { // pipe sınıfı boruların oluşturulması,hareketi ve ekrana çizilmesinden sorumludur

public:// main de kullabilsin diye

    Pipe();//pipe nesnesi oluşturulurken başlangıç ayarlarınıı yapar

    void update(); //boruların konumunu günceller

    void draw(sf::RenderWindow& pencere);//boruları ekrana çizer

private://sadece pipe sınıfına özel değişkenler


    float ust_yukseklik;// üst engelin rastgele yüksekliği

    sf::RectangleShape ust_engel;// üst ve alt engel nesneleri

    sf::RectangleShape alt_engel;

    float engel_x;// boruların x konumu
    float engel_speed; // boruların hareket hızı
};