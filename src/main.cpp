#include <SFML/Graphics.hpp>
#include "../include/Pipe.h"



int main() {
    sf::RenderWindow ana_pencere(sf::VideoMode(600, 400), "flappy bird game");//pencere oluşturduk

    ana_pencere.setFramerateLimit(60);//saniyede en fazla 60 kez çalıştırır

    sf::CircleShape bird_shape(25.f);//karakter tanımlaması yaptık burda 25 piksel yarıçaplı bir daire

    bird_shape.setFillColor(sf::Color::Yellow);//kuşun iç rengi 

    bird_shape.setPosition(250, 150);//kuşun başlangıç konumu belirleniyor(x,y)koordinatları

    float bird_speed=0.0f;// kuşun dikey hızı
    float gravity=0.50f;// her döngüde hıza eklenecek olan yerçekimi
 
    Pipe pipe;// Pipe sınıfından engel sistemi oluşturuldu
    
    while(ana_pencere.isOpen()) {//açık olduğu sürece
        sf::Event etkilesim;//işletim sisteminden gelen etkileşimleri algılar
        while (ana_pencere.pollEvent(etkilesim)) {//sırada bekleyen bir etkilesim var mı
            
            if (etkilesim.type == sf::Event::Closed){
                ana_pencere.close();//pencereyi kapatıp döngüden çıkıyoruz
            }
           
            if(etkilesim.type == sf::Event::KeyPressed){//kullanıcı klavyeden tuşa bastı mı?
                if(etkilesim.key.code == sf::Keyboard::Space){//basılan tuş Space mi degil mi?
                    bird_speed=-6.0f;//yukarı yönlü bir zıplama için negatif bir hız verilir
                }
            }
        }
        

        bird_speed+=gravity;// yerçekimi kuşun hızına eklenir ve kuş her karede daha hızlı düşer
        
        bird_shape.move(0,bird_speed);//yatayda hareket yok ama dikeyde hareket eder (bird_speed kadar).y+:aşağı,y-:yukarı hareket

        pipe.update();//engeller güncelleniyor,fonksiyonun çağrılması

        if (pipe.check_collision(bird_shape)) {
        ana_pencere.close();// kuş engellere çarptıysa pencere kapatılır
        }

        ana_pencere.clear();//her karede ekran temizlenir
        
        pipe.draw(ana_pencere); // engellerin ekrana çizilmesi
       
        ana_pencere.draw(bird_shape);//hazırlanan nesne ekrana çiziliyor,kuş engellerden sonra çiziliyor
        
        ana_pencere.display();//ekrana yansıtma 
    }
    return 0;
} 