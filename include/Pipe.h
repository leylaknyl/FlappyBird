#pragma once// dosyanın program içinde 1 kez yüklenmesini sağlar

#include <SFML/Graphics.hpp>// sfml kütüphanesi

class Pipe { // pipe sınıfı boruların oluşturulması,hareketi ve ekrana çizilmesinden sorumludur

public:// main de kullabilsin diye

    Pipe();//pipe nesnesi oluşturulurken başlangıç ayarlarınıı yapar

    void update(); //boruların konumunu günceller

    void draw(sf::RenderWindow& pencere);//boruları ekrana çizer

    bool check_collision(sf::Sprite& bird);//kuş sprite'ı ile engeller arasındaki çarpışma kontrol ediliyor
    
    float get_x();//engelin mevcut x konumunu döndürür

    void reset();// engelleri başlangıç konumuna geri alır
 
    
private://sadece pipe sınıfına özel değişkenler


    float ust_yukseklik;// üst engelin rastgele yüksekliği

    float engel_x;// boruların x konumu
    
    float engel_speed; // boruların hareket hızı

    float bosluk;//engeller arasındaki geçiş boşluğu

    // engellerin  görünmez çarpışma ve boyut alanlarını tutan nesneler
    sf::RectangleShape ust_engel;

    sf::RectangleShape alt_engel;

    // boru görsellerini belleğe yüklemek için texture nesnesi
    sf::Texture pipe_texture;

    // boru görsellerini ekranda gösterecek sprite nesneleri
    sf::Sprite ust_pipe_sprite;
    sf::Sprite alt_pipe_sprite;

};