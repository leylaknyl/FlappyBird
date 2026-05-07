#include "../include/Pipe.h"//pipe.h dosyası kullanıma açıldı

Pipe::Pipe() {// Pipe sınıfının constructor fonksiyonu

    engel_x = 600.0f;// engellerin yataydaki başlangıç konumu

    engel_speed = 3.0f;// engellerin sola doğru hareket hızı

    //üst engelin boyutu ayarlandı
    ust_engel.setSize(
        sf::Vector2f(70.0f,150.0f)
    );

    // alt engelin boyutu ayarlandı
    alt_engel.setSize(
        sf::Vector2f(70.0f,150.0f)
    );

    //engellerin rengi ayarlandı
    ust_engel.setFillColor(sf::Color::Magenta);

    alt_engel.setFillColor(sf::Color::Magenta);
}


void Pipe::update() {//engellerin konumu her frame güncellensin

   engel_x-=engel_speed;// engellerin x konumu azalır ve sola doğru kaymasını sağlar

        ust_engel.setPosition(engel_x,0);//üst engel ekranın üst kısmına yerleştirildi

        alt_engel.setPosition(engel_x,250);//alt engel ekranın altına yerleştirildi

        if(engel_x<-70.0f){ // engel ekrandan çıkarsa tekrar en sağa kaydırma
        engel_x=600.0f;
        }
}

// engeller pencereye çizdirilir
void Pipe::draw(sf::RenderWindow& pencere) {

    pencere.draw(ust_engel);

    pencere.draw(alt_engel);
}