#pragma once// dosyanın program içinde 1 kez yüklenmesini sağlar

#include <SFML/Graphics.hpp>// sfml kütüphanesi

class Pipe { // pipe sınıfı boruların oluşturulması,hareketi ve ekrana çizilmesinden sorumludur

public:// main de kullabilsin diye

    Pipe();//pipe nesnesi oluşturulurken başlangıç ayarlarınıı yapar

    void update(); //boruların konumunu günceller

    void draw(sf::RenderWindow& pencere);//boruları ekrana çizer

    bool check_collision(sf::CircleShape& bird);//kuşun üst veya alt engele çarpıp çarpmadığını kontrol eder

private://sadece pipe sınıfına özel değişkenler


    float ust_yukseklik;// üst engelin rastgele yüksekliği

    float engel_x;// boruların x konumu
    
    float engel_speed; // boruların hareket hızı

    float bosluk;//engeller arasındaki geçiş boşluğu

    sf::RectangleShape ust_engel;// üst ve alt engel nesneleri

    sf::RectangleShape alt_engel;


};