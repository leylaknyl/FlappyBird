#include "../include/Pipe.h"//pipe.h dosyası kullanıma açıldı

#include <cstdlib>// rand() fonksiyonu için

Pipe::Pipe() {// Pipe sınıfının constructor fonksiyonu

    engel_x = 600.0f;// engellerin yataydaki başlangıç konumu

    engel_speed = 3.0f;// engellerin sola doğru hareket hızı

    bosluk=130.0f;// üst ve alt engel arasındaki geçiş boşluğu

    ust_yukseklik=80 +rand()% 120;//üst engel için rastgele yükseklik oluşturldu

    // Üst engelin boyutu ayarlandı
    ust_engel.setSize(
    sf::Vector2f(70.0f,ust_yukseklik)
    );

   alt_engel.setSize(
    sf::Vector2f(70.0f, 400.0f - ust_yukseklik - bosluk)
);

    //engellerin rengi ayarlandı
    ust_engel.setFillColor(sf::Color::Magenta);

    alt_engel.setFillColor(sf::Color::Magenta);
}


void Pipe::update() {//engellerin konumu her frame güncellensin

   engel_x-=engel_speed;// engellerin x konumu azalır ve sola doğru kaymasını sağlar

        ust_engel.setPosition(engel_x,0);//üst engel ekranın üst kısmına yerleştirildi

        // Alt engelin konumu üst engel yüksekliği ve boşluğa göre ayarlandı
        alt_engel.setPosition(
            engel_x,
            ust_yukseklik +bosluk
        );

        if(engel_x<-70.0f){ // engel ekrandan çıkarsa tekrar en sağa kaydırma

        engel_x=600.0f;

        ust_yukseklik = 80 + rand() % 120;// her yeni gelen engel için rastgele yükseklik oluşturuldu

         // Üst engelin boyutu güncellensin
        ust_engel.setSize(
        sf::Vector2f(70.0f,ust_yukseklik)
         );

        // alt engelin yüksekliği üst engel ve bosluga göre hesaplandı
         alt_engel.setSize(
            sf::Vector2f(70.0f,400.0f-bosluk - ust_yukseklik)
        );
    }
}

// engeller pencereye çizdirilir
void Pipe::draw(sf::RenderWindow& pencere) {

    pencere.draw(ust_engel);

    pencere.draw(alt_engel);
}

