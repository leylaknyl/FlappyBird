#include "../include/Pipe.h"//pipe.h dosyası kullanıma açıldı

#include <cstdlib>// rand() fonksiyonu için

Pipe::Pipe() {// Pipe sınıfının constructor fonksiyonu

    // pipe.png dosyası assets klasöründen yüklenir
    pipe_texture.loadFromFile("assets/images/pipe.png");

    // yüklenen texture sprite nesnelerine bağlanır
    ust_pipe_sprite.setTexture(pipe_texture);

    alt_pipe_sprite.setTexture(pipe_texture);

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
}


void Pipe::update() {//engellerin konumu her frame güncellensin

   engel_x-=engel_speed;// engellerin x konumu azalır ve sola doğru kaymasını sağlar

        ust_engel.setPosition(engel_x,0);//üst engel ekranın üst kısmına yerleştirildi

        // Alt engelin konumu üst engel yüksekliği ve boşluğa göre ayarlandı
        alt_engel.setPosition(
            engel_x,
            ust_yukseklik +bosluk
        );


       
    // pipe görselinin gerçek genişliği ve yüksekliği alınır
    float pipe_resim_genislik = pipe_texture.getSize().x;
    float pipe_resim_yukseklik = pipe_texture.getSize().y;

    // üst borunun boyutu rastgele yüksekliğe göre ayarlanır
     ust_pipe_sprite.setScale( 
    70.0f / pipe_resim_genislik,
      -ust_yukseklik / pipe_resim_yukseklik    
   );

    // alt borunun boyutu kalan yüksekliğe göre ayarlanır
    alt_pipe_sprite.setScale(
    70.0f / pipe_resim_genislik,
    (400.0f - ust_yukseklik - bosluk) / pipe_resim_yukseklik
);
        // Üst boru görselinin konumu ayarlanır
        ust_pipe_sprite.setPosition(engel_x,ust_yukseklik);

        // Alt boru görselinin konumu üst boru yüksekliği ve boşluğa göre ayarlanır
        alt_pipe_sprite.setPosition(
        engel_x,
        ust_yukseklik + bosluk
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

    pencere.draw(ust_pipe_sprite); // üst engel görseli ekrana çizdirilir

    pencere.draw(alt_pipe_sprite); // alt engel görseli ekrana çizdirilir
}

// kuş ile engeller arasında çarpışma olup olmadığını kontrol eder
bool Pipe::check_collision(sf::Sprite& bird) {

    // kuş üst engele veya alt engele çarptıysa true döndür
    if (
        bird.getGlobalBounds().intersects(ust_pipe_sprite.getGlobalBounds()) ||
        bird.getGlobalBounds().intersects(alt_pipe_sprite.getGlobalBounds())
    ) {
        return true;
    }

    return false;// çarpışma yoksa false döndür
}


//pipe içindeki değeri getir
float Pipe::get_x(){
    return engel_x;
}

void Pipe::reset(){

    engel_x = 600.0f; // borular tekrar ekranın sağ tarafına alınır

    ust_yukseklik = 80 + rand() % 120; // yeni rastgele yükseklik oluşturulur

    // üst engelin boyutu yeniden ayarlanır
    ust_engel.setSize(
        sf::Vector2f(70.0f, ust_yukseklik)
    );

    // alt engelin boyutu yeniden hesaplanır
    alt_engel.setSize(
        sf::Vector2f(70.0f, 400.0f - ust_yukseklik - bosluk)
    );

// üst engel görseli başlangıç konumuna alınır
ust_pipe_sprite.setPosition(engel_x, ust_yukseklik);

// alt engel görseli boşluk hesabına göre başlangıç konumuna alınır
alt_pipe_sprite.setPosition(
    engel_x,
    ust_yukseklik + bosluk
);
}