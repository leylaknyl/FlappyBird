#include <SFML/Graphics.hpp>
#include "../include/Pipe.h"
#include <string>//skoru metne çevirmek için



int main() {
    sf::RenderWindow ana_pencere(sf::VideoMode(600, 400), "flappy bird game");//pencere oluşturduk

    ana_pencere.setFramerateLimit(60);//saniyede en fazla 60 kez çalıştırır

    sf::CircleShape bird_shape(25.f);//karakter tanımlaması yaptık burda 25 piksel yarıçaplı bir daire

    bird_shape.setFillColor(sf::Color::Yellow);//kuşun iç rengi 

    bird_shape.setPosition(250, 150);//kuşun başlangıç konumu belirleniyor(x,y)koordinatları

    float bird_speed=0.0f;// kuşun dikey hızı
    float gravity=0.50f;// her döngüde hıza eklenecek olan yerçekimi
 

    int skor=0;//oyuncunun mevcut puanını tutar
    bool skor_alindi=false;//aynı engelden sadece bir kez puan alınmasını kontrol eder

    Pipe pipe;// Pipe sınıfından engel sistemi oluşturuldu
    
    sf::Font font;//yazı tipi için font nesnesi

    //font dosyası assets klasöründen yüklendi.
    font.loadFromFile("assets/fonts/ARIALI.TTF");

    sf::Text skor_yazi;// skorun ekranda gösterileceği yazı nesnesi

    skor_yazi.setFont(font);//skor yazısında kullanılacak font ayarlandı
    skor_yazi.setCharacterSize(30);//skor yazısının boyutu
    skor_yazi.setFillColor(sf::Color::White);//skorun rengi
    skor_yazi.setPosition(20,20);//skor yazısının ekrandaki konumu ayarlandı


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


        //engel kuşun arkasında kaldıysa ve bu engelden daha önce puan alınmadıysa skor arttırılır
        if (pipe.get_x() + 70 < bird_shape.getPosition().x && skor_alindi == false) {
         skor++;
         skor_alindi = true;
        }

        //engel tekrar sağ tarafa geldiğinde yeni skor alınabilmesi için kontrol sıfırlanır
        if (pipe.get_x() > 590) {
        skor_alindi = false;
        }


        // kuş engellere çarptıysa pencere kapatılır
        if (pipe.check_collision(bird_shape)) {
        ana_pencere.close();
        }

        //kuş ekranın üstüne çıkarsa veya yere düşerse oyun kapansın
        if(
            bird_shape.getPosition().y<0 // kuş ekran üstüne çıkmışsa
            || bird_shape.getPosition().y +
            bird_shape.getRadius()*2>400
        )
        {
            ana_pencere.close();
        }

        // Skor değeri ekranda gösterilecek yazıya çevrilir
        skor_yazi.setString("Skor: " + std::to_string(skor));

        ana_pencere.clear();//her karede ekran temizlenir
        
        pipe.draw(ana_pencere); // engellerin ekrana çizilmesi
       
        ana_pencere.draw(bird_shape);//hazırlanan nesne ekrana çiziliyor,kuş engellerden sonra çiziliyor

        ana_pencere.draw(skor_yazi);//skor yazısı ekrana çizilir
        
        ana_pencere.display();//ekrana yansıtma 
    }
    return 0;
} 